#include "Knight_male_EnergeBall.h"


namespace jk
{
	Knight_male_EnergeBall::Knight_male_EnergeBall()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Knight_male_EnergeBall::~Knight_male_EnergeBall()
	{
	}
	void Knight_male_EnergeBall::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Bullet\\EnergeBall_Projectile", this);

		Bullet_Effect = new Kngiht_EnergyBall_Impact;
		Bullet_Effect->Initialize();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(eLayerType::Bullet, Bullet_Effect);
		Transform* EffectTR = Bullet_Effect->GetComponent<Transform>();
		EffectTR->SetPosition(tr->GetPosition());
		Bullet_Effect->SetState(eState::Paused);

		at->PlayAnimation(L"BulletEnergeBall_Projectile", true);
		GameObject::Initialize();

	}
	void Knight_male_EnergeBall::Update()
	{
		if (_BoomSwitch == true)
			EnergeBall_Boomb();
		GameObject::Update();
	}
	void Knight_male_EnergeBall::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Knight_male_EnergeBall::Render()
	{
		GameObject::Render();
	}
	void Knight_male_EnergeBall::OnCollisionEnter(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			_rigidbody->SetGround(true);
			_rigidbody->ClearVelocity();

			if (_EffectSwitch == true)
			{
				Transform* EffectTR = Bullet_Effect->GetComponent<Transform>();
				EffectTR->SetPosition(tr->GetPosition());
				Bullet_Effect->SetState(eState::Active);
				_EffectSwitch = false;
				_BoomSwitch = false;
				this->SetState(eState::Paused);
			}
			else
			{
				//_EffectSwitch = true;
			}
		}

		if (Player* mGround = dynamic_cast<Player*>(other->GetOwner()))
		{
			_rigidbody->SetGround(true);
			_rigidbody->ClearVelocity();

			if (_EffectSwitch == true)
			{
				Transform* EffectTR = Bullet_Effect->GetComponent<Transform>();
				EffectTR->SetPosition(tr->GetPosition());
				Bullet_Effect->SetState(eState::Active);
				_EffectSwitch = false;
				_BoomSwitch = false;
				this->SetState(eState::Paused);
			}
			else
			{
				//_EffectSwitch = true;
			}
		}
	}
	void Knight_male_EnergeBall::OnCollisionStay(Collider2D* other)
	{
	}
	void Knight_male_EnergeBall::OnCollisionExit(Collider2D* other)
	{
	}
	void Knight_male_EnergeBall::EnergeBall_Boomb()
	{
		Transform* EffectTR = Bullet_Effect->GetComponent<Transform>();
		EffectTR->SetPosition(tr->GetPosition());
		Bullet_Effect->SetState(eState::Active);
		//_EffectSwitch = false;
		_BoomSwitch = false;
		this->SetState(eState::Paused);
	}
}
