#include "jkRenderer.h"
#include "jkTime.h"


namespace jk::renderer
{	
	Vertex vertexes[372] = {};

	// Input Layout (정점 정보)
	ID3D11InputLayout* triangleLayout = nullptr;

	// Vertex Buffer
	ID3D11Buffer* triangleBuffer = nullptr;

	// error blob
	ID3DBlob* errorBlob = nullptr;

	// Vertex Shader code -> Binary Code
	ID3DBlob* triangleVSBlob = nullptr;

	// Vertex Shader
	ID3D11VertexShader* triangleVSShader = nullptr;

	// Pixel Shader code -> Binary Code
	ID3DBlob* trianglePSBlob = nullptr;

	// Vertex Shader
	ID3D11PixelShader* trianglePSShader = nullptr;


	void SetupState()
	{

	}

	void LoadBuffer()
	{
		D3D11_BUFFER_DESC triangleDesc = {};
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.ByteWidth = sizeof(Vertex) * 372;
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;
		jk::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);
	}

	void LoadShader()
	{
		jk::graphics::GetDevice()->CreateShader();
	}


	void Initialize()
	{
		//원
		float angle = 0;
		float radius = 0.1f;
		Vector3 Pos = Vector3(0.0f, 0.0f, 0.0f);

		for (UINT i = 0; i < 360; i++)
		{
			float X = Pos.x;
			float Y = Pos.y;
			

			if (i % 3 == 2)
			{
				vertexes[i].pos = Pos;
				continue;
			}

			//angle +=  Time::DeltaTime() * 10;
			float radian = (360 - i) * 3.14 / 180;
			X += radius * cos(radian);
			Y += radius * sin(radian);

			vertexes[i].pos = Vector3(X, Y, 0.0f);
			vertexes[i].color = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
		}


		//마름모
		vertexes[360].pos = Vector3(0.6f, 0.1f, 0.0f);
		vertexes[360].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[361].pos = Vector3(0.7f, -0.1f, 0.0f);
		vertexes[361].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[362].pos = Vector3(0.5f, -0.1f, 0.0f);
		vertexes[362].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[363].pos = Vector3(0.7f, -0.1f, 0.0f);
		vertexes[363].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[364].pos = Vector3(0.6f, -0.3f, 0.0f);
		vertexes[364].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[365].pos = Vector3(0.5f, -0.1f, 0.0f);
		vertexes[365].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);



		//사각형
		vertexes[366].pos = Vector3(0.3f, 0.3f, 0.0f);
		vertexes[366].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[367].pos = Vector3(0.4f, 0.3f, 0.0f);
		vertexes[367].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[368].pos = Vector3(0.4f, 0.2f, 0.0f);
		vertexes[368].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[369].pos = Vector3(0.4f, 0.2f, 0.0f);
		vertexes[369].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[370].pos = Vector3(0.3f, 0.2f, 0.0f);
		vertexes[370].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[371].pos = Vector3(0.3f, 0.3f, 0.0f);
		vertexes[371].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);





		SetupState();
		LoadBuffer();
		LoadShader();

	}
}


