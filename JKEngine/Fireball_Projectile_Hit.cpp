#include "Fireball_Projectile_Hit.h"
#include "Include_Common.h"

namespace jk
{
	Fireball_Projectile_Hit::Fireball_Projectile_Hit()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Fireball_Projectile_Hit::~Fireball_Projectile_Hit()
	{
	}
	void Fireball_Projectile_Hit::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Bullet\\Fireball_ProjectileHit", this,0,0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Bullet\\Fireball_ProjectileHit", this, 1,0.05f);

		at->CompleteEvent(L"BulletFireball_ProjectileHit") = std::bind(&Fireball_Projectile_Hit::Compelete, this);
		at->CompleteEvent(L"BulletFireball_ProjectileHitR") = std::bind(&Fireball_Projectile_Hit::Compelete, this);


		at->PlayAnimation(L"BulletFireball_ProjectileHit", true);

		GameObject::Initialize();
	}
	void Fireball_Projectile_Hit::Update()
	{
		if (_effect_On == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"BulletFireball_ProjectileHit", true);
			if (_dir == -1)
				at->PlayAnimation(L"BulletFireball_ProjectileHitR", true);
			_effect_On = false;
		}


		GameObject::Update();
	}
	void Fireball_Projectile_Hit::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Fireball_Projectile_Hit::Render()
	{
		GameObject::Render();
	}
	void Fireball_Projectile_Hit::OnCollisionEnter(Collider2D* other)
	{
	}
	void Fireball_Projectile_Hit::OnCollisionStay(Collider2D* other)
	{
	}
	void Fireball_Projectile_Hit::OnCollisionExit(Collider2D* other)
	{
	}
	void Fireball_Projectile_Hit::Compelete()
	{
		this->SetState(eState::Paused);
	}
}