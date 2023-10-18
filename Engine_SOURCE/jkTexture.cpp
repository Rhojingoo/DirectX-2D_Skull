#include "jkTexture.h"
#include "jkGraphicDevice_Dx11.h"
#include "jkGameObject.h"

namespace jk::graphics
{
    Texture::Texture()
        : Resource(enums::eResourceType::Texture)
        , mImage{}
        , mTexture(nullptr)
        , mSRV(nullptr)
        , mDesc{}
        , mBitmap(NULL)
        , mHdc(NULL)
        , mWidth(0)
        , mHeight(0)
    {
    }

    Texture::~Texture()
    {
    }

    bool Texture::Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag)
    {
        if (mTexture == nullptr)
        {
            mDesc.BindFlags = bindFlag;
            mDesc.Usage = D3D11_USAGE_DEFAULT;
            mDesc.CPUAccessFlags = 0;
            mDesc.Format = format;
            mDesc.Width = width;
            mDesc.Height = height;
            mDesc.ArraySize = 1;

            mDesc.SampleDesc.Count = 1;
            mDesc.SampleDesc.Quality = 0;

            mDesc.MipLevels = 0;
            mDesc.MiscFlags = 0;

            mWidth = width;
            mHeight = height;

            if (!GetDevice()->CreateTexture2D(&mDesc, nullptr, mTexture.GetAddressOf()))
                return false;
        }

        if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
        {
            if (!GetDevice()->CraeteDepthStencilView(mTexture.Get(), nullptr, mDSV.GetAddressOf()))
                return false;
        }
        if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
        {
            D3D11_SHADER_RESOURCE_VIEW_DESC tSRVDesc = {};
            tSRVDesc.Format = mDesc.Format;
            tSRVDesc.Texture2D.MipLevels = 1;
            tSRVDesc.Texture2D.MostDetailedMip = 0;
            tSRVDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;

            if (!GetDevice()->CreateShaderResourceView(mTexture.Get(), &tSRVDesc, mSRV.GetAddressOf()))
                return false;
        }

        if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
        {
            D3D11_RENDER_TARGET_VIEW_DESC tSRVDesc = {};
            tSRVDesc.Format = mDesc.Format;
            tSRVDesc.Texture2D.MipSlice = 0;
            tSRVDesc.ViewDimension = D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2D;

            if (!GetDevice()->CreateRenderTargetView(mTexture.Get(), nullptr, mRTV.GetAddressOf()))
                return false;
        }

        if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS)
        {
            D3D11_UNORDERED_ACCESS_VIEW_DESC tUAVDesc = {};
            tUAVDesc.Format = mDesc.Format;
            tUAVDesc.Texture2D.MipSlice = 0;
            tUAVDesc.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_TEXTURE2D;

            if (!GetDevice()->CreateUnordedAccessView(mTexture.Get(), &tUAVDesc, mUAV.GetAddressOf()))
                return false;
        }

        return true;
    }


    void Texture::Reverse_Image(DirectX::ScratchImage& image)
    {
        auto img = *image.GetImage(0, 0, 0);

        for (size_t y = 0; y < img.height; y++)
        {
            auto rowStart = reinterpret_cast<UINT32*>(img.pixels + y * img.rowPitch);
            auto rowEnd = rowStart + img.width - 1;

            while (rowStart < rowEnd)
            {
                std::swap(*rowStart, *rowEnd);
                rowStart++;
                rowEnd--;
            }
        }
    }

    HRESULT Texture::CreateTex(const std::wstring& path, UINT width, UINT height, UINT fileCount, int check_reverse)
    {
        ScratchImage atlasImage;
        HRESULT hr = S_OK;
        reversecheck = check_reverse;

        wchar_t ext[_MAX_EXT] = {};
        _wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT);
        ScratchImage image;
        int count = 0;
        std::filesystem::path fs(path);

        bool isMake = false;
        for (const auto& p : std::filesystem::recursive_directory_iterator(path))
        {
            std::wstring fileName = p.path().filename();
            std::wstring fullName = p.path().wstring(); // Use the full path from the iterator
            if (_wcsicmp(ext, L".dds") == 0)
            {
                hr = LoadFromDDSFile(fullName.c_str(), DDS_FLAGS_NONE, nullptr, image);
            }
            else if (_wcsicmp(ext, L".tga") == 0)
            {
                hr = LoadFromTGAFile(fullName.c_str(), nullptr, image);
            }
            else if (_wcsicmp(ext, L".hdr") == 0)
            {
                hr = LoadFromHDRFile(fullName.c_str(), nullptr, image);
            }
            else
            {
                hr = LoadFromWICFile(fullName.c_str(), WIC_FLAGS_NONE, nullptr, image);
            }

            if (SUCCEEDED(hr))
            {
                ScratchImage convertedImage;
                hr = Convert(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DXGI_FORMAT_R8G8B8A8_UNORM, TEX_FILTER_DEFAULT, TEX_THRESHOLD_DEFAULT, convertedImage);
                if (FAILED(hr))
                {
                    return hr;
                }

                if (reversecheck == 1 )
                    Reverse_Image(convertedImage);

                if (isMake == false)
                {
                    hr = atlasImage.Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, width * fileCount, height, 1, 1);
                    isMake = true;
                }
                if (FAILED(hr))
                {
                    return hr;
                }


                if (reversecheck == 0 )
                {
 
                    UINT checkwidth = static_cast<UINT>(convertedImage.GetMetadata().width);       //각각 스프라이트 이미지 사이즈 받아오기
                    UINT checkheight = static_cast<UINT>(convertedImage.GetMetadata().height);
                    UINT spriteRight = checkwidth;
                    UINT spriteBottom = checkheight;
                    UINT atlasSegmentRight = (width * count) + width;
                    UINT atlasSegmentBottom = height;
                    INT offsetX = atlasSegmentRight - checkwidth;
                    INT offsetY = atlasSegmentBottom - checkheight;
                    hr = CopyRectangle(*convertedImage.GetImage(0, 0, 0), Rect(0, 0, checkwidth, checkheight),
                        *atlasImage.GetImage(0, 0, 0), TEX_FILTER_DEFAULT, offsetX, offsetY);

                }

                else
                {

                    UINT checkwidth = static_cast<UINT>(convertedImage.GetMetadata().width);
                    UINT checkheight = static_cast<UINT>(convertedImage.GetMetadata().height);
                    UINT spriteRight = checkwidth;
                    UINT spriteBottom = checkheight;
                    UINT atlasSegmentRight = (width * count) + width;
                    UINT atlasSegmentBottom = height;
                    INT offsetX = atlasSegmentRight - checkwidth;
                    INT offsetY = atlasSegmentBottom - checkheight;
                    hr = CopyRectangle(*convertedImage.GetImage(0, 0, 0), Rect(0, 0, checkwidth, checkheight),
                        *atlasImage.GetImage(0, 0, 0), TEX_FILTER_DEFAULT, offsetX, offsetY);
                }
                if (FAILED(hr))
                {
                    return hr;
                }
            }
            count++;
        }

        CreateShaderResourceView
        (
            GetDevice()->GetID3D11Device()
            , atlasImage.GetImages()
            , atlasImage.GetImageCount()
            , atlasImage.GetMetadata()
            , mSRV.GetAddressOf()
        );

        mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());


        this->mImage.Initialize2D(
            atlasImage.GetMetadata().format,
            atlasImage.GetMetadata().width,
            atlasImage.GetMetadata().height,
            atlasImage.GetMetadata().arraySize,
            atlasImage.GetMetadata().mipLevels
        );
        return S_OK;
    }

    HRESULT Texture::Load(const std::wstring& path)
    {
        wchar_t szExtension[256] = {};
        _wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, 256);

        std::wstring extension = szExtension;
        if (extension == L".dds" || extension == L".DDS")
        {
            if (FAILED(LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
                return S_FALSE;
        }
        else if (extension == L".tga" || extension == L".TGA")
        {
            if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, mImage)))
                return S_FALSE;
        }
        else // WIC (png, jpg, jpeg, bmp )
        {
            if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
                return S_FALSE;
        }

        CreateShaderResourceView
        (
            GetDevice()->GetID3D11Device()
            , mImage.GetImages()
            , mImage.GetImageCount()
            , mImage.GetMetadata()
            , mSRV.GetAddressOf()
        );
        mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());
        mTexture->GetDesc(&mDesc);

        mTextureSize.x = (float)mImage.GetImages()[0].width;
        mTextureSize.y = (float)mImage.GetImages()[0].height;


        mWidth = mImage.GetMetadata().width;
        mHeight = mImage.GetMetadata().height;
        return S_OK;
    }

    void Texture::BindShader(eShaderStage stage, UINT startSlot)
    {
        GetDevice()->BindShaderResource(stage, startSlot, mSRV.GetAddressOf());
    }
    void Texture::BindShaderResource(eShaderStage stage, UINT startSlot)
    {
        GetDevice()->BindShaderResource(stage, startSlot, mSRV.GetAddressOf());
    }

    void Texture::BindUnorderedAccessViews(UINT slot)
    {
        UINT i = -1;
        GetDevice()->BindUnorderedAccess(slot, mUAV.GetAddressOf(), &i);
    }
    void Texture::ClearUnorderedAccessViews(UINT slot)
    {
        ID3D11UnorderedAccessView* p = nullptr;
        UINT i = -1;
        GetDevice()->BindUnorderedAccess(slot, &p, &i);
    }


    void Texture::Clear()
    {
        ID3D11ShaderResourceView* srv = nullptr;

        GetDevice()->BindShaderResource(eShaderStage::VS, 0, &srv);
        GetDevice()->BindShaderResource(eShaderStage::DS, 0, &srv);
        GetDevice()->BindShaderResource(eShaderStage::GS, 0, &srv);
        GetDevice()->BindShaderResource(eShaderStage::HS, 0, &srv);
        GetDevice()->BindShaderResource(eShaderStage::CS, 0, &srv);
        GetDevice()->BindShaderResource(eShaderStage::PS, 0, &srv);
    }
}


