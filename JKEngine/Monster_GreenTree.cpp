#include "Monster_GreenTree.h"

namespace jk
{
	int Monster_GreenTree::mDir = 1;
	bool Monster_GreenTree::_switch = false;

	Monster_GreenTree::Monster_GreenTree()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Monster_GreenTree::~Monster_GreenTree()
	{
	}
	void Monster_GreenTree::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Attack_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Walk", this);


		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Attack_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GreenTree\\Walk", this, 1);

		at->CompleteEvent(L"GreenTreeAttack") = std::bind(&Monster_GreenTree::Complete_Attack, this);
		at->CompleteEvent(L"GreenTreeAttackR") = std::bind(&Monster_GreenTree::Complete_Attack, this);
				
		_first_place = _pos;
		at->PlayAnimation(L"GreenTreeIdle", true);


		{
			GroundAttack_Sign = new Monster_GroundAttack_Sign;
			GroundAttack_Sign->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, GroundAttack_Sign);
			Transform* bullet_tr = GroundAttack_Sign->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			GroundAttack_Sign->SetState(eState::Paused);
		}
		{
			GroundAttack = new Monster_Ent_GroundAttack;
			GroundAttack->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, GroundAttack);
			Transform* bullet_tr = GroundAttack->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			GroundAttack->SetState(eState::Paused);
		}
		
		GameObject::Initialize();
	}
	
	void Monster_GreenTree::Update()
	{
		tr = GetComponent<Transform>();
		_pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_walkdistance = _first_place.x - _pos.x;
		if (_walkdistance >= 0.f)
			_walkdir = 1;
		else
			_walkdir = -1;

		_distance = _playerpos.x - _pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;

		switch (_state)
		{
		case jk::Monster_GreenTree::Monster_GreenTree_State::Idle:
			idle();
			break;

		case jk::Monster_GreenTree::Monster_GreenTree_State::Attack_Ready:
			attack_ready();
			break;

		case jk::Monster_GreenTree::Monster_GreenTree_State::Attack:
			attack();
			break;

		case jk::Monster_GreenTree::Monster_GreenTree_State::Attack_End:
			attack_end();
			break;

		case jk::Monster_GreenTree::Monster_GreenTree_State::Dead:
			dead();
			break;

		case jk::Monster_GreenTree::Monster_GreenTree_State::Hit:
			hit();
			break;

		case jk::Monster_GreenTree::Monster_GreenTree_State::WalkR:
			walk_R();
			break;

		case jk::Monster_GreenTree::Monster_GreenTree_State::WalkL:
			walk_L();
			break;

		default:
			break;
		}
		tr->SetPosition(_pos);
		GameObject::Update();
	}
	void Monster_GreenTree::LateUpdate()
	{
		_collider->SetSize(Vector2(0.5f, 0.8f));
		_collider->SetCenter(Vector2(1.f, -5.5f));
		GameObject::LateUpdate();
	}
	void Monster_GreenTree::Render()
	{
		GameObject::Render();
	}
	void Monster_GreenTree::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster_GreenTree::OnCollisionStay(Collider2D* other)
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

		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
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
	void Monster_GreenTree::OnCollisionExit(Collider2D* other)
	{
	}


	void Monster_GreenTree::idle()
	{
		_time += Time::DeltaTime();

		if ((_distance <= 250) && (_distance >= -250))		
			_choiceattack = 0;			
		
		else
			_choiceattack = 1;

		if (_choiceattack == 0)
		{
			if (_time >= 3.f)
				_attackcheck = true;
		}

		if ((_choiceattack == 0)&& (_attackcheck ==true))
		{
			_state = Monster_GreenTree_State::Attack_Ready;
			if (mDir == 1)
				at->PlayAnimation(L"GreenTreeAttack_Ready", false);
			else
				at->PlayAnimation(L"GreenTreeAttack_ReadyR", false);

			_Attack_place = Vector3(_playerpos.x, _playerpos.y - 20, _playerpos.z - 1);
			Transform* bullet_tr = GroundAttack_Sign->GetComponent<Transform>();
			bullet_tr->SetPosition(_Attack_place);
			GroundAttack_Sign->_effect_end = true;
			GroundAttack_Sign->SetState(eState::Active);
		}

		if (_time > 5.f)
		{
			if (_walkdir == 1)
			{
				_state = Monster_GreenTree_State::WalkR;
				at->PlayAnimation(L"GreenTreeWalk", true);
			}
			else if (_walkdir == -1)
			{
				_state = Monster_GreenTree_State::WalkL;
				at->PlayAnimation(L"GreenTreeWalkR", true);
			}
		}
	}

	void Monster_GreenTree::attack_ready()
	{
	
		if (GroundAttack_Sign->_effect_end == false)
		{
			_attacktime += Time::DeltaTime();
			if (_attacktime > 0.5)
			{
				Transform* bullet_tr = GroundAttack->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(_Attack_place.x, _Attack_place.y, _Attack_place.z));
				GroundAttack->SetState(eState::Active);


				_state = Monster_GreenTree_State::Attack;
				if (mDir == 1)
					at->PlayAnimation(L"GreenTreeAttack", true);
				else
					at->PlayAnimation(L"GreenTreeAttackR", true);
				_attacktime = 0;
			}
		}
	}
	void Monster_GreenTree::attack()
	{
	}
	void Monster_GreenTree::attack_end()
	{
	}

	void Monster_GreenTree::dead()
	{
	}

	void Monster_GreenTree::hit()
	{
	}

	void Monster_GreenTree::walk_R()
	{
		if (_walkdistance > -50)
			_pos.x += 80.f * Time::DeltaTime();
		else
		{
			_state = Monster_GreenTree_State::Idle;
			at->PlayAnimation(L"GreenTreeIdle", true);
			_time = 0; _walkdir *= -1;
		}
	}
	void Monster_GreenTree::walk_L()
	{
		if (_walkdistance < 50)
			_pos.x -= 80.f * Time::DeltaTime();
		else
		{
			_state = Monster_GreenTree_State::Idle;
			at->PlayAnimation(L"GreenTreeIdleR", true);
			_time = 0; _walkdir *= -1;
		}
	}

	void Monster_GreenTree::Complete_Attack()
	{
		_state = Monster_GreenTree_State::Idle;
		if (mDir == 1)
		at->PlayAnimation(L"GreenTreeIdle", true);
		else
		at->PlayAnimation(L"GreenTreeIdleR", true);
		_time = 0; _attackcheck = false;
	}
	
}