#include "jkBaseRenderer.h"
#include "jkGameObject.h"
#include "jkTransform.h"
#include "jkRenderer.h"

namespace jk
{
	BaseRenderer::BaseRenderer(eComponentType type)
		: Component(type)
	{
	}
	BaseRenderer::~BaseRenderer()
	{
	}
	void BaseRenderer::Initialize()
	{
	}
	void BaseRenderer::Update()
	{
	}
	void BaseRenderer::LateUpdate()
	{
	}

	void BaseRenderer::Render()
	{
		//GetOwner()->GetComponent<Transform>()->BindConstantBuffer();

		//GetMesh()->BindBuffer();
		//GetMaterial()->Binds();
		//GetMesh()->Render();
		//GetMaterial()->Clear();
	}
}