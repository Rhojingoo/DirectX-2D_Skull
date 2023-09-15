#pragma once
#include "jkResource.h"
#include "jkGraphics.h"

#include "../External/DirectXTex/Include/DirectXTex.h"
#include "../External/DirectXTex/Include/DirectXTex.inl"




#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Release\\DirectXTex.lib")
#endif

namespace jk::graphics
{
	using namespace jk::math;
	class Texture : public Resource
	{
	public:
		Texture();
		~Texture();

		bool Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag);
		HRESULT CreateTex(const std::wstring& path, UINT width, UINT height, UINT fileCount, int check_reverse = 0);
		void Reverse_Image(DirectX::ScratchImage& image);//Horizontally

		virtual HRESULT Load(const std::wstring& path) override;
		void BindShader(eShaderStage stage, UINT startSlot);

		void BindShaderResource(eShaderStage stage, UINT startSlot);
		void BindUnorderedAccessViews(UINT slot);
		void ClearUnorderedAccessViews(UINT slot);


		void Clear();

		const Vector2& GetTexSize() { return mTextureSize; }
		void SetTexSize(const Vector2& textureSize) { mTextureSize = textureSize; }

		size_t GetWidth() { return mImage.GetMetadata().width; }
		size_t GetHeight() { return mImage.GetMetadata().height; }
		//size_t GetWidth() { return mWidth; }
		//size_t GetHeight() { return mHeight; }

		size_t GetHeight_Desc() { return mDesc.Height; }
		size_t GetWidth_Desc() { return mDesc.Width; }



		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>    GetRTV() { return  mRTV; }
		void SetRTV(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv) { mRTV = rtv; }
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>    GetDSV() { return  mDSV; }
		void SetDSV(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv) { mDSV = dsv; }
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>  GetSRV() { return  mSRV; }
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> GetUAV() { return  mUAV; }
		Microsoft::WRL::ComPtr<ID3D11Texture2D> GetTexture() { return mTexture; }
		void SetTexture(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture) { mTexture = texture; }


	private:
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRTV;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDSV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mUAV;
		D3D11_TEXTURE2D_DESC mDesc;


	private:
		ScratchImage mImage;
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
		Vector2 mTextureSize;
		int reversecheck;


	};
}
