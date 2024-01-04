#include "Yggdrasil_FaceDead_Effect.h"
#include "Include_Common.h"


namespace jk
{
	Yggdrasil_FaceDead_Effect::Yggdrasil_FaceDead_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_FaceDead_Effect::~Yggdrasil_FaceDead_Effect()
	{
	}
	void Yggdrasil_FaceDead_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_Die_Effect", this, 0);


		at->PlayAnimation(L"FaceYggdrasilFace_Die_Effect", false);
		GameObject::Initialize();
	}
	void Yggdrasil_FaceDead_Effect::Update()
	{
		_Time = static_cast<float>(Time::DeltaTime());
		if (_Time > 1)
		{
			this->SetState(eState::Paused);
		}		
		GameObject::Update();
	}
	void Yggdrasil_FaceDead_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_FaceDead_Effect::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_FaceDead_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_FaceDead_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_FaceDead_Effect::OnCollisionExit(Collider2D* other)
	{
	}
}