#pragma once
#include "JKEngine.h"
#include "jkGraphicDevice_Dx11.h"
#include "jkMesh.h"
#include "jkShader.h"
#include "jkConstantBuffer.h"
#include "jkCamera.h"

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

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};

	extern Vertex vertexes[];
	extern jk::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];


	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<jk::Camera*> cameras;

	void Initialize();
	void Render();
	void Release();
}


