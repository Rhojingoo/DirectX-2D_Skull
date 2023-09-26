#include "Layana_Dark_Awaken.h"


namespace jk
{
	bool Layana_Dark_Awaken::_AttackStageON = true;
	Layana_Dark_Awaken::Layana_Dark_Awaken_State Layana_Dark_Awaken::_DarkMode_state = Layana_Dark_Awaken_State();
	int Layana_Dark_Awaken::_Dir = 1;


	int	Layana_Dark_Awaken::_HitType = 0;
	int	Layana_Dark_Awaken::_Dammege = 0;
	Player_Hp_Bar* Layana_Dark_Awaken::Player_Hp = nullptr;
	Monster_Hit_Effect* Layana_Dark_Awaken::_Hit_Effect = nullptr;
	Player_Hit_Effect* Layana_Dark_Awaken::_Hit_Effect_player = nullptr;
	Hit_Sword* Layana_Dark_Awaken::_Hit_Sword = nullptr;
	Hit_Critical_Middle* Layana_Dark_Awaken::_Critical_Middle = nullptr;
	Hit_Critical_High* Layana_Dark_Awaken::_Critical_High = nullptr;
	Monster_Death_Effect* Layana_Dark_Awaken::_Death_Effect = nullptr;


	Layana_Dark_Awaken::Layana_Dark_Awaken()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Layana_Dark_Awaken::~Layana_Dark_Awaken()
	{
	}


