#include "Ultimate_On_Fire_Projectile.h"


namespace jk
{
	Ultimate_On_Fire_Projectile::Ultimate_On_Fire_Projectile()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Ultimate_On_Fire_Projectile::~Ultimate_On_Fire_Projectile()
	{
	}
	void Ultimate_On_Fire_Projectile::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Bullet\\World_On_Fire_Projectile", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Bullet\\World_On_Fire_Projectile", this,1);
		//at->CompleteEvent(L"BulletWorld_On_Fire_Projectile") = std::bind(&Ultimate_On_Fire_Projectile::complete, this);


		at->PlayAnimation(L"BulletWorld_On_Fire_Projectile", true);
		GameObject::Initialize();
	}
	void Ultimate_On_Fire_Projectile::Update()
	{
		if (_bullet_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"BulletWorld_On_Fire_Projectile", true);
			if (_dir == -1)
				at->PlayAnimation(L"BulletWorld_On_Fire_ProjectileR", true);
			_bullet_animation = false;
		}

		if (_bullet_On == true)
		{
			_Lifetime += Time::DeltaTime();
			if (_Lifetime >= 7)
			{				
				this->SetState(eState::Paused);
				_bullet_On = false;
				_Lifetime = 0;
			}
		}

		GameObject::Update();
	}
	void Ultimate_On_Fire_Projectile::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.9f));
		_collider->SetCenter(Vector2(0.0f, -0.07f));
		GameObject::LateUpdate();
	}
	void Ultimate_On_Fire_Projectile::Render()
	{
		GameObject::Render();
	}
	void Ultimate_On_Fire_Projectile::OnCollisionEnter(Collider2D* other)
	{
	}
	void Ultimate_On_Fire_Projectile::OnCollisionStay(Collider2D* other)
	{
	}
	void Ultimate_On_Fire_Projectile::OnCollisionExit(Collider2D* other)
	{
	}
	void Ultimate_On_Fire_Projectile::complete()
	{
	}
}