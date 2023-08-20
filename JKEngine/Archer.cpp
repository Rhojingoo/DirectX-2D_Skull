#include "Archer.h"
#include <iostream>
#include <random>

namespace jk
{
	int Archer::mDir = 1;
	bool Archer::_switch = false;
	
	Archer::Archer()
		: _state()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Archer::~Archer()
	{
	}
	void Archer::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);
		_tr = GetComponent<Transform>();
		//_playerpos = oWner->GetComponent<Transform>()->GetPosition();

		//Skul_Head = new Skul_head();
		//Skul_Head->Initialize();
		//Scene* scene = SceneManager::GetActiveScene();
		//scene->AddGameObject(eLayerType::Item, Skul_Head);
		//Transform* tr_head = Skul_Head->GetComponent<Transform>();
		//tr_head->SetPosition(Vector3(pos.x, pos.y, -250.f));
		//Skul_Head->GetComponent<Transform>()->SetScale(Vector3(15.f, 13.f, 0.f));
		//Skul_Head->SetState(eState::Paused);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Attack_A", this,0);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Attack_B", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Attack_C", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\BackStep", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Die", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Groggy", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Intro", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Potion", this);
		

		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Attack_A", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Attack_B", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Attack_C", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\BackStep", this, 1);
		//at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Dash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Die", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Groggy", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Intro", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Potion", this, 1);



		//bind ºÎºÐ
		at->CompleteEvent(L"ArcherAttack_A") = std::bind(&Archer::choicecombo, this);
		at->CompleteEvent(L"ArcherAttack_AR") = std::bind(&Archer::choicecombo, this);
		at->CompleteEvent(L"ArcherAttack_B") = std::bind(&Archer::choicecombo, this);
		at->CompleteEvent(L"ArcherAttack_BR") = std::bind(&Archer::choicecombo, this);
		at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);
		at->CompleteEvent(L"ArcherAttack_CR") = std::bind(&Archer::choicecombo, this);		


		at->CompleteEvent(L"ArcherHit") = std::bind(&Archer::complete_hit, this);
		at->CompleteEvent(L"ArcherHitR") = std::bind(&Archer::complete_hit, this);
		//at->CompleteEvent(L"Knight_maleExplosion_Loop") = std::bind(&Knight_male::choicecombo, this);
		//at->CompleteEvent(L"Knight_maleExplosion_LoopR") = std::bind(&Knight_male::choicecombo, this);

		
		_archer_arrow = new Archer_Arrow;
		_archer_arrow->Initialize();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(eLayerType::Bullet, _archer_arrow);
		Transform* EffectTR = _archer_arrow->GetComponent<Transform>();
		EffectTR->SetPosition(_tr->GetPosition());
		_archer_arrow->SetState(eState::Paused);


		at->PlayAnimation(L"ArcherIdle", true);
		GameObject::Initialize();
	}
	void Archer::Update()
	{
		_tr = GetComponent<Transform>();
		pos = _tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_playerpos;
		_distance = _playerpos.x - pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;		

		switch (_state)
		{
		case jk::Archer::Archer_State::Idle:
			idle();
			break;

		case jk::Archer::Archer_State::BackDash:
			backdash();
			break;

		case jk::Archer::Archer_State::Die:
			die();
			break;

		case jk::Archer::Archer_State::Attack_A_Ready:
			attack_a_ready();
			break;

		case jk::Archer::Archer_State::Attack_A:
			attack_a();
			break;

		case jk::Archer::Archer_State::Attack_A_End:
			attack_a_end();
			break;

		case jk::Archer::Archer_State::Attack_B:
			attack_b();
			break;

		case jk::Archer::Archer_State::Attack_C:
			attack_c();
			break;

		case jk::Archer::Archer_State::Groggy:
			groggy();
			break;

		case jk::Archer::Archer_State::Hit:
			hit();
			break;

		case jk::Archer::Archer_State::Intro:
			intro();
			break;

		case jk::Archer::Archer_State::Potion:
			potion();
			break;

		default:
			break;
		}		
		_tr->SetPosition(Vector3(pos));
		GameObject::Update();
	}

	void Archer::LateUpdate()
	{
		_collider->SetSize(Vector2(0.5f, 0.5f));
		if(mDir ==1)
			_collider->SetCenter(Vector2(-20.0f, -25.f));
		else
			_collider->SetCenter(Vector2(20.0f, -25.f));

		GameObject::LateUpdate();
	}

	void Archer::Render()
	{
		GameObject::Render();
	}

	void Archer::OnCollisionEnter(Collider2D* other)
	{	
		if (Attack_HitBox* player = dynamic_cast<Attack_HitBox*>(other->GetOwner()))
		{
			if (_state == Archer_State::Hit || _state == Archer_State::BackDash)
				return;
	
				_state = Archer_State::Hit;
				if (mDir == 1)
				{
					at->PlayAnimation(L"ArcherHit", true);						
					_hit_switch = true;	_hit++;
					pos.x -= 50.0f * Time::DeltaTime();
					_tr->SetPosition(pos);
				}
				if (mDir == -1)
				{
					at->PlayAnimation(L"ArcherHitR", true);						
					_hit_switch = true;	_hit++;
					pos.x += 50.0f * Time::DeltaTime();
					_tr->SetPosition(pos);
				}						
				if (_hit >= 2)
					int a = 0;
		}
		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner())){}

		if (Skul_Spear* player = dynamic_cast<Skul_Spear*>(other->GetOwner())){}

		if (Skul_Wolf* player = dynamic_cast<Skul_Wolf*>(other->GetOwner())){}

	}
	void Archer::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();
				_rigidbody->ClearVelocity();				
		}
		
	}
	void Archer::OnCollisionExit(Collider2D* other)
	{
	}

	void Archer::idle()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(0, 1);
	

		_time += Time::DeltaTime();
	
		_hit_switch = false;

		if (_hit >= 3)
		{
			int a = 0;
			_state = Archer_State::BackDash;
			if (mDir == 1)
			{
				_Ground_check = false;
				_rigidbody->SetGround(false);
				at->PlayAnimation(L"ArcherBackStep", false);
				_rigidbody->SetVelocity(Vector2(-350.f, 200.f));
			}
			else
			{
				_Ground_check = false;
				_rigidbody->SetGround(false);
				at->PlayAnimation(L"ArcherBackStepR", false);
				_rigidbody->SetVelocity(Vector2(350.f, 200.f));
			}
			_hit = 0;
		}

		if ((_distance <= 80 && _distance >= -80))
		{
			_choicecombo = 2;
		}
		else
		{
			_choicecombo = distribution(gen);
		}
		if (_time > 3.f)
		{		
			_attack = true;
			choicecombo();				
		}
	}

	void Archer::backdash()
	{
		_rigidbody->ClearVelocityY();
		if (mDir == 1 && _velocity.x <= 200.f)
		{
			_state = Archer_State::Idle;
			at->PlayAnimation(L"ArcherIdle", true);
			_rigidbody->ClearVelocityX();
		}
		else if (mDir == -1 && _velocity.x >= -200.f)
		{
			_state = Archer_State::Idle;
			at->PlayAnimation(L"ArchereIdleR", true);
			_rigidbody->ClearVelocityX();
		}		
		_hit = 0;
	}

	void Archer::die()
	{
	}

	void Archer::attack_a_ready()
	{
		_attack_time += Time::DeltaTime();
		if (_attack_time > 0.7)
		{
			_state = Archer_State::Attack_A;
			_attack_time = 0;
		}
	}
	void Archer::attack_a()
	{
		Transform* EffectTR = _archer_arrow->GetComponent<Transform>();
		if (_attack_a == false)
		{			
			if (mDir == 1)
			{
				_archer_arrow->_bullet_animation= true;
				_archer_arrow->SetDirection(1);
				EffectTR->SetPosition(pos.x + 20, pos.y - 30, pos.z - 1);
			}
			else
			{
				_archer_arrow->_bullet_animation = true;
				_archer_arrow->SetDirection(-1);
				EffectTR->SetPosition(pos.x - 20, pos.y - 30, pos.z - 1);
			}
			_archer_arrow->SetState(eState::Active);
			_attack_a = true;
		}
		if (_attack_a == true)
		{
			Vector3 arrowpos = EffectTR->GetPosition();
			_attack_time += Time::DeltaTime();
			if (_attack_time < 2)
			{		
				if (mDir == 1)
					arrowpos.x += 450 * Time::DeltaTime();
				else
					arrowpos.x -= 450 * Time::DeltaTime();
				EffectTR->SetPosition(arrowpos);		
			}		
			else
			{
				_archer_arrow->SetState(eState::Paused);
				_state = Archer_State::Attack_A_End;
				_attack_time = 0;				
			}
		}	
	}

	void Archer::attack_a_end()
	{
		_attack_a = false;
		_attack = false;
		choicecombo();
	}

	void Archer::attack_b()
	{
		//_attackorder = 0;
		_attack = false;
	}

	void Archer::attack_c()
	{
		//_attackorder = 0;
		_attack = false;
	}

	void Archer::groggy()
	{
	}

	void Archer::hit()
	{	


		//if ( /*&& _velocity.x >= -240.0 */)
		//{
		//	_state = Archer_State::Idle;
		//	at->PlayAnimation(L"ArcherIdle", true);
		//	_rigidbody->ClearVelocityX();
		//}
		//else if (mDir == -1 /*&& _velocity.x <= 240.0*/)
		//{
		//	_state = Archer_State::Idle;
		//	at->PlayAnimation(L"ArchereIdleR", true);
		//	_rigidbody->ClearVelocityX();
		//}				
	}

	void Archer::intro()
	{
	}

	void Archer::potion()
	{
	}

	void Archer::choicecombo()
	{
		if (_attack == true)
		{
			if (_choicecombo == 0)
			{
				_number_of_attack++;
				shootbow_forward();
			}
			if (_choicecombo == 1)
			{
				_number_of_attack++;
				shootbow_upward();
			}
			if (_choicecombo == 2)
			{
				_number_of_attack++;
				pushaway();
			}
			if (_choicecombo == 3)
			{
				_number_of_attack++;
			//	pushaway();
			}
		}
		else
		{			
			if (_number_of_attack >= 3)
			{
				_number_of_attack = 0;
				_time = 0.f;
			}
			_state = Archer_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"ArcherIdle", true);
			else
				at->PlayAnimation(L"ArcherIdleR", true);
		}
	}

	void Archer::shootbow_forward()
	{
		_state = Archer_State::Attack_A_Ready;
		if (mDir == 1)
			at->PlayAnimation(L"ArcherAttack_A", false);
		else
			at->PlayAnimation(L"ArcherAttack_AR", false);
	}

	void Archer::shootbow_upward()
	{
		_state = Archer_State::Attack_B;
		if (mDir == 1)
			at->PlayAnimation(L"ArcherAttack_B", true);
		else
			at->PlayAnimation(L"ArcherAttack_BR", true);
	}

	void Archer::pushaway()
	{
		_state = Archer_State::Attack_C;
		if (mDir == 1)
			at->PlayAnimation(L"ArcherAttack_C", true);
		else
			at->PlayAnimation(L"ArcherAttack_CR", true);
	}
	void Archer::complete_hit()
	{
		if (mDir == 1)
		{
			_state = Archer_State::Idle;
			at->PlayAnimation(L"ArcherIdle", true);
		}
		else if (mDir == -1)
		{
			_state = Archer_State::Idle;
			at->PlayAnimation(L"ArchereIdleR", true);
		}
	}
	void Archer::complete_attackA()
	{
	
	}
}