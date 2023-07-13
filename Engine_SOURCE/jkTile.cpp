#include "jkTile.h"
#include "jkTransform.h"
#include "jkCamera.h"
#include "jkMeshRenderer.h"
#include "jkResources.h"
#include "jkImage.h"
#include "jkRenderer.h"


namespace jk
{
	Tile::Tile()
		:mAtlas(nullptr)
		, mIndex(-1)
		, mX(-1)
		, mY(-1)
	{

	}
	Tile::Tile(Vector2 pos)
		:mAtlas(nullptr)
		, mIndex(-1)
		, mX(-1)
		, mY(-1)
	{
	}
	Tile::~Tile()
	{
	}
	void Tile::InitializeTile(std::shared_ptr<Image> atlas, int index)
	{
		mIndex = index;
		if (atlas == nullptr || index < 0)
			return;
		SetName(L"Tile");

		mAtlas = atlas;
		SetIndex(index);
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(TILE_SIZE_X, TILE_SIZE_Y, -10.0f));
		//GameObject::Initialize();
	}

	void Tile::SetIndex(int index)
	{
		int maxCol = mAtlas->GetWidth() / TILE_SIZE_X;
		int maxRow = mAtlas->GetHeight() / TILE_SIZE_Y;

		mY = index / maxCol;
		mX = index % maxCol;
	}
	void Tile::Update()
	{
		GameObject::Update();
	}
	void Tile::Render()
	{
		
		BindConstantBuffer(mX, mY);
		
		GameObject::Render();
	}

	void Tile::BindConstantBuffer(UINT X, UINT Y)
	{
		UINT index_x = 1/8;
		UINT index_y = 1/8;

		jk::renderer::TileMap_CB TILECB = {};		
		TILECB.LeftTop = Vector4(mX*0.125f, mY*0.1666f, 0.0f, 0.0f);
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::UV];
		cb->SetData(&TILECB);
		cb->Bind(eShaderStage::VS);
	}


	//void Tile::BindConstantBuffer()
	//{
	//	renderer::MoveCB trCB = {};
	//	trCB.mTime.x = mTime;
	//	trCB.mTime.y = _Time;

	//	ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Move];
	//	cb->SetData(&trCB);
	//	cb->Bind(eShaderStage::PS);
	//}
}