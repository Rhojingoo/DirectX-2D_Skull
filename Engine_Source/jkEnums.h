#pragma once


namespace jk::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		MeshRenderer,
		Camera,
		TileMap,
		Script,
		End,
	};

	enum class eLayerType
	{
		Grid,
		Player,
		Monster,
		UI,
		MapEffect,
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
}