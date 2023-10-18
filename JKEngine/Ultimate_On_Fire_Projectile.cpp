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


		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\Hit_Flame_Short.wav", "Hit_Flame_Short");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\Arson_Explosion.wav", "Arson_Explosion");


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Bullet\\World_On_Fire_Projectile", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Bullet\\World_On_Fire_Projectile", this,1);
		//at->CompleteEvent(L"BulletWorld_On_Fire_Projectile") = std::bind(&Ultimate_On_Fire_Projectile::complete, this);


		Bullet_Effect = new Ultimate_On_Fire_Projectile_Hit;
		Bullet_Effect->Initialize();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(eLayerType::Effect, Bullet_Effect);
		Transform* EffectTR = Bullet_Effect->GetComponent<Transform>();
		EffectTR->SetPosition(tr->GetPosition());
		Bullet_Effect->SetState(eState::Paused);


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
			_Lifetime += static_cast<float>(Time::DeltaTime());
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
		_collider->SetSize(Vector2(0.75f, 0.5f));
		_collider->SetCenter(Vector2(0.0f, -0.07f));
		GameObject::LateUpdate();
	}
	void Ultimate_On_Fire_Projectile::Render()
	{
		GameObject::Render();
	}
	void Ultimate_On_Fire_Projectile::OnCollisionEnter(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			_rigidbody->SetGround(true);
			_rigidbody->ClearVelocity();
			{
				Transform* EffectTR = Bullet_Effect->GetComponent<Transform>();
				EffectTR->SetPosition(tr->GetPosition());
				if (_dir == 1)
					Bullet_Effect->SetDirection(1);
				else
					Bullet_Effect->SetDirection(-1);
				Bullet_Effect->SetState(eState::Active);
				as->Play("Arson_Explosion");
				this->SetState(eState::Paused);
				_bullet_On = false;
				_Lifetime = 0;
			}
		}

		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			_rigidbody->SetGround(true);
			_rigidbody->ClearVelocity();
			{
				Transform* EffectTR = Bullet_Effect->GetComponent<Transform>();
				EffectTR->SetPosition(tr->GetPosition());
				if (_dir == 1)
					Bullet_Effect->SetDirection(1);
				else
					Bullet_Effect->SetDirection(-1);
				Bullet_Effect->SetState(eState::Active);
				as->Play("Arson_Explosion");
				this->SetState(eState::Paused);
				_bullet_On = false;
				_Lifetime = 0;
			}
		}

		if (Ground_and_Wall* mGround = dynamic_cast<Ground_and_Wall*>(other->GetOwner()))
		{
			_rigidbody->SetGround(true);
			_rigidbody->ClearVelocity();
			{
				Transform* EffectTR = Bullet_Effect->GetComponent<Transform>();
				EffectTR->SetPosition(tr->GetPosition());
				if (_dir == 1)
					Bullet_Effect->SetDirection(1);
				else
					Bullet_Effect->SetDirection(-1);
				Bullet_Effect->SetState(eState::Active);
				as->Play("Arson_Explosion");
				this->SetState(eState::Paused);
				_bullet_On = false;
				_Lifetime = 0;
			}
		}


		if (Player* mGround = dynamic_cast<Player*>(other->GetOwner()))
		{
			_rigidbody->SetGround(true);
			_rigidbody->ClearVelocity();
			{
				Transform* EffectTR = Bullet_Effect->GetComponent<Transform>();
				EffectTR->SetPosition(tr->GetPosition());
				if (_dir == 1)
					Bullet_Effect->SetDirection(1);
				else
					Bullet_Effect->SetDirection(-1);
				Bullet_Effect->SetState(eState::Active);
				as->Play("Arson_Explosion");
				this->SetState(eState::Paused);
				_bullet_On = false;
				_Lifetime = 0;
			}
		}
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