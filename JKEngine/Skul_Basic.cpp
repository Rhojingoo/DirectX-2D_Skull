#include "Skul_Basic.h"
#include "jktime.h"
#include "Particle_DamageEffect.h"

namespace jk
{
	int Skul_Basic::mDir = 1;
	bool Skul_Basic::_switch = false;
	


	Skul_Basic::Skul_Basic()
		: _State(Skul_Basic_State::Idle)
		, at(nullptr)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Basic_Skul"));
	}
	Skul_Basic::~Skul_Basic()
	{
	}


	void Skul_Basic::Initialize()
	{
		_collider = AddComponent<Collider2D>();		

		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);

		as = AddComponent<AudioSource>();	
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Skul_Atk1.wav", "Skul_Atk1");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Skul_Atk2.wav", "Skul_Atk2");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Skul_Jump_Atk.wav", "Skul_Jump_Atk");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Atk_BluntWeapon_Small1.wav", "Atk_BluntWeapon_Small1");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Common\\Default_Dash.wav", "Default_Dash");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Common\\Default_Jump.wav", "Default_Jump");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Common\\Default_Jump_Air.wav", "Default_Jump_Air");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Common\\Default_Switch.wav", "Default_Switch");


		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Hit\\Hit_Blunt_Small.wav", "Hit_Blunt_Small");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Hit\\Hit_Blunt_Large.wav", "Hit_Blunt_Large");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Hit\\Hit_Sword_Small.wav", "Hit_Sword_Small");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Hit\\Hit_Energy_Medium.wav", "Hit_Energy_Medium");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Hit\\Hit_Ice.wav", "Hit_Ice");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Hit\\Hit_Energy_Large.wav", "Hit_Energy_Large");




		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Archer\\AdventurerHunter_Attack_Hit.wav", "AdventurerHunter_Attack_Hit");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\Hit_Flame_Short.wav", "Hit_Flame_Short");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\Arson_Explosion.wav", "Arson_Explosion");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Knight\\Hit_Sword_Large.wav", "Hit_Sword_Large");
	
		{
			Skul_Head = new Skul_head();
			Skul_Head->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Player, Skul_Head);
			Transform* tr_head = Skul_Head->GetComponent<Transform>();
			tr_head->SetPosition(Vector3(pos.x, pos.y, -250.f));
			Skul_Head->GetComponent<Transform>()->SetScale(Vector3(15.f, 13.f, 0.f));
			Skul_Head->SetState(eState::Paused);
		}
		{
			Hit_Box = new HitBox_Player();
			Hit_Box->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetState(eState::Paused);
		}


		{
			_Hit_Effect = new Player_Hit_Effect;
			_Hit_Effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Hit_Effect);
			_Hit_Effect->SetState(eState::Paused);
		}
		{
			_Hit_Sword = new Hit_Sword;
			_Hit_Sword->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Hit_Sword);
			_Hit_Sword->SetState(eState::Paused);
		}		 
		{
			_Critical_Middle = new Hit_Critical_Middle;
			_Critical_Middle->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Critical_Middle);
			_Critical_Middle->SetState(eState::Paused);
		}
		{
			_Critical_High = new Hit_Critical_High;
			_Critical_High->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Critical_High);
			_Critical_High->SetState(eState::Paused);
		}
		{
			_Knight_Slash = new Slash_Effect;
			_Knight_Slash->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Knight_Slash);
			_Knight_Slash->SetState(eState::Paused);
		}
		{
			_DarkKnight = new Hit_DarkPaladin;
			_DarkKnight->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _DarkKnight);
			_DarkKnight->SetState(eState::Paused);
		}


		{
			for (int i = 0; i < 10; i++)
			{
				AfterImage_TEST[i] = new Player_AfterImage();
				AfterImage_TEST[i]-> Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Effect, AfterImage_TEST[i]);
				AfterImage_TEST[i]->Set_Owner(this); 
				AfterImage_TEST[i]->SetState(eState::Paused);
			}			
		}
		{
			Hit_Particle = new GameObject();
			Particle_DamageEffect* mr = Hit_Particle->AddComponent<Particle_DamageEffect>(Vector3());
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Hit_Particle);
			Hit_Particle->SetState(eState::Paused);
		}	


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\AttackA", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\AttackB", this) ;
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Fall", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\FallRepeat", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\JumpAttack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Skill", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Switch", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Walk", this);

		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\AttackA", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\AttackB", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Dash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Fall", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\FallRepeat", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Jump", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\JumpAttack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Skill", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Switch", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_Basic\\Walk", this, 1);

		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\AttackA", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\AttackB", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Fall", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\FallRepeat", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\JumpAttack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Walk", this);		

		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\AttackA", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\AttackB", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Dash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Fall", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\FallRepeat", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Jump", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\JumpAttack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\NoHead\\Walk", this, 1);

		at->PlayAnimation(L"Skul_BasicIdle", true);
		at->CompleteEvent(L"Skul_BasicAttackA") = std::bind(&Skul_Basic::attack_choice, this);		
		at->CompleteEvent(L"Skul_BasicAttackAR") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"Skul_BasicAttackB") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"Skul_BasicAttackBR") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"Skul_BasicJumpAttack") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"Skul_BasicJumpAttackR") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"Skul_BasicSkill") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"Skul_BasicSkillR") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"Skul_BasicSwitch") = std::bind(&Skul_Basic::switch_on_off, this);
		at->CompleteEvent(L"Skul_BasicSwitchR") = std::bind(&Skul_Basic::switch_on_off, this);

		at->CompleteEvent(L"NoHeadAttackA") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"NoHeadAttackAR") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"NoHeadAttackB") = std::bind(&Skul_Basic::attack_choice, this);
		at->CompleteEvent(L"NoHeadAttackBR") = std::bind(&Skul_Basic::attack_choice, this);	

		GameObject::Initialize();
	}

	void Skul_Basic::Update()
	{	
		tr = GetComponent<Transform>();
		pos = tr->GetPosition();		
		_velocity = _rigidbody->GetVelocity();
		_Ground_On = _Ground_check;

		{
			Transform* _Hit_Effect_TR = _Hit_Effect->GetComponent<Transform>();
			if (mDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 15, pos.y, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 15, pos.y, pos.z - 1));
		}
		{
			Transform* _Hit_Effect_TR = _Hit_Sword->GetComponent<Transform>();
			if (mDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 15, pos.y, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 15, pos.y, pos.z - 1));
		}
		{
			Transform * _Hit_Effect_TR = _Knight_Slash->GetComponent<Transform>();
			if (mDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 15, pos.y, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 15, pos.y, pos.z - 1));
		}
		{
			Transform* _Hit_Effect_TR = _DarkKnight->GetComponent<Transform>();
			if (mDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 15, pos.y, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 15, pos.y, pos.z - 1));
		}

		
		if (_switch == true)
		{
			_attack_Acheck = true;
			as->Play("Default_Switch");
			_State = Skul_Basic::Skul_Basic_State::Switch;
			if (mDir == 1)		
				at->PlayAnimation(L"Skul_BasicSwitch", true);			
			else
				at->PlayAnimation(L"Skul_BasicSwitchR", true);		
		}

		if (_Skulhead == true)
		{
			_skulhead_time += Time::DeltaTime();
			if (_skulhead_time > 3)
			{
				_Skulhead = false;
				Skul_Head->SetHead = false;
				Skul_Head->SetState(eState::Paused);
				_skulhead_time = 0.f;

				if (mDir == 1)
					at->PlayAnimation(L"Skul_BasicIdle", true);
				else 	
					at->PlayAnimation(L"Skul_BasicIdleR", true);			
			}
		}

		switch (_State)
		{
		case jk::Skul_Basic::Skul_Basic_State::Idle:idle();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Move:move();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Jump:jump();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Fall:fall();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Falling:falling();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Dash:dash();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Attack_A:attack_a();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Attack_B:attack_b();
			break;

		case jk::Skul_Basic::Skul_Basic_State::JumpAttack:jumpattack();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Skill_A:skill_a();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Skill_B:skill_b();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Stun:stun();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Switch:change();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Death:death();
			break;

		case jk::Skul_Basic::Skul_Basic_State::Hit:hit();
			break;			

		default:
			break;
		}

		Input_move();
		tr->SetPosition(pos);
		SetPlayer_Pos(pos);
		GameObject::Update();
	}

	void Skul_Basic::LateUpdate()
	{
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_attack_Acheck==true)
		{		
			Hit_Box->SetSize(Vector2(50.f, 60.f));
			Hit_Box->SetState(eState::Active);
			if (mDir == 1)			
				HitBox_TR->SetPosition(Vector3(pos.x + 20, pos.y, pos.z));			
			else			
				HitBox_TR->SetPosition(Vector3(pos.x - 20, pos.y, pos.z));			
		}
		else if (_attack_Bcheck==true)
		{
			Hit_Box->SetSize(Vector2(50.f, 60.f));
			Hit_Box->SetState(eState::Active);
			if (mDir == 1)
				HitBox_TR->SetPosition(Vector3(pos.x + 20, pos.y, pos.z));
			else
				HitBox_TR->SetPosition(Vector3(pos.x - 20, pos.y, pos.z));
		}
		else
		{
			Hit_Box->SetState(eState::Paused);			
		}		
		
		_collider->SetSize(Vector2(0.35f, 0.5f));
		if(mDir ==1)
			_collider->SetCenter(Vector2(5.0f, -2.5f));
		else
			_collider->SetCenter(Vector2(-5.0f, -2.5f));

		GameObject::LateUpdate();		
	}

	void Skul_Basic::Render()
	{
		GameObject::Render();
	}

	void Skul_Basic::idle()
	{
		if (Input::GetKey(eKeyCode::RIGHT)
			|| Input::GetKey(eKeyCode::LEFT))
		{
			_State = Skul_Basic_State::Move;
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				at->PlayAnimation(L"Skul_BasicWalk", true);
			
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadWalk", true);
				mDir = 1;

			}
			else if (Input::GetKey(eKeyCode::LEFT))
			{
				at->PlayAnimation(L"Skul_BasicWalkR", true);
				
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadWalkR", true);
				mDir = -1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::C))
		{
			_State = Skul_Basic_State::Jump;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicJump", true);
				
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJump", true);
				
				_rigidbody->SetVelocity(Vector2(0.f, 350.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicJumpR", true);

				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpR", true);

				_rigidbody->SetVelocity(Vector2(0.f, 350.f));
				_rigidbody->SetGround(false);	mDir = -1;
			}
			_jump++;
		}

		if (Input::GetKey(eKeyCode::X))
		{		
			_State = Skul_Basic_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicAttackA", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicAttackAR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadAttackAR", true);
				mDir = -1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{

			_State = Skul_Basic_State::Dash;

			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicDash", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadDash", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicDashR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}						
		}

		if (Input::GetKey(eKeyCode::A))
		{
			if (_Skulhead == false)
			{
				_State = Skul_Basic_State::Skill_A;
				RigidBody* head_rjg = Skul_Head->Getrigidbody();
				head_rjg->SetGround(false);				
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicSkill", true);
					_Skulhead = true;
					Skul_Head->Setattack(true);				
					Skul_Head->SetHead = true;
					Skul_Head->SetDirection(1);
					Skul_Head->SetState(eState::Active);
					Skul_Head->SetBeforeAttackPos(pos);
					Skul_Head->GetComponent<Transform>()->SetPositionXY(Vector2{ tr->GetPosition().x+45, tr->GetPosition().y +10 });
					Skul_Head->GetComponent<RigidBody>()->SetVelocity(Vector2{ 450.f, 0.0f });
					Skul_Head->GetComponent<RigidBody>()->SetFriction(true);
					Skul_Head->GetComponent<RigidBody>()->SetGravity(true);
					_skulheadtemp = pos;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicSkillR", true);
					_Skulhead = true;		
					Skul_Head->SetHead = true;
					Skul_Head->Setattack(true);
					Skul_Head->SetDirection(-1);
					Skul_Head->SetState(eState::Active);
					Skul_Head->SetBeforeAttackPos(pos);
					Skul_Head->GetComponent<Transform>()->SetPositionXY(Vector2{ tr->GetPosition().x-45, tr->GetPosition().y + 10 });		
					Skul_Head->GetComponent<RigidBody>()->SetVelocity(Vector2{ -450.f, 0.0f });
					Skul_Head->GetComponent<RigidBody>()->SetFriction(true);
					Skul_Head->GetComponent<RigidBody>()->SetGravity(true);
					_skulheadtemp = pos;
				}					
			}
		}

		if (Input::GetKey(eKeyCode::S))
		{
			if (_Skulhead == true)
			{
				_State = Skul_Basic_State::Skill_B;
				if (mDir == 1)
				{
					at->PlayAnimation(L"NoHeadFall", false);
					mDir = 1; 
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"NoHeadFallR", false);
					mDir = -1; 
				}
				Transform* tr_head = Skul_Head->GetComponent<Transform>();
				Vector3 headbullet = tr_head->GetPosition();
				pos = Vector3(headbullet.x, headbullet.y+30, headbullet.z);
				Skul_Head->Setattack(true);
				Skul_Head->SetDirection(mDir);
				_rigidbody->SetGround(false);
				_Ground_check = false;
			}
			else
			{
			}
		}

		if (_fall_check == true)
		{
			_fallcheck_time += Time::DeltaTime();
			if (_fallcheck_time > 0.5)
			{
				_State = Skul_Basic_State::Fall;
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicFall", false);
					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadFall", false);
					mDir = 1;
				}
				if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicFallR", false);
					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadFallR", false);
					mDir = -1;
				}

				_fallcheck_time = 0;
			}
		}
	}

	void Skul_Basic::move()
	{
		if (Input::GetKeyUp(eKeyCode::RIGHT)
			|| Input::GetKeyUp(eKeyCode::LEFT))
		{
			_State = Skul_Basic_State::Idle;
			if (Input::GetKeyUp(eKeyCode::RIGHT))
			{
				at->PlayAnimation(L"Skul_BasicIdle", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadIdle", true);
				mDir = 1;
			}
			else if (Input::GetKeyUp(eKeyCode::LEFT))
			{
				at->PlayAnimation(L"Skul_BasicIdleR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadIdleR", true);
				mDir = -1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::C))
		{
			_State = Skul_Basic_State::Jump;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicJump", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJump", true);
				_rigidbody->SetVelocity(Vector2(0.f, 350.f));
				_rigidbody->SetGround(false);	mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicJumpR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpR", true);
				_rigidbody->SetVelocity(Vector2(0.f, 350.f));
				_rigidbody->SetGround(false);	mDir = -1;
			}
			_jump++;
		}


		if (Input::GetKey(eKeyCode::X))
		{
			_State = Skul_Basic_State::Attack_A;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicAttackA", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadAttackA", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicAttackAR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadAttackAR", true);
				mDir = -1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Basic_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicDash", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadDash", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicDashR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}

		if (Input::GetKey(eKeyCode::A))
		{
			if (_Skulhead == false)
			{
				_State = Skul_Basic_State::Skill_A;
				RigidBody* head_rjg = Skul_Head->Getrigidbody();
				head_rjg->SetGround(false);
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicSkill", true);
					_Skulhead = true;
					Skul_Head->Setattack(true);
					Skul_Head->SetHead = true;
					Skul_Head->SetDirection(1);
					Skul_Head->SetState(eState::Active);
					Skul_Head->SetBeforeAttackPos(pos);
					Skul_Head->GetComponent<Transform>()->SetPositionXY(Vector2{ tr->GetPosition().x + 45, tr->GetPosition().y + 10 });
					Skul_Head->GetComponent<RigidBody>()->SetVelocity(Vector2{ 450.f, 0.0f });
					Skul_Head->GetComponent<RigidBody>()->SetFriction(true);
					Skul_Head->GetComponent<RigidBody>()->SetGravity(true);
					_skulheadtemp = pos;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicSkillR", true);
					_Skulhead = true;
					Skul_Head->SetHead = true;
					Skul_Head->Setattack(true);
					Skul_Head->SetDirection(-1);
					Skul_Head->SetState(eState::Active);
					Skul_Head->SetBeforeAttackPos(pos);
					Skul_Head->GetComponent<Transform>()->SetPositionXY(Vector2{ tr->GetPosition().x - 45, tr->GetPosition().y + 10 });
					Skul_Head->GetComponent<RigidBody>()->SetVelocity(Vector2{ -450.f, 0.0f });
					Skul_Head->GetComponent<RigidBody>()->SetFriction(true);
					Skul_Head->GetComponent<RigidBody>()->SetGravity(true);
					_skulheadtemp = pos;
				}
			}
		}

		if (Input::GetKey(eKeyCode::S))
		{
			if (_Skulhead == true)
			{
				_State = Skul_Basic_State::Skill_B;
				if (mDir == 1)
				{
					at->PlayAnimation(L"NoHeadFall", false);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"NoHeadFallR", false);
					mDir = -1;
				}
				Transform* tr_head = Skul_Head->GetComponent<Transform>();
				Vector3 headbullet = tr_head->GetPosition();
				pos = Vector3(headbullet.x, headbullet.y + 30, headbullet.z);
				Skul_Head->Setattack(true);
				Skul_Head->SetDirection(mDir);
				_rigidbody->SetGround(false);
				_Ground_check = false;
			}
			else
			{
			}
		}
	}

	void Skul_Basic::jump()
	{		
		as->Play("Default_Jump");
		_Ground_check = false;
		_SkyGround_check = false;
		if((_velocity.y <= 0.f)||(_jump>=2))
		{
			_State = Skul_Basic_State::Fall;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicFall", false);	
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadFall", false);
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicFallR", false);		
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadFallR", false);
				mDir = -1;
			}
			_jump = 0;
		}

		if (_jump < 3)
		{
			if (Input::GetKeyDown(eKeyCode::C))
			{
				as->Play("Default_Jump_Air");
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicJump", true);
					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadJump", true);
					_rigidbody->SetVelocity(Vector2(0.f, 350.f));
					_rigidbody->SetGround(false);	mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicJumpR", true);
					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadJumpR", true);
					_rigidbody->SetVelocity(Vector2(0.f, 350.f));
					_rigidbody->SetGround(false);	mDir = -1;
				}
				_jump++;
			}
		}

		if (Input::GetKeyDown(eKeyCode::X))
		{
			if (mDir == 1)
			{
				_State = Skul_Basic_State::JumpAttack;
				at->PlayAnimation(L"Skul_BasicJumpAttack", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpAttack", true);
			}
			if (mDir == -1)
			{
				_State = Skul_Basic_State::JumpAttack;
				at->PlayAnimation(L"Skul_BasicJumpAttackR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpAttackR", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Basic_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicDash", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadDash", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicDashR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}

		if (Input::GetKey(eKeyCode::A))
		{
			if (_Skulhead == false)
			{
				_State = Skul_Basic_State::Skill_A;
				RigidBody* head_rjg = Skul_Head->Getrigidbody();
				head_rjg->SetGround(false);
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicSkill", true);
					_Skulhead = true;
					Skul_Head->Setattack(true);
					Skul_Head->SetHead = true;
					Skul_Head->SetDirection(1);
					Skul_Head->SetState(eState::Active);
					Skul_Head->SetBeforeAttackPos(pos);
					Skul_Head->GetComponent<Transform>()->SetPositionXY(Vector2{ tr->GetPosition().x + 45, tr->GetPosition().y + 10 });
					Skul_Head->GetComponent<RigidBody>()->SetVelocity(Vector2{ 450.f, 0.0f });
					Skul_Head->GetComponent<RigidBody>()->SetFriction(true);
					Skul_Head->GetComponent<RigidBody>()->SetGravity(true);
					_skulheadtemp = pos;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicSkillR", true);
					_Skulhead = true;
					Skul_Head->SetHead = true;
					Skul_Head->Setattack(true);
					Skul_Head->SetDirection(-1);
					Skul_Head->SetState(eState::Active);
					Skul_Head->SetBeforeAttackPos(pos);
					Skul_Head->GetComponent<Transform>()->SetPositionXY(Vector2{ tr->GetPosition().x - 45, tr->GetPosition().y + 10 });
					Skul_Head->GetComponent<RigidBody>()->SetVelocity(Vector2{ -450.f, 0.0f });
					Skul_Head->GetComponent<RigidBody>()->SetFriction(true);
					Skul_Head->GetComponent<RigidBody>()->SetGravity(true);
					_skulheadtemp = pos;
				}
			}
		}

		if (Input::GetKey(eKeyCode::S))
		{
			if (_Skulhead == true)
			{
				_State = Skul_Basic_State::Skill_B;
				if (mDir == 1)
				{
					at->PlayAnimation(L"NoHeadFall", false);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"NoHeadFallR", false);
					mDir = -1;
				}
				Transform* tr_head = Skul_Head->GetComponent<Transform>();
				Vector3 headbullet = tr_head->GetPosition();
				pos = Vector3(headbullet.x, headbullet.y + 30, headbullet.z);
				Skul_Head->Setattack(true);
				Skul_Head->SetDirection(mDir);
				_rigidbody->SetGround(false);
				_Ground_check = false;
			}
			else
			{
			}
		}
	}

	void Skul_Basic::fall()
	{
		_Ground_check = false;
		_SkyGround_check = false;
		if (_jump < 3)
		{
			if (Input::GetKeyDown(eKeyCode::C))
			{
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicJump", true);
					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadJump", true);
					_rigidbody->SetVelocity(Vector2(0.f, 350.f));
					_rigidbody->SetGround(false);	mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicJumpR", true);
					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadJumpR", true);
					_rigidbody->SetVelocity(Vector2(0.f, 350.f));
					_rigidbody->SetGround(false);	mDir = -1;
				}
				_jump++;
			}
		}


		_time += Time::DeltaTime();
		if (_time > 1.f)
		{
			_State = Skul_Basic_State::Falling;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicFallRepeat", true);	
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadFallRepeat", true);
				mDir = 1;  _fallcheck = 2;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicFallRepeatR", true);	
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadFallRepeatR", true);
				mDir = -1; _fallcheck = 2;
			}
			_time = 0;
		}
		if (Input::GetKeyDown(eKeyCode::X))
		{
			if (mDir == 1)
			{
				_State = Skul_Basic_State::JumpAttack;
				at->PlayAnimation(L"Skul_BasicJumpAttack", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpAttack", true);
			}
			if (mDir == -1)
			{
				_State = Skul_Basic_State::JumpAttack;
				at->PlayAnimation(L"Skul_BasicJumpAttackR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpAttackR", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Basic_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicDash", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpDash", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicDashR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}

		if (Input::GetKey(eKeyCode::A))
		{
			if (_Skulhead == false)
			{
				_State = Skul_Basic_State::Skill_A;
				RigidBody* head_rjg = Skul_Head->Getrigidbody();
				head_rjg->SetGround(false);
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicSkill", true);
					_Skulhead = true;
					Skul_Head->Setattack(true);
					Skul_Head->SetHead = true;
					Skul_Head->SetDirection(1);
					Skul_Head->SetState(eState::Active);
					Skul_Head->SetBeforeAttackPos(pos);
					Skul_Head->GetComponent<Transform>()->SetPositionXY(Vector2{ tr->GetPosition().x + 45, tr->GetPosition().y + 10 });
					Skul_Head->GetComponent<RigidBody>()->SetVelocity(Vector2{ 450.f, 0.0f });
					Skul_Head->GetComponent<RigidBody>()->SetFriction(true);
					Skul_Head->GetComponent<RigidBody>()->SetGravity(true);
					_skulheadtemp = pos;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicSkillR", true);
					_Skulhead = true;
					Skul_Head->SetHead = true;
					Skul_Head->Setattack(true);
					Skul_Head->SetDirection(-1);
					Skul_Head->SetState(eState::Active);
					Skul_Head->SetBeforeAttackPos(pos);
					Skul_Head->GetComponent<Transform>()->SetPositionXY(Vector2{ tr->GetPosition().x - 45, tr->GetPosition().y + 10 });
					Skul_Head->GetComponent<RigidBody>()->SetVelocity(Vector2{ -450.f, 0.0f });
					Skul_Head->GetComponent<RigidBody>()->SetFriction(true);
					Skul_Head->GetComponent<RigidBody>()->SetGravity(true);
					_skulheadtemp = pos;
				}
			}
		}

		if (Input::GetKey(eKeyCode::S))
		{
			if (_Skulhead == true)
			{
				_State = Skul_Basic_State::Skill_B;
				if (mDir == 1)
				{
					at->PlayAnimation(L"NoHeadFall", false);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"NoHeadFallR", false);
					mDir = -1;
				}
				Transform* tr_head = Skul_Head->GetComponent<Transform>();
				Vector3 headbullet = tr_head->GetPosition();
				pos = Vector3(headbullet.x, headbullet.y + 30, headbullet.z);
				Skul_Head->Setattack(true);
				Skul_Head->SetDirection(mDir);
				_rigidbody->SetGround(false);
				_Ground_check = false;
			}
			else
			{
			}
		}
	}

	void Skul_Basic::falling()
	{
		_Ground_check = false;
		_SkyGround_check = false;
		if (Input::GetKeyDown(eKeyCode::X))
		{
			if (mDir == 1)
			{
				_State = Skul_Basic_State::JumpAttack;
				at->PlayAnimation(L"Skul_BasicJumpAttack", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpAttack", true);
			}
			if (mDir == -1)
			{
				_State = Skul_Basic_State::JumpAttack;
				at->PlayAnimation(L"Skul_BasicJumpAttackR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadJumpAttackR", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			_State = Skul_Basic_State::Dash;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicDash", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadDash", true);
				_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				mDir = 1;
			}
			if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicDashR", true);
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadDashR", true);
				_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				mDir = -1;
			}
		}

		if (Input::GetKey(eKeyCode::A))
		{
			if (_Skulhead == false)
			{
				_State = Skul_Basic_State::Skill_A;
				RigidBody* head_rjg = Skul_Head->Getrigidbody();
				head_rjg->SetGround(false);
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicSkill", true);
					_Skulhead = true;
					Skul_Head->Setattack(true);
					Skul_Head->SetHead = true;
					Skul_Head->SetDirection(1);
					Skul_Head->SetState(eState::Active);
					Skul_Head->SetBeforeAttackPos(pos);
					Skul_Head->GetComponent<Transform>()->SetPositionXY(Vector2{ tr->GetPosition().x + 45, tr->GetPosition().y + 10 });
					Skul_Head->GetComponent<RigidBody>()->SetVelocity(Vector2{ 450.f, 0.0f });
					Skul_Head->GetComponent<RigidBody>()->SetFriction(true);
					Skul_Head->GetComponent<RigidBody>()->SetGravity(true);
					_skulheadtemp = pos;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicSkillR", true);
					_Skulhead = true;
					Skul_Head->SetHead = true;
					Skul_Head->Setattack(true);
					Skul_Head->SetDirection(-1);
					Skul_Head->SetState(eState::Active);
					Skul_Head->SetBeforeAttackPos(pos);
					Skul_Head->GetComponent<Transform>()->SetPositionXY(Vector2{ tr->GetPosition().x - 45, tr->GetPosition().y + 10 });
					Skul_Head->GetComponent<RigidBody>()->SetVelocity(Vector2{ -450.f, 0.0f });
					Skul_Head->GetComponent<RigidBody>()->SetFriction(true);
					Skul_Head->GetComponent<RigidBody>()->SetGravity(true);
					_skulheadtemp = pos;
				}
			}
		}

		if (Input::GetKey(eKeyCode::S))
		{
			if (_Skulhead == true)
			{
				_State = Skul_Basic_State::Skill_B;
				if (mDir == 1)
				{
					at->PlayAnimation(L"NoHeadFall", false);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"NoHeadFallR", false);
					mDir = -1;
				}
				Transform* tr_head = Skul_Head->GetComponent<Transform>();
				Vector3 headbullet = tr_head->GetPosition();
				pos = Vector3(headbullet.x, headbullet.y + 30, headbullet.z);
				Skul_Head->Setattack(true);
				Skul_Head->SetDirection(mDir);
				_rigidbody->SetGround(false);
				_Ground_check = false;
			}
			else
			{
			}
		}
	}

	void Skul_Basic::dash()
	{
		as->Play("Default_Dash");
		_Leftmove_Lock = false;
		_Rightmove_Lock = false;
		_Ground_check = false;
		_attack_Acheck = false;
		_attack_Bcheck = false;
		_rigidbody->ClearVelocityY();
		if (mDir == 1 && _velocity.x <= 220.0)
		{
			_State = Skul_Basic_State::Idle;
			at->PlayAnimation(L"Skul_BasicIdle", true);
			if (_Skulhead == true)
				at->PlayAnimation(L"NoHeadIdle", true);
			_rigidbody->SetGround(false);
			_rigidbody->ClearVelocityX();
			mDir = 1;
		}
		else if (mDir == -1 && _velocity.x >= -220.0)
		{
			_State = Skul_Basic_State::Idle;
			at->PlayAnimation(L"Skul_BasicIdleR", true);
			if (_Skulhead == true)
				at->PlayAnimation(L"NoHeadIdleR", true);
			_rigidbody->SetGround(false);
			_rigidbody->ClearVelocityX();
			mDir = -1;
		}		
		//else
		{
			timeSinceLastImage += Time::DeltaTime();
			if (timeSinceLastImage >= delayBetweenImages)
			{
				for (int i = 0; i < 10; i++)
				{
					if (AfterImage_TEST[i]->_AfterImage == false)
					{
						int direction = (mDir == 1) ? 1 : -1;
						AfterImage_TEST[i]->Set_Basic_Dash(direction, Vector3(pos.x, pos.y, pos.z+1));
						AfterImage_TEST[i]->SetState(eState::Active);
						AfterImage_TEST[i]->_AfterImage = true;
						timeSinceLastImage = 0.0f;  // 시간 초기화
						break;  // 하나의 잔상만 생성한 후 for문 종료					
					}
				}				
			}
		}
	}

	void Skul_Basic::attack_a()
	{		
		_attack_Acheck = true;		
		as->Play("Skul_Atk1");		
		
		if (Input::GetKeyDown(eKeyCode::X))
		{						
			_attack = true;				
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{			
			mDir = 1;			
		}
		else if (Input::GetKeyDown(eKeyCode::LEFT))
		{			
			mDir = -1;
		}
	}
	void Skul_Basic::attack_b()
	{			
		as->Play("Skul_Atk2");
		_attack = false;
		_attack_Bcheck = true;

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mDir = 1;
		}
		else if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mDir = -1;
		}
	}
	void Skul_Basic::jumpattack()
	{
		as->Play("Skul_Atk2");
		_attack_Acheck = true;
	}

	void Skul_Basic::skill_a()
	{
		as->Play("Hit_Blunt_Small");
	}
	void Skul_Basic::skill_b()
	{
	}

	void Skul_Basic::stun()
	{
		_attack_time += Time::DeltaTime();
		if (_attack_time > 1)
		{
			_State = Skul_Basic_State::Idle;
			_attack_time = 0;
			_Leftmove_Lock = false;
			_Rightmove_Lock = false;
		}
	}

	void Skul_Basic::change()
	{
		{
			if (mDir == 1)
			{
				_rigidbody->SetVelocity(Vector2(100.f, 0.f));				
				_switch = false; _Ground_check = false;
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(-100.f, 0.f));				
				_switch = false; _Ground_check = false; _rigidbody->SetGround(false);
			}
		}
	}
	void Skul_Basic::death()
	{

	}

	void Skul_Basic::hit()
	{
		if (_hit == true)
		{
			_Ground_check = false;
			_rigidbody->SetGround(false);
			if (HitDir == 1)
				_rigidbody->SetVelocity(Vector2(-75.f, 175.f));

			if (HitDir == -1)
				_rigidbody->SetVelocity(Vector2(75.f, 175.f));
			_hit = false;
		}
	}

	void Skul_Basic::OnCollisionEnter(Collider2D* other)
	{		
		if (Skul_head* _head = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			if (_Skulhead == true)
			{
				if (_State == Skul_Basic_State::Dash)
				{
				}
				else
				{
					_State = Skul_Basic_State::Idle;
					if (mDir == 1)
						at->PlayAnimation(L"Skul_BasicIdle", true);
					else
						at->PlayAnimation(L"Skul_BasicIdleR", true);
				}
				Setskillcheck(false);
				_Skulhead = false;
				_skulhead_time = 0.f;
				Skul_Head->SetState(eState::Paused);
			}
		}

		//spring
		if (Mushroom_Spring* _Spring = dynamic_cast<Mushroom_Spring*>(other->GetOwner()))
		{
				Transform* Ground_TR = other->GetOwner()->GetComponent<Transform>();
				Collider2D* Ground_Col = other->GetOwner()->GetComponent<Collider2D>();
				Vector3 Ground_pos = Ground_TR->GetPosition();
				float Gr_Size = Ground_Col->GetScale().y / 2;
				float Gr_Top_pos = Ground_pos.y + Gr_Size;

				float Skul_halfsize = _collider->GetScale().y / 2;
				float skul_footpos = pos.y - Skul_halfsize;

				if (skul_footpos > Gr_Top_pos)
				{
					_rigidbody->ClearVelocity();
					_Ground_check = true;
					_rigidbody->SetGround(false);
					_rigidbody->SetVelocity(Vector2(0.f, 950.f));
							
					_State = Skul_Basic_State::Jump;
					if (mDir == 1)
					{
						at->PlayAnimation(L"Skul_BasicJump", true);
							
						if (_Skulhead == true)
							at->PlayAnimation(L"NoHeadJump", true);
					}
					else
					{
						at->PlayAnimation(L"Skul_BasicJumpR", true);
							
						if (_Skulhead == true)
							at->PlayAnimation(L"NoHeadJumpR", true);
					}					
				}
		}

		if (Sofa_Spring* _Spring = dynamic_cast<Sofa_Spring*>(other->GetOwner()))
		{
			Transform* Ground_TR = other->GetOwner()->GetComponent<Transform>();
			Collider2D* Ground_Col = other->GetOwner()->GetComponent<Collider2D>();
			Vector3 Ground_pos = Ground_TR->GetPosition();
			float Gr_Size = Ground_Col->GetScale().y / 2;
			float Gr_Top_pos = Ground_pos.y + Gr_Size;

			float Skul_halfsize = _collider->GetScale().y / 2;
			float skul_footpos = pos.y - Skul_halfsize;

			if (skul_footpos > Gr_Top_pos)
			{
				_rigidbody->ClearVelocity();
				_Ground_check = true;
				_rigidbody->SetGround(false);
				_rigidbody->SetVelocity(Vector2(0.f, 700.f));

				_State = Skul_Basic_State::Jump;
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicJump", true);

					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadJump", true);
				}
				else
				{
					at->PlayAnimation(L"Skul_BasicJumpR", true);

					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadJumpR", true);
				}
			}
		}

		//Monster
		if (HitBox_Monster* _Monster = dynamic_cast<HitBox_Monster*>(other->GetOwner()))
		{		
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = _Monster->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();

			if(_Monster->GetSound() ==1)
				as->Play("Hit_Blunt_Large");
			else
				as->Play("Hit_Sword_Small");

			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(-1);
				_Hit_Effect->SetState(eState::Active);
			}
		}

		if (Monster_Hammer* Hammer = dynamic_cast<Monster_Hammer*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;


			hammer_st = Hammer->GetState();
			
			if (hammer_st == Monster_Hammer::Monster_Hammer_State::Tackle)
			{
				Transform* hittr = Hammer->GetComponent<Transform>();
				Vector3 hitpos = hittr->GetPosition();
				as->Play("Hit_Blunt_Large");
				if (hitpos.x > pos.x)
				{
					_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(1);
					_Hit_Effect->SetState(eState::Active);
				}
				else
				{
					_rigidbody->SetVelocity(Vector2(50.f, 0.f));
					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(-1);
					_Hit_Effect->SetState(eState::Active);
				}
			}
		}

		if (Monster_GoldHammer* GoldHammer = dynamic_cast<Monster_GoldHammer*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Goldham_st = GoldHammer->GetState();
			
			if (Goldham_st == Monster_GoldHammer::Monster_GoldHammer_State::Tackle)
			{
				Transform* hittr = GoldHammer->GetComponent<Transform>();
				Vector3 hitpos = hittr->GetPosition();
				as->Play("Hit_Blunt_Large");
				if (hitpos.x > pos.x)
				{
					_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(1);
					_Hit_Effect->SetState(eState::Active);
				}
				else
				{
					_rigidbody->SetVelocity(Vector2(50.f, 0.f));
					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(-1);
					_Hit_Effect->SetState(eState::Active);
				}
			}
		}

		if (Monster_Bullet* Bullet = dynamic_cast<Monster_Bullet*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;


			if(Bullet->Getsound()==0)
				as->Play("Hit_Energy_Medium");		
			else if(Bullet->Getsound() ==1)
				as->Play("Hit_Ice");
			
			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(-1);
				_Hit_Effect->SetState(eState::Active);
			}		
		}

		if (Monster_Ent_GroundAttack* Bullet = dynamic_cast<Monster_Ent_GroundAttack*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			
			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(-1);
				_Hit_Effect->SetState(eState::Active);
			}
		}

		//MiniBoss
		if (Mini_Boss*  Boss = dynamic_cast<Mini_Boss*>(other->GetOwner()))
		{
		}

		if (HitBox_Archer* HitBox = dynamic_cast<HitBox_Archer*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			as->Play("Hit_Blunt_Large");
			Transform* hittr = HitBox->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Knight_Slash->SetDirection(1);
				_Knight_Slash->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
				_Knight_Slash->_effect_animation = true;
				_Knight_Slash->SetDirection(-1);
				_Knight_Slash->SetState(eState::Active);
			}
		}

		if (MiniBoss_Bullet_Archer* Bullet = dynamic_cast<MiniBoss_Bullet_Archer*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			as->Play("AdventurerHunter_Attack_Hit"); 
			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
				_Hit_Sword->_effect_animation = true;
				_Hit_Sword->SetDirection(-1);
				_Hit_Sword->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
				_Hit_Sword->_effect_animation = true;
				_Hit_Sword->SetDirection(1);
				_Hit_Sword->SetState(eState::Active);
			}
		}

		if (Archer_Trap* Bullet = dynamic_cast<Archer_Trap*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;
			else
			{
				_State = Skul_Basic_State::Stun;
				_Leftmove_Lock = true;
				_Rightmove_Lock = true;
				if (mDir == 1)
					at->PlayAnimation(L"Skul_BasicIdle", true);
				else
					at->PlayAnimation(L"Skul_BasicIdleR", true);
			}			
		}

		if (HitBox_Knight* HitBox = dynamic_cast<HitBox_Knight*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

		
			Transform* hittr = HitBox->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Knight_Slash->SetDirection(1);
				_Knight_Slash->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
				_Knight_Slash->_effect_animation = true;
				_Knight_Slash->SetDirection(-1);
				_Knight_Slash->SetState(eState::Active);
			}
		}

		if (MiniBoss_Bullet_Knight* Bullet = dynamic_cast<MiniBoss_Bullet_Knight*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			
			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
				_Hit_Sword->_effect_animation = true;
				_Hit_Sword->SetDirection(-1);
				_Hit_Sword->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
				_Hit_Sword->_effect_animation = true;
				_Hit_Sword->SetDirection(1);
				_Hit_Sword->SetState(eState::Active);
			}
		}

		if (Knight_Energe_Blast* Bullet = dynamic_cast<Knight_Energe_Blast*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
				HitDir = -1;
			else
				HitDir = 1;
			_State = Skul_Basic_State::Hit;
		}

		if (Knight_UltimateSkill_Projectile* Bullet = dynamic_cast<Knight_UltimateSkill_Projectile*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			
			as->Play("Hit_Sword_Large");
			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				HitDir = -1;
				_rigidbody->SetVelocity(Vector2(-50.f, 50.f));

				_DarkKnight->_effect_animation = true;
				_DarkKnight->SetDirection(-1);
				_DarkKnight->SetState(eState::Active);
			}
			else
			{
				HitDir = 1;
				_rigidbody->SetVelocity(Vector2(50.f, 50.f));

				_DarkKnight->_effect_animation = true;
				_DarkKnight->SetDirection(1);
				_DarkKnight->SetState(eState::Active);
			}
			_State = Skul_Basic_State::Hit;

			//if (mDir == 1)
			//{
			//	_rigidbody->SetVelocity(Vector2(-50.f, 50.f));
			//	_DarkKnight->_effect_animation = true;
			//	_DarkKnight->SetDirection(-1);
			//	_DarkKnight->SetState(eState::Active);
			//}
			//if (mDir == -1)
			//{
			//	_rigidbody->SetVelocity(Vector2(50.f, 50.f));
			//	_DarkKnight->_effect_animation = true;
			//	_DarkKnight->SetDirection(1);
			//	_DarkKnight->SetState(eState::Active);
			//}
		}

		if (Cleric_HolyThunder* Bullet = dynamic_cast<Cleric_HolyThunder*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
				HitDir = -1;
			else
				HitDir = 1;
			_State = Skul_Basic_State::Hit;
		}

		if (HitBox_Mage* Bullet = dynamic_cast<HitBox_Mage*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			as->Play("Arson_Explosion");
			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
				HitDir = -1;
			else
				HitDir = 1;
			_State = Skul_Basic_State::Hit;
		}

		if (Mage_FireBoom* Bullet = dynamic_cast<Mage_FireBoom*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
				HitDir = -1;
			else
				HitDir = 1;
			_State = Skul_Basic_State::Hit;
		}

		if (Mage_FireBall* Bullet = dynamic_cast<Mage_FireBall*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
			else
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
		}

		if (Ultimate_On_Fire_Projectile* Bullet = dynamic_cast<Ultimate_On_Fire_Projectile*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
			else
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));				
		}		


		//Boss_YggDrasil
		if (HitBox_YggDrasil* Hit_Boss = dynamic_cast<HitBox_YggDrasil*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash || _State == Skul_Basic_State::Hit)
				return;

			Transform* hittr = Hit_Boss->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				HitDir = 1;
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}
			else
			{
				HitDir = -1;
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}

			_hit = true;
			_State = Skul_Basic_State::Hit;
		}

		if (Yggdrasil_Energy_Bomb* Hit_Boss = dynamic_cast<Yggdrasil_Energy_Bomb*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash || _State == Skul_Basic_State::Hit)
				return;

			Transform* hittr = Hit_Boss->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				HitDir = 1;
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}
			else
			{
				HitDir = -1;
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}

			_hit = true;
			_State = Skul_Basic_State::Hit;
		}
	
		if (Yggdrsil_Energy_Corps* Hit_Boss = dynamic_cast<Yggdrsil_Energy_Corps*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash || _State == Skul_Basic_State::Hit)
				return;

			Transform* hittr = Hit_Boss->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				HitDir = 1;
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}
			else
			{
				HitDir = -1;
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}

			_hit = true;
			_State = Skul_Basic_State::Hit;
		}

		//Boss_Layana
		if (HitBox_Layana* Hit_Boss = dynamic_cast<HitBox_Layana*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Hit_Boss->GetComponent<Transform>();
			Vector3 hitpos = hittr-> GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetDirection(1);
				_Hit_Effect->SetState(eState::Active);
			}
		}

		if (Homing_Pierce_LongHair* Bullet = dynamic_cast<Homing_Pierce_LongHair*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)			
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));			
			else		
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));			
		}

		if (Homing_Pierce_ShortHair* Bullet = dynamic_cast<Homing_Pierce_ShortHair*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
			else
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));
		}

		if (TwinMeteor_Effect* Bullet = dynamic_cast<TwinMeteor_Effect*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x+20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x-20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}

		if (Dimension_Pierce_BulletEffect* Bullet = dynamic_cast<Dimension_Pierce_BulletEffect*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}

		if (Rising_Pierce* Bullet = dynamic_cast<Rising_Pierce*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}

		if (Golden_Meteor_Bullet* Bullet = dynamic_cast<Golden_Meteor_Bullet*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}
		
		if (Latana_Awake_Rush_Bullet* Bullet = dynamic_cast<Latana_Awake_Rush_Bullet*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}

		if (Layana_Ground_Thunder* Bullet = dynamic_cast<Layana_Ground_Thunder*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}

		if (Layana_Awaken_Meteor_Projectile* Bullet = dynamic_cast<Layana_Awaken_Meteor_Projectile*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}

		if (Layana_Awaken_Homing_Attac* Bullet = dynamic_cast<Layana_Awaken_Homing_Attac*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}

		if (Dark_DimensionPierce_BulletEffect* Bullet = dynamic_cast<Dark_DimensionPierce_BulletEffect*>(other->GetOwner()))
		{
			if (_State == Skul_Basic_State::Dash)
				return;

			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (hitpos.x > pos.x)
			{
				_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x + 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				_rigidbody->SetVelocity(Vector2(50.f, 0.f));

				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x - 20, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
		}
		
		
		//Ground
		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{			
			_rigidbody->ClearVelocity();
			Transform* Ground_TR = other->GetOwner()->GetComponent<Transform>();
			Collider2D* Ground_Col = other->GetOwner()->GetComponent<Collider2D>();
			Vector3 Ground_pos = Ground_TR->GetPosition();
			float Gr_Size = Ground_Col->GetScale().y / 2;
			float Gr_Top_pos = Ground_pos.y + Gr_Size;
			float Skul_halfsize = _collider->GetScale().y / 2;
			float skul_footpos = pos.y - Skul_halfsize;
		}
		
		if (Ground_and_Wall* mGround = dynamic_cast<Ground_and_Wall*>(other->GetOwner()))
		{
			_Wall_check = true;
			_rigidbody->ClearVelocity();
			Transform* Ground_TR = other->GetOwner()->GetComponent<Transform>();
			Vector3 wall_pos = Ground_TR->GetPosition();
			if (_Wall_check == true)
			{
				if (pos.x < wall_pos.x)
				{
					_Rightmove_Lock = true;
					at->PlayAnimation(L"Skul_BasicIdle", true);
					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadIdle", true);
				}
				else if (pos.x > wall_pos.x)
				{
					_Leftmove_Lock = true;
					at->PlayAnimation(L"Skul_BasicIdleR", true);
					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadIdleR", true);
				}				
			}
		}

		if (Sky_Ground* mGround = dynamic_cast<Sky_Ground*>(other->GetOwner()))
		{			
			{			
				Transform* Ground_TR = other->GetOwner()->GetComponent<Transform>();
				Collider2D* Ground_Col = other->GetOwner()->GetComponent<Collider2D>();
				Vector3 Ground_pos = Ground_TR->GetPosition();
				float Gr_Size = Ground_Col->GetScale().y / 2;
				float Gr_Top_pos = Ground_pos.y + Gr_Size;
				float Skul_halfsize = _collider->GetScale().y / 2;
				float skul_footpos = pos.y - Skul_halfsize;
		
				if (skul_footpos > Gr_Top_pos)
				{
					_rigidbody->ClearVelocity();
					_Ground_check = true;
					_SkyGround_check = true;
			;		_rigidbody->SetGround(true);

					if (_State == Skul_Basic_State::JumpAttack || _State == Skul_Basic_State::Fall || _State == Skul_Basic_State::Falling)
					{
						_State = Skul_Basic_State::Idle;
						if (mDir == 1)
							at->PlayAnimation(L"Skul_BasicIdle", true);
						else
							at->PlayAnimation(L"Skul_BasicIdleR", true);
					}
				}				
			}
		}
	}
	void Skul_Basic::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{			
			if (_Ground_check == false)
			{
				_attack_Acheck = false;
				_Player_GRpos = pos;
				_fallcheck = 0;	_jump = 0;
				_rigidbody->SetGround(true);
				_Ground_check = true;	
				_Ground_On = true;
				mGround->_SkullOn = true; // 캐슬아리어에서 땅밟고 다음신넘어갈때 필요 및 몬스터들이 달려오는 기준	

				
				if (_Firsrt_Ground == false)
				{
					firstGroundcheck = true;
					_Firsrt_Ground = true;
				}

				if (_State == Skul_Basic_State::JumpAttack || _State == Skul_Basic_State::Fall || _State == Skul_Basic_State::Falling || _State == Skul_Basic_State::Hit)
				{
					_State = Skul_Basic_State::Idle;
					if (mDir == 1)
					{
						at->PlayAnimation(L"Skul_BasicIdle", true);
						if (_Skulhead == true)
							at->PlayAnimation(L"NoHeadIdle", true);
						mDir = 1;
					}
					else if (mDir == -1)
					{
						at->PlayAnimation(L"Skul_BasicIdleR", true);

						if (_Skulhead == true)
							at->PlayAnimation(L"NoHeadIdleR", true);
						mDir = -1;
					}
				}
			}
			else
			{
				Transform* GRTR = mGround->GetComponent<Transform>();
				Vector3 GRpos = GRTR->GetPosition();
				{
					Collider2D* GRCol = mGround->GetComponent<Collider2D>();
					float GrColsize = GRCol->GetScale().y / 2;
					float playercolsize = _collider->GetScale().y / 2;
					float Sizecheck = playercolsize + GrColsize + 2;


					float CheckPos = fabs(pos.y - GRpos.y);
					if (Sizecheck > CheckPos)
					{
						pos.y = GRpos.y + Sizecheck;
						tr->SetPosition(pos);
					}
				}



				_Player_GRpos = pos;
				if (Input::GetKeyDown(eKeyCode::Z))
				{
					_State = Skul_Basic_State::Dash;				
					if (mDir == 1)
					{
						at->PlayAnimation(L"Skul_BasicDash", true);
						if (_Skulhead == true)
							at->PlayAnimation(L"NoHeadDash", true);
						_rigidbody->SetVelocity(Vector2(250.f, 0.f));
						mDir = 1;
					}
					if (mDir == -1)
					{
						at->PlayAnimation(L"Skul_BasicDashR", true);
						if (_Skulhead == true)
							at->PlayAnimation(L"NoHeadDashR", true);
						_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
						mDir = -1;
					}
				}
				if (_State == Skul_Basic_State::Hit)
				{
					_Ground_check = false;
					_rigidbody->SetGround(false);
					if (HitDir == 1)
						_rigidbody->SetVelocity(Vector2(-75.f, 175.f));

					if (HitDir == -1)
						_rigidbody->SetVelocity(Vector2(75.f, 175.f));	
				}
			}
		}

		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			_Ground_On = true;
			if (_Ground_check == false)
			{
				_attack_Acheck = false;
				_Player_GRpos = pos;
				_fallcheck = 0;	_jump = 0;
				_rigidbody->SetGround(true);
				_Ground_check = true;				
				mGround->_SkullOn = true; // 캐슬아리어에서 땅밟고 다음신넘어갈때 필요 및 몬스터들이 달려오는 기준				

				if (_Firsrt_Ground == false)
				{
					firstGroundcheck = true;
					_Firsrt_Ground = true;
				}

				if (_State == Skul_Basic_State::JumpAttack || _State == Skul_Basic_State::Fall || _State == Skul_Basic_State::Falling || _State == Skul_Basic_State::Hit)
				{
					_State = Skul_Basic_State::Idle;
					if (mDir == 1)
					{
						at->PlayAnimation(L"Skul_BasicIdle", true);
						if (_Skulhead == true)
							at->PlayAnimation(L"NoHeadIdle", true);


						mDir = 1;
					}
					else if (mDir == -1)
					{
						at->PlayAnimation(L"Skul_BasicIdleR", true);

						if (_Skulhead == true)
							at->PlayAnimation(L"NoHeadIdleR", true);

						mDir = -1;
					}
				}
			}
			else
			{
				Transform* GRTR = mGround->GetComponent<Transform>();
				Vector3 GRpos = GRTR->GetPosition();
				{
					Collider2D* GRCol = mGround->GetComponent<Collider2D>();
					float GrColsize = GRCol->GetScale().y / 2;
					float playercolsize = _collider->GetScale().y / 2;
					float Sizecheck = playercolsize + GrColsize + 2;

					float CheckPos = fabs(pos.y - GRpos.y);
					if (Sizecheck > CheckPos)
					{
						pos.y = GRpos.y + Sizecheck;
						tr->SetPosition(pos);
					}
				}


				_Player_GRpos = pos;
				if (Input::GetKeyDown(eKeyCode::Z))
				{
					_State = Skul_Basic_State::Dash;
					if (mDir == 1)
					{
						at->PlayAnimation(L"Skul_BasicDash", true);
						if (_Skulhead == true)
							at->PlayAnimation(L"NoHeadDash", true);
						_rigidbody->SetVelocity(Vector2(250.f, 0.f));
						mDir = 1;
					}
					if (mDir == -1)
					{
						at->PlayAnimation(L"Skul_BasicDashR", true);
						if (_Skulhead == true)
							at->PlayAnimation(L"NoHeadDashR", true);
						_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
						mDir = -1;
					}
				}
				if (_State == Skul_Basic_State::Hit)
				{
					_Ground_check = false;
					_rigidbody->SetGround(false);
					if (HitDir == 1)
						_rigidbody->SetVelocity(Vector2(-75.f, 175.f));

					if (HitDir == -1)
						_rigidbody->SetVelocity(Vector2(75.f, 175.f));	
				}
			}	
		}

		if (Sky_Ground* mGround = dynamic_cast<Sky_Ground*>(other->GetOwner()))
		{

			_Ground_On = true;
			Transform* Ground_TR = other->GetOwner()->GetComponent<Transform>();
			Collider2D* Ground_Col = other->GetOwner()->GetComponent<Collider2D>();
			Vector3 Ground_pos = Ground_TR->GetPosition();
			float Gr_Size = Ground_Col->GetScale().y / 2;
			float Gr_Top_pos = Ground_pos.y + Gr_Size +10;
			float Skul_halfsize = _collider->GetScale().y / 2;
			float skul_footpos = pos.y - Skul_halfsize;

			if (_SkyGround_check == true)
			{
				Transform* GRTR = mGround->GetComponent<Transform>();
				Vector3 GRpos = GRTR->GetPosition();
				{
					Collider2D* GRCol = mGround->GetComponent<Collider2D>();
					float GrColsize = GRCol->GetScale().y / 2;
					float playercolsize = _collider->GetScale().y / 2;
					float Sizecheck = playercolsize + GrColsize + 2;


					float CheckPos = fabs(pos.y - GRpos.y);
					if (Sizecheck > CheckPos)
					{
						_attack_Acheck = false;
						pos.y = GRpos.y + Sizecheck;
						tr->SetPosition(pos);
					}
				}




				_Player_GRpos = pos;
				mGround->_SkullOn = true;
				_Ground_check = true;		
				_rigidbody->SetGround(true);
				if (_State == Skul_Basic_State::JumpAttack || _State == Skul_Basic_State::Fall || _State == Skul_Basic_State::Falling || _State == Skul_Basic_State::Hit)
				{
					_State = Skul_Basic_State::Idle;
					if (mDir == 1)
						at->PlayAnimation(L"Skul_BasicIdle", true);
					else
						at->PlayAnimation(L"Skul_BasicIdleR", true);
				}

				if (Input::GetKey(eKeyCode::V))
				{
					_rigidbody->SetVelocity(Vector2(0.f, -150.f));
					_Ground_check = false;
					_rigidbody->SetGround(false);
					_SkyGround_check = false;
				}
			}			
		}

		if (Cleric_Veteran_Sanctuary* Bullet = dynamic_cast<Cleric_Veteran_Sanctuary*>(other->GetOwner()))
		{
			if (_Hit_Effect->_endeffect == true)
			{
				if (mDir == 1)
				{
					_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(-1);
					_Hit_Effect->SetState(eState::Active);
				}
				if (mDir == -1)
				{
					_rigidbody->SetVelocity(Vector2(50.f, 0.f));

					_Hit_Effect->_effect_animation = true;
					_Hit_Effect->SetDirection(1);
					_Hit_Effect->SetState(eState::Active);
				}
				_Hit_Effect->_endeffect = false;
			}
		}
	}
	void Skul_Basic::OnCollisionExit(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			_Wall_check = false;
			_Rightmove_Lock = false;
			_Leftmove_Lock = false;		
			_Ground_On = false;
			if (_skul_act == true)
				mGround->_SkullOn = false;			
		}

		if (Ground_and_Wall* mGround = dynamic_cast<Ground_and_Wall*>(other->GetOwner()))
		{
			_Wall_check = false;
			_Rightmove_Lock = false;
			_Leftmove_Lock = false;	
		}

		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			_Ground_check = false;
			_rigidbody->SetGround(false);
			_fall_check = true;
			_Ground_On = false;
			if (_skul_act == true)
				mGround->_SkullOn = false;
		}
		 
		if (Sky_Ground* mGround = dynamic_cast<Sky_Ground*>(other->GetOwner()))
		{
			_Ground_check = false;
			_rigidbody->SetGround(false);
			_Ground_On = false;
			if (_skul_act == true)
				mGround->_SkullOn = false;
		}


	}

	void Skul_Basic::attack_choice()
	{
		as->Stop("Skul_Atk1");
		as->Stop("Skul_Atk2");
		_attack_Acheck = false;
		_attack_Bcheck = false;
		Hit_Box->SetState(eState::Paused);	
		if (_attack == true)
		{		
			_State = Skul_Basic_State::Attack_B;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicAttackB", true);				
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadAttackB", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicAttackBR", true);					
				if (_Skulhead == true)
					at->PlayAnimation(L"NoHeadAttackBR", true);
				mDir = -1;
			}			
		}
		if (_attack == false)
		{
			if (Input::GetKeyDown(eKeyCode::Z))
			{
				_State = Skul_Basic_State::Dash;
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicDash", false);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicDashR", false);
					mDir = -1;
				}
			}

			if (_fallcheck == 1)
			{				
				_State = Skul_Basic_State::Fall;
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicFall", false);					
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicFallR", false);					
				}				
			}
			if (_fallcheck == 2)
			{
				_State = Skul_Basic_State::Falling;
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicFallRepeat", true);
					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicFallRepeatR", true);
					mDir = -1;
				}				
			}

			if (Input::GetKey(eKeyCode::RIGHT)
				|| Input::GetKey(eKeyCode::LEFT))
			{
				_State = Skul_Basic_State::Move;
				if (Input::GetKey(eKeyCode::RIGHT))
				{
					at->PlayAnimation(L"Skul_BasicWalk", true);
					mDir = 1;
				}
				else if (Input::GetKey(eKeyCode::LEFT))
				{
					at->PlayAnimation(L"Skul_BasicWalkR", true);
					mDir = -1;
				}
			}
			else
			{
				_State = Skul_Basic_State::Idle;
				if (mDir == 1)
				{
					at->PlayAnimation(L"Skul_BasicIdle", true);
					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadIdle", true);


					mDir = 1;
				}
				else if (mDir == -1)
				{
					at->PlayAnimation(L"Skul_BasicIdleR", true);

					if (_Skulhead == true)
						at->PlayAnimation(L"NoHeadIdleR", true);

					mDir = -1;
				}
			}
		}
	}
	void Skul_Basic::Input_move()
	{
		if (_Leftmove_Lock == false)
		{
			if (Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				pos.x -= 150.0f * Time::DeltaTime();
				//_rigidbody->SetVelocity(Vector2(-150.f, 0.f));
			}
		}
		if (_Rightmove_Lock == false)
		{
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mDir = 1;
				pos.x += 150.0f * Time::DeltaTime();
				//_rigidbody->SetVelocity(Vector2(150.f, 0.f));
			}
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			_rigidbody->SetGround(true);
			_Ground_check = true;
			pos.y -= 100.0f * Time::DeltaTime();
		}
		
		if (Input::GetKey(eKeyCode::UP))
		{
			_rigidbody->SetGround(true);
			_Ground_check = true;
			pos.y += 100.0f * Time::DeltaTime();
		}
		

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			Hit_Box->SetState(eState::Paused);
			SetPlay_List(PlayerList::wolf_Skul,PlayerList::basic_Skul, true, mDir);
			//SetPlay_List(PlayerList::spere_Skul, PlayerList::basic_Skul, true, mDir);
			//SetPlay_List(PlayerList::sowrd_Skul, PlayerList::basic_Skul, true, mDir);
			//SetPlay_List(PlayerList::thief_Skul, PlayerList::basic_Skul, true, mDir);
			pos.y = pos.y + 5;
			SetPlayer_Pos(pos);	
		}
	}
	void Skul_Basic::switch_on_off()
	{	
		if(_switch == false)
		{
			_attack_Acheck = false;
			_State = Skul_Basic_State::Idle;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Skul_BasicIdle", true);
				mDir = 1;
			}
			else if (mDir == -1)
			{
				at->PlayAnimation(L"Skul_BasicIdleR", true);
				mDir = -1;
			}
			_rigidbody->ClearVelocity();
		}
	}
}
