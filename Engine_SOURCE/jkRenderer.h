#pragma once
#include "JKEngine.h"
#include "jkGraphicDevice_Dx11.h"
#include "jkMesh.h"
#include "jkShader.h"
#include "jkConstantBuffer.h"

using namespace jk::math;
using namespace jk::graphics;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	extern Vertex vertexes[];
	extern jk::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	void Initialize();
	void Release();
}