	void Layana_Dark_Awaken::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);


		tr = GetComponent<Transform>();
		_pos = Vector3(0.f, 0.f, -200.f);
		_Createpos = _pos;
		tr->SetPosition(_pos);
		
		
		at = AddComponent<Animator>(); 
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\AwakenEnd", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Backstep", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Death_00", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Death_01", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Death_02", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Death_03", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Cross00_Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Cross01_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Cross02_Landing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Cross03_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Cross04_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Ground01_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Ground02_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Ground03_Landing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Ground04_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Vertical00_Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Vertical01_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Vertical02_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Vertical03_Landing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Vertical04_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Rush_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Rush_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushA", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushB", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushC", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushC_1", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushC_2", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushC_3", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushC_4", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushC_5", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushC_6", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushC_7", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_A_Bullet", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_A_Bullet_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_B_RisingPierce", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_B_RisingPierce_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_C_DimensionPierce", this);


		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\AwakenEnd", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Backstep", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Dash", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Death_00", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Death_01", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Death_02", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Death_03", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Idle", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Cross00_Jump", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Cross01_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Cross02_Landing", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Cross03_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Cross04_Attack", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Ground01_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Ground02_Attack", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Ground03_Landing", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Ground04_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Vertical00_Jump", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Vertical01_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Vertical02_Attack", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Vertical03_Landing", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Meteor_Vertical04_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Rush_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Rush_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushA", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushB", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushC", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushC_1", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushC_2", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushC_3", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushC_4", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushC_5", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushC_6", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\RushC_7", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_A_Bullet", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_A_Bullet_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_B_RisingPierce", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_B_RisingPierce_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_C_DimensionPierce", this,1);
		

		//bind 부분
		at->CompleteEvent(L"Awaken_PowerAwakenEnd") = std::bind(&Layana_Dark_Awaken::Complete_AwakenEnd, this);
		at->CompleteEvent(L"Awaken_PowerRush_Ready") = std::bind(&Layana_Dark_Awaken::Complete_RushReady, this);
		at->CompleteEvent(L"Awaken_PowerRushA") = std::bind(&Layana_Dark_Awaken::Complete_RushA, this);
		at->CompleteEvent(L"Awaken_PowerRushB") = std::bind(&Layana_Dark_Awaken::Complete_RushB, this);
		at->CompleteEvent(L"Awaken_PowerRush_End") = std::bind(&Layana_Dark_Awaken::Complete_RushEnd, this);
		at->CompleteEvent(L"Awaken_PowerRushC_1") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C1, this);
		at->CompleteEvent(L"Awaken_PowerRushC_2") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C2, this);
		at->CompleteEvent(L"Awaken_PowerRushC_3") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C3, this);
		at->CompleteEvent(L"Awaken_PowerRushC_4") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C4, this);
		at->CompleteEvent(L"Awaken_PowerRushC_5") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C5, this);
		at->CompleteEvent(L"Awaken_PowerRushC_6") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C6, this);
		at->CompleteEvent(L"Awaken_PowerRushC_7") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C7, this);
	
		at->CompleteEvent(L"Awaken_PowerMeteor_Cross01_Ready") = std::bind(&Layana_Dark_Awaken::Complete_CrossJump, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Cross03_End") = std::bind(&Layana_Dark_Awaken::Complete_CrossEnd, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Ground04_End") = std::bind(&Layana_Dark_Awaken::Complete_GroundEnd, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Vertical00_Jump") = std::bind(&Layana_Dark_Awaken::Complete_VerticalJump, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Vertical01_Ready") = std::bind(&Layana_Dark_Awaken::Complete_VerticalReady, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Vertical04_End") = std::bind(&Layana_Dark_Awaken::Complete_VerticalEnd, this);
		at->CompleteEvent(L"Awaken_PowerSkill_A_Bullet_End") = std::bind(&Layana_Dark_Awaken::Complete_Skill_A, this);
		at->CompleteEvent(L"Awaken_PowerSkill_B_RisingPierce") = std::bind(&Layana_Dark_Awaken::Complete_Skill_B, this);
		at->CompleteEvent(L"Awaken_PowerSkill_B_RisingPierce_End") = std::bind(&Layana_Dark_Awaken::Complete_Skill_B, this);


		at->CompleteEvent(L"Awaken_PowerAwakenEndR") = std::bind(&Layana_Dark_Awaken::Complete_AwakenEnd, this);
		at->CompleteEvent(L"Awaken_PowerRush_ReadyR") = std::bind(&Layana_Dark_Awaken::Complete_RushReady, this);
		at->CompleteEvent(L"Awaken_PowerRushAR") = std::bind(&Layana_Dark_Awaken::Complete_RushA, this);
		at->CompleteEvent(L"Awaken_PowerRushBR") = std::bind(&Layana_Dark_Awaken::Complete_RushB, this);
		at->CompleteEvent(L"Awaken_PowerRush_EndR") = std::bind(&Layana_Dark_Awaken::Complete_RushEnd, this);
		at->CompleteEvent(L"Awaken_PowerRushC_1R") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C1, this);
		at->CompleteEvent(L"Awaken_PowerRushC_2R") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C2, this);
		at->CompleteEvent(L"Awaken_PowerRushC_3R") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C3, this);
		at->CompleteEvent(L"Awaken_PowerRushC_4R") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C4, this);
		at->CompleteEvent(L"Awaken_PowerRushC_5R") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C5, this);
		at->CompleteEvent(L"Awaken_PowerRushC_6R") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C6, this);
		at->CompleteEvent(L"Awaken_PowerRushC_7R") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C7, this);
		
		at->CompleteEvent(L"Awaken_PowerMeteor_Cross01_ReadyR") = std::bind(&Layana_Dark_Awaken::Complete_CrossJump, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Cross03_EndR") = std::bind(&Layana_Dark_Awaken::Complete_CrossEnd, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Ground04_EndR") = std::bind(&Layana_Dark_Awaken::Complete_GroundEnd, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Vertical00_JumpR") = std::bind(&Layana_Dark_Awaken::Complete_VerticalJump, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Vertical01_ReadyR") = std::bind(&Layana_Dark_Awaken::Complete_VerticalReady, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Vertical04_EndR") = std::bind(&Layana_Dark_Awaken::Complete_VerticalEnd, this);
		at->CompleteEvent(L"Awaken_PowerSkill_A_Bullet_EndR") = std::bind(&Layana_Dark_Awaken::Complete_Skill_A, this);
		at->CompleteEvent(L"Awaken_PowerSkill_B_RisingPierceR") = std::bind(&Layana_Dark_Awaken::Complete_Skill_B, this);
		at->CompleteEvent(L"Awaken_PowerSkill_B_RisingPierce_EndR") = std::bind(&Layana_Dark_Awaken::Complete_Skill_B, this);
		at->CompleteEvent(L"Awaken_PowerSkill_C_DimensionPierce") = std::bind(&Layana_Dark_Awaken::Complete_Skill_B, this);
		at->CompleteEvent(L"Awaken_PowerSkill_C_DimensionPierceR") = std::bind(&Layana_Dark_Awaken::Complete_Skill_B, this);
		
			
	
		at->CompleteEvent(L"Awaken_PowerDeath_00") = std::bind(&Layana_Dark_Awaken::Complete_Death_00, this);
		at->CompleteEvent(L"Awaken_PowerDeath_00R") = std::bind(&Layana_Dark_Awaken::Complete_Death_00, this);
		at->CompleteEvent(L"Awaken_PowerDeath_01") = std::bind(&Layana_Dark_Awaken::Complete_Death_01, this);
		at->CompleteEvent(L"Awaken_PowerDeath_01R") = std::bind(&Layana_Dark_Awaken::Complete_Death_01, this);
		at->CompleteEvent(L"Awaken_PowerDeath_02") = std::bind(&Layana_Dark_Awaken::Complete_Death_02, this);
		at->CompleteEvent(L"Awaken_PowerDeath_02R") = std::bind(&Layana_Dark_Awaken::Complete_Death_02, this);		


		{
			Hit_Box = new HitBox_Layana();
			Hit_Box->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetState(eState::Paused);
		}

		for (int i = 0; i < 10; i++)
		{
			AfterImage[i] = new Layana_AfterImage();
			AfterImage[i]->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, AfterImage[i]);
			AfterImage[i]->Set_Owner(this);
			AfterImage[i]->SetState(eState::Paused);
		}

		for (int i = 0; i < 7; i++)
		{
			Rush_Sign[i] = new Layana_Awken_Rush_Sign;
			Rush_Sign[i]->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Rush_Sign[i]);
			Transform* bullet_tr = Rush_Sign[i]->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			Rush_Sign[i]->SetState(eState::Paused);
		}

		for (int i = 0; i < 7; i++)
		{
			Rush_Bullet[i] = new Latana_Awake_Rush_Bullet;
			Rush_Bullet[i]->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Rush_Bullet[i]);
			Transform* bullet_tr = Rush_Bullet[i]->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			Rush_Bullet[i]->SetState(eState::Paused);
		}

		{
			_Meteoreffect = new Layana_Awaken_Meteoreffect;
			_Meteoreffect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Meteoreffect);
			Transform* boss_effect = _Meteoreffect->GetComponent<Transform>();
			boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z-1));
			_Meteoreffect->SetState(eState::Paused);
		}

		{
			_Ground_Sign = new Layana_Awaken_Ground_Sign;
			_Ground_Sign->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Ground_Sign);
			Transform* boss_effect = _Ground_Sign->GetComponent<Transform>();
			boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			_Ground_Sign->SetState(eState::Paused);
		}
		
		{
			_Ground_Attack = new Latana_Awake_Rush_Bullet;
			_Ground_Attack->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, _Ground_Attack);
			Transform* boss_effect = _Ground_Attack->GetComponent<Transform>();
			boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			_Ground_Attack->SetState(eState::Paused);
		}

		{
			for (int i = 0; i < 7; i++)
			{
				_Ground_Thunder_Sign[i] = new Layana_Awaken_Ground_Thunder_Sign;
				_Ground_Thunder_Sign[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Effect, _Ground_Thunder_Sign[i]);
				_Ground_Thunder_Sign[i]->SetState(eState::Paused);
			}
			{
				Transform* effect0 = _Ground_Thunder_Sign[0]->GetComponent<Transform>();
				effect0->SetPosition(Vector3(_Createpos.x + 325, -115, _pos.z - 1));
				Transform* effect1 = _Ground_Thunder_Sign[1]->GetComponent<Transform>();
				effect1->SetPosition(Vector3(_Createpos.x + 217, -115, _pos.z - 1));
				Transform* effect2 = _Ground_Thunder_Sign[2]->GetComponent<Transform>();
				effect2->SetPosition(Vector3(_Createpos.x + 109, -115, _pos.z - 1));
				Transform* effect3 = _Ground_Thunder_Sign[3]->GetComponent<Transform>();
				effect3->SetPosition(Vector3(_Createpos.x, -115, _pos.z - 1));
				Transform* effect4 = _Ground_Thunder_Sign[4]->GetComponent<Transform>();
				effect4->SetPosition(Vector3(_Createpos.x - 109, -115, _pos.z - 1));
				Transform* effect5 = _Ground_Thunder_Sign[5]->GetComponent<Transform>();
				effect5->SetPosition(Vector3(_Createpos.x - 217, -115, _pos.z - 1));
				Transform* effect6 = _Ground_Thunder_Sign[6]->GetComponent<Transform>();
				effect6->SetPosition(Vector3(_Createpos.x - 325, -115, _pos.z - 1));
			}
		}

		
		{
			for (int i = 0; i < 7; i++)
			{
				_Ground_Thunder[i] = new Layana_Ground_Thunder;
				_Ground_Thunder[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Bullet, _Ground_Thunder[i]);
				_Ground_Thunder[i]->SetState(eState::Paused);
			}
			{
				Transform* bullet0 = _Ground_Thunder[0]->GetComponent<Transform>();
				bullet0->SetPosition(Vector3(_Createpos.x + 325, -40, _pos.z - 1));
				Transform* bullet1 = _Ground_Thunder[1]->GetComponent<Transform>();
				bullet1->SetPosition(Vector3(_Createpos.x + 217, -40, _pos.z - 1));
				Transform* bullet2 = _Ground_Thunder[2]->GetComponent<Transform>();
				bullet2->SetPosition(Vector3(_Createpos.x + 109, -40, _pos.z - 1));
				Transform* bullet3 = _Ground_Thunder[3]->GetComponent<Transform>();
				bullet3->SetPosition(Vector3(_Createpos.x, -40, _pos.z - 1));
				Transform* bullet4 = _Ground_Thunder[4]->GetComponent<Transform>();
				bullet4->SetPosition(Vector3(_Createpos.x - 109, -40, _pos.z - 1));
				Transform* bullet5 = _Ground_Thunder[5]->GetComponent<Transform>();
				bullet5->SetPosition(Vector3(_Createpos.x - 217, -40, _pos.z - 1));
				Transform* bullet6 = _Ground_Thunder[6]->GetComponent<Transform>();
				bullet6->SetPosition(Vector3(_Createpos.x - 325, -40, _pos.z - 1));
			}
		}


		{
			_Ground_DashSmoke= new  Layana_Awake_Ground_DashSmoke;
			_Ground_DashSmoke->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Ground_DashSmoke);
			Transform* boss_effect = _Ground_DashSmoke->GetComponent<Transform>();
			boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			_Ground_DashSmoke->SetState(eState::Paused);
		}


		{
			_GoldenMeteor_Effect = new  Layana_Awaken_GoldenMeteor_Effect;
			_GoldenMeteor_Effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _GoldenMeteor_Effect);
			Transform* boss_effect = _GoldenMeteor_Effect->GetComponent<Transform>();
			boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			_GoldenMeteor_Effect->SetState(eState::Paused);
		}

		
		{
			_Meteor_Electric = new  Layana_Awaken_Meteor_Electric;
			_Meteor_Electric->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Meteor_Electric);
			Transform* boss_effect = _Meteor_Electric->GetComponent<Transform>();
			boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			_Meteor_Electric->SetState(eState::Paused);
		}

		{
			for (int i = 0; i < 2; i++)
			{
				_Meteor_Projectile[i] = new  Layana_Awaken_Meteor_Projectile;
				_Meteor_Projectile[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Bullet, _Meteor_Projectile[i]);
				Transform* boss_effect = _Meteor_Projectile[i]->GetComponent<Transform>();
				boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
				_Meteor_Projectile[i]->SetState(eState::Paused);
			}
		}


		{
			for (int i = 0; i < 5; i++)
			{
				_Dark_HomingPierce[i] = new  Layana_Dark_HomingPierce;
				_Dark_HomingPierce[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Effect, _Dark_HomingPierce[i]);
				_Dark_HomingPierce[i]->SetState(eState::Paused);
			}
			{
				Transform* bullet0 = _Dark_HomingPierce[0]->GetComponent<Transform>();
				bullet0->SetPosition(Vector3(_Createpos.x + 250, 50, _pos.z - 1));
				Transform* bullet1 = _Dark_HomingPierce[1]->GetComponent<Transform>();
				bullet1->SetPosition(Vector3(_Createpos.x + 100, 100, _pos.z - 1));
				Transform* bullet2 = _Dark_HomingPierce[2]->GetComponent<Transform>();
				bullet2->SetPosition(Vector3(_Createpos.x , -25, _pos.z - 1));
				Transform* bullet3 = _Dark_HomingPierce[3]->GetComponent<Transform>();
				bullet3->SetPosition(Vector3(_Createpos.x-100, 100, _pos.z - 1));
				Transform* bullet4 = _Dark_HomingPierce[4]->GetComponent<Transform>();
				bullet4->SetPosition(Vector3(_Createpos.x -250, 50, _pos.z - 1));
			}
		}

		{
			for (int i = 0; i < 5; i++)
			{
				_HomingPierce_Effect[i] = new  Layana_Dark_HomingPierce_Effect;
				_HomingPierce_Effect[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Effect, _HomingPierce_Effect[i]);
				_HomingPierce_Effect[i]->SetState(eState::Paused);
			}
			{
				Transform* bullet0 = _HomingPierce_Effect[0]->GetComponent<Transform>();
				bullet0->SetPosition(Vector3(_Createpos.x + 250, 50, _pos.z - 1));
				Transform* bullet1 = _HomingPierce_Effect[1]->GetComponent<Transform>();
				bullet1->SetPosition(Vector3(_Createpos.x + 100, -50, _pos.z - 1));
				Transform* bullet2 = _HomingPierce_Effect[2]->GetComponent<Transform>();
				bullet2->SetPosition(Vector3(_Createpos.x, -25, _pos.z - 1));
				Transform* bullet3 = _HomingPierce_Effect[3]->GetComponent<Transform>();
				bullet3->SetPosition(Vector3(_Createpos.x - 100, -50, _pos.z - 1));
				Transform* bullet4 = _HomingPierce_Effect[4]->GetComponent<Transform>();
				bullet4->SetPosition(Vector3(_Createpos.x - 250, 50, _pos.z - 1));
			}	
		}

		{
			for (int i = 0; i < 5; i++)
			{
				_HomingPierce_Attack[i] = new  Layana_Awaken_Homing_Attac;
				_HomingPierce_Attack[i]->Initialize();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(eLayerType::Bullet, _HomingPierce_Attack[i]);
				_HomingPierce_Attack[i]->SetState(eState::Paused);
			}
			{
				Transform* bullet0 = _HomingPierce_Attack[0]->GetComponent<Transform>();
				bullet0->SetPosition(Vector3(_Createpos.x + 250, 50, _pos.z - 1));
				Transform* bullet1 = _HomingPierce_Attack[1]->GetComponent<Transform>();
				bullet1->SetPosition(Vector3(_Createpos.x + 100, -50, _pos.z - 1));
				Transform* bullet2 = _HomingPierce_Attack[2]->GetComponent<Transform>();
				bullet2->SetPosition(Vector3(_Createpos.x, -25, _pos.z - 1));
				Transform* bullet3 = _HomingPierce_Attack[3]->GetComponent<Transform>();
				bullet3->SetPosition(Vector3(_Createpos.x - 100, -50, _pos.z - 1));
				Transform* bullet4 = _HomingPierce_Attack[4]->GetComponent<Transform>();
				bullet4->SetPosition(Vector3(_Createpos.x - 250, 50, _pos.z - 1));			
			}			
		}


		{
			_DimensionPierce_Bosseffect = new  Dark_DimensionPierce_Attack;
			_DimensionPierce_Bosseffect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _DimensionPierce_Bosseffect);
			Transform* boss_effect = _DimensionPierce_Bosseffect->GetComponent<Transform>();
			boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			_DimensionPierce_Bosseffect->SetState(eState::Paused);
		}		
		
		{
			_DimensionPierce_Sign = new  Dark_DimensionPierce_Sign;
			_DimensionPierce_Sign->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _DimensionPierce_Sign);
			Transform* boss_effect = _DimensionPierce_Sign->GetComponent<Transform>();
			boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			_DimensionPierce_Sign->SetState(eState::Paused);
		}

		{
			_DimensionPierce_BulletEffect = new  Dark_DimensionPierce_BulletEffect;
			_DimensionPierce_BulletEffect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, _DimensionPierce_BulletEffect);
			Transform* boss_effect = _DimensionPierce_BulletEffect->GetComponent<Transform>();
			boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			_DimensionPierce_BulletEffect->SetState(eState::Paused);
		}

		//어웨이큰
		{
			Awaken_End_ElecEF = new  Awaken_End_Electric;
			Awaken_End_ElecEF->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Awaken_End_ElecEF);
			Transform* boss_effect = Awaken_End_ElecEF->GetComponent<Transform>();
			boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			Awaken_End_ElecEF->SetState(eState::Paused);
		}
		{
			Awaken_End_SmA_EF = new  Awaken_End_SmokeA;
			Awaken_End_SmA_EF->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Awaken_End_SmA_EF);
			Transform* boss_effect = Awaken_End_SmA_EF->GetComponent<Transform>();
			boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			Awaken_End_SmA_EF->SetState(eState::Paused);
		}
		{
			Awaken_End_SmB_EF = new  Awaken_End_SmokeB2;
			Awaken_End_SmB_EF->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Awaken_End_SmB_EF);
			Transform* boss_effect = Awaken_End_SmB_EF->GetComponent<Transform>();
			boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			Awaken_End_SmB_EF->SetState(eState::Paused);
		}


		//hp관련
		{
			Player_Hp = new Player_Hp_Bar;
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Monster, Player_Hp);
			Player_Hp->SetName(L"player_hp_bar");
			Transform* hp_tr = Player_Hp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(_pos.x, _pos.y + 50, _pos.z - 1));
			hp_tr->SetScale(_Max_LongHair_Hp, 10, 0);
			Player_Hp->Set_Max_Hp(_Max_LongHair_Hp);
			Player_Hp->Set_Current_Hp(_Max_LongHair_Hp);
			Player_Hp->SetState(eState::Paused);
		}

		{
			_Hit_Effect = new Monster_Hit_Effect;
			_Hit_Effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Hit_Effect);
			_Hit_Effect->SetState(eState::Paused);
		}

		{
			_Hit_Effect_player = new Player_Hit_Effect;
			_Hit_Effect_player->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Hit_Effect_player);
			_Hit_Effect_player->SetState(eState::Paused);
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
			_Death_Effect = new Monster_Death_Effect;
			_Death_Effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Death_Effect);
			_Death_Effect->SetState(eState::Paused);
		}




		//데스이펙트
		{
			_Death_Intro = new Death_IntroEffect;
			_Death_Intro->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Death_Intro);
			_Death_Intro->SetState(eState::Paused);
		}
		{
			_Death_EF_First = new Death_Effect_First;
			_Death_EF_First->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Death_EF_First);
			_Death_EF_First->SetState(eState::Paused);
		}
		{
			_Death_EF_Second = new Death_Effect_Second;
			_Death_EF_Second->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Death_EF_Second);
			_Death_EF_Second->SetState(eState::Paused);
		}
		{
			_Death_Elect1 = new Death_Elect_First;
			_Death_Elect1->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Death_Elect1);
			_Death_Elect1->SetState(eState::Paused);
		}
		{
			_Death_Elect2 = new Death_Elect_Second;
			_Death_Elect2->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Death_Elect2);
			_Death_Elect2->SetState(eState::Paused);
		}

		at->PlayAnimation(L"Awaken_PowerIdle", true);
		GameObject::Initialize();
	}
	void Layana_Dark_Awaken::Update()
	{
		_Playerpos = Player::GetPlayer_Pos();
		_velocity = _rigidbody->GetVelocity();
		_pos = tr->GetPosition();

		if (_EnergyChange == true)
		{
			_CurrenHp_Dark_Awaken_scale = 4500;
			Player_Hp->SetState(eState::Active);
			_MaxHp_Dark_Awaken_scale = _Max_Dark_Awaken_Hp / 100;
			_CurrenHp_Dark_Awaken_scale = _Curren_Dark_Awaken_Hp / 100;
			Transform* hp_tr = Player_Hp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(_pos.x - (_MaxHp_Dark_Awaken_scale - _CurrenHp_Dark_Awaken_scale) + 200 / 2, 150, _pos.z - 1));
			hp_tr->SetScale(_CurrenHp_Dark_Awaken_scale, 10, 0);
		}


		if (_Awaken_Switch == true) // 어웨이큰 On 만들어야함.★★★★★★★★★★★★★★★★★★★★
		{
			Awaken_Combo();
			_EnergyChange = true;
			_Awaken_Switch = false;
		}
		else
		{
			_Playerdistance.x = _Playerpos.x - _pos.x;
			_Playerdistance.y = _Playerpos.y - _pos.y;
			if (_Playerdistance.x >= 0)
				_Dir = 1;
			else
				_Dir = -1;		
		}

		switch (_DarkMode_state)
		{
		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Idle:
			Layana_Dark_Awaken::idle();
			break;



		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Awaken_End:
			Layana_Dark_Awaken::Awaken_End();
			break;


		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Telleport_In:
			Layana_Dark_Awaken::Telleport_In();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Telleport_Out:
			Layana_Dark_Awaken::Telleport_Out();
			break;



		//case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Dash:
		//	Layana_Dark_Awaken::Dash();
		//	break;

		//case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::FlyDash:
		//	Layana_Dark_Awaken::FlyDash();
		//	break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::LandingDash:
			Layana_Dark_Awaken::LandingDash();
			break;

		//case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::BackStep:
		//	Layana_Dark_Awaken::BackStep();
		//	break;




		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Rush_Ready:
			Layana_Dark_Awaken::Rushready();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::RushA:
			Layana_Dark_Awaken::Rush_A();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::RushB:
			Layana_Dark_Awaken::Rush_B();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::RushC_1:
			Layana_Dark_Awaken::Rush_C_1();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::RushC_2:
			Layana_Dark_Awaken::Rush_C_2();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::RushC_3:
			Layana_Dark_Awaken::Rush_C_3();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::RushC_4:
			Layana_Dark_Awaken::Rush_C_4();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::RushC_5:
			Layana_Dark_Awaken::Rush_C_5();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::RushC_6:
			Layana_Dark_Awaken::Rush_C_6();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::RushC_7:
			Layana_Dark_Awaken::Rush_C_7();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::RushC_8:
			Layana_Dark_Awaken::Rush_C_8();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Rush_End:
			Layana_Dark_Awaken::Rush_End();
			break;
		

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Meteor_Cross_Ready:
			Layana_Dark_Awaken::CrossReady();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Meteor_Cross_Jump:
			Layana_Dark_Awaken::CrossJump();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Meteor_Cross_Attack:
			Layana_Dark_Awaken::CrossAttack();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Meteor_Cross_Landing:
			Layana_Dark_Awaken::CrossLanding();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Meteor_Cross_End:
			Layana_Dark_Awaken::CrossEnd();
			break;




		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Meteor_Ground_Ready:
			Layana_Dark_Awaken::GroundReady();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Meteor_Ground_Attack:
			Layana_Dark_Awaken::GroundAttack();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Meteor_Ground_Landing:
			Layana_Dark_Awaken::GroundLanding();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Meteor_Ground_End:
			Layana_Dark_Awaken::GroundEnd();
			break;



		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Meteor_Vertical_Jump:
			Layana_Dark_Awaken::Vertical_Jump();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Meteor_Vertical_Ready:
			Layana_Dark_Awaken::Vertical_Ready();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Meteor_Vertical_Attack:
			Layana_Dark_Awaken::Vertical_Attack();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Meteor_Vertical_Landing:
			Layana_Dark_Awaken::Vertical_Landing();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Meteor_Vertical_End:
			Layana_Dark_Awaken::Vertical_End();
			break;


		case Layana_Dark_Awaken::Layana_Dark_Awaken_State::Skill_A_Bullet_Ready:
			Layana_Dark_Awaken::Skill_A_Ready();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Skill_A_Bullet:
			Layana_Dark_Awaken::Skill_A();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Skill_A_Bullet_End:
			Layana_Dark_Awaken::Skill_A_End();
			break;
			


		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Skill_B_RisingPierce_Ready:
			Layana_Dark_Awaken::Skill_B_Ready();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Skill_B_RisingPierce:
			Layana_Dark_Awaken::Skill_B();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Skill_B_RisingPierce_End:
			Layana_Dark_Awaken::Skill_B_End();
			break;



		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Skill_C_DimensionPierce_Ready:
			Layana_Dark_Awaken::Skill_C_Ready();
			break;


		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Skill_C_DimensionPierce:
			Layana_Dark_Awaken::Skill_C();
			break;



		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Look_Before_Dying:
			Layana_Dark_Awaken::look_before_dying();
			break;


		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Death:
			Layana_Dark_Awaken::death();
			break;


		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Good_Bye_Layana:
			Layana_Dark_Awaken::GoodByeLayana();
			break;


		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Layana_End:
			Layana_Dark_Awaken::GoodByeLayana();
			break;
			

		default:
			break;
		}		

		tr->SetPosition(_pos);
		GameObject::Update();
	}
	void Layana_Dark_Awaken::LateUpdate()
	{
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_HitBox_Attack_On == true)
		{
			if (_DarkMode_state == Layana_Dark_Awaken_State::RushA)
			{
				Hit_Box->SetSize(Vector2(55.f, 5.f));
				Hit_Box->SetState(eState::Active);

				if (_HitBox_Dir == 1)	//오른쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x + 90, _pos.y - 25, _pos.z));
				else					//왼쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x - 90, _pos.y - 25, _pos.z));
			}
			else if (_DarkMode_state == Layana_Dark_Awaken_State::RushB)
			{
				Hit_Box->SetSize(Vector2(55.f, 5.f));
				Hit_Box->SetState(eState::Active);

				if (_HitBox_Dir == 1)	//오른쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x + 90, _pos.y - 35, _pos.z));
				else					//왼쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x - 90, _pos.y - 35, _pos.z));
			}
			else if (_DarkMode_state == Layana_Dark_Awaken_State::Meteor_Cross_Landing)
			{
				Hit_Box->SetSize(Vector2(5.f, 55.f));

				Hit_Box->SetState(eState::Active);

				if (_HitBox_Dir == 1)	//오른쪽으로 공격할때의 기준
				{
					HitBox_TR->SetPosition(Vector3(_pos.x + 30, _pos.y - 50, _pos.z));
					HitBox_TR->SetRotationZ(15 / (180.f / XM_PI));
				}
				else					//왼쪽으로 공격할때의 기준
				{
					HitBox_TR->SetPosition(Vector3(_pos.x - 30, _pos.y - 50, _pos.z));
					HitBox_TR->SetRotationZ(-15 / (180.f / XM_PI));
				}
			}
			else if (_DarkMode_state == Layana_Dark_Awaken_State::Meteor_Vertical_Landing)
			{
				Hit_Box->SetSize(Vector2(35.f, 35.f));

				Hit_Box->SetState(eState::Active);

				if (_HitBox_Dir == 1)//오른쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x, _pos.y - 65, _pos.z));			
				else					//왼쪽으로 공격할때의 기준			
					HitBox_TR->SetPosition(Vector3(_pos.x - 30, _pos.y - 50, _pos.z));
			}

		}
		else
		{
			HitBox_TR->SetRotationZ(0);
			Hit_Box->SetState(eState::Paused);
		}

		_collider->SetSize(Vector2(0.1f, 0.55f));
		_collider->SetCenter(Vector2(0.0f, -20.5f));
		GameObject::LateUpdate();
	}
	void Layana_Dark_Awaken::Render()
	{
		GameObject::Render();
	}


	void Layana_Dark_Awaken::OnCollisionEnter(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_DarkMode_state == Layana_Dark_Awaken_State::Meteor_Cross_Landing)
			{
				Transform* boss_effect = _Meteoreffect->GetComponent<Transform>();
				boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
				_Meteoreffect->SetState(eState::Active);
			}


			if (_DarkMode_state == Layana_Dark_Awaken_State::Meteor_Vertical_Landing)
			{
				{
					Transform* boss_effect = _Meteoreffect->GetComponent<Transform>();
					boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 5));
					_Meteoreffect->SetState(eState::Active);
				}
				{
					Transform* boss_effect = _GoldenMeteor_Effect->GetComponent<Transform>();
					boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 6));
					_GoldenMeteor_Effect->SetState(eState::Active);
				}
				{
					Transform* boss_effect = _Meteor_Electric->GetComponent<Transform>();
					boss_effect->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 7));
					_Meteor_Electric->SetState(eState::Active);
				}
				{
					Transform* boss_bullet1 = _Meteor_Projectile[0]->GetComponent<Transform>();
					RigidBody* bullet_RG = _Meteor_Projectile[0]->GetComponent<RigidBody>();
					boss_bullet1->SetPosition(Vector3(_pos.x, _pos.y-25, _pos.z - 1));					
					_Meteor_Projectile[0]-> SetState(eState::Active);
					bullet_RG->SetFriction(true);
					bullet_RG->SetGravity(true);
					bullet_RG->SetVelocity(Vector2(650, 0));
				}				
				{
					Transform* boss_bullet2 = _Meteor_Projectile[1]->GetComponent<Transform>();
					RigidBody* bullet_RG = _Meteor_Projectile[1]->GetComponent<RigidBody>();
					_Meteor_Projectile[1]->_effect_switch = true;
					_Meteor_Projectile[1]->SetDirection(-1);
					boss_bullet2->SetPosition(Vector3(_pos.x, _pos.y-25, _pos.z - 1));
					_Meteor_Projectile[1]->SetState(eState::Active);
					bullet_RG->SetFriction(true);
					bullet_RG->SetGravity(true);
					bullet_RG->SetVelocity(Vector2(-650, 0));
				}
			}



		}


		if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
			{
				bool attack = false;
				bool attack_Cri_Mid = false;
				bool attack_Cri_High = false;

				_HitType = random(1, 6);
				if (_HitType >= 1 && _HitType < 6)
				{
					_Dammege = 3000;
					attack = true;
				}
				//if (_HitType >= 6 && _HitType < 9)
				//{
				//	_Damage = random(15, 25);
				//	attack_Cri_Mid = true;
				//}
				//if (_HitType >= 9 && _HitType <= 10)
				//{
				//	_Damage = random(30, 45);
				//	attack_Cri_High = true;
				//}

				{
					_Hit_Effect->_effect_animation = true;
					_Critical_Middle->_effect_animation = true;
					_Critical_High->_effect_animation = true;
					if (_Dir == 1)
					{
						Player_Hp->_HitOn = true;
						Player_Hp->SetHitDamage(_Dammege);
						_Curren_LongHair_Hp = _Curren_LongHair_Hp - _Dammege;
						_Hit_Effect->SetDirection(-1);
						_Critical_Middle->SetDirection(-1);
						_Critical_High->SetDirection(-1);
					}
					else
					{
						Player_Hp->_HitOn = true;
						Player_Hp->SetHitDamage(_Dammege);
						_Curren_LongHair_Hp = _Curren_LongHair_Hp - _Dammege;
						_Hit_Sword->SetDirection(1);
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
				if (_Curren_LongHair_Hp <= 0)
				{
					if (_EnergyChange == true)
					{
						_DarkMode_state = Layana_Dark_Awaken_State::Look_Before_Dying;
						if (_Dir == 1)
						{
							at->PlayAnimation(L"Awaken_PowerDeath_00", true);
							_DieDir = 1;
						}
						else
						{
							at->PlayAnimation(L"Awaken_PowerDeath_00R", true);
							_DieDir = -1;
						}
					}						
				}
			}

		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
			{
				bool attack = false;
				bool attack_Cri_Mid = false;
				bool attack_Cri_High = false;

				_HitType = random(1, 10);
				if (_HitType >= 1 && _HitType < 6)
				{
					_Dammege = 25;
					attack = true;
				}
				if (_HitType >= 6 && _HitType < 9)
				{
					_Dammege = random(35, 40);
					attack_Cri_Mid = true;
				}
				if (_HitType >= 9 && _HitType <= 10)
				{
					_Dammege = random(50, 70);
					attack_Cri_High = true;
				}

				{
					_Hit_Effect->_effect_animation = true;
					_Critical_Middle->_effect_animation = true;
					_Critical_High->_effect_animation = true;
					if (_Dir == 1)
					{
						Player_Hp->_HitOn = true;
						Player_Hp->SetHitDamage(_Dammege);
						_Curren_LongHair_Hp = _Curren_LongHair_Hp - _Dammege;
						_Hit_Effect->SetDirection(-1);
						_Critical_Middle->SetDirection(-1);
						_Critical_High->SetDirection(-1);
					}
					else
					{
						Player_Hp->_HitOn = true;
						Player_Hp->SetHitDamage(_Dammege);
						_Curren_LongHair_Hp = _Curren_LongHair_Hp - _Dammege;
						_Hit_Sword->SetDirection(1);
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
				if (_Curren_LongHair_Hp <= 0)
				{
					if (_First_Die == false)
					{
						_First_Die = true;
						_LongHair_Die = true;
					}
				}
			
		}
	}
	void Layana_Dark_Awaken::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_rigidbody->ClearVelocity();
			}
			else
			{
				Transform* GRTR = mGround->GetComponent<Transform>();
				Vector3 GRpos = GRTR->GetPosition();
				float CheckPos = fabs(_pos.y - GRpos.y);
				if (95 > CheckPos)
				{
					_pos.y = GRpos.y+ 95;
					tr->SetPosition(_pos);
				}

				if 	(_DarkMode_state == Layana_Dark_Awaken_State::Meteor_Cross_Landing)
				{
					_HitBox_Attack_On = false;
					if (_Dir == 1)
						at->PlayAnimation(L"Awaken_PowerMeteor_Cross02_Landing", true);
					else
						at->PlayAnimation(L"Awaken_PowerMeteor_Cross02_LandingR", true);
					tr->SetRotationZ(0.f);
					_CrossMeteorLanding = true;
				}
				if (_DarkMode_state == Layana_Dark_Awaken_State::LandingDash)
				{
					if (_Dir == 1)
						at->PlayAnimation(L"Awaken_PowerMeteor_Ground01_Ready", true);
					else
						at->PlayAnimation(L"Awaken_PowerMeteor_Ground01_ReadyR", true);
					_GroundMeteorLanding = true;
				}
				if (_DarkMode_state == Layana_Dark_Awaken_State::Meteor_Vertical_Landing)
				{
					_HitBox_Attack_On = false;
					if (_Dir == 1)
						at->PlayAnimation(L"Awaken_PowerMeteor_Vertical03_Landing", true);
					else
						at->PlayAnimation(L"Awaken_PowerMeteor_Vertical03_LandingR", true);
					_VerticalMeteorLanding = true;
				}
			}
		}
	}
	void Layana_Dark_Awaken::OnCollisionExit(Collider2D* other)
	{
	}


	void Layana_Dark_Awaken::idle()
	{
		_time += Time::DeltaTime();
		_SelectAttack = random(0, 5);
		//_SelectAttack = 5;


		if (_Awaken_Switch == true) // 어웨이큰 On 만들어야함.★★★★★★★★★★★★★★★★★★★★
		{
			//Awaken_Combo();
		}
		else
		{
			if (_time >= 3.0)
			{
				if (_SelectAttack == 0)
					Rush_Combo();
				if (_SelectAttack == 1)
					Meteor_Cross_Combo();
				if (_SelectAttack == 2)
					Meteor_Ground_Combo();
				if (_SelectAttack == 3)
					Meteor_Vertical_Combo();
				if (_SelectAttack == 4)
					Skill_B_Combo();
				if (_SelectAttack == 5)
					Skill_C_Combo();
			/*	if (_SelectAttack == 6)
					Skill_C_Combo();*/

				_SistersAttack_Number++;
			}
		}
	
	}

	void Layana_Dark_Awaken::Awaken_End()
	{
	}


	void Layana_Dark_Awaken::Telleport_In()
	{
		if (_teleport_Rush == true)
		{
			_Attacktime += Time::DeltaTime();
			if (_Attacktime > 0.35f)
			{
				if (_Dir == 1)
				{
					_pos.x = _Playerpos.x - 65;
					_teleport_Rush = false;
				}
				else
				{
					_pos.x = _Playerpos.x + 65;					
					_teleport_Rush = false;
				}
				_DarkMode_state = Layana_Dark_Awaken_State::Telleport_Out;
				_Attacktime = 0;
			}
		}
		if (_teleport_Cross == true)
		{
			_Attacktime += Time::DeltaTime();
			if (_Attacktime > 0.35f)
			{
				if (_Dir == 1)
				{
					_pos.x = _Playerpos.x - 15;
					_pos.y = _Createpos.y + 150;
					_teleport_Cross = false;
				}
				else
				{
					_pos.x = _Playerpos.x + 15;
					_pos.y = _Createpos.y + 150;
					_teleport_Cross = false;
				}
				_DarkMode_state = Layana_Dark_Awaken_State::Telleport_Out;
				_Attacktime = 0;
			}
		}
		if (_teleport_Ground == true)
		{
			_Attacktime += Time::DeltaTime();
			if (_Attacktime > 0.35f)
			{
				if (_pos.x >= _Createpos.x)
				{
					_pos.x = _Createpos.x + 325;					
					_teleport_Ground = false;
				}
				else
				{
					_pos.x = _Createpos.x - 325;
					_teleport_Ground = false;
				}
				_DarkMode_state = Layana_Dark_Awaken_State::Telleport_Out;
				_Attacktime = 0;
			}
		}
		if (_teleport_Vertical == true)
		{
			_Attacktime += Time::DeltaTime();
			if (_Attacktime > 0.35f)
			{				
				_pos.x = _Playerpos.x;
				_pos.y = _Createpos.y + 150;
				_teleport_Vertical = false;
				_DarkMode_state = Layana_Dark_Awaken_State::Telleport_Out;
				_Attacktime = 0;
			}
		}	
	}
	void Layana_Dark_Awaken::Telleport_Out()
	{
		if (_RushSwitch == true)
		{			
			_DarkMode_state = Layana_Dark_Awaken_State::Rush_Ready;
				if (_Dir == 1)
					at->PlayAnimation(L"Awaken_PowerRush_Ready", true);
				else
					at->PlayAnimation(L"Awaken_PowerRush_ReadyR", true);			
		}
		if (_CrossMeteorSwitch == true)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Cross_Jump;
			if (_Dir == 1)			
				at->PlayAnimation(L"Awaken_PowerMeteor_Cross00_JumpR", false);			
			else			
				at->PlayAnimation(L"Awaken_PowerMeteor_Cross00_Jump", false);			
		}
		if(_GroundMeteorSwitch == true)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Ground_Ready;
			if (_pos.x < _Createpos.x)
				at->PlayAnimation(L"Awaken_PowerMeteor_Ground01_Ready", false);
			else
				at->PlayAnimation(L"Awaken_PowerMeteor_Ground01_ReadyR", false);
			_GroundMeteorLanding = true;
		}
		if (_VerticalMeteorSwitch == true)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Vertical_Jump;
			_Ground_check = false;
			at->PlayAnimation(L"Awaken_PowerMeteor_Vertical00_Jump", true);		
		}
	}


	void Layana_Dark_Awaken::Dash()
	{
		if (!(_Playerdistance.x <= 80 && _Playerdistance.x >= -80))
		{
			if (_Dir == 1)
				_pos.x += 450.f * Time::DeltaTime();
			else
				_pos.x -= 450.f * Time::DeltaTime();
		}
		else
		{
			if (_RushSwitch == true)
			{
				_DarkMode_state = Layana_Dark_Awaken_State::Rush_Ready;
				if (_Dir == 1)
					at->PlayAnimation(L"Awaken_PowerRush_Ready", true);
				else
					at->PlayAnimation(L"Awaken_PowerRush_ReadyR", true);
			}
			if (_CrossMeteorSwitch == true)
			{
				_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Cross_Jump;
				if (_Dir == 1)
				{
					at->PlayAnimation(L"Awaken_PowerMeteor_Cross00_JumpR", false);
					_rigidbody->SetVelocity(Vector2(250.f, 450.f));
					_rigidbody->SetGround(false);
				}
				else
				{
					at->PlayAnimation(L"Awaken_PowerMeteor_Cross00_Jump", false);
					_rigidbody->SetVelocity(Vector2(-250.f, 450.f));
					_rigidbody->SetGround(false);
				}
			}
		}
	}
	void Layana_Dark_Awaken::FlyDash()
	{
		if (_pos.x < _Createpos.x)
		{
			if (_pos.x > _Createpos.x - 700)
				_pos.x -= 750.f * Time::DeltaTime();
			if (_pos.y < _Createpos.y + 150)
				_pos.y += 150.f * Time::DeltaTime();
		}
		else
		{
			if (_pos.x < _Createpos.x + 700)
				_pos.x += 750.f * Time::DeltaTime();
			if (_pos.y < _Createpos.y + 155)
				_pos.y += 150.f * Time::DeltaTime();
		}
		if (_pos.y >= _Createpos.y + 150.f)
		{
			//if (_GroundMeteorSwitch == true)
			//{
			//	_DarkMode_state = Layana_Dark_Awaken_State::LandingDash;
			//	_Ground_check = false;
			//	_rigidbody->SetGround(false);
			//	if (_pos.x < _Createpos.x)
			//	{
			//		_rigidbody->SetVelocity(Vector2(650.f, -150.f));
			//		at->PlayAnimation(L"Awaken_PowerDash", true);
			//	}
			//	else
			//	{
			//		_rigidbody->SetVelocity(Vector2(-650.f, -150.f));
			//		at->PlayAnimation(L"Awaken_PowerDashR", true);
			//	}
			//}
			if (_VerticalMeteorSwitch == true)
			{
				_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Vertical_Jump;
				_Ground_check = false;
				
				at->PlayAnimation(L"Awaken_PowerMeteor_Vertical00_Jump", true);
				//if (_Dir == 1)
				//	at->PlayAnimation(L"Long_hairMeteor_Vertical00_Jump", true);	
				//else
				//	at->PlayAnimation(L"Long_hairMeteor_Vertical00_JumpR", true);
			}
		}
	}
	void Layana_Dark_Awaken::LandingDash()
	{
	}
	void Layana_Dark_Awaken::BackStep()
	{
	}


	void Layana_Dark_Awaken::Rushready()
	{
	}
	void Layana_Dark_Awaken::Rush_A()
	{
	
	}
	void Layana_Dark_Awaken::Rush_B()
	{
		_Attacktime += Time::DeltaTime();
		if (_Attacktime > 0.5)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::Rush_End;
			if (_Dir == 1)
				at->PlayAnimation(L"Awaken_PowerRush_End", true);
			else
				at->PlayAnimation(L"Awaken_PowerRush_EndR", true);
			_Rushnumber = 2;
			_Attacktime = 0;
		}		
	}
	void Layana_Dark_Awaken::Rush_C_1()
	{
	}
	void Layana_Dark_Awaken::Rush_C_2()
	{
		if (_Rush_C_Number == 2)
		{
			if (_BulletDir == 1)
				at->PlayAnimation(L"Awaken_PowerRushC_3", true);
			else
				at->PlayAnimation(L"Awaken_PowerRushC_3R", true);
			_DarkMode_state = Layana_Dark_Awaken_State::RushC_3;
			{
				Transform* boss_bullet = Rush_Sign[1]->GetComponent<Transform>();
				Rush_Sign[1]->_SwitchOn = true;
				Rush_Sign[1]->SetDirection(1);
				float anglew = 45 / (180.0f / XM_PI);
				boss_bullet->SetRotationZ(anglew);
				boss_bullet->SetPosition(Vector3(_Createpos.x, _Createpos.y + 150, -250));
				Rush_Sign[1]->SetState(eState::Active);

				Rush_Bullet[1]->_bulletoff = false;
				Transform* bullet_tr = Rush_Bullet[1]->GetComponent<Transform>();
				bullet_tr->SetRotationZ(anglew);
				bullet_tr->SetPosition(Vector3(_Createpos.x, _Createpos.y + 150, -251));;
			}
		}
	}
	void Layana_Dark_Awaken::Rush_C_3()
	{
		if (_Rush_C_Number == 3)
		{
			if (_BulletDir == 1)
				at->PlayAnimation(L"Awaken_PowerRushC_4", true);
			else
				at->PlayAnimation(L"Awaken_PowerRushC_4R", true);
			_DarkMode_state = Layana_Dark_Awaken_State::RushC_4;
			{
				Transform* boss_bullet = Rush_Sign[2]->GetComponent<Transform>();
				Rush_Sign[2]->_SwitchOn = true;
				Rush_Sign[2]->SetDirection(1);
				float anglew = -45 / (180.0f / XM_PI);
				boss_bullet->SetRotationZ(anglew);
				boss_bullet->SetPosition(Vector3(_Createpos.x, _Createpos.y + 150, -250));
				Rush_Sign[2]->SetState(eState::Active);

				Rush_Bullet[2]->_bulletoff = false;
				Transform* bullet_tr = Rush_Bullet[2]->GetComponent<Transform>();
				bullet_tr->SetRotationZ(anglew);
				bullet_tr->SetPosition(Vector3(_Createpos.x, _Createpos.y + 150, -251));;
			}
		}
	}
	void Layana_Dark_Awaken::Rush_C_4()
	{
		if (_Rush_C_Number == 4)
		{
			if (_BulletDir == 1)
				at->PlayAnimation(L"Awaken_PowerRushC_5", true);
			else
				at->PlayAnimation(L"Awaken_PowerRushC_5R", true);
			_DarkMode_state = Layana_Dark_Awaken_State::RushC_5;
			{
				Transform* boss_bullet = Rush_Sign[3]->GetComponent<Transform>();
				Rush_Sign[3]->_SwitchOn = true;
				Rush_Sign[3]->SetDirection(1);
				float anglew = 45 / (180.0f / XM_PI);
				boss_bullet->SetRotationZ(anglew);
				boss_bullet->SetPosition(Vector3(_Createpos.x, _Createpos.y - 150, -250));
				Rush_Sign[3]->SetState(eState::Active);

				Rush_Bullet[3]->_bulletoff = false;
				Transform* bullet_tr = Rush_Bullet[3]->GetComponent<Transform>();
				bullet_tr->SetRotationZ(anglew);
				bullet_tr->SetPosition(Vector3(_Createpos.x, _Createpos.y - 150, -251));;
			}
		}
	}
	void Layana_Dark_Awaken::Rush_C_5()
	{
		if (_Rush_C_Number == 5)
		{
			if (_BulletDir == 1)
				at->PlayAnimation(L"Awaken_PowerRushC_6", true);
			else
				at->PlayAnimation(L"Awaken_PowerRushC_6R", true);
			_DarkMode_state = Layana_Dark_Awaken_State::RushC_6;
			{
				Transform* boss_bullet = Rush_Sign[4]->GetComponent<Transform>();
				Rush_Sign[4]->_SwitchOn = true;
				Rush_Sign[4]->SetDirection(1);
				float anglew = -45 / (180.0f / XM_PI);
				boss_bullet->SetRotationZ(anglew);
				boss_bullet->SetPosition(Vector3(_Createpos.x, _Createpos.y - 150, -250));
				Rush_Sign[4]->SetState(eState::Active);

				Rush_Bullet[4]->_bulletoff = false;
				Transform* bullet_tr = Rush_Bullet[4]->GetComponent<Transform>();
				bullet_tr->SetRotationZ(anglew);
				bullet_tr->SetPosition(Vector3(_Createpos.x, _Createpos.y - 150, -251));;
			}
		}
	}
	void Layana_Dark_Awaken::Rush_C_6()
	{
		if (_Rush_C_Number == 6)
		{
			if (_BulletDir == 1)
				at->PlayAnimation(L"Awaken_PowerRushC_7", false);
			else
				at->PlayAnimation(L"Awaken_PowerRushC_7R", false);
			_DarkMode_state = Layana_Dark_Awaken_State::RushC_7;
			{
				Transform* boss_bullet = Rush_Sign[5]->GetComponent<Transform>();
				Rush_Sign[5]->_SwitchOn = true;
				Rush_Sign[5]->SetDirection(1);
				boss_bullet->SetPosition(Vector3(_Createpos.x, _Createpos.y - 100, -250));
				Rush_Sign[5]->SetState(eState::Active);

				Rush_Bullet[5]->_bulletoff = false;
				Transform* bullet_tr = Rush_Bullet[5]->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(_Createpos.x, _Createpos.y - 100, -251));;
			}
		}
	}
	void Layana_Dark_Awaken::Rush_C_7()
	{
		if (_Rush_C_Number == 6)
		{
			_Attacktime += Time::DeltaTime();
			if (_Attacktime > 0.5)
			{
				//임펙트 터트리기 작업 실시			
				Transform* boss_bullet = Rush_Sign[6]->GetComponent<Transform>();
				Rush_Sign[6]->_SwitchOn = true;
				Rush_Sign[6]->SetDirection(1);
				float anglew = 45 / (180.0f / XM_PI);
				boss_bullet->SetRotationZ(anglew);
				boss_bullet->SetPosition(Vector3(_Playerpos.x, _Playerpos.y, -250));
				Rush_Sign[6]->SetState(eState::Active);
				_Rush_C_Number = 7;

				Rush_Bullet[6]->_bulletoff = false;
				Transform* bullet_tr = Rush_Bullet[6]->GetComponent<Transform>();
				bullet_tr->SetRotationZ(anglew);
				bullet_tr->SetPosition(Vector3(boss_bullet->GetPosition().x, boss_bullet->GetPosition().y, -251));;
				_Attacktime = 0;
			}
		}
		else
		{
			_Attacktime += Time::DeltaTime();
			if (_Attacktime > 2)
			{
				for (int i = 0; i < 7; i++)
				{
					Rush_Bullet[i]->SetState(eState::Active);
				}
				_DarkMode_state = Layana_Dark_Awaken_State::RushC_8;
				_Attacktime = 0;
			}
		}
	}
	void Layana_Dark_Awaken::Rush_C_8()
	{
		for (int i = 0; i < 7; i++)
		{
			Rush_Sign[i]->SetState(eState::Paused);
		}
		_Rushnumber = 3;
		_DarkMode_state = Layana_Dark_Awaken_State::Rush_End;
		if (_Dir == 1)
			at->PlayAnimation(L"Awaken_PowerRush_End", true);
		else
			at->PlayAnimation(L"Awaken_PowerRush_EndR", true);
		
	}
	void Layana_Dark_Awaken::Rush_End()
	{
	}


	void Layana_Dark_Awaken::CrossJump()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Awaken_PowerMeteor_Cross01_Ready", true);
		else
			at->PlayAnimation(L"Awaken_PowerMeteor_Cross01_ReadyR", true);
		_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Cross_Ready;		
	}
	void Layana_Dark_Awaken::CrossReady()
	{		
	}
	void Layana_Dark_Awaken::CrossAttack()
	{
		//몸뚱이 회전
		{
			if (_Playerpos.x >= _pos.x)
			{
				at->PlayAnimation(L"Awaken_PowerMeteor_Cross04_AttackR", false);
				float angle = 15 / (180.0f / XM_PI);
				tr->SetRotationZ(angle);
				afterimageangle = angle;
				_HitBox_Dir = 1;
			}
			else
			{
				at->PlayAnimation(L"Awaken_PowerMeteor_Cross04_AttackR", false);
				float angle = -15 / (180.0f / XM_PI);
				tr->SetRotationZ(angle);
				afterimageangle = angle;
				_HitBox_Dir = -1;
			}
		}
		//몸땡이 발사
		{
			Vector2 attack_pos = Vector2(_Playerpos.x - _pos.x, _Playerpos.y - _pos.y);
			attack_pos.Normalize();
			_rigidbody->SetGround(false);
			_Ground_check = false;
			_rigidbody->SetVelocity(Vector2(attack_pos.x * 650.f, attack_pos.y * 750));
			_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Cross_Landing;
			_HitBox_Attack_On = true;
		}
	}
	void Layana_Dark_Awaken::CrossLanding()
	{
		{
			timeSinceLastImage += Time::DeltaTime();
			if (timeSinceLastImage >= delayBetweenImages)
			{
				for (int i = 0; i < 10; i++)
				{
					if (AfterImage[i]->_AfterImage == false)
					{
						int direction = (_Dir == 1) ? 1 : -1;
						Transform* AfterimageTR = AfterImage[i]->GetComponent<Transform>();
						AfterimageTR->SetRotationZ(afterimageangle);
						AfterImage[i]->Set_Basic_Dash(direction, Vector3(_pos.x, _pos.y, _pos.z + 1));
						AfterImage[i]->SetState(eState::Active);
						AfterImage[i]->_AfterImage = true;
						timeSinceLastImage = 0.0f;  // 시간 초기화
						break;  // 하나의 잔상만 생성한 후 for문 종료					
					}
				}
			}
		}

		if (_CrossMeteorLanding == true)
			Complete_CrossLanding();
	}
	void Layana_Dark_Awaken::CrossEnd()
	{
	}


	void Layana_Dark_Awaken::GroundReady()
	{
		if (_GroundMeteorLanding == true)
		{
			Transform* boss_effect = _Ground_Sign->GetComponent<Transform>();			
			_Ground_Sign->_SwitchOn = true;
			if (_Dir == 1)
			{
				_Ground_Sign->SetDirection(1);
				boss_effect->SetPosition(Vector3(_Createpos.x, _pos.y-35, _pos.z - 1));
			}
			else
			{
				_Ground_Sign->SetDirection(-1);
				boss_effect->SetPosition(Vector3(_Createpos.x, _pos.y - 35, _pos.z - 1));
			}
			_Ground_Sign->SetState(eState::Active);
			_GroundMeteorLanding = false;

		}
		else
		{
			_Attacktime += Time::DeltaTime();		
			if (_Attacktime >= 0.5f)
			{
			 if(_Ground_Sign->_SwitchOff ==true)
				{
					_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Ground_Attack;
					if (_Dir == 1)
					{
						at->PlayAnimation(L"Awaken_PowerMeteor_Ground02_Attack", true);
						_rigidbody->SetVelocity(Vector2(1150.f, 0.f));
						_GroundMeteorAttack_Right = true;
					}
					else
					{
						at->PlayAnimation(L"Awaken_PowerMeteor_Ground02_AttackR", true);
						_rigidbody->SetVelocity(Vector2(-1150.f, 0.f));
						_GroundMeteorAttack_Left = true;
					}

					Transform* boss_effect = _Ground_Attack->GetComponent<Transform>();
					boss_effect->SetPosition(Vector3(_Createpos.x, _pos.y - 35, _pos.z - 1));
					_Ground_Attack->SetState(eState::Active);

					for (int i = 0; i < 7; i++)
						_Ground_Thunder_Sign[i]->SetState(eState::Active);			

					_Attacktime = 0;
					_Ground_Sign->_SwitchOff = false;
				}
			}
		}
	}
	void Layana_Dark_Awaken::GroundAttack()
	{
		if (_GroundMeteorAttack_Right == true)
		{
			if (_pos.x >= _Createpos.x + 312)
			{
				_rigidbody->ClearVelocity();
				_GroundMeteorAttack_Right = false;
				_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Ground_Landing;
				at->PlayAnimation(L"Awaken_PowerMeteor_Ground03_Landing", false);	

				Transform* boss_effect = _Ground_DashSmoke->GetComponent<Transform>();
				_Ground_DashSmoke->_SwitchOn = true;
				_Ground_DashSmoke->SetDirection(-1);
				boss_effect->SetPosition(Vector3(_pos.x-65, _pos.y-15, _pos.z - 1));
				_Ground_DashSmoke->SetState(eState::Active);
			}
		}
		if (_GroundMeteorAttack_Left == true)
		{
			if (_pos.x <= _Createpos.x - 312)
			{
				_rigidbody->ClearVelocity();
				_GroundMeteorAttack_Left = false;
				_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Ground_Landing;
				at->PlayAnimation(L"Awaken_PowerMeteor_Ground03_LandingR", false);

				Transform* boss_effect = _Ground_DashSmoke->GetComponent<Transform>();
				_Ground_DashSmoke->_SwitchOn = true;
				_Ground_DashSmoke->SetDirection(1);
				boss_effect->SetPosition(Vector3(_pos.x+65, _pos.y-15, _pos.z - 1));
				_Ground_DashSmoke->SetState(eState::Active);
			}
		}
	}
	void Layana_Dark_Awaken::GroundLanding()
	{
		if (_pos.x >= _Createpos.x)
		{
			_Attacktime += Time::DeltaTime();
			int index = 6 - (_Attacktime / 0.5f);

			if (index >= 0)
			{
				_Ground_Thunder[index]->SetState(eState::Active);
			
				if (index == 0)
				{
					at->PlayAnimation(L"Awaken_PowerMeteor_Ground04_End", true);
					_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Ground_End;
					_Attacktime = 0;
				}
			}	
		}
		if (_pos.x < _Createpos.x)
		{
			_Attacktime += Time::DeltaTime();		
			int index = _Attacktime / 0.5f;

			if (index < 7)
			{
				_Ground_Thunder[index]->SetState(eState::Active);
			
				if (index == 6)
				{
					at->PlayAnimation(L"Awaken_PowerMeteor_Ground04_EndR", true);
					_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Ground_End;
					_Attacktime = 0;
				}			
			}
		}	
	}
	void Layana_Dark_Awaken::GroundEnd()
	{
	}


	void Layana_Dark_Awaken::Vertical_Jump()
	{
	}
	void Layana_Dark_Awaken::Vertical_Ready()
	{
	}
	void Layana_Dark_Awaken::Vertical_Attack()
	{
	}
	void Layana_Dark_Awaken::Vertical_Landing()
	{
		_Attacktime += Time::DeltaTime();
		if (_VerticalMeteorLanding == true)
		{
			if (_Attacktime >= 1.f)
			{
				_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Vertical_End;

				if (_Dir == 1)
					at->PlayAnimation(L"Awaken_PowerMeteor_Vertical04_End", true);
				else
					at->PlayAnimation(L"Awaken_PowerMeteor_Vertical04_EndR", true);
				_Attacktime = 0;
			}
		}
	}
	void Layana_Dark_Awaken::Vertical_End()
	{
	}


	void Layana_Dark_Awaken::Skill_A_Ready()
	{
	}
	void Layana_Dark_Awaken::Skill_A()
	{
	}
	void Layana_Dark_Awaken::Skill_A_End()
	{
	}


	void Layana_Dark_Awaken::Skill_B_Ready()
	{
		_Attacktime += Time::DeltaTime();
		if (_Attacktime <= 3.5f)
		{
			for (int i = 0; i < 5; i++)
			{
				if (_Attacktime >= (1.0f + 0.5f * i))
				{
					if (_Dark_HomingPierce[i]->_Create_ball == false)
					{
						int randomposX = random(_Createpos.x - 150, _Createpos.x + 150);
						int randomposY = random(_Createpos.y - 25, _Createpos.y + 70);
						Transform* boss_effect = _Dark_HomingPierce[i]->GetComponent<Transform>();
						//boss_effect->SetPosition(Vector3(randomposX, randomposY, _pos.z - 1));
						_Dark_HomingPierce[i]->_effect_switch = true;
						_Dark_HomingPierce[i]->SetState(eState::Active);
						_Dark_HomingPierce[i]->_Create_ball = true;


						Transform* _effect_Line = _HomingPierce_Effect[i]->GetComponent<Transform>();
						_effect_Line->SetPosition(Vector3(boss_effect->GetPosition().x, boss_effect->GetPosition().y, _pos.z - 2));

						Transform* bullet = _HomingPierce_Attack[i]->GetComponent<Transform>();
						bullet->SetPosition(Vector3(boss_effect->GetPosition().x, boss_effect->GetPosition().y, _pos.z - 3));
					}
				}
			}
		}
		else
		{
			if (_SkillBWait == false)
			{
				for (int i = 0; i < 5; i++)
				{
					_HomingPierce_Effect[i]->SetState(eState::Active);
					Transform* _effect_Line = _HomingPierce_Effect[i]->GetComponent<Transform>();
					Transform* bullet = _HomingPierce_Attack[i]->GetComponent<Transform>();
					Vector3 bulletpos = _effect_Line->GetPosition();

					{
						Vector2 attackpoint = Vector2(_Playerpos.x - _effect_Line->GetPositionX(), _Playerpos.y - _effect_Line->GetPositionY());
						attackpoint.Normalize();

						float angle = std::atan2(attackpoint.y, attackpoint.x);
						_effect_Line->SetRotationZ(angle);
						bullet->SetRotationZ(angle);
					}
				}
				_SkillBWait = true;
			}
			_Picerwaitintime += Time::DeltaTime();
			if (_Picerwaitintime >= 1.f)
			{
				_HomingPierce_Attack[0]->SetState(eState::Active);
				_HomingPierce_Attack[1]->SetState(eState::Active);
				_HomingPierce_Attack[2]->SetState(eState::Active);
				_HomingPierce_Attack[3]->SetState(eState::Active);
				_HomingPierce_Attack[4]->SetState(eState::Active);
				_DarkMode_state = Layana_Dark_Awaken_State::Skill_B_RisingPierce;
				_Attacktime = 0;
				_Picerwaitintime = 0;
				_SkillBWait = false;
			}
		}
	}
	void Layana_Dark_Awaken::Skill_B()
	{
		if (_HomingPierce_Attack[4]->_bulletoff == true)
		{
			if (_Dir == 1)
				at->PlayAnimation(L"Awaken_PowerSkill_B_RisingPierce_End", true);
			else
				at->PlayAnimation(L"Awaken_PowerSkill_B_RisingPierce_EndR", true);
			_DarkMode_state = Layana_Dark_Awaken_State::Skill_B_RisingPierce_End;
		}		
	}
	void Layana_Dark_Awaken::Skill_B_End()
	{
	}



	void Layana_Dark_Awaken::Skill_C_Ready()
	{
		if (_SkillC_Switch == false)
		{
			{
				Transform* boss_effect = _DimensionPierce_Bosseffect->GetComponent<Transform>();
				boss_effect->SetPosition(Vector3(_pos.x, _pos.y - 10, -250));
				_DimensionPierce_Bosseffect->SetState(eState::Active);
				_DimensionPierce_Bosseffect->_SwitchOn = true;
				if (_Dir == 1)
					_DimensionPierce_Bosseffect->SetDirection(1);
				else
					_DimensionPierce_Bosseffect->SetDirection(-1);
			}
			{
				Transform* boss_bullet = _DimensionPierce_Sign->GetComponent<Transform>();
				_DimensionPierce_Sign->_SwitchOn = true;
				int Setrotation = random(1, 2);
				if (_Dir == 1)
				{
					_DimensionPierce_Sign->SetDirection(1);
					float anglew = 0.f;
					if (Setrotation == 1)
					{
						int setangle = random(295, 335);
						float anglew = setangle / (180.0f / XM_PI);
						boss_bullet->AddRotationZ(anglew);
						boss_bullet->SetPosition(Vector3(_Playerpos.x, _Playerpos.y + 25, -250));
					}
					else
					{
						int setangle = random(25, 65);
						float anglew = setangle / (180.0f / XM_PI);
						boss_bullet->AddRotationZ(anglew);
						boss_bullet->SetPosition(Vector3(_Playerpos.x, _Playerpos.y - 25, -250));
					}
					_DimensionPierce_Sign->SetState(eState::Active);
				}
				else
				{
					_DimensionPierce_Sign->SetDirection(-1);
					if (Setrotation == 1)
					{
						int setangle = random(-335, -295);
						float anglew = setangle / (180.0f / XM_PI);
						boss_bullet->AddRotationZ(anglew);
						boss_bullet->SetPosition(Vector3(_Playerpos.x, _Playerpos.y + 25, -250));
					}
					else
					{
						int setangle = random(-65, -25);
						float anglew = setangle / (180.0f / XM_PI);
						boss_bullet->AddRotationZ(anglew);
						boss_bullet->SetPosition(Vector3(_Playerpos.x, _Playerpos.y - 25, -250));
					}
					_DimensionPierce_Sign->SetState(eState::Active);
				}
			}
			_SkillC_Switch = true;
			_DarkMode_state = Layana_Dark_Awaken_State::Skill_C_DimensionPierce;
		}
	}
	void Layana_Dark_Awaken::Skill_C()
	{
		
		if (_SkillC_Switch == true)
		{
			_Attacktime += Time::DeltaTime();

			if (_Attacktime >= 1.0 && _Attacktime < 1.5)
			{
				Transform* boss_bullet = _DimensionPierce_Sign->GetComponent<Transform>();
				Transform* boss_effect = _DimensionPierce_BulletEffect->GetComponent<Transform>();
				boss_effect->SetPosition(Vector3(boss_bullet->GetPositionX(), boss_bullet->GetPositionY(), -250));
				boss_effect->SetRotationZ(boss_bullet->GetRotationZ());
				_DimensionPierce_BulletEffect->_effect_switch = true;
				_DimensionPierce_BulletEffect->_bulletoff = true;
				_DimensionPierce_BulletEffect->SetState(eState::Active);		
				if (_Dir == 1)
					_DimensionPierce_BulletEffect->SetDirection(1);
				else
					_DimensionPierce_BulletEffect->SetDirection(-1);
			}

			if (_DimensionPierce_BulletEffect->_bulletoff == true)
			{
				_DimensionPierce_Sign->SetState(eState::Paused);
				_DimensionPierce_BulletEffect->_bulletoff = false;

				if (_Dir == 1)
					at->PlayAnimation(L"Awaken_PowerIdle", true);
				else
					at->PlayAnimation(L"Awaken_PowerIdleR", true);
				_DarkMode_state = Layana_Dark_Awaken_State::Idle;
				_Attacktime = 0;
				_time = 0;
			}
		}
	}



	void Layana_Dark_Awaken::look_before_dying()
	{
	}
	void Layana_Dark_Awaken::death()
	{
		if (Death_effect_connection == false)
		{
			if (_Death_Intro->GetFinish() == true)
			{				
				if (_DieDir == 1)
				{
					_Death_EF_First->SetState(eState::Active);
					_Death_EF_First->SetSwitch(true);
					_Death_EF_First->SetDirection(1);
					Transform* Eftr = _Death_EF_First->GetComponent<Transform>();
					Eftr->SetPosition(Vector3(_pos.x, _pos.y + 115, _pos.z + 1));
				}
				else
				{
					_Death_EF_First->SetState(eState::Active);
					_Death_EF_First->SetSwitch(true);
					_Death_EF_First->SetDirection(-1);
					Transform* Eftr = _Death_EF_First->GetComponent<Transform>();
					Eftr->SetPosition(Vector3(_pos.x, _pos.y + 115, _pos.z + 1));
				}
				Death_effect_connection = true;
			}
		}
	}
	void Layana_Dark_Awaken::GoodByeLayana()
	{
	}


	void Layana_Dark_Awaken::Complete_Telleport_In()
	{
	}
	void Layana_Dark_Awaken::Complete_Telleport_Out()
	{
	}



	void Layana_Dark_Awaken::Rush_Combo()
	{
		_RushSwitch = true;
		_Rushnumber = 0;//Awaken_PowerDash
		if (_Playerdistance.x <= 65 && _Playerdistance.x >= -65)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::Rush_Ready;
			if (_Dir == 1)
				at->PlayAnimation(L"Awaken_PowerRush_Ready", true);
			else
				at->PlayAnimation(L"Awaken_PowerRush_ReadyR", true);
		}
		else
		{
			_teleport_Rush = true;
			_DarkMode_state = Layana_Dark_Awaken_State::Telleport_In;
		}	
	}
	void Layana_Dark_Awaken::Complete_RushReady()
	{
		if (_Rushnumber == 0)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::RushA;
			if (_Dir == 1)
			{
				_HitBox_Attack_On = true;
				_HitBox_Dir = 1;
				_BulletDir = 1;
				at->PlayAnimation(L"Awaken_PowerRushA", true);
			}
			else
			{
				_HitBox_Attack_On = true;
				_HitBox_Dir = -1;
				_BulletDir = -1;
				at->PlayAnimation(L"Awaken_PowerRushAR", true);
			}
		}
		if (_Rushnumber == 1)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::RushB;
			if (_Dir == 1)
			{
				_HitBox_Attack_On = true;
				_HitBox_Dir = 1;
				_BulletDir = 1;
				at->PlayAnimation(L"Awaken_PowerRushB", true);
			}
			else
			{
				_HitBox_Attack_On = true;
				_HitBox_Dir = -1;
				_BulletDir = -1;
				at->PlayAnimation(L"Awaken_PowerRushBR", true);
			}
		}
		if (_Rushnumber == 2)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::RushC_1;			
			if (_BulletDir == 1)
				at->PlayAnimation(L"Awaken_PowerRushC_1", true);
			else
				at->PlayAnimation(L"Awaken_PowerRushC_1R", true);
		}
	}
	void Layana_Dark_Awaken::Complete_RushA()
	{
		_HitBox_Attack_On = false;
		{
			_DarkMode_state = Layana_Dark_Awaken_State::Rush_End;
			if (_BulletDir == 1)
				at->PlayAnimation(L"Awaken_PowerRush_End", true);
			else
				at->PlayAnimation(L"Awaken_PowerRush_EndR", true);
			_Rushnumber = 1;			
		}
	}
	void Layana_Dark_Awaken::Complete_RushB()
	{
		_HitBox_Attack_On = false;
		{
			_DarkMode_state = Layana_Dark_Awaken_State::Rush_End;
			if (_BulletDir == 1)
				at->PlayAnimation(L"Awaken_PowerRush_End", true);
			else
				at->PlayAnimation(L"Awaken_PowerRush_EndR", true);
			_Rushnumber = 2;
		}
	}
	void Layana_Dark_Awaken::Complete_RushEnd()
	{
		if (_Rushnumber == 1)
		{
			if (_Playerdistance.x <= 65 && _Playerdistance.x >= -65)
			{
				_DarkMode_state = Layana_Dark_Awaken_State::Rush_Ready;
				if (_Dir == 1)
					at->PlayAnimation(L"Awaken_PowerRush_Ready", true);
				else
					at->PlayAnimation(L"Awaken_PowerRush_ReadyR", true);
			}
			else
			{
				_teleport_Rush = true;
				_DarkMode_state = Layana_Dark_Awaken_State::Telleport_In;
				if (_Dir == 1)
					at->PlayAnimation(L"Awaken_PowerIdle", true);
				else
					at->PlayAnimation(L"Awaken_PowerIdleR", true);
			}
		}
		if (_Rushnumber == 2)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::Rush_Ready;
			if (_BulletDir == 1)
				at->PlayAnimation(L"Awaken_PowerRush_Ready", true);
			else
				at->PlayAnimation(L"Awaken_PowerRush_ReadyR", true);
		}
		if (_Rushnumber >= 3)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::Idle;
			if (_Dir == 1)
				at->PlayAnimation(L"Awaken_PowerIdle", true);
			else
				at->PlayAnimation(L"Awaken_PowerIdleR", true);
			_time = 0;
			_Rushnumber = 0;
		}
	}

	void Layana_Dark_Awaken::Complete_Rush_C1()
	{
		if (_BulletDir == 1)
			at->PlayAnimation(L"Awaken_PowerRushC_2", true);
		else
			at->PlayAnimation(L"Awaken_PowerRushC_2R", true);
		_DarkMode_state = Layana_Dark_Awaken_State::RushC_2;
		Transform* boss_Effect = Rush_Sign[0]->GetComponent<Transform>();

		boss_Effect->SetPosition(Vector3(_Createpos.x, _Createpos.y + 50, -250));
		Rush_Sign[0]->SetState(eState::Active);

		Rush_Bullet[0]->_bulletoff = false;
		Transform* bullet_tr = Rush_Bullet[0]->GetComponent<Transform>();
		bullet_tr->SetPosition(Vector3(_Createpos.x, _Createpos.y + 50, -251));;
	}
	void Layana_Dark_Awaken::Complete_Rush_C2()
	{
		_Rush_C_Number = 2;
	}
	void Layana_Dark_Awaken::Complete_Rush_C3()
	{
		_Rush_C_Number = 3;
	}
	void Layana_Dark_Awaken::Complete_Rush_C4()
	{
		_Rush_C_Number = 4;
	}
	void Layana_Dark_Awaken::Complete_Rush_C5()
	{
		_Rush_C_Number = 5;
	}
	void Layana_Dark_Awaken::Complete_Rush_C6()
	{
		_Rush_C_Number = 6;
	}
	void Layana_Dark_Awaken::Complete_Rush_C7()
	{
		_Rush_C_Number = 7;
	}


	void Layana_Dark_Awaken::Meteor_Cross_Combo()
	{
		_CrossMeteorSwitch = true;
		_teleport_Cross = true;
		_DarkMode_state = Layana_Dark_Awaken_State::Telleport_In;
	}
	void Layana_Dark_Awaken::Complete_CrossJump()
	{
		_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Cross_Attack;
	}
	void Layana_Dark_Awaken::Complete_CrossLanding()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Awaken_PowerMeteor_Cross03_End", true);
		else
			at->PlayAnimation(L"Awaken_PowerMeteor_Cross03_EndR", true);
		_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Cross_End;
	}
	void Layana_Dark_Awaken::Complete_CrossEnd()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Awaken_PowerIdle", true);
		else
			at->PlayAnimation(L"Awaken_PowerIdleR", true);
		_DarkMode_state = Layana_Dark_Awaken_State::Idle;
		_time = 0;
		_CrossMeteorSwitch = false;
		_CrossMeteorLanding = false;	
	}


	void Layana_Dark_Awaken::Meteor_Ground_Combo()
	{
		_GroundMeteorSwitch = true; // 이동이 되었을때 공격하는 모션 온
		_teleport_Ground = true;
		_DarkMode_state = Layana_Dark_Awaken_State::Telleport_In;
	}
	void Layana_Dark_Awaken::Complete_GroundLanding()
	{
	}
	void Layana_Dark_Awaken::Complete_GroundEnd()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Awaken_PowerIdle", true);
		else
			at->PlayAnimation(L"Awaken_PowerIdleR", true);
		_DarkMode_state = Layana_Dark_Awaken_State::Idle;

		_time = 0;
		_GroundMeteorSwitch = false;
		_GroundMeteorLanding = false;
		_GroundMeteorAttack_Right = false;
		_GroundMeteorAttack_Left = false;
	}


	void Layana_Dark_Awaken::Meteor_Vertical_Combo()
	{
		_VerticalMeteorSwitch = true;
		_teleport_Vertical = true;
		_DarkMode_state = Layana_Dark_Awaken_State::Telleport_In;

	}
	void Layana_Dark_Awaken::Complete_VerticalJump()
	{
		_Ground_check = false;
		_pos.x = _Playerpos.x;
		_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Vertical_Ready;
		at->PlayAnimation(L"Awaken_PowerMeteor_Vertical01_Ready", true);
	}
	void Layana_Dark_Awaken::Complete_VerticalReady()
	{
		_HitBox_Attack_On = true;
		_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Vertical_Landing;
		_Ground_check = false;
		_pos.x = _Playerpos.x;
		at->PlayAnimation(L"Awaken_PowerMeteor_Vertical02_Attack", false);
		_rigidbody->SetGround(false);
		_rigidbody->SetVelocity(Vector2(0.f, -1350.f));
	}
	void Layana_Dark_Awaken::Complete_VerticalEnd()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Awaken_PowerIdle", true);
		else
			at->PlayAnimation(L"Awaken_PowerIdleR", true);
		_DarkMode_state = Layana_Dark_Awaken_State::Idle;

		_time = 0;
		_VerticalMeteorSwitch = false;
		_VerticalMeteorLanding = false;
	}


	void Layana_Dark_Awaken::Skill_A_Combo()
	{
	}
	void Layana_Dark_Awaken::Complete_Skill_A()
	{
	}


	void Layana_Dark_Awaken::Skill_B_Combo()
	{
		_DarkMode_state = Layana_Dark_Awaken_State::Skill_B_RisingPierce_Ready;
		if (_Dir == 1)
			at->PlayAnimation(L"Awaken_PowerSkill_B_RisingPierce", false);
		else
			at->PlayAnimation(L"Awaken_PowerSkill_B_RisingPierceR", false);

		for (int i = 0; i < 5; i++)		
			_Dark_HomingPierce[i]->_bulletoff = false;
	}
	void Layana_Dark_Awaken::Complete_Skill_B()
	{		
		for (int i = 0; i < 5; i++)
		{
			_HomingPierce_Attack[i]->SetState(eState::Paused);
			_HomingPierce_Effect[i]->SetState(eState::Paused);
			_HomingPierce_Attack[i]->_bulletoff = false;
			_Dark_HomingPierce[i]->_bulletoff = true;
			_Dark_HomingPierce[i]->_Create_ball = false;
		}
		if (_Dir == 1)
			at->PlayAnimation(L"Awaken_PowerIdle", true);
		else
			at->PlayAnimation(L"Awaken_PowerIdleR", true);
		_DarkMode_state = Layana_Dark_Awaken_State::Idle;
		_time = 0.f;
		_SkillB_Switch = false;
	}


	void Layana_Dark_Awaken::Skill_C_Combo()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Awaken_PowerSkill_C_DimensionPierce", false);
		else
			at->PlayAnimation(L"Awaken_PowerSkill_C_DimensionPierceR", false);
		_DarkMode_state = Layana_Dark_Awaken_State::Skill_C_DimensionPierce_Ready;
		_SkillC_Switch = false;
	}

	void Layana_Dark_Awaken::Awaken_Combo()
	{
		_DarkMode_state = Layana_Dark_Awaken_State::Awaken_End;
		if (_Dir == 1)
		{
			Awaken_End_ElecEF->SetSwitch(true);
			Awaken_End_ElecEF->SetDirection(1);
			Awaken_End_ElecEF->SetState(eState::Active);
			Transform* Ellect_EFtr = Awaken_End_ElecEF->GetComponent<Transform>();
			Ellect_EFtr->SetPosition(Vector3(_pos.x-20, _pos.y+80, _pos.z - 1));

			Awaken_End_SmA_EF->SetSwitch(true);
			Awaken_End_SmA_EF->SetDirection(1);
			Awaken_End_SmA_EF->SetState(eState::Active);
			Transform* Ellect_SMAtr = Awaken_End_SmA_EF->GetComponent<Transform>();
			Ellect_SMAtr->SetPosition(Vector3(_pos.x, _pos.y-40, _pos.z - 1));


			Awaken_End_SmB_EF->SetSwitch(true);
			Awaken_End_SmB_EF->SetDirection(1);
			Awaken_End_SmB_EF->SetState(eState::Active);
			Transform* Ellect_SMBtr = Awaken_End_SmB_EF->GetComponent<Transform>();
			Ellect_SMBtr->SetPosition(Vector3(_pos.x, _pos.y - 60, _pos.z - 1));

			at->PlayAnimation(L"Awaken_PowerAwakenEnd", true);
		}
		else
		{
			Awaken_End_ElecEF->SetSwitch(true);
			Awaken_End_ElecEF->SetDirection(-1);
			Awaken_End_ElecEF->SetState(eState::Active);
			Transform* Ellect_EFtr = Awaken_End_ElecEF->GetComponent<Transform>();
			Ellect_EFtr->SetPosition(Vector3(_pos.x-20, _pos.y+80, _pos.z - 1));


			Awaken_End_SmA_EF->SetSwitch(true);
			Awaken_End_SmA_EF->SetDirection(-1);
			Awaken_End_SmA_EF->SetState(eState::Active);
			Transform* Ellect_SMAtr = Awaken_End_SmA_EF->GetComponent<Transform>();
			Ellect_SMAtr->SetPosition(Vector3(_pos.x, _pos.y - 40, _pos.z - 1));


			Awaken_End_SmB_EF->SetSwitch(true);
			Awaken_End_SmB_EF->SetDirection(-1);
			Awaken_End_SmB_EF->SetState(eState::Active);
			Transform* Ellect_SMBtr = Awaken_End_SmB_EF->GetComponent<Transform>();
			Ellect_SMBtr->SetPosition(Vector3(_pos.x, _pos.y - 60, _pos.z - 1));

			at->PlayAnimation(L"Awaken_PowerAwakenEndR", true);
		}
	}
	void Layana_Dark_Awaken::Complete_AwakenEnd()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Awaken_PowerIdle", true);
		else
			at->PlayAnimation(L"Awaken_PowerIdleR", true);
		_DarkMode_state = Layana_Dark_Awaken_State::Idle;
		_Awaken_Switch = false;
	}


	

	void Layana_Dark_Awaken::Complete_Death_00()
	{
		_DarkMode_state = Layana_Dark_Awaken_State::Death;
		if (_DieDir == 1)
		{
			at->PlayAnimation(L"Awaken_PowerDeath_01", true);
			_Death_Intro->SetState(eState::Active);
			_Death_Intro->SetSwitch(true);
			_Death_Intro->SetDirection(1);
			Transform* Eftr = _Death_Intro->GetComponent<Transform>();
			Eftr->SetPosition(Vector3(_pos.x, _pos.y+110, _pos.z - 1));
		}
		else
		{
			at->PlayAnimation(L"Awaken_PowerDeath_01R", true);
			_Death_Intro->SetState(eState::Active);
			_Death_Intro->SetSwitch(true);
			_Death_Intro->SetDirection(-1);
			Transform* Eftr = _Death_Intro->GetComponent<Transform>();
			Eftr->SetPosition(Vector3(_pos.x, _pos.y+110, _pos.z - 1));
		}
	}

	void Layana_Dark_Awaken::Complete_Death_01()
	{		
		_DarkMode_state = Layana_Dark_Awaken_State::Good_Bye_Layana;
		if (_DieDir == 1)
		{
			_Death_Elect1->SetState(eState::Active);
			_Death_Elect1->SetSwitch(true);
			_Death_Elect1->SetDirection(1);
			Transform* Elect_Eftr = _Death_Elect1->GetComponent<Transform>();
			Elect_Eftr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));

			at->PlayAnimation(L"Awaken_PowerDeath_02", true);
		}
		else
		{
			_Death_Elect1->SetState(eState::Active);
			_Death_Elect1->SetSwitch(true);
			_Death_Elect1->SetDirection(1);
			Transform* Elect_Eftr = _Death_Elect1->GetComponent<Transform>();
			Elect_Eftr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));

			at->PlayAnimation(L"Awaken_PowerDeath_02R", true);
		}
	}

	void Layana_Dark_Awaken::Complete_Death_02()
	{
		_Death_EF_First->SetState(eState::Paused);
		_DarkMode_state = Layana_Dark_Awaken_State::Layana_End;
		if (_DieDir == 1)
		{
			_Death_Elect2->SetState(eState::Active);
			_Death_Elect2->SetSwitch(true);
			_Death_Elect2->SetDirection(1);
			Transform* Elect_Eftr = _Death_Elect2->GetComponent<Transform>();
			Elect_Eftr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));


			_Death_EF_Second->SetState(eState::Active);
			_Death_EF_Second->SetSwitch(true);
			_Death_EF_Second->SetDirection(1);
			Transform* _Eftr = _Death_EF_Second->GetComponent<Transform>();
			_Eftr->SetPosition(Vector3(_pos.x, _pos.y + 115, _pos.z + 1));

			at->PlayAnimation(L"Awaken_PowerDeath_03", false);
		}
		else
		{
			_Death_Elect2->SetState(eState::Active);
			_Death_Elect2->SetSwitch(true);
			_Death_Elect2->SetDirection(1);
			Transform* Elect_Eftr = _Death_Elect2->GetComponent<Transform>();
			Elect_Eftr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));


			_Death_EF_Second->SetState(eState::Active);
			_Death_EF_Second->SetSwitch(true);
			_Death_EF_Second->SetDirection(1);
			Transform* _Eftr = _Death_EF_Second->GetComponent<Transform>();
			_Eftr->SetPosition(Vector3(_pos.x, _pos.y + 115, _pos.z + 1));

			at->PlayAnimation(L"Awaken_PowerDeath_03R", false);
		}
	}


	void Layana_Dark_Awaken::CreateHoming()
	{
	}
	void Layana_Dark_Awaken::SettingHoming(Transform* set, int angle_of_number)
	{
	}
}