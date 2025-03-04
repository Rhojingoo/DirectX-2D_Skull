#include "Mage.h"
#include <iostream>
#include <random>
#include "HitBox_Mage.h"
#include "Include_Common.h"
#include "Ultimate_OnFire_Ready.h"
#include "Ultimate_OnFire.h"
#include "Ultimate_On_Fire_Projectile.h"
#include "Ultimate_OnFire_Fire.h"
#include "Mage_FireBall.h"
#include "Mage_BoomSign.h"
#include "Mage_FireBoom.h"
#include "Mage_Landing_Ready.h"
#include "Mage_Phoenix_Landing.h"
#include "Mage_Phoenix_Landing_Land.h"
#include "HitBox_Mage.h"
#include "Monster_Hp_Bar.h"
#include "HP_Frame.h"
#include "MiniBoss_State_UI.h"
#include "AdventureUI.h"
#include "..\Engine_SOURCE\jkAudioSource.h"

#include "Public_Ultimate_Aura.h"
#include "Public_Ultimate_AuraSmoke.h"
#include "Public_UltimateSkill_Effect_Complete.h"
#include "Public_UltimateSkill_Effect_Complete.h"
#include "Public_UltimateSkill_Effect_Complete.h"
#include "Public_UltimateSkill_Effect_Fail.h"
#include "AdventureUI.h"
#include "Monster_Hit_Effect.h"
#include "Player_Hit_Effect.h"
#include "Hit_Sword.h"
#include "Hit_Critical_Middle.h"
#include "Hit_Critical_High.h"
#include "Monster_Death_Effect.h"

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
		_rigidbody->SetGround(false);




		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Adventure_public\\Adventurer_Charge_Start.wav", "Adventurer_Charge_Start");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Adventure_public\\Adventurer_Charge_End.wav", "Adventurer_Charge_End");

		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\AdventurerMagician_Voice_Middle.wav", "AdventurerMagician_Voice_Middle");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\AdventurerMagician_Voice_FlameImpact.wav", "AdventurerMagician_Voice_FlameImpact");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\AdventurerMagician_Voice_Casting.wav", "AdventurerMagician_Voice_Casting");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\AdventurerMagician_Voice_Dead.wav", "AdventurerMagician_Voice_Dead");

				
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\AdventurerMagician_PhoenixLanding.wav", "Atk_Whoosh_High");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\AdventurerMagician_PhoenixLanding.wav", "AdventurerMagician_PhoenixLanding");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\AdventurerMagician_PhoenixLanding_Ready.wav", "AdventurerMagician_PhoenixLanding_Ready");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\AdventurerMagician_FlameImpact_Summon.wav", "AdventurerMagician_FlameImpact_Summon");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\AdventurerMagician_FlameImpact.wav", "AdventurerMagician_FlameImpact");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\Atk_Flame_Large_1.wav", "Atk_Flame_Large_1");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\Atk_Flame_Large_2.wav", "Atk_Flame_Large_2");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\Atk_Flame_Large_3.wav", "Atk_Flame_Large_3");
		

		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Blunt_Small.wav", "Hit_Blunt_Small");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Monster\\Common_Hit\\Hit_Sword_Small.wav", "Hit_Sword_Small");







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
		Scene* scene = SceneManager::GetInitializeScene();
		//UI 및 체력관련		
		{
			_MbossFace = new AdventureUI();
			_MbossFace->Initialize();
			_MbossFace->Set_animation(true);
			_MbossFace->Set_UISelect(6);
			scene->AddGameObject(eLayerType::UI, _MbossFace);
			_MbossFace->SetName(L"_MbossFace");
			Transform* face_tr = _MbossFace->GetComponent<Transform>();
			face_tr->SetPosition(Vector3(762.f, 375.f, pos.z));
			face_tr->SetScale(26 * 2, 26.f * 2, 0);
		}

		{
			_State_UI = new MiniBoss_State_UI();
			scene->AddGameObject(eLayerType::UI, _State_UI);
			_State_UI->SetName(L"hp_bar_frame");
			Transform* hp_tr = _State_UI->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(685.f, 375.f, pos.z));
			hp_tr->SetScale(108.f * 2, 30.f * 2, 0);
		}
		{
			Monster_UIHp = new Monster_Hp_Bar(L"EnemyHealthBar");
			scene->AddGameObject(eLayerType::UI, Monster_UIHp);
			Monster_UIHp->SetName(L"warrior_hp_bar");
			Transform* hp_tr = Monster_UIHp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(pos.x, pos.y + 50, pos.z - 1));
			hp_tr->SetScale(137, 12.5, 0);
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
			hp_tr->SetPosition(Vector3(pos.x, pos.y - 90, pos.z - 1));
			hp_tr->SetScale(50, 5, 0);
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
			hp_tr->SetPosition(Vector3(pos.x, pos.y + 50, pos.z - 1));
			hp_tr->SetScale(48, 3, 0);
			Monster_Hp->Set_Max_Hp(_MaxHp);
			Monster_Hp->Set_Current_Hp(_MaxHp);
			Monster_Hp->SetState(eState::Paused);
		}

	

		{
			Ultimate_Aura = new Public_Ultimate_Aura;
			Ultimate_Aura->Initialize();
			scene->AddGameObject(eLayerType::Effect, Ultimate_Aura);
			Transform* bullet_tr = Ultimate_Aura->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Ultimate_Aura->SetState(eState::Paused);
		}
		{
			Ultimate_AuraSmoke = new Public_Ultimate_AuraSmoke;
			Ultimate_AuraSmoke->Initialize();
			scene->AddGameObject(eLayerType::Effect, Ultimate_AuraSmoke);
			Transform* bullet_tr = Ultimate_AuraSmoke->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Ultimate_AuraSmoke->SetState(eState::Paused);
		}
		{
			UltimateSkill_Effect_Complete = new Public_UltimateSkill_Effect_Complete;
			UltimateSkill_Effect_Complete->Initialize();
			scene->AddGameObject(eLayerType::Effect, UltimateSkill_Effect_Complete);
			Transform* bullet_tr = UltimateSkill_Effect_Complete->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			UltimateSkill_Effect_Complete->SetState(eState::Paused);
		}
		{
			UltimateSkill_Effect_Fail = new Public_UltimateSkill_Effect_Fail;
			UltimateSkill_Effect_Fail->Initialize();
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
				scene->AddGameObject(eLayerType::Bullet, FireBoom[i]);
				Transform* bullet_tr = FireBoom[i]->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
				FireBoom[i]->SetState(eState::Paused);
			}
		}
		{
			Landing_Ready = new Mage_Landing_Ready;
			Landing_Ready->Initialize();
			scene->AddGameObject(eLayerType::Effect, Landing_Ready);
			Transform* bullet_tr = Landing_Ready->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Landing_Ready->SetState(eState::Paused);
		}
		{
			Phoenix_Landing = new Mage_Phoenix_Landing;
			Phoenix_Landing->Initialize();
			scene->AddGameObject(eLayerType::Effect, Phoenix_Landing);
			Transform* bullet_tr = Phoenix_Landing->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Phoenix_Landing->SetState(eState::Paused);
		}
		{
			Phoenix_Landing_Land = new Mage_Phoenix_Landing_Land;
			Phoenix_Landing_Land->Initialize();
			scene->AddGameObject(eLayerType::Effect, Phoenix_Landing_Land);
			Transform* bullet_tr = Phoenix_Landing_Land->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(pos.x, pos.y, -205));
			Phoenix_Landing_Land->SetState(eState::Paused);		
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

		{
			Hit_Box = new HitBox_Mage();
			Hit_Box->Initialize();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetState(eState::Paused);
		}

		_first_place = pos;
		at->PlayAnimation(L"MageIdle", true);
		GameObject::Initialize();
	}
	void Mage::Update()
	{
		SetDirection();
		Particle_Control();
		Hpcontrol();
		Effect_Control();		

		ground_distance_L = Left_Ground.x - pos.x;
		ground_distance_R = Right_Ground.x - pos.x;



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
		_collider->SetCenter(Vector2(0.0f, -30.f));

		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_attack_Col == true)
		{
			Hit_Box->SetSize(Vector2(150.f, 85.f));
			HitBox_TR->SetPosition(Vector3(pos.x, pos.y - 30, pos.z));

			Hit_Box->SetState(eState::Active);
			//if (_attackDir == 1)
			//	HitBox_TR->SetPosition(Vector3(_Pos.x + 50, _Pos.y - 30, _Pos.z));
			//else
			//	HitBox_TR->SetPosition(Vector3(_Pos.x - 50, _Pos.y - 30, _Pos.z));
		}
		else if(_state == Mage_State::Die)
		{
			Hit_Box->SetState(eState::Paused);
		}
		else
		{
			Hit_Box->SetState(eState::Paused);
		}



		GameObject::LateUpdate();
	}
	void Mage::Render()
	{
		GameObject::Render();
	}


	void Mage::OnCollisionEnter(Collider2D* other)
	{
		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
		{
			if (_state == Mage_State::Die)
				return;

			_Damage = player->GetDamage();
			bool attack = player->Geteffect();
			bool attack_Cri_Mid = player->Geteffect_Mid();
			bool attack_Cri_High = player->Geteffect_Hight();
									
			if (_state == Mage_State::Idle)
			{
				_hit++;
				_state = Mage_State::Hit;
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


				if (mDir == 1)
				{
					_attackDir = 1;
					at->PlayAnimation(L"MageHit", true);
					if (_hit < 2)
						_rigidbody->SetVelocity(Vector2(-50.f, 0.f));
					_Hit_Effect->SetDirection(-1);
					_Critical_Middle->SetDirection(-1);
					_Critical_High->SetDirection(-1);

				}
				if (mDir == -1)
				{
					_attackDir = -1;
					at->PlayAnimation(L"MageHitR", true);
					if (_hit < 2)
						_rigidbody->SetVelocity(Vector2(50.f, 0.f));
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


				if (_attackDir == 1)
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


			if (_CurrenHp <= 0)
			{
				_state = Mage_State::Die;				
				as->Play("AdventurerMagician_Voice_Dead");
				_Hit_Effect->_effect_animation = true;
				if (mDir == 1)
				{
					at->PlayAnimation(L"MageDie", false);
					_Hit_Effect->SetDirection(-1);
				}
				else
				{
					at->PlayAnimation(L"MageDieR", false);
					_Hit_Effect->SetDirection(1);
				}
				_Death_Effect->SetState(eState::Active);

				if (_sky == true)
				{
					_rigidbody->SetGround(false);
					_Ground_check = false;
					_ground = true;
				}
			}
		}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			if (_state == Mage_State::Die)
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
				if (_state == Mage_State::Idle)
				{
					_hit++;
					_Hit_Effect->_effect_animation = true;
					_Critical_Middle->_effect_animation = true;
					_Critical_High->_effect_animation = true;
					_state = Mage_State::Hit;
					if (mDir == 1)
					{
						_attackDir = 1;
						at->PlayAnimation(L"MageHit", true);
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
					if (mDir == -1)
					{
						_attackDir = -1;
						at->PlayAnimation(L"MageHitR", true);
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

					if (mDir == 1)
					{
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
					_state = Mage_State::Die;
					as->Play("AdventurerMagician_Voice_Dead");
					_Hit_Effect->_effect_animation = true;
					if (mDir == 1)
					{
						at->PlayAnimation(L"MageDie", false);
						_Hit_Effect->SetDirection(-1);
					}
					else
					{
						at->PlayAnimation(L"MageDieR", false);
						_Hit_Effect->SetDirection(1);
					}
					_Death_Effect->SetState(eState::Active);
				}

				_bulletcheck++;
			}
		}
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
					if(_GroundLanding == false)
						as->Play("AdventurerMagician_PhoenixLanding");
					_GroundLanding = true;
				}
			}
		}

		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				if (_state == Mage_State::Attack_C)
				{
					if (_GroundLanding == false)
						as->Play("AdventurerMagician_PhoenixLanding");

					_GroundLanding = true;
				}
			}
		}

		if (Ground_and_Wall* mGround = dynamic_cast<Ground_and_Wall*>(other->GetOwner()))
		{
			Transform* GRTR = mGround->GetComponent<Transform>();
			Vector3 GRpos = GRTR->GetPosition();
			_rigidbody->ClearVelocity();
		}
	}
	void Mage::OnCollisionExit(Collider2D* other)
	{
		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			_bulletcheck = 0;
		}
	}


	void Mage::idle()
	{
		if(_ground == true)
			_Ground_check = true;
		else
			_Ground_check = false;

		Fly_or_Landing();

		_swich_checkpoint = randomcount(0, 3);
		//_swich_checkpoint = 3;
	

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
			_time += static_cast<float>(Time::DeltaTime());
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

					as->Play("AdventurerMagician_Voice_Casting");
					as->Play("Adventurer_Charge_Start");
					_state = Mage_State::Finishing_Move_Ready;
					if (mDir == 1)
						at->PlayAnimation(L"MageUltimate_Set", true);
					if (mDir == -1)
						at->PlayAnimation(L"MageUltimate_SetR", true);
					_UltimateSet = false;					
				}


				if (_swich_checkpoint ==4)// 각성 공격
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
	}	
	void Mage::die()
	{
		Ultimate_Aura->SetState(eState::Paused);
		Ultimate_AuraSmoke->SetState(eState::Paused);
		_attack_Col = false;
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
				int voice_archer = random(0, 1);
				if (voice_archer == 0)
					as->Play("AdventurerMagician_Voice_Middle");
				if (voice_archer == 1)
					as->Play("AdventurerMagician_Voice_FlameImpact");
				as->Play("Atk_Whoosh_High");

				
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
				int voice_archer = random(0, 1);
				if (voice_archer == 0)
					as->Play("AdventurerMagician_Voice_Middle");
				if (voice_archer == 1)
					as->Play("AdventurerMagician_Voice_FlameImpact");
				as->Play("Atk_Whoosh_High");

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
				as->Play("AdventurerMagician_FlameImpact");
				BoomSign[_Number_of_attackB]->_effect_check = false;
			}
			if (BoomSign[_Number_of_attackB]->_effect_On == false)
			{
				Vector3 effectpos = Effect_tr->GetPosition();
				bullet_tr->SetPosition(effectpos);
				FireBoom[_Number_of_attackB]->SetState(eState::Active);
				as->Play("AdventurerMagician_FlameImpact_Summon");
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
				pos.x += 300.f * static_cast<float>(Time::DeltaTime());

				if (pos.y < 150 + _playerpos.y)
					pos.y += 200.f * static_cast<float>(Time::DeltaTime());
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
				pos.x -= 300.f * static_cast<float>(Time::DeltaTime());

				if (pos.y < 150 + _playerpos.y)
					pos.y += 200.f * static_cast<float>(Time::DeltaTime());
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

				int voice_archer = random(0, 1);
				if (voice_archer == 0)
					as->Play("AdventurerMagician_Voice_Middle");
				if (voice_archer == 1)
					as->Play("AdventurerMagician_Voice_FlameImpact");

				as->Play("AdventurerMagician_PhoenixLanding_Ready");

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
			_attack_Col = true;
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
				_attack_Col = false;
				_attack_time += static_cast<float>(Time::DeltaTime());
				if (_attack_time > 0.5)
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
			pos.y += 200.f * static_cast<float>(Time::DeltaTime());
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
				if (mDir == 1)
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
			_UltimateSet = false;
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
				if (mDir == 1)
					UltimateSkill_Effect_Fail->SetDirection(1);
				else
					UltimateSkill_Effect_Fail->SetDirection(-1);
				UltimateSkill_Effect_Fail->SetState(eState::Active);

				as->Play("Adventurer_Charge_End");
				_state = Mage_State::Finishing_Move_Fail;
				_attack_time = 0.f;
			}
			else
			{
				// 이펙트 설정시 5초가 10번이상의 타격이 없다면 석세스로 넘어간뒤 Effect 날려야한다.
				Transform* bullet_tr = UltimateSkill_Effect_Complete->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(pos.x, pos.y - 25.f, pos.z - 1.1f));
				if (mDir == 1)
					UltimateSkill_Effect_Complete->SetDirection(1);
				else
					UltimateSkill_Effect_Complete->SetDirection(-1);
				UltimateSkill_Effect_Complete->SetState(eState::Active);

				{
					Transform* _OnFire_Ready_tr0 = _OnFire_Ready[0]->GetComponent<Transform>();
					_OnFire_Ready_tr0->SetPosition(Vector3(_playerpos.x, _first_place.y, pos.z + 1.f));

					Transform* _OnFire_Ready_tr1 = _OnFire_Ready[1]->GetComponent<Transform>();
					_OnFire_Ready_tr1->SetPosition(Vector3(_playerpos.x-200.f, _first_place.y-100.f, pos.z + 1.f));

					Transform* _OnFire_Ready_tr2 = _OnFire_Ready[2]->GetComponent<Transform>();
					_OnFire_Ready_tr2->SetPosition(Vector3(_playerpos.x+200.f, _first_place.y-100.f, pos.z + 1.f));


					Transform* _OnFire_tr0 = _OnFire[0]->GetComponent<Transform>();
					_OnFire[0]->_effect_On = false;
					_OnFire_tr0->SetPosition(Vector3(_playerpos.x, _first_place.y, pos.z + 1.f));

					Transform* _OnFire_tr1 = _OnFire[1]->GetComponent<Transform>();
					_OnFire[1]->_effect_On = false;
					_OnFire_tr1->SetPosition(Vector3(_playerpos.x-200.f, _first_place.y-100.f, pos.z + 1.f));

					Transform* _OnFire_tr2 = _OnFire[2]->GetComponent<Transform>();
					_OnFire[2]->_effect_On = false;
					_OnFire_tr2->SetPosition(Vector3(_playerpos.x+200.f, _first_place.y-100.f, pos.z + 1.f));
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
			_attack_time += static_cast<float>(Time::DeltaTime());
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
							as->Play("AdventurerMagician_FlameImpact_Summon");					
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
					firefire_tr->SetPosition(Vector3(BulletPos.x, BulletPos.y, BulletPos.z-1.1f));
				}
				for (int i = 3; i < 6; i++)
				{
					Transform* _OnFire_tr = _OnFire[i-3]->GetComponent<Transform>();
					Vector3  BulletPos = _OnFire_tr->GetPosition();
					Transform* bullet_tr = On_Fire_Projectile[i]->GetComponent<Transform>();
					On_Fire_Projectile[i]->_rotationswitch = false;
					On_Fire_Projectile[i]->_missile = false;
					bullet_tr->SetPosition(Vector3(BulletPos.x, BulletPos.y, BulletPos.z - 1.f));
					bullet_tr->SetRotationZ(0);
					Transform* firefire_tr = OnFire_Fire[i]->GetComponent<Transform>();
					OnFire_Fire[i]->_effect_On = false;
					firefire_tr->SetPosition(Vector3(BulletPos.x, BulletPos.y, BulletPos.z - 1.1f));
				}
				for (int i = 6; i < 9; i++)
				{
					Transform* _OnFire_tr = _OnFire[i-6]->GetComponent<Transform>();
					Vector3  BulletPos = _OnFire_tr->GetPosition();
					Transform* bullet_tr = On_Fire_Projectile[i]->GetComponent<Transform>();
					On_Fire_Projectile[i]->_rotationswitch = false;
					On_Fire_Projectile[i]->_missile = false;
					bullet_tr->SetPosition(Vector3(BulletPos.x, BulletPos.y, BulletPos.z - 1.f));
					bullet_tr->SetRotationZ(0);
					Transform* firefire_tr = OnFire_Fire[i]->GetComponent<Transform>();
					OnFire_Fire[i]->_effect_On = false;
					firefire_tr->SetPosition(Vector3(BulletPos.x, BulletPos.y, BulletPos.z - 1.1f));
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
		_state = Mage_State::Groggy;
		if (mDir == 1)
			at->PlayAnimation(L"MageGroggy", true);
		else
			at->PlayAnimation(L"MageGroggyR", true);
		_hit = 0;
	}
	void Mage::Finishing_Move()
	{
		_attack_time += static_cast<float>(Time::DeltaTime());

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
						
						int voice_archer = random(1, 3);
						if (voice_archer == 1)
							as->Play("Atk_Flame_Large_1");
						if (voice_archer == 2)
							as->Play("Atk_Flame_Large_2");
						if (voice_archer == 3)
							as->Play("Atk_Flame_Large_3");
						_OnFire_Projectile_rg->SetGravity(true);
						_OnFire_Projectile_rg->SetFriction(true);
						Fire_Projectile(i);

						On_Fire_Projectile[i]->_missile = true;
						if (i == 8)
						{
							_OnFire[0]->_effect_On = false;
							_OnFire[1]->_effect_On = false;
							_OnFire[2]->_effect_On = false;
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

			if (_ground == true)
				_flyswich++;
			if (_sky == true)
				_landingswich++;

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
		_attack_time += static_cast<float>(Time::DeltaTime());
		if (_attack_time >= 3.5)
		{
			_attack_time = 0;
			_attack = false;

			_state = Mage_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"MageIdle", true);
			else
				at->PlayAnimation(L"MageIdleR", true);
		}
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
		_movetime += static_cast<float>(Time::DeltaTime());

		if (_maxright > pos.x)
		{
			if (_movetime < _mtime)
			{				
				pos.x += 100.f * static_cast<float>(Time::DeltaTime());
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
			_movetime += static_cast<float>(Time::DeltaTime());
			if (_movetime < _mtime)
			{
				pos.x += 100.f * static_cast<float>(Time::DeltaTime());
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
		_movetime += static_cast<float>(Time::DeltaTime());

		if (_maxleft < pos.x)
		{
			if (_movetime < _mtime)
			{
				pos.x -= 100.f * static_cast<float>(Time::DeltaTime());
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
		_movetime += static_cast<float>(Time::DeltaTime());
		if (_movetime < _mtime)
		{
			pos.x -= 100.f * static_cast<float>(Time::DeltaTime());
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
				attackpoint.Normalize();
				float angle = std::atan2(attackpoint.y, attackpoint.x);
				tr->AddRotationZ(angle);
			}
			else
			{
				On_Fire_Projectile[i]->SetDirection(-1);
				Vector2 attackpoint = Vector2(tr->GetPositionX() - _playerpos.x, tr->GetPositionY() - _playerpos.y);
				attackpoint.Normalize();
				float angle = std::atan2(attackpoint.y, attackpoint.x);
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
				attackpoint.Normalize();
				float angle = std::atan2(attackpoint.y, attackpoint.x);
				tr->AddRotationZ(angle);
			}
			else
			{
				FireBall[i]->SetDirection(-1);
				Vector2 attackpoint = Vector2(tr->GetPositionX() - _playerpos.x, tr->GetPositionY() - _playerpos.y);
				attackpoint.Normalize();
				float angle = std::atan2(attackpoint.y, attackpoint.x);
				tr->AddRotationZ(angle);
			}
			FireBall[i]->_rotationswitch = true;
		}
	}


	void Mage::SetDirection()
	{
		tr = GetComponent<Transform>();
		pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_playerpos = Player::GetPlayer_Pos();
		_distance = _playerpos.x - pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;
	}
	void Mage::Particle_Control()
	{
	}
	void Mage::Hpcontrol()
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
			STATEUIhp_tr1->SetPosition(Vector3(650.f, 354.f, 5));
			STATEUIhp_tr2->SetPosition(Vector3(650.f, 354.f, 6));
			face_tr->SetPosition(Vector3(762.f, 375.f, 1));
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
			STATEUI_tr->SetPosition(Vector3(685.f, 175.f, 10.f));
			STATEUIhp_tr1->SetPosition(Vector3(650.f, 154.f, 5.f));
			STATEUIhp_tr2->SetPosition(Vector3(650.f, 154.f, 6.f));
			face_tr->SetPosition(Vector3(762.f, 175.f, 1.f));
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
			_attack_Col = false;
			_MbossFace->Set_animation(true);
			_MbossFace->Set_UISelect(7);
		}
	}
	void Mage::Effect_Control()
	{
		{
			Transform* _Hit_Effect_TR = _Hit_Effect->GetComponent<Transform>();
			if (_attackDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 20, pos.y - 30, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 20, pos.y - 30, pos.z - 1));
		}
		{
			Transform* _Hit_Effect_TR = _Critical_Middle->GetComponent<Transform>();
			if (_attackDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 20, pos.y - 30, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 20, pos.y - 30, pos.z - 1));
		}
		{
			Transform* _Hit_Effect_TR = _Critical_High->GetComponent<Transform>();
			if (_attackDir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(pos.x + 20, pos.y - 30, pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(pos.x - 20, pos.y - 30, pos.z - 1));
		}
		{
			Transform* _Effect_TR = _Death_Effect->GetComponent<Transform>();
			_Effect_TR->SetPosition(Vector3(pos.x, pos.y, pos.z - 1));
		}
	}


	void Mage::complete_hit()
	{
		_state = Mage_State::Idle;
		if (mDir == 1)
			at->PlayAnimation(L"MageIdle", true);
		else
			at->PlayAnimation(L"MageIdleR", true);
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
		as->Play("Adventurer_Charge_End");
	}


	void Mage::complete_intro()
	{
		float randomposX = static_cast<float>(random(static_cast<int>(_playerpos.x) - 100, static_cast<int>(_playerpos.x) + 100));
		Vector3 TeleportPos = Vector3(randomposX, _playerpos.y + 150.f, pos.z);
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

		int voice_archer = random(0, 1);
		if (voice_archer == 0)
			as->Play("AdventurerMagician_Voice_Middle");
		if (voice_archer == 1)
			as->Play("AdventurerMagician_Voice_FlameImpact");
		as->Play("Atk_Whoosh_High");
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
		int voice_archer = random(0, 1);
		if (voice_archer == 0)
			as->Play("AdventurerMagician_Voice_Middle");
		if (voice_archer == 1)
			as->Play("AdventurerMagician_Voice_FlameImpact");

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
		if (_flyswich >= 5)
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
		if (_landingswich >= 3)
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
		return distribution(gen);

		//_swich_checkpoint = distribution(gen);		
		//return _swich_checkpoint;
	}
}
