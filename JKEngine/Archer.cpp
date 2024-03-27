#include "Archer.h"
#include "Include_Common.h"
#include "Archer_Arrow.h"
#include "Archer_Arrow_Upward_Sign.h"
#include "Archer_Upward_Impact_Bullet.h"
#include "Archer_Arrow_Bye.h"
#include "Archer_Trap.h"
#include "Public_Ultimate_Aura.h"
#include "Public_Ultimate_AuraSmoke.h"
#include "Public_UltimateSkill_Effect_Complete.h"
#include "Public_UltimateSkill_Effect_Fail.h"
#include "Archer_Utimate_Sign.h"
#include "HitBox_Archer.h"
#include "Player_Hp_Bar.h"
#include "Monster_Hit_Effect.h"
#include "Monster_Death_Effect.h"
#include "Monster_Hp_Bar.h"
#include "HP_Frame.h"
#include "MiniBoss_State_UI.h"
#include "AdventureUI.h"
#include "..\Engine_SOURCE\jkAudioSource.h"
#include "Monster_Hit_Effect.h"
#include "Player_Hit_Effect.h"
#include "Hit_Sword.h"
#include "Hit_Critical_Middle.h"
#include "Hit_Critical_High.h"


namespace jk
{
	int Archer::_Dir = 1;
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


		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Adventure_public\\Adventurer_Charge_Start.wav", "Adventurer_Charge_Start");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Adventure_public\\Adventurer_Charge_End.wav", "Adventurer_Charge_End");

		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Archer\\AdventurerHunter_Voice_Middle.wav", "AdventurerHunter_Voice_Middle");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Archer\\AdventurerHunter_Voice_Short.wav", "AdventurerHunter_Voice_Short");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Archer\\AdventurerHunter_Voice_Casting.wav", "AdventurerHunter_Voice_Casting");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Archer\\AdventurerHunter_Voice_Dead.wav", "AdventurerHunter_Voice_Dead");

		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Archer\\AdventurerHunter_Trap.wav", "AdventurerHunter_Trap");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Archer\\AdventurerHunter_Attack.wav", "AdventurerHunter_Attack");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Archer\\AdventurerHunter_Attack_Ready.wav", "AdventurerHunter_Attack_Ready");

		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Archer\\AdventurerHunter_ArrowRain_1.wav", "AdventurerHunter_ArrowRain_1");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Archer\\AdventurerHunter_ArrowRain_2.wav", "AdventurerHunter_ArrowRain_2");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Archer\\AdventurerHunter_ArrowRain_3.wav", "AdventurerHunter_ArrowRain_3");

		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Blunt_Small.wav", "Hit_Blunt_Small");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Sword_Small.wav", "Hit_Sword_Small");



		
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
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Ultimate", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Ultimate_Ready", this);
		
		
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
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Ultimate", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Ultimate_Ready", this, 1);
		

		//bind 부분
		at->CompleteEvent(L"ArcherAttack_A") = std::bind(&Archer::choicecombo, this);
		at->CompleteEvent(L"ArcherAttack_AR") = std::bind(&Archer::choicecombo, this);

		at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);
		at->CompleteEvent(L"ArcherAttack_CR") = std::bind(&Archer::choicecombo, this);		


		at->CompleteEvent(L"ArcherHit") = std::bind(&Archer::complete_hit, this);
		at->CompleteEvent(L"ArcherHitR") = std::bind(&Archer::complete_hit, this);

		at->CompleteEvent(L"ArcherIntro") = std::bind(&Archer::CompleteArcherIntro, this);
		at->CompleteEvent(L"ArcherIntroR") = std::bind(&Archer::CompleteArcherIntro, this);
		
		Scene* scene = SceneManager::GetInitializeScene();
		//UI 및 체력관련		
		{
			_MbossFace = new AdventureUI();
			_MbossFace->Initialize();			
			scene->AddGameObject(eLayerType::UI, _MbossFace);
			_MbossFace->SetName(L"_MbossFace");
			Transform* face_tr = _MbossFace->GetComponent<Transform>();
			face_tr->SetPosition(Vector3(762.f, 375.f, pos.z));
			face_tr->SetScale(26 * 2.f, 26.f * 2.f, 0.f);
		}

		{
			_State_UI = new MiniBoss_State_UI();
			scene->AddGameObject(eLayerType::UI, _State_UI);
			_State_UI->SetName(L"hp_bar_frame");
			Transform* hp_tr = _State_UI->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(685.f, 375.f, pos.z));
			hp_tr->SetScale(108.f*2.f, 30.f*2.f, 0.f);		
		}
		{
			Monster_UIHp = new Monster_Hp_Bar(L"EnemyHealthBar");
			scene->AddGameObject(eLayerType::UI, Monster_UIHp);
			Monster_UIHp->SetName(L"warrior_hp_bar");
			Transform* hp_tr = Monster_UIHp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(pos.x, pos.y + 50.f, pos.z - 1.f));
			hp_tr->SetScale(137.f, 12.5f, 0.f);
			Monster_UIHp->Set_Max_Hp(_MaxHp);
			Monster_UIHp->Set_Current_Hp(_MaxHp);
			Monster_UIHp->SetState(eState::Paused);
		}
		{
			Monster_UIDamegeHp = new Monster_Hp_Bar(L"EnemyHealthBar_Damage");
			scene->AddGameObject(eLayerType::UI, Monster_UIDamegeHp);
			Monster_UIDamegeHp->SetName(L"warrior_hp_bar");
			Transform* hp_tr = Monster_UIDamegeHp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(pos.x, pos.y + 50.f, pos.z - 1.5f));
			hp_tr->SetScale(137.f, 12.5f, 0.f);
			Monster_UIDamegeHp->Set_Max_Hp(_MaxHp);
			Monster_UIDamegeHp->Set_Current_Hp(_MaxHp);
			Monster_UIDamegeHp->Set_Type(1);
			Monster_UIDamegeHp->SetState(eState::Paused);
		}

		{
			Hpbar_Frame = new HP_Frame(L"EnemyHealthBar_Frame");
			scene->AddGameObject(eLayerType::Monster, Hpbar_Frame);
			Hpbar_Frame->SetName(L"hp_bar_frame");
			Transform* hp_tr = Hpbar_Frame->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(pos.x, pos.y -90.f, pos.z - 1.f));
			hp_tr->SetScale(50.f, 5.f, 0.f);
			Hpbar_Frame->SetState(eState::Paused);
		}

		{
			Monster_DamegeHp = new Monster_Hp_Bar(L"EnemyHealthBar_Damage");
			scene->AddGameObject(eLayerType::Monster, Monster_DamegeHp);
			Monster_DamegeHp->SetName(L"warrior_hp_bar");
			Transform* hp_tr = Monster_DamegeHp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(pos.x, pos.y + 50.f, pos.z - 1.5f));
			hp_tr->SetScale(48.f, 3.f, 0.f);
			Monster_DamegeHp->Set_Max_Hp(_MaxHp);
			Monster_DamegeHp->Set_Current_Hp(_MaxHp);
			Monster_DamegeHp->Set_Type(1);
			Monster_DamegeHp->SetState(eState::Paused);
		}

		{
			Monster_Hp = new Monster_Hp_Bar(L"EnemyHealthBar");
			scene->AddGameObject(eLayerType::Monster, Monster_Hp);
			Monster_Hp->SetName(L"warrior_hp_bar");
			Transform* hp_tr = Monster_Hp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(pos.x, pos.y + 50.f, pos.z - 1.f));
			hp_tr->SetScale(48.f, 3.f, 0.f);
			Monster_Hp->Set_Max_Hp(_MaxHp);
			Monster_Hp->Set_Current_Hp(_MaxHp);
			Monster_Hp->SetState(eState::Paused);
		}
		
		
		{
			_archer_arrow = new Archer_Arrow;
			_archer_arrow->Initialize();
			scene->AddGameObject(eLayerType::Bullet, _archer_arrow);
			Transform* EffectTR = _archer_arrow->GetComponent<Transform>();
			EffectTR->SetPosition(_tr->GetPosition());
			_archer_arrow->SetState(eState::Paused);
		}
		{
			Upward_Sign = new Archer_Arrow_Upward_Sign;
			Upward_Sign->Initialize();
			scene->AddGameObject(eLayerType::Effect, Upward_Sign);
			Transform* EffectTR = Upward_Sign->GetComponent<Transform>();
			EffectTR->SetPosition(_tr->GetPosition());
			Upward_Sign->SetState(eState::Paused);
		}
		{
			Upward_Impact_Bullet = new Archer_Upward_Impact_Bullet;
			Upward_Impact_Bullet->Initialize();
			scene->AddGameObject(eLayerType::Bullet, Upward_Impact_Bullet);
			Transform* EffectTR = Upward_Impact_Bullet->GetComponent<Transform>();
			EffectTR->SetPosition(_tr->GetPosition());
			Upward_Impact_Bullet->SetState(eState::Paused);
		}
		{
			Arrow_Bye_effect = new Archer_Arrow_Bye;
			Arrow_Bye_effect->Initialize();
			scene->AddGameObject(eLayerType::Effect, Arrow_Bye_effect);
			Transform* EffectTR = Arrow_Bye_effect->GetComponent<Transform>();
			EffectTR->SetPosition(_tr->GetPosition());
			Arrow_Bye_effect->SetState(eState::Paused);
		}
		{
			for (int i = 0; i < 6; i++)
			{
				Bullet_Trap[i] = new Archer_Trap;
				Bullet_Trap[i]->Initialize();
				scene->AddGameObject(eLayerType::Bullet, Bullet_Trap[i]);
				Transform* EffectTR = Bullet_Trap[i]->GetComponent<Transform>();
				EffectTR->SetPosition(_tr->GetPosition());
				Bullet_Trap[i]->SetState(eState::Paused);
			}
		}

		{
			Ultimate_Aura = new Public_Ultimate_Aura;
			Ultimate_Aura->Initialize();
			scene->AddGameObject(eLayerType::Effect, Ultimate_Aura);
			Transform* bullet_tr = Ultimate_Aura->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205.f));
			Ultimate_Aura->SetState(eState::Paused);
		}

		{
			Ultimate_AuraSmoke = new Public_Ultimate_AuraSmoke;
			Ultimate_AuraSmoke->Initialize();
			scene->AddGameObject(eLayerType::Effect, Ultimate_AuraSmoke);
			Transform* bullet_tr = Ultimate_AuraSmoke->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205.f));
			Ultimate_AuraSmoke->SetState(eState::Paused);
		}
		{
			UltimateSkill_Effect_Complete = new Public_UltimateSkill_Effect_Complete;
			UltimateSkill_Effect_Complete->Initialize();
			scene->AddGameObject(eLayerType::Effect, UltimateSkill_Effect_Complete);
			Transform* bullet_tr = UltimateSkill_Effect_Complete->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205.f));
			UltimateSkill_Effect_Complete->SetState(eState::Paused);
		}
		{
			UltimateSkill_Effect_Fail = new Public_UltimateSkill_Effect_Fail;
			UltimateSkill_Effect_Fail->Initialize();
			scene->AddGameObject(eLayerType::Effect, UltimateSkill_Effect_Fail);
			Transform* bullet_tr = UltimateSkill_Effect_Fail->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205.f));
			UltimateSkill_Effect_Fail->SetState(eState::Paused);
		}

		{
			Utimate_Sign = new Archer_Utimate_Sign;
			Utimate_Sign->Initialize();
			scene->AddGameObject(eLayerType::Effect, Utimate_Sign);
			Transform* bullet_tr = Utimate_Sign->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205.f));
			Utimate_Sign->SetState(eState::Paused);
		}

		{
			for (int i = 0; i < 40; i++)
			{
				Ultimate_Upward_ImpactBullet[i] = new Archer_Upward_Impact_Bullet;
				Ultimate_Upward_ImpactBullet[i]->Initialize();
				scene->AddGameObject(eLayerType::Bullet, Ultimate_Upward_ImpactBullet[i]);
				Transform* EffectTR = Ultimate_Upward_ImpactBullet[i]->GetComponent<Transform>();
				EffectTR->SetPosition(_tr->GetPosition());
				Ultimate_Upward_ImpactBullet[i]->SetState(eState::Paused);
			}
		}
			
		{
			for (int i = 0; i < 40; i++)
			{
				Ultimate_ArrowBye_effect[i] = new Archer_Arrow_Bye;
				Ultimate_ArrowBye_effect[i]->Initialize();
				scene->AddGameObject(eLayerType::Effect, Ultimate_ArrowBye_effect[i]);
				Transform* EffectTR = Ultimate_ArrowBye_effect[i]->GetComponent<Transform>();
				EffectTR->SetPosition(_tr->GetPosition());
				Ultimate_ArrowBye_effect[i]->SetState(eState::Paused);
			}
		}

		{
			Hit_Box = new HitBox_Archer();
			Hit_Box->Initialize();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetState(eState::Paused);
		}
		
		{
			_Hit_Effect = new Monster_Hit_Effect;
			_Hit_Effect->Initialize();
			scene->AddGameObject(eLayerType::Effect, _Hit_Effect);
			_Hit_Effect->SetState(eState::Paused);
		}

		{
			_Hit_Sword = new Hit_Sword;
			_Hit_Sword->Initialize();
			scene->AddGameObject(eLayerType::Effect, _Hit_Sword);
			_Hit_Sword->SetState(eState::Paused);
		}

		{
			_Critical_Middle = new Hit_Critical_Middle;
			_Critical_Middle->Initialize();
			scene->AddGameObject(eLayerType::Effect, _Critical_Middle);
			_Critical_Middle->SetState(eState::Paused);
		}
		{
			_Critical_High = new Hit_Critical_High;
			_Critical_High->Initialize();
			scene->AddGameObject(eLayerType::Effect, _Critical_High);
			_Critical_High->SetState(eState::Paused);
		}

		{
			_Death_Effect = new Monster_Death_Effect;
			_Death_Effect->Initialize();
			scene->AddGameObject(eLayerType::Effect, _Death_Effect);
			_Death_Effect->SetState(eState::Paused);
		}



		at->PlayAnimation(L"ArcherIdle", true);
		GameObject::Initialize();
	}
	void Archer::Update()
	{
		SetDirection();
		Particle_Control();
		Hpcontrol();
		Effect_Control();

		ground_distance_L = Left_Ground.x - pos.x;
		ground_distance_R = Right_Ground.x - pos.x;

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

		case jk::Archer::Archer_State::Attack_B_Ready:
			attack_b_ready();
			break;

		case jk::Archer::Archer_State::Attack_B:
			attack_b();
			break;

		case jk::Archer::Archer_State::Attack_B_End:
			attack_b_end();
			break;

		case jk::Archer::Archer_State::Attack_C:
			attack_c();
			break;

		case jk::Archer::Archer_State::Finishing_Move_Ready:
			Finishing_Move_Ready();
			break;

		case jk::Archer::Archer_State::Finishing_Move_Succes:
			Finishing_Move_Succes();
			break;

		case jk::Archer::Archer_State::Finishing_Move_Fail:
			Finishing_Move_Fail();
			break;

		case jk::Archer::Archer_State::Finishing_Move:
			Finishing_Move();
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

		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_PushAway == true)
		{
			Hit_Box->SetSize(Vector2(50.f, 85.f));
			Hit_Box->SetState(eState::Active);
			if (_attackDir == 1)
				HitBox_TR->SetPosition(Vector3(pos.x + 50, pos.y - 30, pos.z));
			else
				HitBox_TR->SetPosition(Vector3(pos.x - 50, pos.y - 30, pos.z));
		}
		else
		{
			Hit_Box->SetState(eState::Paused);
		}

		_collider->SetSize(Vector2(0.5f, 0.5f));
		if(_Dir ==1)
			_collider->SetCenter(Vector2(0.0f, -25.f));
		else
			_collider->SetCenter(Vector2(0.0f, -25.f));

		GameObject::LateUpdate();
	}
	void Archer::Render()
	{
		GameObject::Render();
	}


	void Archer::OnCollisionEnter(Collider2D* other)
	{	
		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			if (_state == Archer_State::Die)
				return;

			_Damage = player->GetDamage();
			bool attack = player->Geteffect();
			bool attack_Cri_Mid = player->Geteffect_Mid();
			bool attack_Cri_High = player->Geteffect_Hight();			

			if (_state == Archer_State::Idle)
			{
				_state = Archer_State::Hit;
				_Hit_Effect->_effect_animation = true;
				_Critical_Middle->_effect_animation = true;
				_Critical_High->_effect_animation = true;

				_CurrenHp = _CurrenHp - _Damage;
				Monster_Hp->_HitOn = true;
				Monster_Hp->SetHitDamage(_Damage);
				Monster_DamegeHp->_HitOn = true;
				Monster_DamegeHp->Set_Target(_CurrenHp);

				Monster_UIHp->_HitOn = true;
				Monster_UIHp->SetHitDamage(_Damage);
				Monster_UIDamegeHp->_HitOn = true;
				Monster_UIDamegeHp->Set_Target(_CurrenHp);
				_Hp_control = true;
				Hpbar_Frame->SetState(eState::Active);
				Monster_DamegeHp->SetState(eState::Active);
				Monster_Hp->SetState(eState::Active);


				if (_Dir == 1)
				{
					at->PlayAnimation(L"ArcherHit", true);
					if (_hit < 2)
					_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
					_hit_switch = true;	_hit++;

					_Hit_Effect->SetDirection(-1);
					_Critical_Middle->SetDirection(-1);
					_Critical_High->SetDirection(-1);

				}
				if (_Dir == -1)
				{
					at->PlayAnimation(L"ArcherHitR", true);
					if (_hit < 2)
					_rigidbody->SetVelocity(Vector2(50.f, 0.f));
					_hit_switch = true;	_hit++;
					_Hit_Effect->SetDirection(1);
					_Critical_Middle->SetDirection(1);
					_Critical_High->SetDirection(1);
				}
			}
			else
			{
				_hit++;
				_Hit_Effect->_effect_animation = true;
				_Critical_Middle->_effect_animation = true;
				_Critical_High->_effect_animation = true;

				_CurrenHp = _CurrenHp - _Damage;
				Monster_Hp->_HitOn = true;
				Monster_Hp->SetHitDamage(_Damage);
				Monster_DamegeHp->_HitOn = true;
				Monster_DamegeHp->Set_Target(_CurrenHp);

				Monster_UIHp->_HitOn = true;
				Monster_UIHp->SetHitDamage(_Damage);
				Monster_UIDamegeHp->_HitOn = true;
				Monster_UIDamegeHp->Set_Target(_CurrenHp);


				_Hp_control = true;
				Hpbar_Frame->SetState(eState::Active);
				Monster_DamegeHp->SetState(eState::Active);
				Monster_Hp->SetState(eState::Active);


				if (_Dir == 1)
				{
					_Hit_Effect->SetDirection(-1);
					_Critical_Middle->SetDirection(-1);
					_Critical_High->SetDirection(-1);
				}
				else
				{
					_Hit_Effect->SetDirection(1);
					_Critical_Middle->SetDirection(1);
					_Critical_High->SetDirection(1);
				}
			}

			if (attack == true)
			{
				_Hit_Effect->_effect_animation = true;
				_Hit_Effect->SetState(eState::Active);
				attack = false;
				player->Seteffect(false);
			}
			if (attack_Cri_Mid == true)
			{
				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetState(eState::Active);
				attack_Cri_Mid = false;
				player->Seteffect_Mid(false);
			}
			if (attack_Cri_High == true)
			{
				_Critical_High->_effect_animation = true;
				_Critical_High->SetState(eState::Active);
				attack_Cri_High = false;
				player->Seteffect_Hight(false);
			}

			if (_CurrenHp <= 0)
			{
				_state = Archer_State::Die;
				as->Play("AdventurerHunter_Voice_Dead");
				Hit_Box->SetState(eState::Paused);
				_Hit_Effect->_effect_animation = true;
				if (_Dir == 1)
				{
					at->PlayAnimation(L"ArcherDie", false);
					_Hit_Effect->SetDirection(-1);
				}
				else
				{
					at->PlayAnimation(L"ArcherDieR", false);
					_Hit_Effect->SetDirection(1);
				}
				_Death_Effect->SetState(eState::Active);
			}
		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			if (_state == Archer_State::Die)
				return;

			_Damage = player->GetDamage();
			bool attack = player->Geteffect();
			bool attack_Cri_Mid = player->Geteffect_Mid();
			bool attack_Cri_High = player->Geteffect_Hight();


			if (player->_Head_Attack == false && _bulletcheck == 0)
			{
				if (player->_Ground_check == true)
					return;

				as->Play("Hit_Blunt_Small");
				if (_state == Archer_State::Idle)
				{
					_hit_switch = true;	_hit++;
					_Hit_Effect->_effect_animation = true;
					_Critical_Middle->_effect_animation = true;
					_Critical_High->_effect_animation = true;
					_state = Archer_State::Hit;
					if (_Dir == 1)
					{
						at->PlayAnimation(L"ArcherHit", true);
						if (_hit < 2)
							_rigidbody->SetVelocity(Vector2(-50.f, 0.f));

						Monster_Hp->_HitOn = true;
						_CurrenHp = _CurrenHp - _Damage;
						Monster_Hp->SetHitDamage(_Damage);
						Monster_DamegeHp->_HitOn = true;
						Monster_DamegeHp->Set_Target(_CurrenHp);
						Monster_UIHp->_HitOn = true;
						Monster_UIHp->SetHitDamage(_Damage);
						Monster_UIDamegeHp->_HitOn = true;
						Monster_UIDamegeHp->Set_Target(_CurrenHp);
						_Hp_control = true;
						Hpbar_Frame->SetState(eState::Active);
						Monster_DamegeHp->SetState(eState::Active);
						Monster_Hp->SetState(eState::Active);

						_Hit_Effect->SetDirection(-1);
						_Critical_Middle->SetDirection(-1);
						_Critical_High->SetDirection(-1);

					}
					if (_Dir == -1)
					{
						at->PlayAnimation(L"ArcherHitR", true);
						if (_hit < 2)
							_rigidbody->SetVelocity(Vector2(50.f, 0.f));
						Monster_Hp->_HitOn = true;
						_CurrenHp = _CurrenHp - _Damage;
						Monster_Hp->SetHitDamage(_Damage);
						Monster_DamegeHp->_HitOn = true;
						Monster_DamegeHp->Set_Target(_CurrenHp);
						Monster_UIHp->_HitOn = true;
						Monster_UIHp->SetHitDamage(_Damage);
						Monster_UIDamegeHp->_HitOn = true;
						Monster_UIDamegeHp->Set_Target(_CurrenHp);
						_Hp_control = true;
						Hpbar_Frame->SetState(eState::Active);
						Monster_DamegeHp->SetState(eState::Active);
						Monster_Hp->SetState(eState::Active);

						_Hit_Effect->SetDirection(1);
						_Critical_Middle->SetDirection(1);
						_Critical_High->SetDirection(1);
					}
					if (attack == true)
					{
						_Hit_Effect->_effect_animation = true;
						_Hit_Effect->SetState(eState::Active);
					}
					if (attack_Cri_Mid == true)
					{
						_Critical_Middle->_effect_animation = true;
						_Critical_Middle->SetState(eState::Active);
					}
					if (attack_Cri_High == true)
					{
						_Critical_High->_effect_animation = true;
						_Critical_High->SetState(eState::Active);
					}
				
				}
				else
				{
					_hit++;
					_Hit_Effect->_effect_animation = true;
					_Critical_Middle->_effect_animation = true;
					_Critical_High->_effect_animation = true;

					if (_Dir == 1)
					{
						_rigidbody->SetVelocity(Vector2(-20.f, 0.f));						
						Monster_Hp->_HitOn = true;
						_CurrenHp = _CurrenHp - _Damage;
						Monster_Hp->SetHitDamage(_Damage);
						Monster_DamegeHp->_HitOn = true;
						Monster_DamegeHp->Set_Target(_CurrenHp);
						Monster_UIHp->_HitOn = true;
						Monster_UIHp->SetHitDamage(_Damage);
						Monster_UIDamegeHp->_HitOn = true;
						Monster_UIDamegeHp->Set_Target(_CurrenHp);
						_Hp_control = true;
						Hpbar_Frame->SetState(eState::Active);
						Monster_DamegeHp->SetState(eState::Active);
						Monster_Hp->SetState(eState::Active);
						_Hit_Effect->SetDirection(-1);
						_Critical_Middle->SetDirection(-1);
						_Critical_High->SetDirection(-1);
					}
					else
					{
						_rigidbody->SetVelocity(Vector2(20.f, 0.f));	
						Monster_Hp->_HitOn = true;
						_CurrenHp = _CurrenHp - _Damage;
						Monster_Hp->SetHitDamage(_Damage);
						Monster_DamegeHp->_HitOn = true;
						Monster_DamegeHp->Set_Target(_CurrenHp);
						Monster_UIHp->_HitOn = true;
						Monster_UIHp->SetHitDamage(_Damage);
						Monster_UIDamegeHp->_HitOn = true;
						Monster_UIDamegeHp->Set_Target(_CurrenHp);
						_Hp_control = true;
						Hpbar_Frame->SetState(eState::Active);
						Monster_DamegeHp->SetState(eState::Active);
						Monster_Hp->SetState(eState::Active);
						_Hit_Effect->SetDirection(1);
						_Critical_Middle->SetDirection(1);
						_Critical_High->SetDirection(1);
					}
					if (attack == true)
					{
						_Hit_Effect->_effect_animation = true;
						_Hit_Effect->SetState(eState::Active);
					}
					if (attack_Cri_Mid == true)
					{
						_Critical_Middle->_effect_animation = true;
						_Critical_Middle->SetState(eState::Active);
					}
					if (attack_Cri_High == true)
					{
						_Critical_High->_effect_animation = true;
						_Critical_High->SetState(eState::Active);
					}
				}
				if (_CurrenHp <= 0)
				{
					_state = Archer_State::Die;
					Hit_Box->SetState(eState::Paused);
					as->Play("AdventurerHunter_Voice_Dead");
					_Hit_Effect->_effect_animation = true;
					if (_Dir == 1)
					{
						at->PlayAnimation(L"ArcherDie", false);
						_Hit_Effect->SetDirection(-1);
					}
					else
					{
						at->PlayAnimation(L"ArcherDieR", false);
						_Hit_Effect->SetDirection(1);
					}
					_Death_Effect->SetState(eState::Active);
				}
				_bulletcheck++;
			}
		}		

		if (Skul_Spear* player = dynamic_cast<Skul_Spear*>(other->GetOwner())){}

		if (Skul_Wolf* player = dynamic_cast<Skul_Wolf*>(other->GetOwner())){}

	}
	void Archer::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_rigidbody->ClearVelocity();
			}
			if (_state == Archer_State::BackDash)
			{
				if (_Ground_check == true)
				{
					_BackDash = false;
				}
			}
		}		

		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_rigidbody->ClearVelocity();
			}
			if (_state == Archer_State::BackDash)
			{
				if (_Ground_check == true)				
					_BackDash = false;

			}
		}

		if (Ground_and_Wall* mGround = dynamic_cast<Ground_and_Wall*>(other->GetOwner()))
		{
			Transform* GRTR = mGround->GetComponent<Transform>();
			Vector3 GRpos = GRTR->GetPosition();
			_rigidbody->ClearVelocityX();
		}
	}
	void Archer::OnCollisionExit(Collider2D* other)
	{
		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			_bulletcheck = 0;
		}
	}


	void Archer::idle()
	{
		_time += static_cast<float>(Time::DeltaTime());
	
		_hit_switch = false;

		if (_Intro == false)
		{
			_state = Archer_State::Intro;
			at->PlayAnimation(L"ArcherIntroR", true);
		}
		else
		{
			if (_hit >= 3)
			{
				if (_Numberof_BackDash <= 2)
				{
					if (_Dir == 1)
					{
						if (ground_distance_L < -100)
						{
							at->PlayAnimation(L"ArcherBackStep", false);
							_rigidbody->SetVelocity(Vector2(-200.f, 200.f));
							_rigidbody->AddForce(Vector2(-10, 20));
							_Ground_check = false;
							_rigidbody->SetGround(false);
							_BackDash = true;
							_state = Archer_State::BackDash;
							_Numberof_BackDash++;
						}
						else
						{
							at->PlayAnimation(L"ArcherBackStepR", false);
							_rigidbody->SetVelocity(Vector2(350.f, 200.f));
							_rigidbody->AddForce(Vector2(10, 20));
							_Ground_check = false;
							_rigidbody->SetGround(false);
							_BackDash = true;
							_state = Archer_State::BackDash;			
							_Numberof_BackDash++;
						}
					}
					else
					{
						if (ground_distance_R > 100)
						{
							at->PlayAnimation(L"ArcherBackStepR", false);
							_rigidbody->SetVelocity(Vector2(200.f, 200.f));
							_rigidbody->AddForce(Vector2(10, 20));
							_Ground_check = false;
							_rigidbody->SetGround(false);
							_BackDash = true;
							_state = Archer_State::BackDash;
							_Numberof_BackDash++;
						}
						else
						{
							at->PlayAnimation(L"ArcherBackStep", false);
							_rigidbody->SetVelocity(Vector2(-350.f, 200.f));
							_rigidbody->AddForce(Vector2(-10, 20));
							_Ground_check = false;
							_rigidbody->SetGround(false);
							_BackDash = true;
							_state = Archer_State::BackDash;
							_Numberof_BackDash++;
						}
					}
				}
				else
				{
					_hit = 0; _Numberof_BackDash = 0;
				}
			}
			else
			{
				if (_time > 3.f)
				{
					if ((_distance <= 80 && _distance >= -80))
					{
						_choicecombo = 10;
						_attack = true;
						choicecombo();
					}
					else
					{
						_choicecombo = random(0, 3);		
						//_choicecombo = 0;
						_attack = true;
						choicecombo();
					}
				}
			}
		}
	}
	void Archer::backdash()
	{
		if (_BackDash == false)
		{
			for (int i = 0; i < 6; i++)
			{
				if (Bullet_Trap[i]->_Bullet_Life == true)
					continue;
				else
				{
					Transform* EffectTR = Bullet_Trap[i]->GetComponent<Transform>();
					RigidBody* Effectrb = Bullet_Trap[i]->GetComponent<RigidBody>();
					EffectTR->SetPosition(_tr->GetPosition());
					Bullet_Trap[i]->_Bullet_Life = true;
					Effectrb->SetGround(false);
					Bullet_Trap[i]->SetState(eState::Active);
					as->Play("AdventurerHunter_Trap");
					break;
				}
			}

			_state = Archer_State::Idle;
			if (_Dir == 1)
				at->PlayAnimation(L"ArcherIdle", true);
			else
				at->PlayAnimation(L"ArcherIdleR", true);
		}	
	}
	void Archer::die()
	{
		_Die = true;
		Ultimate_Aura->SetState(eState::Paused);
		Ultimate_AuraSmoke->SetState(eState::Paused);
	}


	void Archer::attack_a_ready()
	{
		_attack_time += static_cast<float>(Time::DeltaTime());
		if (_attack_time > 0.7)
		{
			int voice_archer = random(0, 1);
			if(voice_archer ==0)
				as->Play("AdventurerHunter_Voice_Short"); 
			if (voice_archer == 1)
				as->Play("AdventurerHunter_Voice_Middle");
			_state = Archer_State::Attack_A;
			as->Play("AdventurerHunter_Attack");
			_attack_time = 0;
		}
	}
	void Archer::attack_a()
	{
		Transform* EffectTR = _archer_arrow->GetComponent<Transform>();
		RigidBody* EffectRG = _archer_arrow->GetComponent<RigidBody>();
		if (_attack_a == false)
		{			
			if (_Dir == 1)
			{
				_attackDir = 1;
				_archer_arrow->_bullet_animation= true;
				_archer_arrow->SetDirection(1);
				EffectTR->SetPosition(pos.x + 20.f, pos.y - 30.f, pos.z - 1.f);
			}
			if (_Dir == -1)
			{
				_attackDir = -1;
				_archer_arrow->_bullet_animation = true;
				_archer_arrow->SetDirection(-1);
				EffectTR->SetPosition(pos.x - 20.f, pos.y - 30.f, pos.z - 1.f);
			}
			_archer_arrow->SetState(eState::Active);
			_attack_a = true;
		}
		if (_attack_a == true)
		{
			Vector3 arrowpos = EffectTR->GetPosition();
			_attack_time += static_cast<float>(Time::DeltaTime());
			if (_attack_time < 2)
			{		
				if (_attackDir == 1)
				{
					EffectRG->SetFriction(true);
					EffectRG->SetGravity(true);
					EffectRG->SetVelocity(Vector2(450.f, 0.f));
				}
				else
				{
					EffectRG->SetFriction(true);
					EffectRG->SetGravity(true);
					EffectRG->SetVelocity(Vector2(-450.f, 0.f));
				}	
			}		
			else
			{
				EffectRG->ClearVelocity();
				EffectRG->SetFriction(false);
				EffectRG->SetGravity(false);
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


	void Archer::attack_b_ready()
	{		
		_attack_time += static_cast<float>(Time::DeltaTime());
		if (_attack_time > 0.5)
		{
			Transform* EffectTR = Upward_Sign->GetComponent<Transform>();
			EffectTR->SetPosition(_playerpos.x, _playerpos.y, _playerpos.z - 1.f);
			Upward_Sign->_effect_On = true;
			Upward_Sign->SetState(eState::Active);

			if (_Dir == 1)
				at->PlayAnimation(L"ArcherIdle", true);
			if(_Dir ==-1)
				at->PlayAnimation(L"ArchereIdleR", false);

			_attack_b_sign = true;

			int voice_archer = random(0, 1);
			if (voice_archer == 0)
				as->Play("AdventurerHunter_Voice_Short");
			if (voice_archer == 1)
				as->Play("AdventurerHunter_Voice_Middle");
			as->Play("AdventurerHunter_Attack");
			_state = Archer_State::Attack_B;
			_attack_time = 0;
		}		
	}
	void Archer::attack_b()
	{
		if (_attack_b_sign == true)
		{
			_attack_time += static_cast<float>(Time::DeltaTime());
			if (_attack_time > 0.5)
			{
				Transform* EffectTR = Upward_Sign->GetComponent<Transform>();
				Vector3 effect = EffectTR->GetPosition();
				Transform* BullettTR = Upward_Impact_Bullet->GetComponent<Transform>();
				BullettTR->SetPosition(effect.x, effect.y+145, effect.z - 1);
				Upward_Impact_Bullet->_bullet_On = true;
				Upward_Impact_Bullet->SetState(eState::Active);				
				_state = Archer_State::Attack_B_End;
				_attack_time = 0;
			}			
		}	
	}
	void Archer::attack_b_end()
	{
		if (Upward_Impact_Bullet->_bullet_On == false)
		{
			Transform* BullettTR = Upward_Impact_Bullet->GetComponent<Transform>();
			Vector3 bullet = BullettTR -> GetPosition();		

			Upward_Sign->SetState(eState::Paused);
			Transform* EffectTR = Arrow_Bye_effect->GetComponent<Transform>();
			EffectTR->SetPosition(bullet.x, bullet.y-125, bullet.z);
			Arrow_Bye_effect->_effect_On = true;
			Arrow_Bye_effect->SetState(eState::Active);

			_attack = false;
			_attack_b_sign = false;
			choicecombo();
		}
	}


	void Archer::attack_c()
	{
		//_attackorder = 0;
		_attack = false;
	}


	void Archer::Finishing_Move_Ready()
	{
		if (_Ultimate == true)
		{
			{
				Transform* bullet_tr = Ultimate_Aura->GetComponent<Transform>();				
				Ultimate_Aura->_effect_animation = true;
				if (_Dir == 1)
				{
					Ultimate_Aura->SetDirection(1);
					bullet_tr->SetPosition(Vector3(pos.x, pos.y - 30.f, pos.z - 1.f));
				}
				else
				{
					Ultimate_Aura->SetDirection(-1);
					bullet_tr->SetPosition(Vector3(pos.x, pos.y - 30.f, pos.z - 1.f));
				}
				Ultimate_Aura->SetState(eState::Active);
			}

			{
				Transform* bullet_tr = Ultimate_AuraSmoke->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y - 55.f, pos.z - 1.1f));
				if (_Dir == 1)
				{
					Ultimate_AuraSmoke->SetDirection(1);
					bullet_tr->SetPosition(Vector3(pos.x, pos.y - 50.f, pos.z - 1.f));
				}					
				else
				{
					Ultimate_AuraSmoke->SetDirection(-1);
					bullet_tr->SetPosition(Vector3(pos.x, pos.y - 50.f, pos.z - 1.f));
				}					
				Ultimate_AuraSmoke->SetState(eState::Active);
			}
			_Ultimate = false;
		}
		// 기모으는 이펙트를 넣을것(7초간 지속상태 만들기)
		_attack_time += static_cast<float>(Time::DeltaTime());
		if (_attack_time >= 4.5)
		{
			Ultimate_Aura->SetState(eState::Paused);
			Ultimate_AuraSmoke->SetState(eState::Paused);
			if (_hit > 8)
			{
				// 이펙트 설정시 9번 hit가 된다면 깨지는 이미지로 넘어간뒤 그로기 상태로넘겨줘야한다.
				Transform* bullet_tr = UltimateSkill_Effect_Fail->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y - 25.f, pos.z - 1.1f));
				if (_Dir == 1)
					UltimateSkill_Effect_Fail->SetDirection(1);
				else
					UltimateSkill_Effect_Fail->SetDirection(-1);
				UltimateSkill_Effect_Fail->SetState(eState::Active);

				_state = Archer_State::Finishing_Move_Fail;
				as->Play("Adventurer_Charge_End");
				_attack_time = 0.f;				
			}
			else
			{
				// 이펙트 설정시 5초가 10번이상의 타격이 없다면 석세스로 넘어간뒤 활공격을 날려야한다.
				Transform* bullet_tr = UltimateSkill_Effect_Complete->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y - 25.f, pos.z - 1.1f));
				if (_Dir == 1)
					UltimateSkill_Effect_Complete->SetDirection(1);
				else
					UltimateSkill_Effect_Complete->SetDirection(-1);
				UltimateSkill_Effect_Complete->SetState(eState::Active);

				if (_Dir == 1)
					at->PlayAnimation(L"ArcherUltimate", false);
				else
					at->PlayAnimation(L"ArcherUltimateR", false);
				_state = Archer_State::Finishing_Move_Succes;
				as->Play("Adventurer_Charge_End");
				_attack_time = 0.f;
			}
		}
	}
	void Archer::Finishing_Move_Succes()
	{
		if (_Ultimate_Skill == false)
		{
			Transform* bullet_tr = Utimate_Sign->GetComponent<Transform>();
			Ultimate_Skill_pos = Vector3(_playerpos.x, _playerpos.y-20.f, _playerpos.z-1.f);
			bullet_tr->SetPosition(Ultimate_Skill_pos);
			Utimate_Sign->_effect_On = true;
			Utimate_Sign->SetState(eState::Active);


			for (int i = 0; i < 40; i++)
			{
				float Ultimate_skill = static_cast<float>(random(static_cast<int>(_playerpos.x) - 75, static_cast<int>(_playerpos.x) + 75));
				Ultimate_Skill_pos.x = Ultimate_skill;

				Transform* BulletTR = Ultimate_Upward_ImpactBullet[i]->GetComponent<Transform>();	
				Ultimate_Upward_ImpactBullet[i]->_bullet_On = true;
				BulletTR->SetPosition(Vector3(Ultimate_Skill_pos.x, Ultimate_Skill_pos.y+150.f, Ultimate_Skill_pos.z));

				Transform* EffectTR = Ultimate_ArrowBye_effect[i]->GetComponent<Transform>();			
				EffectTR->SetPosition(Vector3(Ultimate_Skill_pos.x, Ultimate_Skill_pos.y+40.f, Ultimate_Skill_pos.z));
				
				if(i == 39)
					_Ultimate_Skill = true;
			}			
		}
		else
		{
			if (Utimate_Sign->_effect_On == false)
			{

				_attack_time += static_cast<float>(Time::DeltaTime());
				if (_attack_time < 7.f)
				{
					for (int i = 0; i < 40; i++)
					{
						Ultimate_ArrowBye_effect[i]->_effect_On = true;
						if (_attack_time >= (1.0f + 0.2f * i))
						{
							if (Ultimate_Upward_ImpactBullet[i]->_bullet_On == true)
							{
								Ultimate_Upward_ImpactBullet[i]->SetState(eState::Active);
								int ultimate_bullet = random(1, 3);
								if(ultimate_bullet == 1)
									as->Play("AdventurerHunter_ArrowRain_1");
								else if (ultimate_bullet == 2)
									as->Play("AdventurerHunter_ArrowRain_2");
								else if (ultimate_bullet == 3)
									as->Play("AdventurerHunter_ArrowRain_3");
							}
							if (Ultimate_Upward_ImpactBullet[i]->_bullet_On == false)
							{
								Ultimate_Upward_ImpactBullet[i]->SetState(eState::Paused);
								if (Ultimate_ArrowBye_effect[i]->_effect_On == true)
									Ultimate_ArrowBye_effect[i]->SetState(eState::Active);
							}			
						}	
					}
				}
				else
				{
					_state = Archer_State::Finishing_Move;
					_attack_time = 0;
					_Ultimate_Skill = false;
				}
			}
		}
	}
	void Archer::Finishing_Move_Fail()
	{
		_state = Archer_State::Groggy;
		if (_Dir == 1)
			at->PlayAnimation(L"ArcherGroggy", true);
		else
			at->PlayAnimation(L"ArcherGroggyR", true);
		_hit = 0;
	}
	void Archer::Finishing_Move()
	{
		_attack = false;
		choicecombo();
	}


	void Archer::groggy()
	{
		_attack_time += static_cast<float>(Time::DeltaTime());
		if (_attack_time >= 3.5)
		{
			_attack_time = 0;	
			_attack = false;
			choicecombo();
		}
	}
	void Archer::hit()
	{	
	}
	void Archer::intro()
	{
		_Intro = true;
	}
	void Archer::potion()
	{
	}
	void Archer::choicecombo()
	{
		_PushAway = false;

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
				ultimate();
			}
			if (_choicecombo == 3)
			{				
				dash_combo();
			}

			if (_choicecombo == 10)
			{
				_number_of_attack++;
				pushaway();
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
			if (_Dir == 1)
				at->PlayAnimation(L"ArcherIdle", true);
			else
				at->PlayAnimation(L"ArcherIdleR", true);
		}
	}


	void Archer::shootbow_forward()
	{

		as->Play("AdventurerHunter_Attack_Ready");
		_state = Archer_State::Attack_A_Ready;
		if (_Dir == 1)
			at->PlayAnimation(L"ArcherAttack_A", false);
		else
			at->PlayAnimation(L"ArcherAttack_AR", false);
	}
	void Archer::shootbow_upward()
	{
		as->Play("AdventurerHunter_Attack_Ready");
		_state = Archer_State::Attack_B_Ready;
		if (_Dir == 1)
			at->PlayAnimation(L"ArcherAttack_B", false);
		if (_Dir == -1)
			at->PlayAnimation(L"ArcherAttack_BR", false);
	}
	void Archer::pushaway()
	{
		int voice_archer = random(0, 1);
		if (voice_archer == 0)
			as->Play("AdventurerHunter_Voice_Short");
		if (voice_archer == 1)
			as->Play("AdventurerHunter_Voice_Middle");
		_PushAway = true;
		_state = Archer_State::Attack_C;
		if (_Dir == 1)
		{
			at->PlayAnimation(L"ArcherAttack_C", true);
			_attackDir = 1;
		}
		else
		{
			at->PlayAnimation(L"ArcherAttack_CR", true);
			_attackDir = -1;
		}
	}
	void Archer::ultimate()
	{
		_state = Archer_State::Finishing_Move_Ready;
		as->Play("AdventurerHunter_Voice_Casting"); 
		as->Play("Adventurer_Charge_Start");			
		
		if (_Dir == 1)
			at->PlayAnimation(L"ArcherUltimate_Ready", false);
		else
			at->PlayAnimation(L"ArcherUltimate_ReadyR", false);
		_Ultimate = true;		
	}
	void Archer::dash_combo()
	{
		if (_Dir == 1)
		{
			at->PlayAnimation(L"ArcherBackStep", false);
			_rigidbody->SetVelocity(Vector2(-200.f, 200.f));
			_rigidbody->AddForce(Vector2(-10, 10));
			_Ground_check = false;
			_rigidbody->SetGround(false);
			_BackDash = true;
			_state = Archer_State::BackDash;
			_Numberof_BackDash++;
		}
		else
		{
			at->PlayAnimation(L"ArcherBackStepR", false);
			_rigidbody->SetVelocity(Vector2(200.f, 200.f));
			_rigidbody->AddForce(Vector2(10, 10));
			_Ground_check = false;
			_rigidbody->SetGround(false);
			_BackDash = true;
			_state = Archer_State::BackDash;
			_Numberof_BackDash++;
		}
	}


	void Archer::CompleteArcherIntro()
	{
		_state = Archer_State::Idle;
		if (_Dir == 1)
			at->PlayAnimation(L"ArcherIdle", true);
		else
			at->PlayAnimation(L"ArcherIdleR", true);
	}


	void Archer::SetDirection()
	{
		_tr = GetComponent<Transform>();
		pos = _tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_playerpos = Player::GetPlayer_Pos();
		_distance = _playerpos.x - pos.x;
		if (_distance >= 0.f)
			_Dir = 1;
		else
			_Dir = -1;
	}
	void Archer::Particle_Control()
	{
	}
	void Archer::Hpcontrol()
	{
		Transform* STATEUI_tr = _State_UI->GetComponent<Transform>();
		Transform* STATEUIhp_tr1 = Monster_UIHp->GetComponent<Transform>();
		Transform* STATEUIhp_tr2 = Monster_UIDamegeHp->GetComponent<Transform>();
		Transform* face_tr = _MbossFace->GetComponent<Transform>();
		Monster_UIHp->SetState(eState::Active);
		Monster_UIDamegeHp->SetState(eState::Active);

		if (_UIstate == 0)//1번
		{
			STATEUI_tr->SetPosition(Vector3(685.f, 375.f, 10));
			STATEUIhp_tr1->SetPosition(Vector3(650.f, 354.f, 5 ));
			STATEUIhp_tr2->SetPosition(Vector3(650.f, 354.f, 6));
			face_tr->SetPosition(Vector3(762.f, 375.f,1));
		}
		if (_UIstate == 1)//2번
		{
			STATEUI_tr->SetPosition(Vector3(685.f, 275.f, 10));
			STATEUIhp_tr1->SetPosition(Vector3(650.f, 254.f, 5));
			STATEUIhp_tr2->SetPosition(Vector3(650.f, 254.f, 6));
			face_tr->SetPosition(Vector3(762.f, 275.f, 1));

		}
		if (_UIstate == 2)//3번
		{
			STATEUI_tr->SetPosition(Vector3(685.f, 175.f, 10));
			STATEUIhp_tr1->SetPosition(Vector3(650.f, 154.f, 5));
			STATEUIhp_tr2->SetPosition(Vector3(650.f, 154.f, 6));
			face_tr->SetPosition(Vector3(762.f, 175.f, 1));
		}



		Transform* hp_tr = Monster_Hp->GetComponent<Transform>();
		hp_tr->SetPosition(Vector3(pos.x, pos.y - 90.f, pos.z - 2.f));

		Transform* hpdamege_tr = Monster_DamegeHp->GetComponent<Transform>();
		hpdamege_tr->SetPosition(Vector3(pos.x, pos.y - 90.f, pos.z - 1.5f));

		Transform* hpfr_tr = Hpbar_Frame->GetComponent<Transform>();
		hpfr_tr->SetPosition(Vector3(pos.x, pos.y - 90.f, pos.z - 1.f));


		if (_Hp_control == true)
		{
			if (Monster_DamegeHp->Get_Switch() == true)
			{
				_Hp_time += static_cast<float>(Time::DeltaTime());
				if (_Hp_time > 2)
				{
					Hpbar_Frame->SetState(eState::Paused);
					Monster_DamegeHp->SetState(eState::Paused);
					Monster_Hp->SetState(eState::Paused);
					Monster_DamegeHp->Set_Switch(false);
					_Hp_control = false;
					_Hp_time = 0.f;
				}
			}
		}
		if (_CurrenHp <= 0)
		{
			Hpbar_Frame->SetState(eState::Paused);
			Monster_DamegeHp->SetState(eState::Paused);
			Monster_Hp->SetState(eState::Paused);
			_Die = true;
			_MbossFace->Set_animation(true);
			_MbossFace->Set_UISelect(1);
		}
	}
	void Archer::Effect_Control()
	{ 
		{
			Transform* _Hit_Effect_TR = _Hit_Effect->GetComponent<Transform>();
			if (_Dir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 20, pos.y - 30, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 20, pos.y - 30, pos.z - 1));
		}
		{
			Transform* _Hit_Effect_TR = _Critical_Middle->GetComponent<Transform>();
			if (_Dir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 20, pos.y - 30, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 20, pos.y - 30, pos.z - 1));
		}
		{
			Transform* _Hit_Effect_TR = _Critical_High->GetComponent<Transform>();
			if (_Dir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 20, pos.y - 30, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 20, pos.y - 30, pos.z - 1));
		}
		{
			Transform* _Effect_TR = _Death_Effect->GetComponent<Transform>();
			_Effect_TR->SetPosition(Vector3(pos.x, pos.y, pos.z - 1));
		}
	}




	void Archer::complete_hit()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"ArcherIdle", true);
		else
			at->PlayAnimation(L"ArcherIdleR", true);
		_state = Archer_State::Idle;

	}
	void Archer::complete_attackA()
	{
	
	}
}