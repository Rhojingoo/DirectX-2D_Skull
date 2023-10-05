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
		SpriteRenderer,
		Animator,
		Camera,
		Script,
		AudioListener,
		AudioSource,
		End,
	};

	enum class eLayerType
	{
		Camera,
		Grid,
		Player,
		Monster,
		MiniBoss,
		Bullet,
		Effect,
		Boss,
		Item,
		Hitbox,
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
		ComputeShader,
		AudioClip,
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