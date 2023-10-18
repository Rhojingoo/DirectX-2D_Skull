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

		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\Hit_Flame_Short.wav", "Hit_Flame_Short");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\Arson_Explosion.wav", "Arson_Explosion");


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Bullet\\Fireball_Projectile", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Bullet\\Fireball_Projectile", this, 1);


		Bullet_Effect = new Fireball_Projectile_Hit;
		Bullet_Effect->Initialize();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(eLayerType::Effect, Bullet_Effect);
		Transform* EffectTR = Bullet_Effect->GetComponent<Transform>();
		EffectTR->SetPosition(tr->GetPosition());
		Bullet_Effect->SetState(eState::Paused);



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
			_Lifetime += static_cast<float>(Time::DeltaTime());
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
		_collider->SetSize(Vector2(0.85f, 0.5f));
		_collider->SetCenter(Vector2(0.0f, -0.07f));
		GameObject::LateUpdate();
	}
	void Mage_FireBall::Render()
	{
		GameObject::Render();
	}
	void Mage_FireBall::OnCollisionEnter(Collider2D* other)
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
				as->Play("Hit_Flame_Short");
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
				as->Play("Hit_Flame_Short");
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
				as->Play("Hit_Flame_Short");
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
				as->Play("Hit_Flame_Short");
				this->SetState(eState::Paused);
				_bullet_On = false;
				_Lifetime = 0;
			}
		}
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