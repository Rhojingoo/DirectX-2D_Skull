#include "Ultimate_On_Fire_Projectile_Hit.h"

namespace jk
{
	Ultimate_On_Fire_Projectile_Hit::Ultimate_On_Fire_Projectile_Hit()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Ultimate_On_Fire_Projectile_Hit::~Ultimate_On_Fire_Projectile_Hit()
	{
	}
	void Ultimate_On_Fire_Projectile_Hit::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Bullet\\World_On_Fire_Projectile_Hit", this,0,0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Bullet\\World_On_Fire_Projectile_Hit", this, 1,0.05f);

		at->CompleteEvent(L"BulletWorld_On_Fire_Projectile_Hit") = std::bind(&Ultimate_On_Fire_Projectile_Hit::Compelete, this);
		at->CompleteEvent(L"BulletWorld_On_Fire_Projectile_HitR") = std::bind(&Ultimate_On_Fire_Projectile_Hit::Compelete, this);

		at->PlayAnimation(L"BulletWorld_On_Fire_Projectile_Hit", true);

		GameObject::Initialize();
	}
	void Ultimate_On_Fire_Projectile_Hit::Update()
	{
		if (_effect_On == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"BulletWorld_On_Fire_Projectile_Hit", true);
			if (_dir == -1)
				at->PlayAnimation(L"BulletWorld_On_Fire_Projectile_HitR", true);
			_effect_On = false;
		}

		GameObject::Update();
	}
	void Ultimate_On_Fire_Projectile_Hit::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Ultimate_On_Fire_Projectile_Hit::Render()
	{
		GameObject::Render();
	}
	void Ultimate_On_Fire_Projectile_Hit::OnCollisionEnter(Collider2D* other)
	{
	}
	void Ultimate_On_Fire_Projectile_Hit::OnCollisionStay(Collider2D* other)
	{
	}
	void Ultimate_On_Fire_Projectile_Hit::OnCollisionExit(Collider2D* other)
	{
	}
	void Ultimate_On_Fire_Projectile_Hit::Compelete()
	{
		this->SetState(eState::Paused);
	}
}