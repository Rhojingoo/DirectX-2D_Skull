#include "Monster_Hammer.h"

namespace jk
{
	int Monster_Hammer::mDir = 1;
	bool Monster_Hammer::_switch = false;


	Monster_Hammer::Monster_Hammer()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Monster_Hammer::~Monster_Hammer()
	{
	}


	void Monster_Hammer::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);
		tr = GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Dead", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Tackle_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Tackle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Tackle_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Walk", this);

		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Dead", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Tackle_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Tackle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Tackle_End", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Hammer\\Walk", this, 1);

		//bind ºÎºÐ
		at->CompleteEvent(L"HammerAttack") = std::bind(&Monster_Hammer::Complete_attack, this);
		at->CompleteEvent(L"HammerAttackR") = std::bind(&Monster_Hammer::Complete_attack, this);

		at->PlayAnimation(L"HammerIdle", true);

		{
			Hit_Box = new HitBox_Monster();
			Hit_Box->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetState(eState::Active); 
		}
		{
			Tackle_Flash = new Monster_Tackle_Flash_Effect();
			Tackle_Flash->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Tackle_Flash);
			Effect_tr = Tackle_Flash->GetComponent<Transform>();
			Effect_tr->SetPosition(tr->GetPosition());
			Tackle_Flash->SetState(eState::Paused);			
		}



		GameObject::Initialize();
	}
	void Monster_Hammer::Update()
	{
		tr = GetComponent<Transform>();
		_pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		SetDirection();
		SetEffect_pos();




		switch (_state)
		{
		case jk::Monster_Hammer::Monster_Hammer_State::Idle:idle();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Attack:attack();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Dead:dead();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Tackle_Ready:
			tackle_ready();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Tackle:
			tackle();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Tackle_End:
			tackle_end();
			break;

		case jk::Monster_Hammer::Monster_Hammer_State::Walk:walk();
			break;

		default:
			break;
		}

		tr->SetPosition(_pos);
		Effect_tr->SetPosition(_Effect_pos);
		GameObject::Update();
	}
	void Monster_Hammer::LateUpdate()
	{
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_attack_Col == true)
		{
			Hit_Box->SetSize(Vector2(100.f, 100.f));
			Hit_Box->SetCenter(Vector3(100.f, 100.f,-250.f));

			Hit_Box->SetState(eState::Active);
			if (mDir == 1)
				HitBox_TR->SetPosition(Vector3(_pos.x + 50, _pos.y, _pos.z));
			else
				HitBox_TR->SetPosition(Vector3(_pos.x - 50, _pos.y, _pos.z));
		}
		else
		{
			Hit_Box->SetState(eState::Paused);
		}


		_collider->SetSize(Vector2(0.65f, 0.75f));
		_collider->SetCenter(Vector2(1.f, -8.5f));
		GameObject::LateUpdate();
	}
	void Monster_Hammer::Render()
	{
		GameObject::Render();
	}



	void Monster_Hammer::OnCollisionEnter(Collider2D* other)
	{		
	}
	void Monster_Hammer::OnCollisionStay(Collider2D* other)
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
	void Monster_Hammer::OnCollisionExit(Collider2D* other)
	{
	}



	void Monster_Hammer::idle()
	{
		_time += Time::DeltaTime();
		if (_time > 1.5f)
		{
			if (_AttackCheck == 0)
			{
				if ((_distance >= 90 || _distance <= -90))
				{
					_state = Monster_Hammer_State::Walk;
					if (mDir == 1)
						at->PlayAnimation(L"HammerWalk", true);
					else
						at->PlayAnimation(L"HammerWalkR", true);
				}
				if (_distance > -80 && _distance < 80)
				{

					_state = Monster_Hammer_State::Attack;
					if (mDir == 1)
						at->PlayAnimation(L"HammerAttack", true);
					else
						at->PlayAnimation(L"HammerAttackR", true);					
				}
			}

			if (_AttackCheck == 1)
			{
				if ((_distance >= 125 || _distance <= -125))
				{
					_state = Monster_Hammer_State::Walk;
					if (mDir == 1)
						at->PlayAnimation(L"HammerWalk", true);
					else
						at->PlayAnimation(L"HammerWalkR", true);
				}
				else
				{
					_state = Monster_Hammer_State::Tackle_Ready;
					if (mDir == 1)			
						at->PlayAnimation(L"HammerTackle_Ready", true);				
					else				
						at->PlayAnimation(L"HammerTackle_ReadyR", true);				
				
				}			
			}			
		}		
	}


	void Monster_Hammer::attack()
	{
		_attack_Col = true;
	}


	void Monster_Hammer::tackle_ready()
	{
		_attacktime += Time::DeltaTime();
		if (_attacktime > 2.f)
		{
			_state = Monster_Hammer_State::Tackle;
			if (mDir == 1)
			{
				at->PlayAnimation(L"HammerTackle", true);
				_rigidbody->SetVelocity(Vector2(350.f, 0.f));
				Tackle_Flash->_effect_animation = true;
				Tackle_Flash->SetDirection(1);
			}
			else
			{
				at->PlayAnimation(L"HammerTackleR", true);
				_rigidbody->SetVelocity(Vector2(-350.f, 0.f));
				Tackle_Flash->_effect_animation = true;
				Tackle_Flash->SetDirection(-1);
			}
			_attacktime = 0;	
			Tackle_Flash->SetState(eState::Active);
		}
	}


	void Monster_Hammer::tackle()
	{
		_rigidbody->ClearVelocityY();
		if (mDir == 1 && _velocity.x <= 285.0)
		{
			_state = Monster_Hammer_State::Tackle_End;
			at->PlayAnimation(L"HammerTackle_End", false);
			_rigidbody->ClearVelocityX();
			Tackle_Flash->SetState(eState::Paused);
		}
		else if (mDir == -1 && _velocity.x >= -285.0)
		{
			_state = Monster_Hammer_State::Tackle_End;
			at->PlayAnimation(L"HammerTackle_EndR", false);
			_rigidbody->ClearVelocityX();
			Tackle_Flash->SetState(eState::Paused);
		}		
	}


	void Monster_Hammer::tackle_end()
	{
		_attacktime += Time::DeltaTime();
		if (_attacktime > 0.7f)
		{
			_state = Monster_Hammer_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"HammerIdle", true);
			else
				at->PlayAnimation(L"HammerIdleR", true);

			_time = 0;
			_AttackCheck = 0;
			_attacktime = 0;
		}
	}


	void Monster_Hammer::walk()
	{
		if (_distance >= 0.f)
			_pos.x += 150.f * Time::DeltaTime();
		else
			_pos.x -= 150.f * Time::DeltaTime();

		if (_AttackCheck == 0)
		{
			if (_distance > -80 && _distance < 80)
			{
				_state = Monster_Hammer_State::Attack;
				if (mDir == 1)
					at->PlayAnimation(L"HammerAttack", true);
				else
					at->PlayAnimation(L"HammerAttackR", true);
			}
		}
		if (_AttackCheck == 1)
		{
			if ((_distance >= 125 || _distance <= -125))
			{
				_state = Monster_Hammer_State::Tackle_Ready;
				if (mDir == 1)
					at->PlayAnimation(L"HammerTackle_Ready", true);
				else
					at->PlayAnimation(L"HammerTackle_ReadyR", true);
			}
		}			
		tr->SetPosition(_pos);
	}


	void Monster_Hammer::dead()
	{
	}


	void Monster_Hammer::Complete_attack()
	{
		_attack_Col = false;
		_state = Monster_Hammer_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"HammerIdle", true);
		else
			at->PlayAnimation(L"HammerIdleR", true);

		_time = 0;
		_AttackCheck++;
	}
	void Monster_Hammer::SetDirection()
	{
		_distance = _playerpos.x - _pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;
	}
	void Monster_Hammer::SetEffect_pos()
	{
		if (mDir == 1)
		{
			_Effect_pos.x = _pos.x - 50;
			_Effect_pos.y = _pos.y;
			_Effect_pos.z = _pos.z - 1;
		}
		else
		{
			_Effect_pos.x = _pos.x + 50;
			_Effect_pos.y = _pos.y;
			_Effect_pos.z = _pos.z - 1;
		}
	}
}