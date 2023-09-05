#include "Monster_GreenTree.h"

namespace jk
{
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
		tr = GetComponent<Transform>();
		_pos = tr->GetPosition();
		_first_place = _pos;

		
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

		{
			Player_Hp = new Player_Hp_Bar;
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Monster, Player_Hp);
			Player_Hp->SetName(L"player_hp_bar");
			Transform* hp_tr = Player_Hp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(_pos.x, _pos.y + 50, _pos.z - 1));
			hp_tr->SetScale(_MaxHp, 10, 0);
			Player_Hp->Set_Max_Hp(_MaxHp);
			Player_Hp->Set_Current_Hp(_MaxHp);
			Player_Hp->SetState(eState::Active);
		}
		;
		{
			_Hit_Effect = new Monster_Hit_Effect;
			_Hit_Effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Hit_Effect);
			_Hit_Effect->SetState(eState::Paused);
		}

		{
			_Death_Effect = new Monster_Death_Effect;
			_Death_Effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Death_Effect);
			_Death_Effect->SetState(eState::Paused);
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

		if (_player_groundcheck == true)
			_AttackSign_place = Vector3(_playerGRpos.x, _playerGRpos.y - 20, _playerGRpos.z - 1);

		Transform* hp_tr = Player_Hp->GetComponent<Transform>();
		hp_tr->SetPosition(Vector3(_pos.x - (_MaxHp - _CurrenHp), _pos.y + 50, _pos.z - 1));
		hp_tr->SetScale(_CurrenHp, 10, 0);

		if (_CurrenHp <= 0)
			this->SetState(eState::Paused);

		{
			Transform* _Hit_Effect_TR = _Hit_Effect->GetComponent<Transform>();
			if (mDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(_pos.x + 15, _pos.y, _pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(_pos.x - 15, _pos.y, _pos.z - 1));
		}
		{
			Transform* _Effect_TR = _Death_Effect->GetComponent<Transform>();
			_Effect_TR->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
		}


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
		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			if (!(_state == Monster_GreenTree_State::Idle))
				return;

			if (!(_state == Monster_GreenTree_State::Attack || _state == Monster_GreenTree_State::Attack_Ready))
			{
				_state = Monster_GreenTree_State::Hit;
				if (mDir == 1)
				{
					at->PlayAnimation(L"GreenTreeHit", false);
					_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
					tr->SetPosition(_pos);
					Player_Hp->_HitOn = true;
					Player_Hp->SetHitDamage(10);
					_CurrenHp = _CurrenHp - 10;

					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(1);
					_Hit_Effect->SetState(eState::Active);
				}
				if (mDir == -1)
				{
					at->PlayAnimation(L"GreenTreeHitR", false);
					_rigidbody->SetVelocity(Vector2(70.f, 0.f));
					tr->SetPosition(_pos);
					_CurrenHp = _CurrenHp - 10;
					Player_Hp->_HitOn = true;
					Player_Hp->SetHitDamage(10);

					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(-1);
					_Hit_Effect->SetState(eState::Active);
				}
				if (_CurrenHp <= 0)
				{
					_state = Monster_GreenTree_State::Dead;
					_Hit_Effect->_effect_animation = true;
					_Death_Effect->SetState(eState::Active);
				}
			}
		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			if (!(_state == Monster_GreenTree_State::Attack || _state == Monster_GreenTree_State::Attack_Ready))
			{
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;

					_state = Monster_GreenTree_State::Hit;
					if (mDir == 1)
					{
						at->PlayAnimation(L"GreenTreeHit", false);
						_rigidbody->SetVelocity(Vector2(-70.f, 0.f));
						tr->SetPosition(_pos);
						Player_Hp->_HitOn = true;
						Player_Hp->SetHitDamage(25);
						_CurrenHp = _CurrenHp - 25;

						_Hit_Effect->_effect_animation = true;
						_Hit_Effect->SetDirection(1);
						_Hit_Effect->SetState(eState::Active);
					}
					if (mDir == -1)
					{
						at->PlayAnimation(L"GreenTreeHitR", false);
						_rigidbody->SetVelocity(Vector2(70.f, 0.f));
						tr->SetPosition(_pos);
						_CurrenHp = _CurrenHp - 25;
						Player_Hp->_HitOn = true;
						Player_Hp->SetHitDamage(25);

						_Hit_Effect->_effect_animation = true;
						_Hit_Effect->SetDirection(-1);
						_Hit_Effect->SetState(eState::Active);
					}
					if (_CurrenHp <= 0)
					{
						_state = Monster_GreenTree_State::Dead;
						_Hit_Effect->_effect_animation = true;
					}
					_bulletcheck++;
				}
			}
		}
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
		}

		if (Sky_Ground* mGround = dynamic_cast<Sky_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();
				_rigidbody->ClearVelocity();
			}
		}
	}
	void Monster_GreenTree::OnCollisionExit(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			_rigidbody->SetGround(false);
			_Ground_check = false;
		}
		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			_rigidbody->SetGround(false);
			_Ground_check = false;
		}
		if (Sky_Ground* mGround = dynamic_cast<Sky_Ground*>(other->GetOwner()))
		{
			_rigidbody->SetGround(false);
			_Ground_check = false;
		}
		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			_bulletcheck = 0;
		}
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
			{
				at->PlayAnimation(L"GreenTreeAttack_Ready", false);
				_attackdir = 1;
			}
			else
			{
				at->PlayAnimation(L"GreenTreeAttack_ReadyR", false);
				_attackdir = -1;
			}
			_Attack_place = _AttackSign_place;
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
			if (_attacktime > 0.2)
			{
				Transform* bullet_tr = GroundAttack->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(_Attack_place));
				GroundAttack->SetState(eState::Active);

				_state = Monster_GreenTree_State::Attack;
				if (_attackdir == 1)
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
		_attacktime += Time::DeltaTime();
		if (_attacktime >= 0.5)
		{
			_state = Monster_GreenTree_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"GreenTreeIdle", true);
			else
				at->PlayAnimation(L"GreenTreeIdleR", true);
			_attacktime = 0;
		}
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