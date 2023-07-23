#include "jkTexture.h"
#include "jkGraphicDevice_Dx11.h"

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

    HRESULT Texture::CreateTex(const std::wstring& path, UINT width, UINT height, UINT fileCount)
    {
        ScratchImage atlasImage;
        HRESULT hr = S_OK;

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

                if (isMake == false)
                {
                    hr = atlasImage.Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, width * fileCount, height, 1, 1);
                    isMake = true;
                }
                if (FAILED(hr))
                {
                    return hr;
                }


                UINT checkwidth = convertedImage.GetMetadata().width;
                UINT pluswidth = 0;
                UINT checkheight = convertedImage.GetMetadata().height;
                UINT plusheight = 0;

                if (checkwidth >= width)
                    pluswidth = 0;
                else
                {
                    pluswidth = (width - checkwidth) / 2;
                }
                if (checkheight >= height)
                    plusheight = 0;
                else
                {
                    plusheight = height - checkheight;
                }

                hr = CopyRectangle(*convertedImage.GetImage(0, 0, 0), Rect(0, 0, convertedImage.GetMetadata().width, convertedImage.GetMetadata().height),
                    *atlasImage.GetImage(0, 0, 0), TEX_FILTER_DEFAULT, (width * count) + pluswidth, plusheight);

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

        //atlasTexture = std::make_shared<graphics::Texture>();
        //atlasTexture->mTexture = mTexture.Get();
        //atlasTexture->mSRV = mSRV.Get();

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

		return S_OK;
	}

	void Texture::BindShader(eShaderStage stage, UINT startSlot)
	{
		GetDevice()->BindShaderResource(stage, startSlot, mSRV.GetAddressOf());
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