#include "Archer_Ultimate_Bye.h"
#include "Include_Common.h"


namespace jk
{
	Archer_Ultimate_Bye::Archer_Ultimate_Bye()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Archer_Ultimate_Bye::~Archer_Ultimate_Bye()
	{
	}
	void Archer_Ultimate_Bye::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Effect\\Ultimate_Bye\\END", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Effect\\Ultimate_Bye\\BASIC", this);
		
		at->CompleteEvent(L"Ultimate_ByeEND") = std::bind(&Archer_Ultimate_Bye::Compelete, this);
		at->PlayAnimation(L"Ultimate_ByeBASIC", false);

		GameObject::Initialize();
	}
	void Archer_Ultimate_Bye::Update()
	{
	
		if (_effect_On == true)
		{
			_Lifetime += static_cast<float>(Time::DeltaTime());
			if (_Lifetime >= 10)
			{
				at->PlayAnimation(L"ByeEND", true);
				_Lifetime = 0;
				_effect_On = false;
			}
		}

		GameObject::Update();
	}
	void Archer_Ultimate_Bye::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Archer_Ultimate_Bye::Render()
	{
		GameObject::Render();
	}
	void Archer_Ultimate_Bye::OnCollisionEnter(Collider2D* other)
	{
	}
	void Archer_Ultimate_Bye::OnCollisionStay(Collider2D* other)
	{
	}
	void Archer_Ultimate_Bye::OnCollisionExit(Collider2D* other)
	{
	}
	void Archer_Ultimate_Bye::Compelete()
	{
		this->SetState(eState::Paused);
	}
}