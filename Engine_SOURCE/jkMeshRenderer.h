#pragma once
#include "jkComponent.h"
#include "jkMesh.h"
#include "jkShader.h"

namespace jk
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		Mesh* mMesh;
		Shader* mShader;
	};
}
