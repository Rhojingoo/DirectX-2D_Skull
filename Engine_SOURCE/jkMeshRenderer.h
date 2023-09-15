#pragma once
#include "jkComponent.h"
#include "jkMesh.h"
#include "jkMaterial.h"
#include "jkBaseRenderer.h"

namespace jk
{
	class MeshRenderer : public BaseRenderer
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}
