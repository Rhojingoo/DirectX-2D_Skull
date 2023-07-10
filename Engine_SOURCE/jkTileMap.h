#pragma once
#include "jkBaseRenderer.h"
#include "jkRenderer.h"
#include "jkMesh.h"
#include "jkMaterial.h"
#include "jkStructuredBuffer.h"

namespace jk
{
	using namespace jk::math;

	struct TileData
	{
		int					mImgIdx;
		Vector2				mStartUV;
		int					mPadding;

		TileData()
			: mImgIdx(-1)
			, mPadding(0)
		{}
	};

	class TileMap : public BaseRenderer
	{
	public:
		TileMap();
		virtual ~TileMap();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		
		void UpdateData();


		void SetAtlasTex(std::shared_ptr<Texture> atlasTexture)
		{
			mAtlasTexture = atlasTexture;
			Vector2 atlasSize = mAtlasTexture->GetTexSize();
			mSliceUV = mSlicePixel / atlasSize;
		}

		void SetTileSize(Vector2 pixelSize)
		{
			mSlicePixel = pixelSize;
			if (nullptr != mAtlasTexture)
			{
				Vector2 atlasSize = mAtlasTexture->GetTexSize();
				mSliceUV = mSlicePixel / atlasSize;
			}
		}

		void SetTileMapCount(UINT countX, UINT countY);
		void SetTileData(int tileIdx, int imgIdx);
		void ClearTileData();

		void SetAllTileData(int imgIdx);

	private:
		std::shared_ptr<Texture>       mAtlasTexture;
		Vector2              mSlicePixel;
		Vector2              mSliceUV;

		UINT                mRowCount;
		UINT                mColCount;

		UINT                mTileCountX;
		UINT                mTileCountY;
		std::vector<TileData>   mTileData;
		StructuredBuffer*   mBuffer;

		bool                mbBufferUpdated;
	};
}
