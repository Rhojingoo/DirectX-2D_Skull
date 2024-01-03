#include "Layana_Awaken_Meteor_Projectile.h"
#include "Include_Common.h"

namespace jk
{
	Layana_Awaken_Meteor_Projectile::Layana_Awaken_Meteor_Projectile()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Layana_Awaken_Meteor_Projectile::~Layana_Awaken_Meteor_Projectile()
	{
	}
	void Layana_Awaken_Meteor_Projectile::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Dark_GoldenMeteor_Projectile", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Dark_GoldenMeteor_Projectile", this, 1);


		//at->CompleteEvent(L"BulletDark_DimensionRush_Impact") = std::bind(&Layana_Awaken_Meteor_Projectile::Compelete_Pierce, this);
		//at->CompleteEvent(L"BulletDark_DimensionRush_ImpactR") = std::bind(&Layana_Awaken_Meteor_Projectile::Compelete_Pierce, this);

		at->PlayAnimation(L"BulletDark_GoldenMeteor_Projectile", true);
		GameObject::Initialize();
	}
	void Layana_Awaken_Meteor_Projectile::Update()
	{
		if (_effect_switch == true)
		{
			if (_Dir == 1)
				at->PlayAnimation(L"BulletDark_GoldenMeteor_Projectile", true);
			else
				at->PlayAnimation(L"BulletDark_GoldenMeteor_ProjectileR", true);
			_effect_switch = false;
		}
		if (_bulletoff == true)
		{
			_attackatime += static_cast<float>(Time::DeltaTime());
			if (_attackatime >= 5)
			{
				this->SetState(eState::Paused);
				_bulletoff = false;
				_attackatime = 0;
				_rigidbody->ClearVelocity();
				_rigidbody->SetFriction(false);
				_rigidbody->SetGravity(false);
			}
		}


		GameObject::Update();
	}
	void Layana_Awaken_Meteor_Projectile::LateUpdate()
	{
		_collider->SetSize(Vector2(0.35f, 0.9f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Layana_Awaken_Meteor_Projectile::Render()
	{
		GameObject::Render();
	}
	void Layana_Awaken_Meteor_Projectile::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_Awaken_Meteor_Projectile::OnCollisionStay(Collider2D* other)
	{
	}
	void Layana_Awaken_Meteor_Projectile::OnCollisionExit(Collider2D* other)
	{
	}

	void Layana_Awaken_Meteor_Projectile::Compelete_Pierce()
	{
		_bulletoff = true;
		this->SetState(eState::Paused);
	}
}