#include "Mage.h"
#include <iostream>
#include <random>

namespace jk
{
	Mage::Mage()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Mage::~Mage()
	{
	}
	void Mage::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
	

		//Skul_Head = new Skul_head();
		//Skul_Head->Initialize();
		//Scene* scene = SceneManager::GetActiveScene();
		//scene->AddGameObject(eLayerType::Item, Skul_Head);
		//Transform* tr_head = Skul_Head->GetComponent<Transform>();
		//tr_head->SetPosition(Vector3(pos.x, pos.y, -250.f));
		//Skul_Head->GetComponent<Transform>()->SetScale(Vector3(15.f, 13.f, 0.f));
		//Skul_Head->SetState(eState::Paused);

		at = AddComponent<Animator>();

		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_A", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_A_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_B", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_B_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_C", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_C_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_D", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_D_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Die", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Groggy", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Intro", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Intro2", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Potion", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\WalkBack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\WalkFront", this);


		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_A", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_A_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_B", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_B_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_C", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_C_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_D", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_D_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Die", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Groggy", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Intro", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Intro2", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Potion", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\WalkBack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\WalkFront", this, 1);


		//bind 부분
		at->CompleteEvent(L"MageAttack_A") = std::bind(&Mage::attack_a_complete, this);
		at->CompleteEvent(L"MageAttack_A_Ready") = std::bind(&Mage::attack_a_ready_complete, this);
		at->CompleteEvent(L"MageAttack_B") = std::bind(&Mage::attack_b_complete, this);
		at->CompleteEvent(L"MageAttack_B_Ready") = std::bind(&Mage::attack_b_ready_complete, this);
		//at->CompleteEvent(L"MageAttack_C") = std::bind(&Mage::attack_c_complete, this);
		at->CompleteEvent(L"MageAttack_C_Ready") = std::bind(&Mage::attack_c_ready_complete, this);
		at->CompleteEvent(L"MageAttack_D") = std::bind(&Mage::attack_d_complete, this);
		at->CompleteEvent(L"MageAttack_D_Ready") = std::bind(&Mage::attack_d_ready_complete, this);

		at->CompleteEvent(L"MageAttack_AR") = std::bind(&Mage::attack_a_complete, this);
		at->CompleteEvent(L"MageAttack_A_ReadyR") = std::bind(&Mage::attack_a_ready_complete, this);
		at->CompleteEvent(L"MageAttack_BR") = std::bind(&Mage::attack_b_complete, this);
		at->CompleteEvent(L"MageAttack_B_ReadyR") = std::bind(&Mage::attack_b_ready_complete, this);
		//at->CompleteEvent(L"MageAttack_CR") = std::bind(&Mage::attack_c_complete, this);
		at->CompleteEvent(L"MageAttack_C_ReadyR") = std::bind(&Mage::attack_c_ready_complete, this);
		at->CompleteEvent(L"MageAttack_DR") = std::bind(&Mage::attack_d_complete, this);
		at->CompleteEvent(L"MageAttack_D_ReadyR") = std::bind(&Mage::attack_d_ready_complete, this);

		at->CompleteEvent(L"MageHit") = std::bind(&Mage::complete_hit, this);
		at->CompleteEvent(L"MageHitR") = std::bind(&Mage::complete_hit, this);

		_first_place = pos;
		at->PlayAnimation(L"MageIdle", true);
		GameObject::Initialize();
	}
	void Mage::Update()
	{
		tr = GetComponent<Transform>();
		pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_playerpos;
		_distance = _playerpos.x - pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;


		switch (_state)
		{
		case jk::Mage::Mage_State::Idle:
			idle();
			break;

		case jk::Mage::Mage_State::Die:
			die();
			break;

		case jk::Mage::Mage_State::Attack_A:
			attack_a();
			break;

		case jk::Mage::Mage_State::Attack_A_Ready:
			attack_a_ready();
			break;

		case jk::Mage::Mage_State::Attack_B:
			attack_b();
			break;

		case jk::Mage::Mage_State::Attack_B_Ready:
			attack_b_ready();
			break;

		case jk::Mage::Mage_State::Attack_C:
			attack_c();
			break;

		case jk::Mage::Mage_State::Attack_C_Run:
			attack_c_run();
			break;

		case jk::Mage::Mage_State::Attack_C_Ready:
			attack_c_ready();
			break;

		case jk::Mage::Mage_State::Attack_D:
			attack_d();
			break;

		case jk::Mage::Mage_State::Attack_D_Ready:
			attack_d_ready();
			break;

		case jk::Mage::Mage_State::Fly:
			fly();
			break;			

		case jk::Mage::Mage_State::Groggy:
			groggy();
			break;

		case jk::Mage::Mage_State::Hit:
			hit();
			break;

		case jk::Mage::Mage_State::Intro:
			intro();
			break;

		case jk::Mage::Mage_State::Potion:
			potion();
			break;

		case jk::Mage::Mage_State::WalkBack_R:
			walkBack_R();
			break;

		case jk::Mage::Mage_State::WalkBack_L:
			walkBack_L();
			break;

		case jk::Mage::Mage_State::WalkFront_R:
			WalkFront_R();
			break;

		case jk::Mage::Mage_State::WalkFront_L:
			WalkFront_L();
			break;

		default:
			break;
		}

		tr->SetPosition(Vector3(pos));
		GameObject::Update();
	}
	void Mage::LateUpdate()
	{
		_collider->SetSize(Vector2(0.1f, 0.5f));
		_collider->SetCenter(Vector2(0.0f, -5.55f));	
		GameObject::LateUpdate();
	}
	void Mage::Render()
	{
		GameObject::Render();
	}
	void Mage::OnCollisionEnter(Collider2D* other)
	{
	}
	void Mage::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{

			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;

				if (_state == Mage_State::Attack_C)
				{
					_state = Mage_State::Idle;
					if (mDir == 1)
						at->PlayAnimation(L"MageIdle", true);
					else
						at->PlayAnimation(L"MageIdleR", true);		

					_time = 0;
				}
			}
			else
			{
				//_state = Mage_State::Idle;
				//if (mDir == 1)
				//	at->PlayAnimation(L"MageIdle", true);
				//else
				//	at->PlayAnimation(L"MageIdleR", true);
			}
				
		}
	}
	void Mage::OnCollisionExit(Collider2D* other)
	{
	}


	void Mage::idle()
	{
		if(_ground == true)
			_Ground_check = true;
		else
			_Ground_check = false;

		if (_flyswich >= 3)
		{
			_state = Mage_State::Fly;
			if (mDir == 1)
				at->PlayAnimation(L"MageWalkFront", true);
			if (mDir == -1)
				at->PlayAnimation(L"MageWalkFrontR", true);

			_flyswich = 0;
			_sky = true;
			_ground = false;
		}
		if (_landingswich >= 4)
		{
			if (_Ground_check == true)		// 랜딩시 그라운드가 트루라면 랜딩 빠져나가기
				return;

			_state = Mage_State::Attack_C_Run;
			if (mDir == 1)
				at->PlayAnimation(L"MageWalkFront", true);
			if (mDir == -1)
				at->PlayAnimation(L"MageWalkFrontR", true);

			_landingswich = 0;
			_sky = false;
			_ground = true;
		}

		_swich_checkpoint = randomcount(0, 3);
		//_swich_checkpoint = 3;

		_time += Time::DeltaTime();
		if (_time >= 2.f)
		{
			if (_swich_checkpoint == 0)
			{
				_movechoice = randomcount(1, 2);

				if (_movechoice == 1)
				{
					at->PlayAnimation(L"MageWalkFront", true);
					_state = Mage_State::WalkFront_R;
				}
				if (_movechoice == 2)
				{
					at->PlayAnimation(L"MageWalkFrontR", true);
					_state = Mage_State::WalkFront_L;
				}
			}

			if (_swich_checkpoint == 1)
			{
				_state = Mage_State::Attack_A_Ready;
				if (mDir == 1)
					at->PlayAnimation(L"MageAttack_A_Ready", true);
				if (mDir == -1)					
					at->PlayAnimation(L"MageAttack_A_ReadyR", true);
			}

			if (_swich_checkpoint == 2)
			{
				_state = Mage_State::Attack_B_Ready;
				if (mDir == 1)
					at->PlayAnimation(L"MageAttack_B_Ready", true);
				if (mDir == -1)
					at->PlayAnimation(L"MageAttack_B_ReadyR", true);
			}

			if (_swich_checkpoint == 3)
			{
				if (_sky == false)
					return;

				_state = Mage_State::Attack_D_Ready;
				if (mDir == 1)
					at->PlayAnimation(L"MageAttack_D_Ready", true);
				if (mDir == -1)
					at->PlayAnimation(L"MageAttack_D_ReadyR", true);
			}
		}
	}	

	void Mage::die()
	{
	}

	void Mage::attack_a()
	{
	}
	void Mage::attack_a_ready()
	{
	}

	void Mage::attack_b()
	{
		_attacktB_time += Time::DeltaTime();

		if (_attacktB_time >= 5)
		{
			_state = Mage_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"MageIdle", true);
			else
				at->PlayAnimation(L"MageIdleR", true);

			_time = 0;
			_attacktB_time = 0;

			if (_ground == true)
				_flyswich++;
			if (_sky == true)
				_landingswich++;
		}
	}
	void Mage::attack_b_ready()
	{
	}

	void Mage::attack_c_run()
	{
		if (mDir == 1)
		{
			if (!((_distance <= 30.f) && (_distance >= -30.f)))
			{
				pos.x += 300 * Time::DeltaTime();

				if (pos.y < 150 + _playerpos.y)
					pos.y += 200 * Time::DeltaTime();
			}	
			else
			{
				_state = Mage_State::Attack_C_Ready;
				if (mDir == 1)
					at->PlayAnimation(L"MageAttack_C_Ready", true);
				if (mDir == -1)
					at->PlayAnimation(L"MageAttack_C_ReadyR", true);
			}
		}
		else
		{
			if (!((_distance <= 30.f) && (_distance >= -30.f)))
			{
				pos.x -= 300 * Time::DeltaTime();			

				if (pos.y < 150 + _playerpos.y)
					pos.y += 200 * Time::DeltaTime();
			}
	
			else
			{
				_state = Mage_State::Attack_C_Ready;
				if (mDir == 1)
					at->PlayAnimation(L"MageAttack_C_Ready", true);
				if (mDir == -1)
					at->PlayAnimation(L"MageAttack_C_ReadyR", true);
			}
		}
	}
	void Mage::attack_c_ready()
	{	
	}
	void Mage::attack_c()
	{
		if (_Ground_check == true)
		{
			_rigidbody->SetVelocity(Vector2(0.f, -350.f));
			_rigidbody->SetGround(false);
			_Ground_check = false;
		}
	}

	void Mage::attack_d()
	{
	}
	void Mage::attack_d_ready()
	{
	}
	void Mage::fly()
	{
		if (pos.y < 150 + _playerpos.y)
			pos.y += 200 * Time::DeltaTime();
		else
		{
			_state = Mage_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"MageIdle", true);
			else
				at->PlayAnimation(L"MageIdleR", true);
			_time = 0;			
		}

	}
	void Mage::groggy()
	{
	}
	void Mage::hit()
	{
	}
	void Mage::intro()
	{
	}
	void Mage::potion()
	{
	}

	void Mage::WalkFront_R()
	{	
		_mtime = randomcount(2, 4);
		_movetime += Time::DeltaTime();

		if (_maxright > pos.x)
		{
			if (_movetime < _mtime)
			{				
				pos.x += 100.f * Time::DeltaTime();
				if (mDir == -1)
				{
					_state = Mage_State::WalkBack_R;
					at->PlayAnimation(L"MageWalkBack", true);
				}
			}
			else
			{
				_state = Mage_State::Idle;
				if (mDir == 1)
					at->PlayAnimation(L"MageIdle", true);
				else
					at->PlayAnimation(L"MageIdleR", true);
				_time = 0;
				_mtime = 0;
			}
		}
		else
		{
			_state = Mage_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"MageIdle", true);
			else
				at->PlayAnimation(L"MageIdleR", true);
			_time = 0;
			_mtime = 0;
		}
		
		tr->SetPosition(Vector3(pos));
	}
	void Mage::walkBack_R()
	{	
			_movetime += Time::DeltaTime();
			if (_movetime < _mtime)
			{
				pos.x += 100.f * Time::DeltaTime();
				if (mDir == 1)
				{
					_state = Mage_State::WalkFront_R;
					at->PlayAnimation(L"MageWalkFront", true);
				}
			}
			else
			{
				_state = Mage_State::Idle;
				if (mDir == 1)
					at->PlayAnimation(L"MageIdle", true);
				else
					at->PlayAnimation(L"MageIdleR", true);
				_time = 0;
				_mtime = 0;
			}	
		tr->SetPosition(Vector3(pos));
	}
	void Mage::WalkFront_L()
	{		
		_mtime = randomcount(2, 4);
		_movetime += Time::DeltaTime();

		if (_maxleft < pos.x)
		{
			if (_movetime < _mtime)
			{
				pos.x -= 100.f * Time::DeltaTime();
				if (mDir == 1)
				{
					_state = Mage_State::WalkBack_L;
					at->PlayAnimation(L"MageWalkBackR", true);
				}
			}
			else
			{
				_state = Mage_State::Idle;
				if (mDir == 1)
					at->PlayAnimation(L"MageIdle", true);
				else
					at->PlayAnimation(L"MageIdleR", true);
				_time = 0;
				_mtime = 0;
			}
		}
		else
		{
			_state = Mage_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"MageIdle", true);
			else
				at->PlayAnimation(L"MageIdleR", true);
			_time = 0;
			_mtime = 0;
		}
		tr->SetPosition(Vector3(pos));
	}
	void Mage::walkBack_L()
	{
		_movetime += Time::DeltaTime();
		if (_movetime < _mtime)
		{
			pos.x -= 100.f * Time::DeltaTime();
			if (mDir == -1)
			{
				_state = Mage_State::WalkFront_L;
				at->PlayAnimation(L"MageWalkFrontR", true);
			}
		}
		else
		{
			_state = Mage_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"MageIdle", true);
			else
				at->PlayAnimation(L"MageIdleR", true);
			_time = 0;
			_mtime = 0;
		}
		tr->SetPosition(Vector3(pos));
	}	

	void Mage::complete_hit()
	{
	}
	int Mage::randomcount(int a, int b)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(a, b);
		_swich_checkpoint = distribution(gen);
		
		return _swich_checkpoint;
	}


	void Mage::attack_a_complete()
	{
		_attackA++;

		if (_attackA >= 5)
		{
			_state = Mage_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"MageIdle", true);
			else
				at->PlayAnimation(L"MageIdleR", true);
			_attackA = 0;
			_time = 0;

			if (_ground == true)
				_flyswich++;
			if (_sky == true)
				_landingswich++;
		}
		else
		{
			_state = Mage_State::Attack_A;
			if (mDir == 1)
				at->PlayAnimation(L"MageAttack_A", true);
			if (mDir == -1)
				at->PlayAnimation(L"MageAttack_AR", true);			
		}
	}
	void Mage::attack_a_ready_complete()
	{
		_state = Mage_State::Attack_A;
		if (mDir == 1)
			at->PlayAnimation(L"MageAttack_A", true);
		if (mDir == -1)
			at->PlayAnimation(L"MageAttack_AR", true);
	}


	void Mage::attack_b_complete()
	{
	}
	void Mage::attack_b_ready_complete()
	{
		_state = Mage_State::Attack_B;
		if (mDir == 1)
			at->PlayAnimation(L"MageAttack_B", false);
		if (mDir == -1)
			at->PlayAnimation(L"MageAttack_BR", false);
	}


	void Mage::attack_c_complete()
	{
		
	}
	void Mage::attack_c_ready_complete()
	{
		_state = Mage_State::Attack_C;
		if (mDir == 1)
			at->PlayAnimation(L"MageAttack_C", false);
		if (mDir == -1)
			at->PlayAnimation(L"MageAttack_CR", false);

		_Ground_check = true;
	}



	void Mage::attack_d_complete()
	{
		_state = Mage_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"MageIdle", true);
		else
			at->PlayAnimation(L"MageIdleR", true);
		_attackA = 0;
		_time = 0;

		if (_ground == true)
			_flyswich++;
		if (_sky == true)
			_landingswich++;
	}
	void Mage::attack_d_ready_complete()
	{
		_state = Mage_State::Attack_D;
		if (mDir == 1)
			at->PlayAnimation(L"MageAttack_D", true);
		if (mDir == -1)
			at->PlayAnimation(L"MageAttack_DR", true);
	}
}
