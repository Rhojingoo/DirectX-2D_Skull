#include "jkRenderer.h"
#include "jkResources.h"
#include "jkTexture.h"
#include "jkMaterial.h"

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

	std::vector<jk::Camera*> cameras = {};

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

		
		shader = jk::Resources::Find<Shader>(L"Tile_Shader");
		jk::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());


		shader = jk::Resources::Find<Shader>(L"Move_Shader");
		jk::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

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
#pragma region RECT
		//RECT
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
#pragma endregion

		// Vertex Buffer
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

	}


	void LoadBuffer()
	{

		// Constant Buffer
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		// Material Buffer
		constantBuffer[(UINT)eCBType::Material] = new ConstantBuffer(eCBType::Material);
		constantBuffer[(UINT)eCBType::Material]->Create(sizeof(MaterialCB));

		// Grid Buffer
		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(TransformCB));
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

		std::shared_ptr<Shader> girdShader = std::make_shared<Shader>();
		girdShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		girdShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		jk::Resources::Insert(L"Grid_Shader", girdShader);

		//구름
		std::shared_ptr<Shader> moveShader = std::make_shared<Shader>();
		moveShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		moveShader->Create(eShaderStage::PS, L"MovePS.hlsl", "main");
		jk::Resources::Insert(L"Move_Shader", moveShader);

		//타일 미완성
#pragma region Tile_map
		std::shared_ptr<Shader> TileShader = std::make_shared<Shader>();
		TileShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		TileShader->Create(eShaderStage::PS, L"TileMapPS.hlsl", "main");
		TileShader->SetRSState(eRSType::SolidNone);
		TileShader->SetDSState(eDSType::Less);
		TileShader->SetBSState(eBSType::AlphaBlend);
		jk::Resources::Insert(L"Tile_Shader", TileShader);
#pragma endregion

	
	}

	void LoadMaterial()
	{
		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");
		//std::shared_ptr<Shader> TileShader
		//	= Resources::Find<Shader>(L"Tile_Shader");
		std::shared_ptr<Shader> moveShader
			= Resources::Find<Shader>(L"Move_Shader");
		
#pragma region Title
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Title", L"..\\Resources\\Texture\\Title\\Title.png");

			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetShader(spriteShader);
			material->SetTexture(texture);
			Resources::Insert(L"SpriteMaterial", material);
#pragma endregion
		
#pragma region PlayScene
	#pragma region PlayScene_Devil(back)
				texture	= Resources::Load<Texture>(L"DevilCastle", L"..\\Resources\\Texture\\Devil_Catle\\Catle_wall_Back.png");
				material = std::make_shared<Material>();
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				Resources::Insert(L"Catle_wall_Back", material);
	#pragma endregion


	#pragma region PlayScene_Devil(front)
				texture	= Resources::Load<Texture>(L"Catle_wall_Front", L"..\\Resources\\Texture\\Devil_Catle\\Catle_wall_Front_01.png");
				material = std::make_shared<Material>();
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"Catle_wall_Front_01", material);
	#pragma endregion


	#pragma region PlayScene_Devil(Devil_Chair)
				texture	= Resources::Load<Texture>(L"Devil_chair", L"..\\Resources\\Texture\\Devil_Catle\\Devil_chair.png");
				material = std::make_shared<Material>();
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"Devil_Chair", material);
	#pragma endregion


	#pragma region PlayScene_Devil(UI)
				texture = Resources::Load<Texture>(L"Skul_ui", L"..\\Resources\\Texture\\UI\\Skul_UI.png");
				material = std::make_shared<Material>();
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				material->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"Skul_UI", material);
	#pragma endregion


	#pragma region PlayScene_Tile_map(Dungreed)
				texture = Resources::Load<Texture>(L"DG_Tiles", L"..\\Resource\\Tile\\DG_Tile.png");
				material = std::make_shared<Material>();
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				Resources::Insert(L"DG_Tile", material);
	#pragma endregion


	#pragma region Cloud				
			
				texture = Resources::Load<Texture>(L"Cloud_devil", L"..\\Resources\\Texture\\Effect\\Cloud_devil.png");
				material = std::make_shared<Material>();
				material->SetShader(moveShader);
				material->SetTexture(texture);
				Resources::Insert(L"Cloud_Devil", material);
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



#pragma region Stage2(Back)
				texture = Resources::Load<Texture>(L"King2", L"..\\Resources\\Texture\\Stage2\\King2.png");
				material = std::make_shared<Material>();
				material->SetShader(spriteShader);
				material->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial02", material);
#pragma endregion


#pragma region Grid
		std::shared_ptr<Shader> gridShader
			= Resources::Find<Shader>(L"Grid_Shader");
		material = std::make_shared<Material>();
		material->SetShader(gridShader);
		Resources::Insert(L"GridMaterial", material);
#pragma endregion


#pragma region Tile_window2_Create
		texture = Resources::Load<Texture>(L"TileAtlas", L"..\\Resource\\Tile\\Tile.bmp");
		material->SetTexture(texture);
			//Load<Texture>(L"DevilCastle", L"..\\Resources\\Texture\\Devil_Catle\\Catle_wall_Back.png")
#pragma endregion


		//타일 미완성
#pragma region Tile_map
		//texture = Resources::Load<Texture>(L"King2", L"..\\Resources\\Texture\\Stage2\\King2.png");
		//material = std::make_shared<Material>();
		//material->SetShader(spriteShader);
		//material->SetTexture(texture);
		//material->SetRenderingMode(eRenderingMode::Transparent);
		//Resources::Insert(L"MTRL_Map_Tile", material);
#pragma endregion

	}


	void Initialize()
	{
		LoadMesh();
		LoadShader();
		LoadBuffer();
		SetupState();
		LoadMaterial();	
	}

	void Render()
	{
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


