#include "Yggdrasil_Sweeping.h"

namespace jk
{
	int	 Yggdrasil_Sweeping::mDir =1;
	Yggdrasil_Sweeping::Yggdrasil_Sweeping()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_Sweeping::~Yggdrasil_Sweeping()
	{
	}
	void Yggdrasil_Sweeping::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Effect\\Sweeping", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Effect\\Sweeping", this,1);
		at->CompleteEvent(L"EffectSweeping") = std::bind(&Yggdrasil_Sweeping::Compelete, this);

		at->PlayAnimation(L"EffectSweeping", true);
		GameObject::Initialize();
	}
	void Yggdrasil_Sweeping::Update()
	{
		if (_EffectOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"EffectSweeping", true);
			else
				at->PlayAnimation(L"EffectSweepingR", true);
			_EffectOn = false;
		}
		GameObject::Update();
	}
	void Yggdrasil_Sweeping::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_Sweeping::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_Sweeping::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_Sweeping::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_Sweeping::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdrasil_Sweeping::Compelete()
	{
	}
}