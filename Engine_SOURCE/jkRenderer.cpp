#include "jkRenderer.h"
#include "jkResources.h"
#include "jkTexture.h"
#include "jkMaterial.h"
#include "jkCollider2D.h"
#include "jkCollisionManager.h"
#include "jkStructuredBuffer.h"
#include "jkParticleShader.h"
#include "jkPaintShader.h"

namespace jk::renderer
{	
	using namespace jk;
	using namespace jk::graphics;
	Vertex vertexes[4] = {};
	jk::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};

	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	jk::Camera* mainCamera = nullptr;
	std::vector<jk::Camera*> cameras = {};
	std::vector<DebugMesh> debugMeshs = {};

	void SetupState()
	{
		// Input layout 정점 구조 정보를 넘겨줘야한다.
#pragma region InputLayout		
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		std::shared_ptr<Shader> shader = jk::Resources::Find<Shader>(L"TriangleShader");
		jk::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());


		shader = jk::Resources::Find<Shader>(L"SpriteShader");
		jk::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());


		shader = jk::Resources::Find<Shader>(L"Grid_Shader");
		jk::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());


		shader = jk::Resources::Find<Shader>(L"DebugShader");
		jk::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());


		shader = jk::Resources::Find<Shader>(L"Animation_Shader");
		jk::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf()); 

		
		shader = jk::Resources::Find<Shader>(L"Tile_Shader");
		jk::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());


		shader = jk::Resources::Find<Shader>(L"Move_Shader");
		jk::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());


		shader = jk::Resources::Find<Shader>(L"HP_Bar_Shader");
		jk::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());


		shader = jk::Resources::Find<Shader>(L"Alpha_Shader");
		jk::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());


		shader = jk::Resources::Find<Shader>(L"ParticleShader");
		jk::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());


		shader = jk::Resources::Find<Shader>(L"HITParticleShader");
		jk::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());		
				
			shader = jk::Resources::Find<Shader>(L"AfterImage_Shader");
		jk::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		//애니메이션 파티클 연습용
		//shader = jk::Resources::Find<Shader>(L"ParticleShader2");
		//jk::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
		//	, shader->GetVSCode()
		//	, shader->GetInputLayoutAddressOf());


		//없애도되는 쉐이더 (공부용)
		//shader = jk::Resources::Find<Shader>(L"AfterImageShader");
		//jk::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
		//	, shader->GetVSCode()
		//	, shader->GetInputLayoutAddressOf());

#pragma endregion

		//Sampler State
#pragma region Sampler State		
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion

		//Rasterizer State
#pragma region Rasterizer State
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());
#pragma endregion

		//Depth Stencil State
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

		//less
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

		//Greater
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		//No Write
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		//None
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion

		//Blend State
#pragma region Blend State
		D3D11_BLEND_DESC blendDesc = {};

		//default
		blendStates[(UINT)eBSType::Default] = nullptr;

		// Alpha Blend
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		// one one
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;

		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion
	}


	void LoadMesh()
	{
		std::vector<Vertex> vertexes = {};
		std::vector<UINT> indexes = {};

	#pragma region PointMesh
		{Vertex v = {};
		v.pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexes.push_back(v);
		indexes.push_back(0);
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
		Resources::Insert(L"PointMesh", mesh);

		vertexes.clear();
		indexes.clear(); }
	#pragma endregion

	#pragma region RECT

		//RECT
		vertexes.resize(4);
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);
		mesh->CreateVertexBuffer(vertexes.data(), (UINT)vertexes.size());

	
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), (UINT)indexes.size());		

		#pragma region Rect Debug Mesh
			std::shared_ptr<Mesh> rectDebug = std::make_shared<Mesh>();
			Resources::Insert(L"DebugRect", rectDebug);
			rectDebug->CreateVertexBuffer(vertexes.data(), (UINT)vertexes.size());
			rectDebug->CreateIndexBuffer(indexes.data(), (UINT)indexes.size());
		#pragma endregion
