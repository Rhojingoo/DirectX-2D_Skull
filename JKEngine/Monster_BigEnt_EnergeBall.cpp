#include "Monster_BigEnt_EnergeBall.h"


namespace jk
{
	Monster_BigEnt_EnergeBall::Monster_BigEnt_EnergeBall()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Monster_BigEnt_EnergeBall::~Monster_BigEnt_EnergeBall()
	{
	}
	void Monster_BigEnt_EnergeBall::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_collider->SetType(eColliderType::Circle);
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);
		tr = this->GetComponent<Transform>();

			
		{
			_EnergeBall_Bomb = new BigEnt_EnergeBall_Bomb;
			_EnergeBall_Bomb->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _EnergeBall_Bomb);
			Transform* bullet_tr = _EnergeBall_Bomb->GetComponent<Transform>();
			bullet_tr->SetPosition(tr->GetPosition());
			_EnergeBall_Bomb->SetState(eState::Paused);
		}


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Bullet\\Energe_Ball", this);
		at->PlayAnimation(L"BulletEnerge_Ball", true);
		GameObject::Initialize();
	}
	void Monster_BigEnt_EnergeBall::Update()
	{
		if (_bullet_Life == true)
		{
			_attackatime += static_cast<float>(Time::DeltaTime());
			if (_attackatime >= 3)
			{
				Transform* bullet_tr = _EnergeBall_Bomb->GetComponent<Transform>();
				bullet_tr->SetPosition(tr->GetPosition().x, tr->GetPosition().y, tr->GetPosition().z-1);
				_EnergeBall_Bomb->SetState(eState::Active);
				this->SetState(eState::Paused);
				_attackatime = 0;
			}
			_bullet_Life = false;
		}
		GameObject::Update();
	}
	void Monster_BigEnt_EnergeBall::LateUpdate()
	{
		_collider->SetSize(Vector2(1.f, 1.f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
	
		GameObject::LateUpdate();
	}

	void Monster_BigEnt_EnergeBall::Render()
	{
		GameObject::Render();
	}

	void Monster_BigEnt_EnergeBall::OnCollisionEnter(Collider2D* other)
	{
		if (Player* mGround = dynamic_cast<Player*>(other->GetOwner()))
		{
			Transform* bullet_tr = _EnergeBall_Bomb->GetComponent<Transform>();
			bullet_tr->SetPosition(tr->GetPosition().x, tr->GetPosition().y, tr->GetPosition().z - 1);
			_EnergeBall_Bomb->SetState(eState::Active);
			this->SetState(eState::Paused);
			_bullet_Life = false;
		}


		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			Transform* bullet_tr = _EnergeBall_Bomb->GetComponent<Transform>();
			bullet_tr->SetPosition(tr->GetPosition().x, tr->GetPosition().y, tr->GetPosition().z - 1);
			_EnergeBall_Bomb->SetState(eState::Active);
			this->SetState(eState::Paused);
			_bullet_Life = false;
		}

		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			Transform* bullet_tr = _EnergeBall_Bomb->GetComponent<Transform>();
			bullet_tr->SetPosition(tr->GetPosition().x, tr->GetPosition().y, tr->GetPosition().z - 1);
			_EnergeBall_Bomb->SetState(eState::Active);
			this->SetState(eState::Paused);
			_bullet_Life = false;
		}

		if (Sky_Ground* mGround = dynamic_cast<Sky_Ground*>(other->GetOwner()))
		{
			Transform* bullet_tr = _EnergeBall_Bomb->GetComponent<Transform>();
			bullet_tr->SetPosition(tr->GetPosition().x, tr->GetPosition().y, tr->GetPosition().z - 1);
			_EnergeBall_Bomb->SetState(eState::Active);
			this->SetState(eState::Paused);
			_bullet_Life = false;
		}

		if (Ground_and_Wall* mGround = dynamic_cast<Ground_and_Wall*>(other->GetOwner()))
		{
			Transform* bullet_tr = _EnergeBall_Bomb->GetComponent<Transform>();
			bullet_tr->SetPosition(tr->GetPosition().x, tr->GetPosition().y, tr->GetPosition().z - 1);
			_EnergeBall_Bomb->SetState(eState::Active);
			this->SetState(eState::Paused);
			_bullet_Life = false;
		}
	}
	void Monster_BigEnt_EnergeBall::OnCollisionStay(Collider2D* other)
	{
	}
	void Monster_BigEnt_EnergeBall::OnCollisionExit(Collider2D* other)
	{
	}
	void Monster_BigEnt_EnergeBall::complete()
	{
	}
}