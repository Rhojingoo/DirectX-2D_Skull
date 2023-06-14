#pragma once
#include "JKEngine.h"
#include "jkGraphicDevice_Dx11.h"
#include "jkMesh.h"
#include "jkShader.h"
#include "jkConstantBuffer.h"

using namespace jk::math;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	extern Vertex vertexes[];
	extern jk::Mesh* mesh;
	extern jk::Shader* shader;
	extern jk::graphics::ConstantBuffer* constantBuffer;
	//extern ID3D11Buffer* triangleConstantBuffer;   →   ContantBuffer Class 생기기전버전


	void Initialize();
	void Release();
}


