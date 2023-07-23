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

		HRESULT CreateTex(const std::wstring& path, UINT width, UINT height, UINT fileCount);

		virtual HRESULT Load(const std::wstring& path) override;
		void BindShader(eShaderStage stage, UINT startSlot);
		void Clear();

		const Vector2& GetTexSize() { return mTextureSize; }
		void SetTexSize(const Vector2& textureSize) { mTextureSize = textureSize; }
		
		size_t GetWidth() { return mImage.GetMetadata().width; }
		size_t GetHeight() { return mImage.GetMetadata().height; }
		size_t GetHeight_Desc() { return mDesc.Height; }
		size_t GetWidth_Desc() { return mDesc.Width; }


	private:	
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		D3D11_TEXTURE2D_DESC mDesc;
	private:
		ScratchImage mImage;
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;		
		Vector2 mTextureSize;
	};
}
