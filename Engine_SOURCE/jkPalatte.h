#pragma once
#include "jkTile.h"
#include "jkImage.h"
#include "jkObject.h"

namespace jk
{
	union TileID
	{
		struct
		{
			UINT32 x;
			UINT32 y;
		};
		UINT64 id;
	};



	class TilePalatte
	{
	public:
		static void Intialize();
		static void Update();
		static void Render(HDC hdc);

		static void CreateTile(int index, Vector2 pos);
		static void DeleateTile(Vector2 pos);
		static void CreateTiles(int index, UINT width, UINT height);
		static void Save();
		static void Load();
		static void Load(const std::wstring& path);

		static Vector2 GetTilePos(Vector2 mousePos);
		static void SetIndex(UINT index) { mIndex = index; }
		static UINT GetIndex() { return mIndex; }
		//static Image* GetTilePixels() { return mPixels; }


	private:
		static std::unordered_map<UINT64, Tile*>mTiles;
		static std::shared_ptr<Image> mImage;
		static UINT mIndex;
		UINT mMaxX;
		UINT mMaxY;
		//static Image* mPixels;

	};

}
