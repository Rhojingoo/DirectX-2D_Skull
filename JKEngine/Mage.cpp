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

		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_A_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_A_First", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_A_Second", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_A_End", this);



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
	
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Ultimate_Set", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Ultimate_Castimg", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Ultimate_Skill_Fire", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Utimate_Skill_Action", this);
		




		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_A_Ready", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_A_First", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_A_Second", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Attack_A_End", this, 1);

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

		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Ultimate_Set", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Ultimate_Castimg", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Ultimate_Skill_Fire", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Utimate_Skill_Action", this, 1);
		
		
		//bind 부분
		at->CompleteEvent(L"MageAttack_A_Ready") = std::bind(&Mage::attack_a_ready_complete, this);
		at->CompleteEvent(L"MageAttack_A_ReadyR") = std::bind(&Mage::attack_a_ready_complete, this);

		at->CompleteEvent(L"MageAttack_A_First") = std::bind(&Mage::attack_a_firts_complete, this);
		at->CompleteEvent(L"MageAttack_A_FirstR") = std::bind(&Mage::attack_a_firts_complete, this);

		at->CompleteEvent(L"MageAttack_A_Second") = std::bind(&Mage::attack_a_second_complete, this);
		at->CompleteEvent(L"MageAttack_A_SecondR") = std::bind(&Mage::attack_a_second_complete, this);

		at->CompleteEvent(L"MageAttack_A_End") = std::bind(&Mage::attack_a_complete, this);
		at->CompleteEvent(L"MageAttack_A_EndR") = std::bind(&Mage::attack_a_complete, this);

		at->CompleteEvent(L"MageAttack_B") = std::bind(&Mage::attack_b_complete, this);
		at->CompleteEvent(L"MageAttack_B_Ready") = std::bind(&Mage::attack_b_ready_complete, this);
		//at->CompleteEvent(L"MageAttack_C") = std::bind(&Mage::attack_c_complete, this);
		at->CompleteEvent(L"MageAttack_C_Ready") = std::bind(&Mage::attack_c_ready_complete, this);
		at->CompleteEvent(L"MageAttack_D") = std::bind(&Mage::attack_d_complete, this);
		at->CompleteEvent(L"MageAttack_D_Ready") = std::bind(&Mage::attack_d_ready_complete, this);

		at->CompleteEvent(L"MageAttack_BR") = std::bind(&Mage::attack_b_complete, this);
		at->CompleteEvent(L"MageAttack_B_ReadyR") = std::bind(&Mage::attack_b_ready_complete, this);
		//at->CompleteEvent(L"MageAttack_CR") = std::bind(&Mage::attack_c_complete, this);
		at->CompleteEvent(L"MageAttack_C_ReadyR") = std::bind(&Mage::attack_c_ready_complete, this);
		at->CompleteEvent(L"MageAttack_DR") = std::bind(&Mage::attack_d_complete, this);
		at->CompleteEvent(L"MageAttack_D_ReadyR") = std::bind(&Mage::attack_d_ready_complete, this);

		at->CompleteEvent(L"MageHit") = std::bind(&Mage::complete_hit, this);
		at->CompleteEvent(L"MageHitR") = std::bind(&Mage::complete_hit, this);

		at->CompleteEvent(L"MageUltimate_Set") = std::bind(&Mage::complete_ultimate_set, this);
		at->CompleteEvent(L"MageUltimate_SetR") = std::bind(&Mage::complete_ultimate_set, this);

		at->CompleteEvent(L"MageUltimate_Skill_Fire") = std::bind(&Mage::complete_ultimate_fire, this);
		at->CompleteEvent(L"MageUltimate_Skill_FireR") = std::bind(&Mage::complete_ultimate_fire, this);

		at->CompleteEvent(L"MageIntro") = std::bind(&Mage::complete_intro, this);
		at->CompleteEvent(L"MageIntroR") = std::bind(&Mage::complete_intro, this);
		at->CompleteEvent(L"MageIntro2") = std::bind(&Mage::complete_intro_end, this);
		at->CompleteEvent(L"MageIntro2R") = std::bind(&Mage::complete_intro_end, this);


		{
			Ultimate_Aura = new Public_Ultimate_Aura;
			Ultimate_Aura->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Ultimate_Aura);
			Transform* bullet_tr = Ultimate_Aura->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Ultimate_Aura->SetState(eState::Paused);
		}
		{
			Ultimate_AuraSmoke = new Public_Ultimate_AuraSmoke;
			Ultimate_AuraSmoke->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Ultimate_AuraSmoke);
			Transform* bullet_tr = Ultimate_AuraSmoke->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Ultimate_AuraSmoke->SetState(eState::Paused);
		}
		{
			UltimateSkill_Effect_Complete = new Public_UltimateSkill_Effect_Complete;
			UltimateSkill_Effect_Complete->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, UltimateSkill_Effect_Complete);
			Transform* bullet_tr = UltimateSkill_Effect_Complete->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			UltimateSkill_Effect_Complete->SetState(eState::Paused);
		}
		{
			UltimateSkill_Effect_Fail = new Public_UltimateSkill_Effect_Fail;
			UltimateSkill_Effect_Fail->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, UltimateSkill_Effect_Fail);
			Transform* bullet_tr = UltimateSkill_Effect_Fail->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			UltimateSkill_Effect_Fail->SetState(eState::Paused);
		}
		{
			for (int i = 0; i < 3; i++)
			{
				_OnFire_Ready[i] = new Ultimate_OnFire_Ready;
				_OnFire_Ready[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Effect, _OnFire_Ready[i]);
				Transform* bullet_tr = _OnFire_Ready[i]->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
				_OnFire_Ready[i]->SetState(eState::Paused);
			}
		}
		{
			for (int i = 0; i < 3; i++)
			{
				_OnFire[i] = new Ultimate_OnFire;
				_OnFire[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Effect, _OnFire[i]);
				Transform* bullet_tr = _OnFire[i]->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
				_OnFire[i]->SetState(eState::Paused);
			}
		}
		{
			for (int i = 0; i < 9; i++)
			{
				On_Fire_Projectile[i] = new Ultimate_On_Fire_Projectile;
				On_Fire_Projectile[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Bullet, On_Fire_Projectile[i]);
				Transform* bullet_tr = On_Fire_Projectile[i]->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
				On_Fire_Projectile[i]->SetState(eState::Paused);
			}
		}
		{
			for(int i =0; i<9;i++)
			{
				OnFire_Fire[i] = new Ultimate_OnFire_Fire;
				OnFire_Fire[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Effect, OnFire_Fire[i]);
				Transform* bullet_tr = OnFire_Fire[i]->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
				OnFire_Fire[i]->SetState(eState::Paused);
			}
		}
		{
			for (int i = 0; i < 6; i++)
			{
				FireBall[i] = new Mage_FireBall;
				FireBall[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Bullet, FireBall[i]);
				Transform* bullet_tr = FireBall[i]->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
				FireBall[i]->SetState(eState::Paused);
			}		
		}
		{
			for (int i = 0; i < 3; i++)
			{
				BoomSign[i] = new Mage_BoomSign;
				BoomSign[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Effect, BoomSign[i]);
				Transform* bullet_tr = BoomSign[i]->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
				BoomSign[i]->SetState(eState::Paused);
			}
		}

		{
			for (int i = 0; i < 3; i++)
			{
				FireBoom[i] = new Mage_FireBoom;
				FireBoom[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Bullet, FireBoom[i]);
				Transform* bullet_tr = FireBoom[i]->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
				FireBoom[i]->SetState(eState::Paused);
			}
		}
		{
			Landing_Ready = new Mage_Landing_Ready;
			Landing_Ready->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Landing_Ready);
			Transform* bullet_tr = Landing_Ready->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Landing_Ready->SetState(eState::Paused);
		}
		{
			Phoenix_Landing = new Mage_Phoenix_Landing;
			Phoenix_Landing->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Phoenix_Landing);
			Transform* bullet_tr = Phoenix_Landing->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Phoenix_Landing->SetState(eState::Paused);
		}
		{
			Phoenix_Landing_Land = new Mage_Phoenix_Landing_Land;
			Phoenix_Landing_Land->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Phoenix_Landing_Land);
			Transform* bullet_tr = Phoenix_Landing_Land->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Phoenix_Landing_Land->SetState(eState::Paused);		
		}

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


		case jk::Mage::Mage_State::Attack_A_Ready:
			attack_a_ready();
			break;

		case jk::Mage::Mage_State::Attack_A_First:
			attack_a_first();
			break;

		case jk::Mage::Mage_State::Attack_A_Second:
			attack_a_second();
			break;

		case jk::Mage::Mage_State::Attack_A_End:
			attack_a_end();
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



		case jk::Mage::Mage_State::Finishing_Move_Ready:
			Finishing_Move_Ready();
			break;

		case jk::Mage::Mage_State::Finishing_Move_Succes:
			Finishing_Move_Succes();
			break;

		case jk::Mage::Mage_State::Finishing_Move_Fail:
			Finishing_Move_Fail();
			break;

		case jk::Mage::Mage_State::Finishing_Move:
			Finishing_Move();
			break;

		case jk::Mage::Mage_State::Casting:
			casting();
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

		case jk::Mage::Mage_State::Intro_End:
			intro_end();
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
		_collider->SetCenter(Vector2(0.0f, -25.f));	
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
					_GroundLanding = true;
				}
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

		Fly_or_Landing();;

		//_swich_checkpoint = randomcount(0, 3);
		_swich_checkpoint = 4;
	

		if (_Intro == false)
		{
			_state = Mage_State::Intro;
			if(mDir==1)				
				at->PlayAnimation(L"MageIntro", true);			
			else		
				at->PlayAnimation(L"MageIntroR", true);			
		}
		else
		{ 
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

				if (_swich_checkpoint == 3)// 각성 공격
				{
					if (_sky == false)
						return;

					_state = Mage_State::Attack_D_Ready;
					if (mDir == 1)
						at->PlayAnimation(L"MageAttack_D_Ready", true);
					if (mDir == -1)
						at->PlayAnimation(L"MageAttack_D_ReadyR", true);
				}

				if (_swich_checkpoint == 4)
				{
					if (_sky == false)
						return;

					_state = Mage_State::Finishing_Move_Ready;
					if (mDir == 1)
						at->PlayAnimation(L"MageUltimate_Set", true);
					if (mDir == -1)
						at->PlayAnimation(L"MageUltimate_SetR", true);
					_UltimateSet = false;
				}
			}
		}
	}	

	void Mage::die()
	{
	}


	void Mage::attack_a_ready()
	{
		for (int i = 0; i < 6; i++)
		{
			Transform* bullet_tr = FireBall[i]->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));		
			FireBall[i]->_rotationswitch = false;
			FireBall[i]->SetState(eState::Paused);
		
			bullet_tr->SetRotationZ(0);
		}	
	}
	void Mage::attack_a_first()
	{
		Transform* bullet_tr = FireBall[_attackA]->GetComponent<Transform>();
		RigidBody* bullet_Rb = FireBall[_attackA]->GetComponent<RigidBody>();
		Vector3 bulletpos = bullet_tr->GetPosition();
		if (_firstcomplete == true)
		{
			//if(mDir == 1)
			//	bullet_tr->SetPosition(Vector3(pos.x+20, pos.y-20, -205));
			//else
			//	bullet_tr->SetPosition(Vector3(pos.x-20, pos.y-20, -205));

			FireBall[_attackA]->_bullet_animation = true;
			Fire_Ball_Rotation(bullet_tr, bulletpos, _attackA);
			FireBall[_attackA]->_bullet_On = true;
			FireBall[_attackA]->SetState(eState::Active);
			_attackA_firstSet[_attackA] = true;
			bullet_Rb->SetGravity(true);
			bullet_Rb->SetFriction(true);
			Fire_Ball(_attackA);
			_firstcomplete = false;
			if (_firstcomplete == false)
			{
				_state = Mage_State::Attack_A_Second;
				if (mDir == 1)
					at->PlayAnimation(L"MageAttack_A_Second", true);
				if (mDir == -1)
					at->PlayAnimation(L"MageAttack_A_SecondR", true);
			}
		}
	}
	void Mage::attack_a_second()
	{
		_attackA_Second = 3 + _attackA;
		Transform* bullet_tr = FireBall[_attackA_Second]->GetComponent<Transform>();
		RigidBody* bullet_Rb = FireBall[_attackA_Second]->GetComponent<RigidBody>();
		Vector3 bulletpos = bullet_tr->GetPosition();
		if (_scondcomplete == true)
		{
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			FireBall[_attackA_Second]->_bullet_animation = true;
			Fire_Ball_Rotation(bullet_tr, bulletpos, _attackA_Second);
			FireBall[_attackA_Second]->_bullet_On = true;
			FireBall[_attackA_Second]->SetState(eState::Active);	
			_attackA_secondSet[_attackA_Second] = true;
			bullet_Rb->SetGravity(true);
			bullet_Rb->SetFriction(true);
			Fire_Ball(_attackA_Second);
			_scondcomplete = false;

			if (_scondcomplete == false)
			{
				_state = Mage_State::Attack_A_End;
				if (mDir == 1)
					at->PlayAnimation(L"MageAttack_A_End", true);
				if (mDir == -1)
					at->PlayAnimation(L"MageAttack_A_EndR", true);
			}
		}
	}
	void Mage::attack_a_end()
	{
		//_firstcomplete = false;
		//_scondcomplete = false;
	}


	void Mage::attack_b_ready()
	{
		for (int i = 0; i < 3; i++)
		{
			Transform* bullet_tr = BoomSign[i]->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_playerpos.x, _playerpos.y, _playerpos.z-1));
			BoomSign[i]->SetState(eState::Paused);
			BoomSign[i]->_effect_On = true;			
			BoomSign[i]->_effect_check = true;
		}	
		_Number_of_attackB = 0;
	}
	void Mage::attack_b()
	{
		//_attacktB_time += Time::DeltaTime();
	
		if(_Number_of_attackB<3)
		{
			Transform* Effect_tr = BoomSign[_Number_of_attackB]->GetComponent<Transform>();
			Transform* bullet_tr = FireBoom[_Number_of_attackB]->GetComponent<Transform>();

			if (BoomSign[_Number_of_attackB]->_effect_check == true)
			{
				Effect_tr->SetPosition(Vector3(_playerpos.x, _playerpos.y, _playerpos.z - 1));
				BoomSign[_Number_of_attackB]->SetState(eState::Active);
				BoomSign[_Number_of_attackB]->_effect_check = false;
			}
			if (BoomSign[_Number_of_attackB]->_effect_On == false)
			{
				Vector3 effectpos = Effect_tr->GetPosition();
				bullet_tr->SetPosition(effectpos);
				FireBoom[_Number_of_attackB]->SetState(eState::Active);
				_Number_of_attackB++;
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

			if (_ground == true)
				_flyswich++;
			if (_sky == true)
				_landingswich++;
		}
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
				Landing_Ready->_effect_On = true;
				_LandingOn = false;
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
				Landing_Ready->_effect_On = true;
				_LandingOn = false;
			}
		}
	}
	void Mage::attack_c_ready()
	{	
		if (_LandingOn == false)
		{
			Transform* bullet_tr = Landing_Ready->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y - 25, pos.z-1));
			Landing_Ready->_effect_Animation = true;
			if (mDir == 1)
				Landing_Ready->SetDirection(1);
			else
				Landing_Ready->SetDirection(-1);
			Landing_Ready->SetState(eState::Active);
			_LandingOn = true;
		}
		else			
		{
			if (Landing_Ready->_effect_On == false)
			{				
				Transform* bullet_tr = Phoenix_Landing->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y-55, pos.z-1));
				Phoenix_Landing->SetState(eState::Active);
				Phoenix_Landing->_effect_Animation = true;
				if (mDir == 1)
					Phoenix_Landing->SetDirection(1);
				else
					Phoenix_Landing->SetDirection(-1);

				_Ground_check = true;		
				_GroundLanding = false;
				Phoenix_Landing_Land->_effect_On = true;

				_rigidbody->SetVelocity(Vector2(0.f, -350.f));
				_rigidbody->SetGround(false);
				_Ground_check = false;

				_state = Mage_State::Attack_C;
				if (mDir == 1)
					at->PlayAnimation(L"MageAttack_C", false);
				if (mDir == -1)
					at->PlayAnimation(L"MageAttack_CR", false);
			}
		}
	}
	void Mage::attack_c()
	{
		if (_GroundLanding == true)
		{
			Transform* bullet_tr = Phoenix_Landing_Land->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y-30, pos.z - 1));
			Phoenix_Landing->_effect_Animation = true;
			if (mDir == 1)
				Phoenix_Landing->SetDirection(1);
			else
				Phoenix_Landing->SetDirection(-1);
			Phoenix_Landing_Land->SetState(eState::Active);
			_GroundLanding = false;
		}
		else
		{
			if (Phoenix_Landing_Land->_effect_On == false)
			{
				_attack_time += Time::DeltaTime();
				if (_attack_time > 2)
				{
					_state = Mage_State::Idle;
					if (mDir == 1)
						at->PlayAnimation(L"MageIdle", true);
					else
						at->PlayAnimation(L"MageIdleR", true);
					_time = 0;
				}
			}
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


	void Mage::Finishing_Move_Ready()
	{
		if (_UltimateSet == true)
		{
			{
				Transform* bullet_tr = Ultimate_Aura->GetComponent<Transform>();
				Ultimate_Aura->_effect_animation = true;
				if (mDir == 1)
				{
					Ultimate_Aura->SetDirection(1);
					bullet_tr->SetPosition(Vector3(pos.x, pos.y - 30, pos.z - 1));
				}
				else
				{
					Ultimate_Aura->SetDirection(-1);
					bullet_tr->SetPosition(Vector3(pos.x, pos.y - 30, pos.z - 1));
				}
				Ultimate_Aura->SetState(eState::Active);
			}

			{
				Transform* bullet_tr = Ultimate_AuraSmoke->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y - 55, pos.z - 1.1));
				if (mDir == 1)
				{
					Ultimate_AuraSmoke->SetDirection(1);
					bullet_tr->SetPosition(Vector3(pos.x, pos.y - 50, pos.z - 1));
				}
				else
				{
					Ultimate_AuraSmoke->SetDirection(-1);
					bullet_tr->SetPosition(Vector3(pos.x, pos.y - 50, pos.z - 1));
				}
				Ultimate_AuraSmoke->SetState(eState::Active);
			}
			_UltimateSet = false;
		}

		// 기모으는 이펙트를 넣을것(7초간 지속상태 만들기)
		_attack_time += Time::DeltaTime();
		if (_attack_time >= 7.5)
		{
			Ultimate_Aura->SetState(eState::Paused);
			Ultimate_AuraSmoke->SetState(eState::Paused);
			if (_hit > 8)
			{
				// 이펙트 설정시 9번 hit가 된다면 깨지는 이미지로 넘어간뒤 그로기 상태로넘겨줘야한다.
				Transform* bullet_tr = UltimateSkill_Effect_Fail->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y - 25, pos.z - 1.1));
				if (mDir == 1)
					UltimateSkill_Effect_Fail->SetDirection(1);
				else
					UltimateSkill_Effect_Fail->SetDirection(-1);
				UltimateSkill_Effect_Fail->SetState(eState::Active);

				_state = Mage_State::Finishing_Move_Fail;
				_attack_time = 0.f;
			}
			else
			{
				// 이펙트 설정시 5초가 10번이상의 타격이 없다면 석세스로 넘어간뒤 Effect 날려야한다.
				Transform* bullet_tr = UltimateSkill_Effect_Complete->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y - 25, pos.z - 1.1));
				if (mDir == 1)
					UltimateSkill_Effect_Complete->SetDirection(1);
				else
					UltimateSkill_Effect_Complete->SetDirection(-1);
				UltimateSkill_Effect_Complete->SetState(eState::Active);

				//ultimate 미사일 좌표설정
				for (int i = 0; i < 3; i++)
				{
					float randomposX = random(pos.x - 100, pos.x + 100);
					float randomposY = random(pos.y - 50, pos.x + 50);

					Transform* _OnFire_Ready_tr = _OnFire_Ready[i]->GetComponent<Transform>();
					_OnFire_Ready_tr->SetPosition(Vector3(randomposX, randomposY, pos.z + 1));

					Transform* _OnFire_tr = _OnFire[i]->GetComponent<Transform>();
					_OnFire[i]->_effect_On = false;
					_OnFire_tr->SetPosition(Vector3(randomposX, randomposY, pos.z + 1));
				}

				if (mDir == 1)
					at->PlayAnimation(L"MageUltimate_Skill_Fire", true);
				else
					at->PlayAnimation(L"MageUltimate_Skill_FireR", true);
				_Ultimate_Skill = false;
				_attack_time = 0.f;
			}
		}
	}
	void Mage::Finishing_Move_Succes()
	{
		if (_Ultimate_Skill == false)
		{
			_attack_time += Time::DeltaTime();
			if (_attack_time <= 3.5f)
			{
				for (int i = 0; i < 3; i++)
				{
					if (_attack_time >= (1.0f + 0.5f * i))
					{
						if (_OnFire[i]->_effect_On == false)
						{
							Transform* _OnFire_Ready_tr = _OnFire_Ready[i]->GetComponent<Transform>();
							_OnFire_Ready[i]->SetState(eState::Active);

							Transform* _OnFire_tr = _OnFire[i]->GetComponent<Transform>();
							_OnFire[i]->_effect_On = true;
							_OnFire[i]->SetState(eState::Active);
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < 3; i++)
				{
					Transform* _OnFire_tr = _OnFire[i]->GetComponent<Transform>();
					Vector3  BulletPos = _OnFire_tr->GetPosition();
					Transform* bullet_tr = On_Fire_Projectile[i]->GetComponent<Transform>();
					On_Fire_Projectile[i]->_rotationswitch = false;
					On_Fire_Projectile[i]->_missile = false;
					bullet_tr->SetPosition(Vector3(BulletPos.x, BulletPos.y,BulletPos.z-1));
					bullet_tr->SetRotationZ(0);
					Transform* firefire_tr = OnFire_Fire[i]->GetComponent<Transform>();
					OnFire_Fire[i]->_effect_On = false;
					firefire_tr->SetPosition(Vector3(BulletPos.x, BulletPos.y, BulletPos.z-1.1));
				}
				for (int i = 3; i < 6; i++)
				{
					Transform* _OnFire_tr = _OnFire[i-3]->GetComponent<Transform>();
					Vector3  BulletPos = _OnFire_tr->GetPosition();
					Transform* bullet_tr = On_Fire_Projectile[i]->GetComponent<Transform>();
					On_Fire_Projectile[i]->_rotationswitch = false;
					On_Fire_Projectile[i]->_missile = false;
					bullet_tr->SetPosition(Vector3(BulletPos.x, BulletPos.y, BulletPos.z - 1));
					bullet_tr->SetRotationZ(0);
					Transform* firefire_tr = OnFire_Fire[i]->GetComponent<Transform>();
					OnFire_Fire[i]->_effect_On = false;
					firefire_tr->SetPosition(Vector3(BulletPos.x, BulletPos.y, BulletPos.z - 1.1));
				}
				for (int i = 6; i < 9; i++)
				{
					Transform* _OnFire_tr = _OnFire[i-6]->GetComponent<Transform>();
					Vector3  BulletPos = _OnFire_tr->GetPosition();
					Transform* bullet_tr = On_Fire_Projectile[i]->GetComponent<Transform>();
					On_Fire_Projectile[i]->_rotationswitch = false;
					On_Fire_Projectile[i]->_missile = false;
					bullet_tr->SetPosition(Vector3(BulletPos.x, BulletPos.y, BulletPos.z - 1));
					bullet_tr->SetRotationZ(0);
					Transform* firefire_tr = OnFire_Fire[i]->GetComponent<Transform>();
					OnFire_Fire[i]->_effect_On = false;
					firefire_tr->SetPosition(Vector3(BulletPos.x, BulletPos.y, BulletPos.z - 1.1));
				}
				//On_Fire_Projectile[i]->SetState(eState::Paused);
				_Ultimate_Skill = true;
				_attack_time = 0;
				_state = Mage_State::Finishing_Move;
			}
		
		}
	}
	void Mage::Finishing_Move_Fail()
	{
	}
	void Mage::Finishing_Move()
	{
		_attack_time += Time::DeltaTime();

		if (_attack_time <= 8.f)
		{
			for (int i = 0; i < 9; i++)
			{
				if (_attack_time >= (1.0f + 0.5f * i))
				{
					if (On_Fire_Projectile[i]->_missile == false)
					{
						Transform* _OnFire_Projectile_tr = On_Fire_Projectile[i]->GetComponent<Transform>();
						RigidBody* _OnFire_Projectile_rg = On_Fire_Projectile[i]->GetComponent<RigidBody>();
						Vector3 bulletpos = _OnFire_Projectile_tr->GetPosition();
						On_Fire_Projectile[i]->_bullet_On = true;
						On_Fire_Projectile[i]->_bullet_animation = true;

						Fire_Projectile_Rotation(_OnFire_Projectile_tr, bulletpos, i);					

						if(OnFire_Fire[i]->_effect_On == false)
							OnFire_Fire[i]->SetState(eState::Active);
						On_Fire_Projectile[i]->SetState(eState::Active);

						_OnFire_Projectile_rg->SetGravity(true);
						_OnFire_Projectile_rg->SetFriction(true);
						Fire_Projectile(i);

						On_Fire_Projectile[i]->_missile = true;
						if (i == 8)
						{
							_OnFire[0]->_effect_On == false;
							_OnFire[1]->_effect_On == false;
							_OnFire[2]->_effect_On == false;
						}
					}
				}
			}				
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				_OnFire[i]->SetState(eState::Paused);
				_OnFire_Ready[i]->SetState(eState::Active);
			}

			_state = Mage_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"MageIdle", true);
			else
				at->PlayAnimation(L"MageIdleR", true);
			_attackA = 0;
			_time = 0;
			_attack_time = 0;
		}
	}


	void Mage::casting()
	{
	}
	void Mage::groggy()
	{
	}


	void Mage::hit()
	{
	}
	void Mage::potion()
	{
	}


	void Mage::intro()
	{
	}
	void Mage::intro_end()
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


	void Mage::Fire_Projectile(int i)
	{
		Transform* _OnFire_Projectile_tr = On_Fire_Projectile[i]->GetComponent<Transform>();
		Vector3 _Fire_pos = _OnFire_Projectile_tr->GetPosition();
		RigidBody* bullet_Rb = On_Fire_Projectile[i]->GetComponent<RigidBody>();
		_playerpos.x;
		_playerpos.y;
		Vector2 attack_pos = Vector2(_playerpos.x - _Fire_pos.x, _playerpos.y - _Fire_pos.y); //Vector2(_playerpos.x, _playerpos.y);
		attack_pos.Normalize();
		bullet_Rb->SetGround(false);
		bullet_Rb->SetVelocity(Vector2(attack_pos.x * 250.f, attack_pos.y * 250));		
	}
	void Mage::Fire_Projectile_Rotation(Transform* tr, Vector3 bulletpos, int i)
	{
		if (On_Fire_Projectile[i]->_rotationswitch ==false)
		{
			if (_playerpos.x >= bulletpos.x)
			{
				On_Fire_Projectile[i]->SetDirection(-1);
				Vector2 attackpoint = Vector2(tr->GetPositionX() - _playerpos.x, tr->GetPositionY() - _playerpos.y);
				Vector2 rotation = Vector2(_playerpos.x, _playerpos.y);
				attackpoint.Normalize();
				rotation.Normalize();

				Vector2 direction = attackpoint - rotation; // 플레이어를 향하는 방향 벡터
				float angle = std::atan2(direction.y, direction.x);
				tr->AddRotationZ(angle);
			}
			else
			{
				On_Fire_Projectile[i]->SetDirection(-1);
				Vector2 attackpoint = Vector2(tr->GetPositionX() - _playerpos.x, tr->GetPositionY() - _playerpos.y);
				Vector2 rotation = Vector2(_playerpos.x, _playerpos.y);
				attackpoint.Normalize();
				rotation.Normalize();

				Vector2 direction = attackpoint - rotation; // 플레이어를 향하는 방향 벡터
				float angle = std::atan2(direction.y, direction.x);
				tr->AddRotationZ(angle);
			}
			On_Fire_Projectile[i]->_rotationswitch = true;
		}		
	}


	void Mage::Fire_Ball(int i)
	{
		Transform* _FireBall_tr = FireBall[i]->GetComponent<Transform>();
		Vector3 _FireBall_pos = _FireBall_tr->GetPosition();
		RigidBody* bullet_Rb = FireBall[i]->GetComponent<RigidBody>();
		Vector2 attack_pos = Vector2(_playerpos.x -_FireBall_pos.x , _playerpos.y- _FireBall_pos.y);
		attack_pos.Normalize();
		//bullet_Rb->SetGround(false);
		bullet_Rb->SetVelocity(Vector2(attack_pos.x * 250.f, attack_pos.y * 250));
		int a = 0;

	}
	void Mage::Fire_Ball_Rotation(Transform* tr, Vector3 bulletpos, int i)
	{
		if (FireBall[i]->_rotationswitch == false)
		{
			if (_playerpos.x >= bulletpos.x)
			{
				FireBall[i]->SetDirection(-1);
				Vector2 attackpoint = Vector2(tr->GetPositionX() - _playerpos.x, tr->GetPositionY() - _playerpos.y);
				Vector2 rotation = Vector2(_playerpos.x, _playerpos.y);
				attackpoint.Normalize();
				rotation.Normalize();

				Vector2 direction = attackpoint - rotation; // 플레이어를 향하는 방향 벡터
				float angle = std::atan2(direction.y, direction.x);
				tr->AddRotationZ(angle);
			}
			else
			{
				FireBall[i]->SetDirection(-1);
				Vector2 attackpoint = Vector2(tr->GetPositionX() - _playerpos.x, tr->GetPositionY() - _playerpos.y);
				Vector2 rotation = Vector2(_playerpos.x, _playerpos.y);
				attackpoint.Normalize();
				rotation.Normalize();

				Vector2 direction = attackpoint - rotation; // 플레이어를 향하는 방향 벡터
				float angle = std::atan2(direction.y, direction.x);
				tr->AddRotationZ(angle);
			}
			FireBall[i]->_rotationswitch = true;
		}
	}


	void Mage::complete_hit()
	{
	}
	void Mage::complete_ultimate_set()
	{
		if (mDir == 1)
			at->PlayAnimation(L"MageUltimate_Castimg", true);
		if (mDir == -1)
			at->PlayAnimation(L"MageUltimate_CastimgR", true);
		_UltimateSet = true; 
	}
	void Mage::complete_ultimate_fire()
	{
		if (mDir == 1)
			at->PlayAnimation(L"MageUtimate_Skill_Action", true);
		else
			at->PlayAnimation(L"MageUtimate_Skill_ActionR", true);
		_state = Mage_State::Finishing_Move_Succes;
	}


	void Mage::complete_intro()
	{
		int randomposX = random(_playerpos.x - 100, _playerpos.x + 100);
		Vector3 TeleportPos = Vector3(randomposX, _playerpos.y + 150, pos.z);
		tr->SetPosition(TeleportPos);	
		_rigidbody->SetGround(true);
		_flyswich = 0;
		_sky = true;
		_ground = false;

		if(mDir==1)
			at->PlayAnimation(L"MageIntro2", true);
		else
			at->PlayAnimation(L"MageIntro2R", true);
		_state = Mage_State::Intro_End;	
	}
	void Mage::complete_intro_end()
	{
		_state = Mage_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"MageIdle", true);
		else
			at->PlayAnimation(L"MageIdleR", true);

		_Intro = true;
	}


	void Mage::attack_a_ready_complete()
	{
		if (mDir == 1)
			at->PlayAnimation(L"MageAttack_A_First", true);
		if (mDir == -1)
			at->PlayAnimation(L"MageAttack_A_FirstR", true);
		_state = Mage_State::Attack_A_First;
	}
	void Mage::attack_a_firts_complete()
	{
		_firstcomplete = true;
	}
	void Mage::attack_a_second_complete()
	{
		_scondcomplete = true;
	}
	void Mage::attack_a_complete()
	{
		_attackA++;

		if (_attackA >= 3)
		{
			_state = Mage_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"MageIdle", true);
			else
				at->PlayAnimation(L"MageIdleR", true);
			
			_attackA = 0;
			_time = 0;
			//_fireballswitch = false;
			for (int i = 0; i < 3; i++)
			{
				_attackA_firstSet[i] = false;
				_attackA_secondSet[i] = false;
			}

			if (_ground == true)
				_flyswich++;
			if (_sky == true)
				_landingswich++; 
		}
		else
		{
			_state = Mage_State::Attack_A_First;
			if (mDir == 1)
				at->PlayAnimation(L"MageAttack_A_First", true);
			if (mDir == -1)
				at->PlayAnimation(L"MageAttack_A_FirstR", true);
		}
	}


	void Mage::attack_b_complete()
	{
		if (mDir == 1)
			at->PlayAnimation(L"MageUtimate_Skill_Action", true);
		if (mDir == -1)
			at->PlayAnimation(L"MageUtimate_Skill_ActionR", true);
	}
	void Mage::attack_b_ready_complete()
	{
		_state = Mage_State::Attack_B;
		if (mDir == 1)
			at->PlayAnimation(L"MageAttack_B", true);
		if (mDir == -1)
			at->PlayAnimation(L"MageAttack_BR", true);
	}


	void Mage::attack_c_ready_complete()
	{

	}
	void Mage::attack_c_complete()
	{
		
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


	void Mage::Fly_or_Landing()
	{
		if (_flyswich >= 1)
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
		if (_landingswich >= 1)
		{
			if (_Ground_check == true)// 랜딩시 그라운드가 트루라면 랜딩 빠져나가기
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
	}

	int Mage::randomcount(int a, int b)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(a, b);
		_swich_checkpoint = distribution(gen);
		
		return _swich_checkpoint;
	}
}
