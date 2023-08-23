#include "Monster_BigEnt.h"

namespace jk
{
	int Monster_BigEnt::mDir = 1;

	Monster_BigEnt::Monster_BigEnt()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Monster_BigEnt::~Monster_BigEnt()
	{
	}
	void Monster_BigEnt::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Attack_Melee_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Attack_Melee", this);
		
		
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Attack_Range_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Attack_Range", this);


		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Dead", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Idle", this);

		at->CompleteEvent(L"GiganticEntAttack_Melee") = std::bind(&Monster_BigEnt::attack_idle, this);
		at->CompleteEvent(L"GiganticEntAttack_Range") = std::bind(&Monster_BigEnt::attack_idle, this);

		at->PlayAnimation(L"GiganticEntIdle", true);
		

		{
			Hit_Box = new HitBox_Monster();
			Hit_Box->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetState(eState::Active);
		}
		{
			for (int i = 0; i < 8; i++)
			{
				Energe_Ball[i] = new Monster_BigEnt_EnergeBall;
				Energe_Ball[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Bullet, Energe_Ball[i]);
				Transform* bullet_tr = Energe_Ball[i]->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));				
				Energe_Ball[i]->SetState(eState::Paused);
				set_energeball_Vellocity();
			}
		}
		{
			Attack_Stamp =  new Monster_GiganticEnt_Stamp;
			Attack_Stamp->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Attack_Stamp);
			Transform* bullet_tr = Attack_Stamp->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));			
			Attack_Stamp->SetState(eState::Paused);
		}


		GameObject::Initialize();
	}
	void Monster_BigEnt::Update()
	{
		tr = GetComponent<Transform>();
		_pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_distance = _playerpos.x - _pos.x; 
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;

		switch (_state)
		{
		case jk::Monster_BigEnt::Monster_BigEnt_State::Idle:idle();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::AttackA_Ready:
			attackA_ready();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::AttackA:
			attackA();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::AttackA_End:
			attackA_end();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::AttackB_Ready:
			attackB_ready();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::AttackB:
			attackB();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::Dead:dead();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::Hit:hit();
			break;

		case jk::Monster_BigEnt::Monster_BigEnt_State::Walk:walk();
			break;

		default:
			break;
		}
		GameObject::Update();
	}
	void Monster_BigEnt::LateUpdate()
	{
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_attack_Col == true)
		{
			Hit_Box->SetSize(Vector2(300.f, 30.f));
			HitBox_TR->SetPosition(Vector3(_pos.x, _pos.y-50, _pos.z));
			Hit_Box->SetState(eState::Active);
		}
		else
		{
			Hit_Box->SetState(eState::Paused);
		}


		_collider->SetSize(Vector2(0.5f, 0.9f));
		_collider->SetCenter(Vector2(1.f, 0.1f));
		GameObject::LateUpdate();
	}
	void Monster_BigEnt::Render()
	{
		GameObject::Render();
	}
	void Monster_BigEnt::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster_BigEnt::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();
				_rigidbody->ClearVelocity();
			}
			else
			{
			}
		}
	}
	void Monster_BigEnt::OnCollisionExit(Collider2D* other)
	{
	}

	void Monster_BigEnt::idle()
	{
		_time += Time::DeltaTime();


		if ((_distance >= 200) || (_distance <= -200))
		{
			_state = Monster_BigEnt_State::AttackA_Ready;
			at->PlayAnimation(L"GiganticEntAttack_Melee_Ready", false);
		}

		if (_time > 3.f)
		{
			if (_choiceattack == 0)
			{				
				_state = Monster_BigEnt_State::AttackA_Ready;
				at->PlayAnimation(L"GiganticEntAttack_Melee_Ready", false);
			}
			else if (_choiceattack == 1)
			{				
				_state = Monster_BigEnt_State::AttackB_Ready;
				at->PlayAnimation(L"GiganticEntAttack_Range_Ready", false);			
			}
		}
	}


	void Monster_BigEnt::attackA_ready()
	{
		_attack_time += Time::DeltaTime();
		if (_attack_time > 2.0)
		{
			_state = Monster_BigEnt_State::AttackA;
			at->PlayAnimation(L"GiganticEntAttack_Melee", true);		
			_attack_time = 0;
		}
	}
	void Monster_BigEnt::attackA()
	{
		Transform* bullet_tr = Attack_Stamp->GetComponent<Transform>();
		bullet_tr->SetPosition(Vector3(_pos.x, _pos.y-25, _pos.z - 1));
		Attack_Stamp->SetState(eState::Active);
		_attack_Col = true;
	}
	void Monster_BigEnt::attackA_end()
	{
	}


	void Monster_BigEnt::attackB_ready()
	{
		set_energeball_pos();
		energeball_attack();
		_state = Monster_BigEnt_State::AttackB;			
		at->PlayAnimation(L"GiganticEntAttack_Range", false);		
	}
	void Monster_BigEnt::attackB()
	{
		_attack_time += Time::DeltaTime();
		if (_attack_time > 2.0)
		{
			_state = Monster_BigEnt_State::Idle;
			at->PlayAnimation(L"GiganticEntIdle", true);
			_attack_time = 0;
			_time = 0;
			_choiceattack = 1;
		}
	}


	void Monster_BigEnt::dead()
	{
	}
	void Monster_BigEnt::hit()
	{
	}
	void Monster_BigEnt::walk()
	{
	}


	void Monster_BigEnt::attack_idle()
	{
		_attack_Col = false;
		_state = Monster_BigEnt_State::Idle;
		at->PlayAnimation(L"GiganticEntIdle", true);
		_time = 0;
		_choiceattack = 0;
	}


	void Monster_BigEnt::set_energeball_pos()
	{
		for (int i = 0; i < 8; i++)
		{
			Transform* bullet_tr = Energe_Ball[i]->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
		}
	}
	void Monster_BigEnt::energeball_attack()
	{
		for (int i = 0; i < 8; i++)
		{
			Transform* bullet_tr = Energe_Ball[i]->GetComponent<Transform>();
			RigidBody* bullet_rg = Energe_Ball[i]->GetComponent<RigidBody>();
			Energe_Ball[i]->_bullet_Life = true;
			Energe_Ball[i]->SetState(eState::Active);
			bullet_rg->SetGravity(true);
			bullet_rg->SetFriction(true);
			bullet_rg->SetVelocity(basic_pos[i]);
		}
	}

	void Monster_BigEnt::set_energeball_Vellocity()
	{
		basic_pos[0] = Vector2(0.f, 150.f);
		basic_pos[1] = Vector2(110.f, 110.f);
		basic_pos[2] = Vector2(150.f, 0.f);
		basic_pos[3] = Vector2(110.f, -110.f);
		basic_pos[4] = Vector2(0.f, -150.f);
		basic_pos[5] = Vector2(-110.f, -110.f);
		basic_pos[6] = Vector2(-150.f, 0.f);
		basic_pos[7] = Vector2(-110.f, 110.f);
	}
}