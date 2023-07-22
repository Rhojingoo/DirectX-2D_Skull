#include "jkMeshRenderer.h"
#include "jkGameObject.h"
#include "jkTransform.h"
#include "jkRenderer.h"
#include "jkInput.h"
#include "jkAnimator.h"

namespace jk
{
	MeshRenderer::MeshRenderer()
		: BaseRenderer(eComponentType::MeshRenderer)
	{
	}
	MeshRenderer::~MeshRenderer()
	{
	}
	void MeshRenderer::Initialize()
	{
	}
	void MeshRenderer::Update()
	{
	}
	void MeshRenderer::LateUpdate()
	{
	}
	void MeshRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();

		GetMesh()->BindBuffer();
		GetMaterial()->Binds();
		GetMesh()->Render();
		GetMaterial()->Clear();
		

		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (animator)
		{
			animator->Binds();
		}
		//선생코드
		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//tr->BindConstantBuffer();
		//mMesh->BindBuffer();
		//mMaterial->Binds();
		//mMesh->Render();
		//mMaterial->Clear();
	}
}