#pragma endregion

	#pragma region Circle Debug Mesh
		// 
		vertexes.clear();
		indexes.clear();

		Vertex center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.pos = Vector3(fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.f);
			vertexes.push_back(center);
		}

		//for (UINT i = 0; i < (UINT)iSlice; ++i)
		//{
		//	indexes.push_back(0);
		//	if (i == iSlice - 1)
		//	{
		//		indexes.push_back(1);
		//	}
		//	else
		//	{
		//		indexes.push_back(i + 2);
		//	}
		//	indexes.push_back(i + 1);
		//}

		for (int i = 0; i < vertexes.size() - 2; ++i)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		std::shared_ptr<Mesh> circleDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugCircle", circleDebug);
		circleDebug->CreateVertexBuffer(vertexes.data(), (UINT)vertexes.size());
		circleDebug->CreateIndexBuffer(indexes.data(), (UINT)indexes.size());
	#pragma endregion

	}


	void LoadBuffer()
	{
		// Transform ConBuffer
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		// Material ConBuffer
		constantBuffer[(UINT)eCBType::Material] = new ConstantBuffer(eCBType::Material);
		constantBuffer[(UINT)eCBType::Material]->Create(sizeof(MaterialCB));

		// Grid ConBuffer
		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(TransformCB));

		// Animation Buffer
		constantBuffer[(UINT)eCBType::Animator] = new ConstantBuffer(eCBType::Animator);
		constantBuffer[(UINT)eCBType::Animator]->Create(sizeof(AnimatorCB));

		// Move ConBuffer
		constantBuffer[(UINT)eCBType::Move] = new ConstantBuffer(eCBType::Move);
		constantBuffer[(UINT)eCBType::Move]->Create(sizeof(MoveCB));

		// UV ConBuffer
		constantBuffer[(UINT)eCBType::UV] = new ConstantBuffer(eCBType::UV);
		constantBuffer[(UINT)eCBType::UV]->Create(sizeof(TileMap_CB));

		//ParticleCB
		constantBuffer[(UINT)eCBType::Particle] = new ConstantBuffer(eCBType::Particle);
		constantBuffer[(UINT)eCBType::Particle]->Create(sizeof(ParticleCB));

		//NoiseCB
		constantBuffer[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Noise);
		constantBuffer[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));

		// HP_Bar ConBuffer
		constantBuffer[(UINT)eCBType::HP_Bar] = new ConstantBuffer(eCBType::HP_Bar);
		constantBuffer[(UINT)eCBType::HP_Bar]->Create(sizeof(HP_BarCB));

		// AlphaBlend ConBuffer
		constantBuffer[(UINT)eCBType::AlphaBlend] = new ConstantBuffer(eCBType::AlphaBlend);
		constantBuffer[(UINT)eCBType::AlphaBlend]->Create(sizeof(AnimatorCB));
	}


	void LoadTexture()
	{
		//paint texture
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		jk::Resources::Insert(L"PaintTexuture", uavTexture);


		std::shared_ptr<Texture> particle = std::make_shared<Texture>();
		Resources::Load<Texture>(L"CartoonSmoke", L"..\\Resources\\particle\\CartoonSmoke.png");
		Resources::Load<Texture>(L"Blossom_Particle", L"..\\Resources\\particle\\BlossomParticle_14.png");
		Resources::Load<Texture>(L"HIT_Particle", L"..\\Resources\\particle\\Particle_Hit.png");
		Resources::Load<Texture>(L"Noise01", L"..\\Resources\\noise\\noise_01.png");
		Resources::Load<Texture>(L"Noise02", L"..\\Resources\\noise\\noise_02.png");
		Resources::Load<Texture>(L"Noise03", L"..\\Resources\\noise\\noise_03.png");
	}


	void LoadShader()
	{
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		jk::Resources::Insert(L"TriangleShader", shader);

		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		jk::Resources::Insert(L"SpriteShader", spriteShader);

		std::shared_ptr<Shader> spriteAniShader = std::make_shared<Shader>();
		spriteAniShader->Create(eShaderStage::VS, L"AnimationVS.hlsl", "main");
		spriteAniShader->Create(eShaderStage::PS, L"AnimationPS.hlsl", "main");
		jk::Resources::Insert(L"Animation_Shader", spriteAniShader);


		std::shared_ptr<Shader> sprite_AfterImage_Shader = std::make_shared<Shader>();
		sprite_AfterImage_Shader->Create(eShaderStage::VS, L"AnimationVS.hlsl", "main");
		sprite_AfterImage_Shader->Create(eShaderStage::PS, L"Dash_AniPS.hlsl", "main");
		jk::Resources::Insert(L"AfterImage_Shader", sprite_AfterImage_Shader);


		std::shared_ptr<Shader> girdShader = std::make_shared<Shader>();
		girdShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		girdShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		jk::Resources::Insert(L"Grid_Shader", girdShader);

		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		debugShader->SetRSState(eRSType::WireframeNone);
		jk::Resources::Insert(L"DebugShader", debugShader);

		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		jk::Resources::Insert(L"PaintShader", paintShader);

		// Compute Shader (배경용)
		std::shared_ptr<ParticleShader> psSystemShader = std::make_shared<ParticleShader>();
		psSystemShader->Create(L"ParticleCS.hlsl", "main");
		jk::Resources::Insert(L"ParticleSystemShader", psSystemShader);


		// 파티클 (배경용)
		std::shared_ptr<Shader> paritcleShader = std::make_shared<Shader>();
		paritcleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		paritcleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		paritcleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		paritcleShader->SetRSState(eRSType::SolidNone);
		paritcleShader->SetBSState(eBSType::AlphaBlend);
		paritcleShader->SetDSState(eDSType::NoWrite);
		paritcleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
		jk::Resources::Insert(L"ParticleShader", paritcleShader);


		// Compute Shader (대미지용)
		std::shared_ptr<ParticleShader> hitpsSystemShader = std::make_shared<ParticleShader>();
		hitpsSystemShader->Create(L"HitParticleCS.hlsl", "main");
		jk::Resources::Insert(L"HITParticleSystemShader", hitpsSystemShader);
		
		// 파티클 (대미지용)
		std::shared_ptr<Shader> hitparitcleShader = std::make_shared<Shader>();
		hitparitcleShader->Create(eShaderStage::VS, L"HitParticleVS.hlsl", "main");
		hitparitcleShader->Create(eShaderStage::GS, L"HitParticleGS.hlsl", "main");
		hitparitcleShader->Create(eShaderStage::PS, L"HitParticlePS.hlsl", "main");
		hitparitcleShader->SetRSState(eRSType::SolidNone);
		hitparitcleShader->SetBSState(eBSType::AlphaBlend);
		hitparitcleShader->SetDSState(eDSType::NoWrite);
		hitparitcleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
		jk::Resources::Insert(L"HITParticleShader", hitparitcleShader);


		//파티클 애니메이션화
		//std::shared_ptr<Shader> paritcleShader2 = std::make_shared<Shader>();
		//paritcleShader2->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		//paritcleShader2->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		//paritcleShader2->Create(eShaderStage::PS, L"AnimationPS.hlsl", "main");
		//paritcleShader2->SetRSState(eRSType::SolidNone);
		//paritcleShader2->SetBSState(eBSType::AlphaBlend);
		//paritcleShader2->SetDSState(eDSType::NoWrite);
		//paritcleShader2->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
		//jk::Resources::Insert(L"ParticleShader2", paritcleShader2);


		// 파티클 잔상화
		//std::shared_ptr<Shader> afterimageShader = std::make_shared<Shader>();
		//afterimageShader->Create(eShaderStage::VS, L"AfterImageVS.hlsl", "main");
		//afterimageShader->Create(eShaderStage::GS, L"AfterImageGS.hlsl", "main");
		//afterimageShader->Create(eShaderStage::PS, L"AfterImagePS.hlsl", "main");
		//afterimageShader->SetRSState(eRSType::SolidNone);
		//afterimageShader->SetBSState(eBSType::AlphaBlend);
		//afterimageShader->SetDSState(eDSType::NoWrite);
		//afterimageShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
		//jk::Resources::Insert(L"AfterImageShader", afterimageShader);


		//구름
		std::shared_ptr<Shader> moveShader = std::make_shared<Shader>();
		moveShader->Create(eShaderStage::VS, L"MoveVS.hlsl", "main");
		moveShader->Create(eShaderStage::PS, L"MovePS.hlsl", "main");
		jk::Resources::Insert(L"Move_Shader", moveShader);


		//HP_Bar
		std::shared_ptr<Shader> hp_bar_Shader = std::make_shared<Shader>();
		hp_bar_Shader->Create(eShaderStage::VS, L"HP_Bar_VS.hlsl", "main");
		hp_bar_Shader->Create(eShaderStage::PS, L"HP_Bar_PS.hlsl", "main");
		jk::Resources::Insert(L"HP_Bar_Shader", hp_bar_Shader);


		//AlphaPS
		std::shared_ptr<Shader> alpha_shader = std::make_shared<Shader>();
		alpha_shader->Create(eShaderStage::VS, L"AlphaVS.hlsl", "main");
		alpha_shader->Create(eShaderStage::PS, L"AlphaPS.hlsl", "main");
		jk::Resources::Insert(L"Alpha_Shader", alpha_shader);


		//타일
#pragma region Tile_map_cmarkup
		std::shared_ptr<Shader> tile_shader = std::make_shared<Shader>();
		tile_shader->Create(eShaderStage::VS, L"TileMapVS.hlsl", "main");
		tile_shader->Create(eShaderStage::PS, L"TileMapPS.hlsl", "main");
		jk::Resources::Insert(L"Tile_Shader", tile_shader);
#pragma endregion	
	}


	void LoadMaterial()
	{
		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Shader> gridShader
			= Resources::Find<Shader>(L"Grid_Shader");
		std::shared_ptr<Shader> moveShader
			= Resources::Find<Shader>(L"Move_Shader");
		std::shared_ptr<Shader> tile_shader
			= Resources::Find<Shader>(L"Tile_Shader");
		std::shared_ptr<Shader> animationShader
			= Resources::Find<Shader>(L"Animation_Shader"); 
		std::shared_ptr<Shader> afterImage_Shader
			= Resources::Find<Shader>(L"AfterImage_Shader");
		std::shared_ptr<Shader> debugShader
			= Resources::Find<Shader>(L"DebugShader");
		std::shared_ptr<Shader> particleShader
			= Resources::Find<Shader>(L"ParticleShader");
		std::shared_ptr<Shader> hitparticleShader
			= Resources::Find<Shader>(L"HITParticleShader");

		std::shared_ptr<Shader> hp_bar_Shader
			= Resources::Find<Shader>(L"HP_Bar_Shader");
		std::shared_ptr<Shader> alpha_Shader
			= Resources::Find<Shader>(L"Alpha_Shader");
		//std::shared_ptr<Shader> dahs_Shader  //연습용 파티클 대쉬
		//	= Resources::Find<Shader>(L"AfterImageShader");
		//std::shared_ptr<Shader> particleShader2  //연습용 파티클 애니메이션
		//	= Resources::Find<Shader>(L"ParticleShader2");
		
		#pragma region Public
		#pragma region Mouse
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"mouse", L"..\\Resources\\Texture\\Mouse_Cursor.png");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetShader(spriteShader);
			material->SetTexture(texture);
			Resources::Insert(L"Mouse", material);
		#pragma endregion

		#pragma region Grid	
			material = std::make_shared<Material>();
			material->SetShader(gridShader);
			Resources::Insert(L"GridMaterial", material);
		#pragma endregion

		#pragma region	UI	
				#pragma region UI_PlayerState
						texture = Resources::Load<Texture>(L"state_ui", L"..\\Resources\\Texture\\UI\\State_UI\\State_UI.png");
						material = std::make_shared<Material>(); material->SetShader(spriteShader);	material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"State_UI", material);
				#pragma endregion

				#pragma region UI_PlaerFace
						texture = Resources::Load<Texture>(L"skul_ui", L"..\\Resources\\Texture\\UI\\Face_UI\\Skul_UI.png");
						material = std::make_shared<Material>();material->SetShader(spriteShader);	material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);Resources::Insert(L"Skul_UI", material);
				#pragma endregion

				#pragma region UI_Player_HP_Clean
						texture = Resources::Load<Texture>(L"healthbar_ui", L"..\\Resources\\Texture\\UI\\Hp_Bar\\Player_HealthBar.png");
						material = std::make_shared<Material>(); material->SetShader(hp_bar_Shader);	material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"HealthUar_Ui", material);
				#pragma endregion

				#pragma region UI_Player_HP_Damege
						texture = Resources::Load<Texture>(L"damagebar_ui", L"..\\Resources\\Texture\\UI\\Hp_Bar\\Player_HealthBar_Damage.png");
						material = std::make_shared<Material>(); material->SetShader(spriteShader);	material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"DamageBar_Ui", material);
				#pragma endregion
		#pragma endregion

		#pragma region Player
			#pragma region Skul_Base
				texture = Resources::Load<Texture>(L"basic_skul", L"..\\Resources\\Texture\\Player\\Normal\\Idle\\Idle_1.png");
				material = std::make_shared<Material>(); material->SetShader(animationShader);	//material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"Basic_Skul", material);				
			#pragma endregion

			#pragma region Skul_Item
				texture = Resources::Load<Texture>(L"skill_face", L"..\\Resources\\Texture\\Player\\Skul_head\\Skul_Skill.png");
				material = std::make_shared<Material>(); material->SetShader(spriteShader);	material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"Skill_face", material);
			#pragma endregion

			#pragma region Dash
				material = std::make_shared<Material>();
				material->SetShader(afterImage_Shader);
				material->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"After_Image_Skul", material);				
			#pragma endregion

