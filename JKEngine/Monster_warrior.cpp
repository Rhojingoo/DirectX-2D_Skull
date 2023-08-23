#include "Monster_warrior.h"


namespace jk
{
	int Monster_warrior::mDir = 1;

	Monster_warrior::Monster_warrior()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Monster_warrior::~Monster_warrior()
	{
	}


	void Monster_warrior::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_tr = GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Dead", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Walk", this);
																
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Dead", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Warrior\\Walk", this, 1);

		//bind ºÎºÐ
		at->CompleteEvent(L"WarriorAttack") = std::bind(&Monster_warrior::complete_attack, this);
		at->CompleteEvent(L"WarriorAttackR") = std::bind(&Monster_warrior::complete_attack, this);

		at->PlayAnimation(L"WarriorIdle", true);


		{
			Hit_Box = new HitBox_Monster();
			Hit_Box->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetState(eState::Active);
		}



		GameObject::Initialize();
	}
	void Monster_warrior::Update()
	{
		_tr = GetComponent<Transform>();
		_pos = _tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_distance = _playerpos.x - _pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;


		switch (_state)
		{
		case jk::Monster_warrior::Monster_warrior_State::Idle:
			idle();
			break;

		case jk::Monster_warrior::Monster_warrior_State::Attack:
			attack();
			break;

		case jk::Monster_warrior::Monster_warrior_State::Dead:
			dead();
			break;

		case jk::Monster_warrior::Monster_warrior_State::Hit:
			hit();
			break;

		case jk::Monster_warrior::Monster_warrior_State::Walk:
			walk();
			break;

		default:
			break;
		}


		_tr->SetPosition(_pos);
		GameObject::Update();
	}
	void Monster_warrior::LateUpdate()
	{
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_attack_Col == true)
		{
			Hit_Box->SetSize(Vector2(30.f, 60.f));
			Hit_Box->SetCenter(Vector3(100.f, 100.f, -250.f));

			Hit_Box->SetState(eState::Active);
			if (mDir == 1)
				HitBox_TR->SetPosition(Vector3(_pos.x + 30, _pos.y-5, _pos.z));
			else
				HitBox_TR->SetPosition(Vector3(_pos.x - 30, _pos.y-5, _pos.z));
		}
		else
		{
			Hit_Box->SetState(eState::Paused);
		}

		_collider->SetSize(Vector2(0.35f, 0.75f));
		_collider->SetCenter(Vector2(1.f, -6.5f));


		GameObject::LateUpdate();
	}
	void Monster_warrior::Render()
	{
		GameObject::Render();
	}


	void Monster_warrior::OnCollisionEnter(Collider2D* other)
	{	
	}
	void Monster_warrior::OnCollisionStay(Collider2D* other)
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
	void Monster_warrior::OnCollisionExit(Collider2D* other)
	{
	}


	void Monster_warrior::idle()
	{
		_time += Time::DeltaTime();

		if (_time > 2.f)
		{
			if ((_distance >= 75 || _distance <= -75))
			{					
				{
					_state = Monster_warrior_State::Walk;
					if (mDir == 1)
					{
						at->PlayAnimation(L"WarriorWalk", true);					
					}
					else
					{
						at->PlayAnimation(L"WarriorWalkR", true);							
					}					
				}
			}
			if (_distance > -60 && _distance < 60)
			{
				_state = Monster_warrior_State::Attack;
				if (mDir == 1)
					at->PlayAnimation(L"WarriorAttack", true);
				else
					at->PlayAnimation(L"WarriorAttackR", true);
			}
		}
	}


	void Monster_warrior::attack()
	{
		_attack_Col = true;
	}


	void Monster_warrior::dead()
	{
	}


	void Monster_warrior::hit()
	{
	}


	void Monster_warrior::walk()
	{
		if (_distance > -50 && _distance <50)
		{
			_state = Monster_warrior_State::Attack;
			if (mDir == 1)			
				at->PlayAnimation(L"WarriorAttack", true);			
			else			
				at->PlayAnimation(L"WarriorAttackR", true);
		}
		else
		{
			if (_distance >= 0.f)			
				_pos.x += 150.f * Time::DeltaTime();			
			else			
				_pos.x -= 150.f * Time::DeltaTime();			
			_tr->SetPosition(_pos);
		}
	}


	void Monster_warrior::complete_attack()
	{
		_attack_Col = false;
		_state = Monster_warrior_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"WarriorIdle", true);
		else
			at->PlayAnimation(L"WarriorIdleR", true);

		_time = 0;
	}
}