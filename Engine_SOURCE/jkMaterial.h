#pragma once
#include "jkResource.h"
#include "jkShader.h"
#include "jkTexture.h"
#include "jkRenderer.h"

using namespace jk::renderer;
namespace jk::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		~Material();

		virtual HRESULT Load(const std::wstring& path) override;

		void SetData(eGPUParam param, void* data);
		void Binds();
		void Clear();

		void SetShader(std::shared_ptr<Shader> shader) { mShader = shader; }
		std::shared_ptr<Shader> GetShader() { return mShader; }
		void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }
		std::shared_ptr<Texture> GetTexture() { return mTexture; }
		
		void SetRenderingMode(eRenderingMode mode) { mMode = mode; }
		eRenderingMode GetRenderingMode() { return mMode; }

		//bool Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag);
		//bool Create(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture);
		//const Vector2& GetTexSize() { return mTextureSize; }
		//size_t GetHeight() { return mDesc.Height; }
		//size_t GetWidth() { return mDesc.Width; }


	private:
		std::shared_ptr<Shader> mShader;
		std::shared_ptr<Texture> mTexture;
		MaterialCB mCB;
		eRenderingMode mMode;
	};
}