#pragma endregion

		#pragma region Monster
		#pragma region Knight_male
				texture = Resources::Load<Texture>(L"knight_male", L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Idle\\Idle_0.png");
				material = std::make_shared<Material>(); material->SetShader(animationShader);//material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"Knight_male", material);
		#pragma endregion
		#pragma endregion

		#pragma region Bullet
		#pragma region Knight_male
				material = std::make_shared<Material>(); 
				material->SetShader(animationShader);
				material->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"Bullet", material);
		#pragma endregion
		#pragma endregion


		#pragma region Test & Compute_PaintShader
				texture	= Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");
				material = std::make_shared<Material>();
				material->SetShader(spriteShader);
				material->SetTexture(texture);			
				material->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"SpriteMaterial", material);

				texture = Resources::Find<Texture>(L"PaintTexuture");
				material = std::make_shared<Material>();
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"SpriteMaterial02", material);
#pragma endregion


		#pragma endregion

		std::shared_ptr<Texture> particleText
			= Resources::Find<Texture>(L"CartoonSmoke");
		material = std::make_shared<Material>();
		material->SetShader(particleShader);
		material->SetTexture(particleText);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"ParticleMaterial", material);

		std::shared_ptr<Texture> particleText2
			= Resources::Find<Texture>(L"Blossom_Particle");
		material = std::make_shared<Material>();
		material->SetShader(particleShader);
		material->SetTexture(particleText2);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"ParticleMaterial2", material);

		std::shared_ptr<Texture> particleText3
			= Resources::Find<Texture>(L"HIT_Particle");
		material = std::make_shared<Material>();
		material->SetShader(particleShader);
		material->SetTexture(particleText3);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"HITParticleMaterial", material);

		
		//파티클 애니메이션용
		//#pragma region Dash
		//		material = std::make_shared<Material>();
		//		material->SetShader(particleShader2);
		//		material->SetRenderingMode(eRenderingMode::Transparent);
		//		Resources::Insert(L"AniParticleMaterial", material);
		//#pragma endregion
		
		// 파티클 대쉬용
		//std::shared_ptr<Texture> testText
		//	= Resources::Find<Texture>(L"CartoonSmoke");
		//material = std::make_shared<Material>();
		//material->SetShader(dahs_Shader);
		//material->SetTexture(testText);
		//material->SetRenderingMode(eRenderingMode::Transparent);
		//Resources::Insert(L"DashBase_Material", material);





		#pragma region Title
				texture	= Resources::Load<Texture>(L"title_image", L"..\\Resources\\Texture\\Title\\Title_Art2.png");
				material = std::make_shared<Material>(); material->SetShader(spriteShader);	material->SetTexture(texture);	
				Resources::Insert(L"Title_Image", material); 

				texture = Resources::Load<Texture>(L"title_logo", L"..\\Resources\\Texture\\Title\\Title_Logo.png");
				material = std::make_shared<Material>(); material->SetShader(spriteShader);	material->SetTexture(texture);	
				material->SetRenderingMode(eRenderingMode::Transparent);  Resources::Insert(L"Title_Logo", material);

				texture = Resources::Load<Texture>(L"title_mlogo2", L"..\\Resources\\Texture\\Title\\Title_Logo2.png");
				material = std::make_shared<Material>(); material->SetShader(spriteShader);	material->SetTexture(texture);	
				material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"Title_Mini_Logo", material);
		#pragma endregion		


		#pragma region StartScene

			#pragma region In_Castle
				#pragma region Devil(back)
							texture	= Resources::Load<Texture>(L"DevilCastle", L"..\\Resources\\Texture\\Devil_Catle\\Catle_wall_Back.png");
							material = std::make_shared<Material>();
							material->SetShader(spriteShader);
							material->SetTexture(texture);
							material->SetRenderingMode(eRenderingMode::Transparent);
							Resources::Insert(L"Catle_wall_Back", material);
				#pragma endregion

				#pragma region Devil(mid)
							texture = Resources::Load<Texture>(L"Catle_wall_Front", L"..\\Resources\\Texture\\Devil_Catle\\Catle_wall_Front_01.png");
							material = std::make_shared<Material>();
							material->SetShader(spriteShader);
							material->SetTexture(texture);
							material->SetRenderingMode(eRenderingMode::Transparent);
							Resources::Insert(L"Catle_wall_Front_01", material);
				#pragma endregion

				#pragma region Devil(front)
							texture = Resources::Load<Texture>(L"front_obj", L"..\\Resources\\Texture\\Devil_Catle\\front_obj.png");
							material = std::make_shared<Material>();
							material->SetShader(spriteShader);
							material->SetTexture(texture);
							material->SetRenderingMode(eRenderingMode::Transparent);
							Resources::Insert(L"Front_obj", material);
				#pragma endregion


				#pragma region in(fore_ground)
							texture = Resources::Load<Texture>(L"in_front", L"..\\Resources\\Texture\\Devil_Catle\\In_Fore_GR.png");
							material = std::make_shared<Material>();	material->SetShader(spriteShader);	material->SetTexture(texture);
							material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"In_Fore_GR", material);
				#pragma endregion	

				#pragma region Devil(Devil_Chair)
							texture	= Resources::Load<Texture>(L"Devil_chair", L"..\\Resources\\Texture\\Devil_Catle\\Devil_chair.png");
							material = std::make_shared<Material>();
							material->SetShader(spriteShader);
							material->SetTexture(texture);
							material->SetRenderingMode(eRenderingMode::Transparent);
							Resources::Insert(L"Devil_Chair", material);
				#pragma endregion
			#pragma endregion

			#pragma region out_Castle
			#pragma region Out(fore_ground)
						texture = Resources::Load<Texture>(L"out_front", L"..\\Resources\\Texture\\Devil_Catle\\Out_Fore_GR.png");
						material = std::make_shared<Material>(); material->SetShader(spriteShader); material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"Out_Fore_GR", material);
			#pragma endregion	

			#pragma region Out(catle)
						texture = Resources::Load<Texture>(L"out_catle", L"..\\Resources\\Texture\\Devil_Catle\\Out_Catle.png");
						material = std::make_shared<Material>(); material->SetShader(spriteShader); material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"Out_Catle", material);
			#pragma endregion	


			#pragma region Out(Castle_Out)
						texture = Resources::Load<Texture>(L"rampart_base", L"..\\Resources\\Texture\\Devil_Catle\\Castle_Out\\Rampart_Base.png");
						material = std::make_shared<Material>(); material->SetShader(spriteShader); material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"Rampart_Base", material);
			#pragma endregion


			#pragma region Cylinder
						texture = Resources::Load<Texture>(L"cylinder1", L"..\\Resources\\Texture\\Devil_Catle\\Castle_Out\\Pillar\\Pillar01.png");
						material = std::make_shared<Material>(); material->SetShader(spriteShader); material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"Pillar01", material);

						texture = Resources::Load<Texture>(L"cylinder2", L"..\\Resources\\Texture\\Devil_Catle\\Castle_Out\\Pillar\\Pillar02.png");
						material = std::make_shared<Material>(); material->SetShader(spriteShader); material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"Pillar02", material);

						texture = Resources::Load<Texture>(L"cylinder3", L"..\\Resources\\Texture\\Devil_Catle\\Castle_Out\\Pillar\\Pillar03.png");
						material = std::make_shared<Material>(); material->SetShader(spriteShader); material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"Pillar03", material);

						texture = Resources::Load<Texture>(L"cylinder4", L"..\\Resources\\Texture\\Devil_Catle\\Castle_Out\\Pillar\\Pillar04.png");
						material = std::make_shared<Material>(); material->SetShader(spriteShader); material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"Pillar04", material);
			#pragma endregion	

			#pragma region Trees_bush
						texture = Resources::Load<Texture>(L"bush01", L"..\\Resources\\Texture\\Devil_Catle\\Castle_Out\\Tree_BUSH\\Fore_Bush00.png");
						material = std::make_shared<Material>(); material->SetShader(spriteShader); material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"Fore_Bush00", material);

						texture = Resources::Load<Texture>(L"bush02", L"..\\Resources\\Texture\\Devil_Catle\\Castle_Out\\Tree_BUSH\\Fore_Bush02.png");
						material = std::make_shared<Material>(); material->SetShader(spriteShader); material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"Fore_Bush02", material);

						texture = Resources::Load<Texture>(L"bush03", L"..\\Resources\\Texture\\Devil_Catle\\Castle_Out\\Tree_BUSH\\Fore_Bush03.png");
						material = std::make_shared<Material>(); material->SetShader(spriteShader); material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"Fore_Bush03", material);

						texture = Resources::Load<Texture>(L"bush04", L"..\\Resources\\Texture\\Devil_Catle\\Castle_Out\\Tree_BUSH\\Fore_Bush04.png");
						material = std::make_shared<Material>(); material->SetShader(spriteShader); material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"Fore_Bush04", material);

						texture = Resources::Load<Texture>(L"bush05", L"..\\Resources\\Texture\\Devil_Catle\\Castle_Out\\Tree_BUSH\\Fore_Tree01.png");
						material = std::make_shared<Material>(); material->SetShader(spriteShader); material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent); Resources::Insert(L"Fore_Tree01", material);
			#pragma endregion	

		#pragma endregion	

			#pragma region Cloud				
			
						texture = Resources::Load<Texture>(L"Cloud_devil", L"..\\Resources\\Texture\\Effect\\Cloud_devil.png");
						material = std::make_shared<Material>();
						material->SetShader(moveShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Cloud_Devil", material);
			#pragma endregion

			#pragma region Tile_map(Mark_Up)
									texture = Resources::Load<Texture>(L"Devil_castle_tiles", L"..\\Resources\\Tile\\Devil_castle_tile.png");
									material = std::make_shared<Material>();
									material->SetShader(tile_shader);
									material->SetTexture(texture);
									material->SetRenderingMode(eRenderingMode::Transparent);
									Resources::Insert(L"Devil_castle_tile", material);


									texture = Resources::Load<Texture>(L"out_castle_tiles", L"..\\Resources\\Tile\\S1_tile1.png");
									material = std::make_shared<Material>();
									material->SetShader(tile_shader);
									material->SetTexture(texture);
									material->SetRenderingMode(eRenderingMode::Transparent);
									Resources::Insert(L"Out_castle_tiles", material);
			#pragma endregion	


			#pragma region PlayScene_Devil(background_materials)
						//{
						//	std::shared_ptr<Texture> texture
						//		= Resources::Load<Texture>(L"Catle_wall_Front2", L"..\\Resources\\Texture\\Devil_Catle\\Catle_wall_Front_02.png");
						//	std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
						//	spriteMateiral->SetShader(spriteShader);
						//	spriteMateiral->SetTexture(texture);
						//	Resources::Insert(L"Catle_wall_Front_02", spriteMateiral);
						//}

						//{
						//	std::shared_ptr<Texture> texture
						//		= Resources::Load<Texture>(L"Catle_wall_Front3", L"..\\Resources\\Texture\\Devil_Catle\\Catle_wall_Front_03.png");
						//	std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
						//	spriteMateiral->SetShader(spriteShader);
						//	spriteMateiral->SetTexture(texture);
						//	Resources::Insert(L"Catle_wall_Front_03", spriteMateiral);
						//}

						//{
						//	std::shared_ptr<Texture> texture
						//		= Resources::Load<Texture>(L"Catle_wall_Front4", L"..\\Resources\\Texture\\Devil_Catle\\Catle_wall_Front_04.png");
						//	std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
						//	spriteMateiral->SetShader(spriteShader);
						//	spriteMateiral->SetTexture(texture);
						//	Resources::Insert(L"Catle_wall_Front_04", spriteMateiral);
							//}
			#pragma endregion

		#pragma endregion


		#pragma region Stage1
				#pragma region Stage1(BackGround Public)
						//포그라운드(배경색)
						texture = Resources::Load<Texture>(L"fore_gr_color", L"..\\Resources\\Texture\\Stage1\\PUBLC_BG\\Fore_GR1.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Stage1_Fore_GR_Color", material);

						//포그라운드(나무)
						texture = Resources::Load<Texture>(L"fore_gr_", L"..\\Resources\\Texture\\Stage1\\PUBLC_BG\\Fore_GR2.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Stage1_Fore_GR_Tree", material);

						//미드그라운드(나무)
						texture = Resources::Load<Texture>(L"mid_gr1_1", L"..\\Resources\\Texture\\Stage1\\PUBLC_BG\\Mid_GR.png");
						material = std::make_shared<Material>();
						material->SetShader(moveShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Stage1_Mid_GR1_1", material);	



						//백그라운드 나무00
						texture = Resources::Load<Texture>(L"back_gr00_stage1", L"..\\Resources\\Texture\\Stage1\\PUBLC_BG\\Back_GR00.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Stage1_Back_GR00", material);

		
						//백그라운드 나무01
						texture = Resources::Load<Texture>(L"back_gr01_stage1", L"..\\Resources\\Texture\\Stage1\\PUBLC_BG\\Back_GR01.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Stage1_Back_GR01", material);


						//백그라운드 나무02
						texture = Resources::Load<Texture>(L"back_gr02_stage1", L"..\\Resources\\Texture\\Stage1\\PUBLC_BG\\Back_GR02.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Stage1_Back_GR02", material);


						//백그라운드 나무12
						texture = Resources::Load<Texture>(L"back_gr12_stage1", L"..\\Resources\\Texture\\Stage1\\PUBLC_BG\\Back_GR12.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Stage1_Back_GR12", material);

						//백그라운드 나무13
						texture = Resources::Load<Texture>(L"back_gr13_stage1", L"..\\Resources\\Texture\\Stage1\\PUBLC_BG\\Back_GR13.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Stage1_Back_GR13", material);

						//백그라운드 나무14
						texture = Resources::Load<Texture>(L"back_gr14_stage1", L"..\\Resources\\Texture\\Stage1\\PUBLC_BG\\Back_GR14.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Stage1_Back_GR14", material);

						//백그라운드 나무15
						texture = Resources::Load<Texture>(L"back_gr15_stage1", L"..\\Resources\\Texture\\Stage1\\PUBLC_BG\\Back_GR15.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Stage1_Back_GR15", material);

						//백그라운드 나무16
						texture = Resources::Load<Texture>(L"back_gr16_stage1", L"..\\Resources\\Texture\\Stage1\\PUBLC_BG\\Back_GR16.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Stage1_Back_GR16", material);


						texture = Resources::Load<Texture>(L"back_gr17_stage1", L"..\\Resources\\Texture\\Stage1\\PUBLC_BG\\Back_GR17.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Stage1_Back_GR17", material);



						texture = Resources::Load<Texture>(L"back_gr18_stage1", L"..\\Resources\\Texture\\Stage1\\PUBLC_BG\\Back_GR18.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Stage1_Back_GR18", material);
				#pragma endregion


				#pragma region Stage1_1_Bg
										texture = Resources::Load<Texture>(L"map1_1", L"..\\Resources\\Texture\\Stage1\\PUBLC_BG\\map1_1.png");
										material = std::make_shared<Material>(); material->SetShader(spriteShader);	material->SetTexture(texture);
										Resources::Insert(L"Map1_1", material); material->SetRenderingMode(eRenderingMode::Transparent);
				#pragma endregion



				#pragma region Stage1_2_Bg
										texture = Resources::Load<Texture>(L"map1_2", L"..\\Resources\\Texture\\Stage1\\PUBLC_BG\\map1_2.png");
										material = std::make_shared<Material>(); material->SetShader(spriteShader);	material->SetTexture(texture);
										Resources::Insert(L"Map1_2", material); material->SetRenderingMode(eRenderingMode::Transparent);
				#pragma endregion




			#pragma region Stage1_MiniBoss
						texture = Resources::Load<Texture>(L"miniboss_00", L"..\\Resources\\Texture\\Ground\\Stage_1\\MiniBoss\\Miniboss_00.png");
						material = std::make_shared<Material>(); material->SetShader(spriteShader);	material->SetTexture(texture);
						Resources::Insert(L"Miniboss_00", material); material->SetRenderingMode(eRenderingMode::Transparent);
			#pragma endregion

				#pragma region Stage1_Boss
						texture = Resources::Load<Texture>(L"king1", L"..\\Resources\\Texture\\Stage1\\Stag1_Boss\\King1.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						Resources::Insert(L"Stage_king1", material);
				#pragma endregion
		#pragma endregion


		#pragma region Stage2
			#pragma region Stage2_Boss
			{
				texture = Resources::Load<Texture>(L"King2", L"..\\Resources\\Texture\\Stage2\\King2.png");
				material = std::make_shared<Material>();
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"Stage_king2", material);
			}
			{
				texture = Resources::Load<Texture>(L"Layana_Sisters_Place", L"..\\Resources\\Texture\\Stage2\\Layana_Sisters_Map.png");
				material = std::make_shared<Material>();
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"Layana_Sisters_Map", material);
			}
			{
				texture = Resources::Load<Texture>(L"Stage2_BOSS_Stairs", L"..\\Resources\\Texture\\Stage2\\Layana_Sisters_stairs.png");
				material = std::make_shared<Material>();
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"Layana_Sisters_Stairs", material);
			}
			{
				texture = Resources::Load<Texture>(L"Stage2_BOSS_Steps", L"..\\Resources\\Texture\\Stage2\\Layana_Sisters_Steps.png");
				material = std::make_shared<Material>();
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"Layana_Sisters_Steps", material);
			}

				#pragma region Tile_map(Stage2_Boss)
							texture = Resources::Load<Texture>(L"Stage2_boss", L"..\\Resources\\Tile\\Stage2_Tile.png");
							material = std::make_shared<Material>();
							material->SetShader(tile_shader);
							material->SetTexture(texture);
							material->SetRenderingMode(eRenderingMode::Transparent);
							Resources::Insert(L"Stage2_Boss", material);
				#pragma endregion

			#pragma endregion

			#pragma region Stage2_Public
				{
					texture = Resources::Load<Texture>(L"backGround_stage2_00", L"..\\Resources\\Texture\\Stage2\\PUBLC_BG\\BackGround_Stage2_00.png");
					material = std::make_shared<Material>();
					material->SetShader(spriteShader);
					material->SetTexture(texture);
					material->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"BackGround_Stage2_00", material);
				}

				{
					texture = Resources::Load<Texture>(L"backGround_stage2_01", L"..\\Resources\\Texture\\Stage2\\PUBLC_BG\\BackGround_Stage2_01.png");
					material = std::make_shared<Material>();
					material->SetShader(spriteShader);
					material->SetTexture(texture);
					material->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"BackGround_Stage2_01", material);
				}

				{
					texture = Resources::Load<Texture>(L"foreGround_stage2_00", L"..\\Resources\\Texture\\Stage2\\PUBLC_BG\\ForeGround_Stage2_00.png");
					material = std::make_shared<Material>();
					material->SetShader(spriteShader);
					material->SetTexture(texture);
					material->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"ForeGround_Stage2_00", material);
				}

				#pragma region Cloud	
				{		
					texture = Resources::Load<Texture>(L"stage2_cloud", L"..\\Resources\\Texture\\Effect\\Stage2_Cloud.png");
					material = std::make_shared<Material>();
					material->SetShader(moveShader);
					material->SetTexture(texture);
					material->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"Stage2_Cloud", material); 
				}
				#pragma endregion

			#pragma endregion
		#pragma endregion


		#pragma region Stage_End

				#pragma region Stage_1
					{
						texture = Resources::Load<Texture>(L"ch1_gate_choicetable", L"..\\Resources\\Texture\\Gate\\Stage1\\Ch1_Gate_ChoiceTable.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Ch1_Gate_ChoiceTable", material);
					}
					{
						texture = Resources::Load<Texture>(L"ch1_gate_table", L"..\\Resources\\Texture\\Gate\\Stage1\\Ch1_Gate_Table.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Ch1_Gate_Table", material);
					}
				#pragma endregion

				#pragma region Stage_2
					{
						texture = Resources::Load<Texture>(L"ch2_gate_table", L"..\\Resources\\Texture\\Gate\\Stage2\\Ch2_Gate_Table.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Ch2_Gate_Table", material);
					}

					{
						texture = Resources::Load<Texture>(L"ch2_gate_choicetable", L"..\\Resources\\Texture\\Gate\\Stage2\\Ch2_Gate_ChoiceTable.png");
						material = std::make_shared<Material>();
						material->SetShader(spriteShader);
						material->SetTexture(texture);
						material->SetRenderingMode(eRenderingMode::Transparent);
						Resources::Insert(L"Ch2_Gate_ChoiceTable", material);
					}
				#pragma endregion

		#pragma endregion	


		#pragma region Tile	
				#pragma region Tile_map(Stage1_1)
								texture = Resources::Load<Texture>(L"stage1_1tiles", L"..\\Resources\\Tile\\S1_tile1.png");
								material = std::make_shared<Material>();
								material->SetShader(tile_shader);
								material->SetTexture(texture);
								material->SetRenderingMode(eRenderingMode::Transparent);
								Resources::Insert(L"Stage1_1Tile", material);
				#pragma endregion

				#pragma region Tile_map(Stage1_2)
								texture = Resources::Load<Texture>(L"stage1_2tiles", L"..\\Resources\\Tile\\S1_tile1.png");
								material = std::make_shared<Material>();
								material->SetShader(tile_shader);
								material->SetTexture(texture);
								material->SetRenderingMode(eRenderingMode::Transparent);
								Resources::Insert(L"Stage1_2Tile", material);
				#pragma endregion
						

				#pragma region Tile_map(Stage1_MiniBoss)
								texture = Resources::Load<Texture>(L"Stage1_miniboss", L"..\\Resources\\Tile\\S1_tile1.png");
								material = std::make_shared<Material>();
								material->SetShader(tile_shader);
								material->SetTexture(texture);
								material->SetRenderingMode(eRenderingMode::Transparent);
								Resources::Insert(L"Stage1_MiniBoss", material);
				#pragma endregion

				#pragma region Tile_map(Stage1_Boss)
								texture = Resources::Load<Texture>(L"Stage1_boss", L"..\\Resources\\Tile\\S1_tile1.png");
								material = std::make_shared<Material>();
								material->SetShader(tile_shader);
								material->SetTexture(texture);
								material->SetRenderingMode(eRenderingMode::Transparent);
								Resources::Insert(L"Stage1_Boss", material);
				#pragma endregion

				#pragma region Tile_map(Stage2_1)
								texture = Resources::Load<Texture>(L"stage2_tile", L"..\\Resources\\Tile\\Stage2_Tile.png");
								material = std::make_shared<Material>();
								material->SetShader(tile_shader);
								material->SetTexture(texture);
								material->SetRenderingMode(eRenderingMode::Transparent);
								Resources::Insert(L"Stage2_Tile", material);
				#pragma endregion

		#pragma endregion	


		#pragma region DebugShader_Collider
				//std::shared_ptr<Shader> debugShader
				//	= Resources::Find<Shader>(L"DebugShader");

				material = std::make_shared<Material>();
				material->SetShader(debugShader);
				Resources::Insert(L"DebugMaterial", material);
		#pragma endregion


		#pragma region Pade_In & Out
				texture = Resources::Load<Texture>(L"Blackfade", L"..\\Resources\\Texture\\Blackfade.png");
				material->SetTexture(texture);
				material = std::make_shared<Material>();
				material->SetShader(alpha_Shader);
				material->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"AlphaMaterial", material);
		#pragma endregion


		//#pragma region Dash
		//				texture = Resources::Load<Texture>(L"Blackfade", L"..\\Resources\\Texture\\Blackfade.png");
		//				material->SetTexture(texture);
		//				material = std::make_shared<Material>();
		//				material->SetShader(alpha_Shader);
		//				material->SetRenderingMode(eRenderingMode::Transparent);
		//				Resources::Insert(L"AlphaMaterial", material);
		//#pragma endregion
	}


	void Initialize()
	{
		LoadMesh();
		LoadShader();
		LoadBuffer();
		SetupState();
		LoadTexture();
		LoadMaterial();	
	}


	void PushDebugMeshAttribute(DebugMesh mesh)
	{
		debugMeshs.push_back(mesh);
	}


	void BindNoiseTexture()
	{
		std::shared_ptr<Texture> texture
			= Resources::Find<Texture>(L"Noise01");

		texture->BindShaderResource(eShaderStage::VS, 15);
		texture->BindShaderResource(eShaderStage::HS, 15);
		texture->BindShaderResource(eShaderStage::DS, 15);
		texture->BindShaderResource(eShaderStage::GS, 15);
		texture->BindShaderResource(eShaderStage::PS, 15);
		texture->BindShaderResource(eShaderStage::CS, 15);

		ConstantBuffer* cb = constantBuffer[(UINT)eCBType::Noise];
		NoiseCB data = {};
		data.size.x = texture->GetWidth();
		data.size.y = texture->GetHeight();

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
	}


	void Render()
	{
		BindNoiseTexture();

		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}
		cameras.clear();
	}


	void Release()
	{
		for (ConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}
	}

}


