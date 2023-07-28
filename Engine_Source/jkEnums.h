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
		RigidBody,
		MeshRenderer,
		Animator,
		Camera,
		Script,
		End,
	};

	enum class eLayerType
	{
		Camera,
		Grid,
		Player,
		Monster,
		Item,
		BACK_GROUND,
		Mid_Ground,
		Fore_Ground,
		Map_Effect,
		UI,		
		End = 16, 
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
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

	enum class eMoveDir
	{
		Left = 0,
		Top,
		Right,
		Bottom,
		End,
	};

}