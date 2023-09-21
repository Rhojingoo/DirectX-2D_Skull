#include "Yggdrasil_HandDead_Effect.h"

namespace jk
{
	Yggdrasil_HandDead_Effect::Yggdrasil_HandDead_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_HandDead_Effect::~Yggdrasil_HandDead_Effect()
	{
	}
	void Yggdrasil_HandDead_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandDie", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandDie", this, 1);
		
		at->PlayAnimation(L"HandHandDie", false);
		//at->PlayAnimation(L"HandHandDieR", false);
		GameObject::Initialize();
	}
	void Yggdrasil_HandDead_Effect::Update()
	{
		if (_DirectionSellect == true)
		{
			if (_Dir == 1)
				at->PlayAnimation(L"HandHandDie", false);
			else
				at->PlayAnimation(L"HandHandDieR", false);
			_DirectionSellect = false;
		}

		mTime = Time::DeltaTime();
		if (mTime > 1)
		{
			this->SetState(eState::Paused);
		}
		GameObject::Update();
	}
	void Yggdrasil_HandDead_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_HandDead_Effect::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_HandDead_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_HandDead_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_HandDead_Effect::OnCollisionExit(Collider2D* other)
	{
	}
}