#pragma once
#include "jkResource.h"
#include "jkApplication.h"
#include "jkResources.h"
#include "jkTexture.h"

extern jk::Application application;
namespace jk
{
	class Image : public Resource
	{
	public:
		Image();
		~Image() override;

		virtual HRESULT Load( const std::wstring& path) override;

		HDC GetHdc() { return mHdc; }
		HBITMAP GetBitmap() { return mBitmap; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};
}

