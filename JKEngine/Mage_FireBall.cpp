#include "Mage_FireBall.h"


namespace jk
{
	Mage_FireBall::Mage_FireBall()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Mage_FireBall::~Mage_FireBall()
	{
	}
	void Mage_FireBall::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Bullet\\Fireball_Projectile", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Bullet\\Fireball_Projectile", this, 1);
		//at->CompleteEvent(L"BulletWorld_On_Fire_Projectile_v") = std::bind(&Ultimate_On_Fire_Projectile::complete, this);


		at->PlayAnimation(L"BulletFireball_Projectile", true);
		GameObject::Initialize();
	}
	void Mage_FireBall::Update()
	{
		if (_bullet_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"BulletFireball_Projectile", true);
			if (_dir == -1)
				at->PlayAnimation(L"BulletFireball_ProjectileR", true);
			_bullet_animation = false;
		}

		if (_bullet_On == true)
		{
			_Lifetime += Time::DeltaTime();
			if (_Lifetime >= 5)
			{
				this->SetState(eState::Paused);
				_bullet_On = false;
				_Lifetime = 0;
			}
		}
		GameObject::Update();
	}
	void Mage_FireBall::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.9f));
		_collider->SetCenter(Vector2(0.0f, -0.07f));
		GameObject::LateUpdate();
	}
	void Mage_FireBall::Render()
	{
		GameObject::Render();
	}
	void Mage_FireBall::OnCollisionEnter(Collider2D* other)
	{
	}
	void Mage_FireBall::OnCollisionStay(Collider2D* other)
	{
	}
	void Mage_FireBall::OnCollisionExit(Collider2D* other)
	{
	}
	void Mage_FireBall::complete()
	{
	}
}