#include "Archer_Trap.h"

namespace jk
{
	Archer_Trap::Archer_Trap()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Archer_Trap::~Archer_Trap()
	{
	}
	void Archer_Trap::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);
		tr = this->GetComponent<Transform>();


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Bullet\\Acher_Trap", this);

		at->PlayAnimation(L"BulletAcher_Trap", true);
		GameObject::Initialize();
	}
	void Archer_Trap::Update()
	{
		if (_Bullet_Life == true)
		{
			_attackatime += Time::DeltaTime();
			if (_attackatime > 7)
			{
				this->SetState(eState::Paused);
				_Bullet_Life = false;		
				_attackatime = 0;
			}
		}

		GameObject::Update();
	}
	void Archer_Trap::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Archer_Trap::Render()
	{
		GameObject::Render();
	}
	void Archer_Trap::OnCollisionEnter(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{		
			_rigidbody->SetGround(true);		
			_rigidbody->ClearVelocity();	
		}
	}
	void Archer_Trap::OnCollisionStay(Collider2D* other)
	{
	}
	void Archer_Trap::OnCollisionExit(Collider2D* other)
	{
	}
	void Archer_Trap::complete()
	{
	}
}