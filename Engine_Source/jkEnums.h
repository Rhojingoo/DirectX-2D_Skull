#pragma once


namespace jk::enums
{
	enum class eComponentType
	{
		None,
		TileMap,
		Transform,
		Mesh,
		Collider2D,
		MeshRenderer,
		Camera,
		Script,
		End,
	};

	enum class eLayerType
	{
		Camera,
		Grid,
		Monster,
		Player,
		BACK_GROUND,
		Mid_Ground,
		Fore_Ground,
		Map_Effect,
		UI,		
		End,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Image,
		End,
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End,
	};
}