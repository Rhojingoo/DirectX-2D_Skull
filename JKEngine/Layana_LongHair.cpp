#include "Layana_LongHair.h"


namespace jk
{
	bool Layana_LongHair:: _AttackStageON = true;
	Layana_LongHair::Layana_LongHair_State Layana_LongHair::_LongHair_state = Layana_LongHair_State();
	Layana_LongHair::Layana_Long_Background Layana_LongHair::Background_state = Layana_Long_Background();


	int	Layana_LongHair::_HitType = 0;
	int	Layana_LongHair::_Dammege = 0;
	Player_Hp_Bar* Layana_LongHair::Player_Hp = nullptr;
	Monster_Hit_Effect* Layana_LongHair::_Hit_Effect = nullptr;
	Player_Hit_Effect* Layana_LongHair::_Hit_Effect_player = nullptr;
	Hit_Sword* Layana_LongHair::_Hit_Sword = nullptr;
	Hit_Critical_Middle* Layana_LongHair::_Critical_Middle = nullptr;
	Hit_Critical_High* Layana_LongHair::_Critical_High = nullptr;
	Monster_Death_Effect* Layana_LongHair::_Death_Effect = nullptr;


	Layana_LongHair::Layana_LongHair()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Layana_LongHair::~Layana_LongHair()
	{
	}


	void Layana_LongHair::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);


		tr = GetComponent<Transform>();
		_pos = Vector3(0.f, 90.f, -200.f);		
		_LongHairCreatepos = _pos;
		tr->SetPosition(_pos);

		
		
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Awaken", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\AwakenJump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\AwakenReady", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\BackGround_Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\BackGround_Move", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\BackStep", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Die", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Intro_Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Intro_Fall", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Intro_Landing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Intro_Landing_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross00_Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross01_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross02_Landing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross03_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross04_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground01_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground02_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground03_Landing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground04_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical00_Jump", this, 0,0.065);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical01_Ready", this,0,0.065);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical02_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical03_Landing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical04_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Rush_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Rush_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushA", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushB", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushC", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushC1", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushC2", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushC3", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushC4", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_A_Bullet_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_A_Bullet", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_A_Bullet_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_B_RisingPierce", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_B_RisingPierce_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_C_DimensionPierce", this);
		
		
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Awaken", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\AwakenJump", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\AwakenReady", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\BackGround_Idle", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\BackGround_Move", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\BackStep", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Dash", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Die", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Idle", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Intro_Dash", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Intro_Fall", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Intro_Landing", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Intro_Landing_End", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross00_Jump", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross01_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross02_Landing", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross03_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross04_Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground01_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground02_Attack", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground03_Landing", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground04_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical00_Jump", this,1,0.065);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical01_Ready", this,1,0.065);	
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical02_Attack", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical03_Landing", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical04_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Rush_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Rush_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushA", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushB", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushC", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushC1", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushC2", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushC3", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushC4", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_A_Bullet_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_A_Bullet", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_A_Bullet_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_B_RisingPierce", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_B_RisingPierce_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_C_DimensionPierce", this,1);
		
		

		//bind 부분
		at->CompleteEvent(L"Long_hairRush_Ready") = std::bind(&Layana_LongHair::Complete_RushReady, this);
		at->CompleteEvent(L"Long_hairRushA") = std::bind(&Layana_LongHair::Complete_Rush, this);
		at->CompleteEvent(L"Long_hairRushB") = std::bind(&Layana_LongHair::Complete_Rush, this);
		at->CompleteEvent(L"Long_hairRushC") = std::bind(&Layana_LongHair::Complete_Rush, this);

		at->CompleteEvent(L"Long_hairRushC1") = std::bind(&Layana_LongHair::Complete_RushReady, this);
		at->CompleteEvent(L"Long_hairRushC2") = std::bind(&Layana_LongHair::Complete_RushReady, this);
		at->CompleteEvent(L"Long_hairRushC3") = std::bind(&Layana_LongHair::Complete_RushReady, this);
		at->CompleteEvent(L"Long_hairRushC4") = std::bind(&Layana_LongHair::Complete_Rush, this);
		at->CompleteEvent(L"Long_hairRush_End") = std::bind(&Layana_LongHair::Complete_RushReady, this);

		at->CompleteEvent(L"Long_hairMeteor_Cross01_Ready") = std::bind(&Layana_LongHair::Complete_CrossJump, this);
		at->CompleteEvent(L"Long_hairMeteor_Cross03_End") = std::bind(&Layana_LongHair::Complete_CrossEnd, this);
		//at->CompleteEvent(L"Long_hairMeteor_Ground01_Ready") = std::bind(&Layana_LongHair::Complete_GroundLanding, this);
		at->CompleteEvent(L"Long_hairMeteor_Ground04_End") = std::bind(&Layana_LongHair::Complete_GroundEnd, this);
		at->CompleteEvent(L"Long_hairMeteor_Vertical00_Jump") = std::bind(&Layana_LongHair::Complete_VerticalJump, this);
		at->CompleteEvent(L"Long_hairMeteor_Vertical01_Ready") = std::bind(&Layana_LongHair::Complete_VerticalReady, this);
		at->CompleteEvent(L"Long_hairMeteor_Vertical04_End") = std::bind(&Layana_LongHair::Complete_VerticalEnd, this);
		at->CompleteEvent(L"Long_hairSkill_A_Bullet_End") = std::bind(&Layana_LongHair::Complete_Skill_A, this);
		at->CompleteEvent(L"Long_hairSkill_B_RisingPierce_End") = std::bind(&Layana_LongHair::Complete_Skill_B, this);
		at->CompleteEvent(L"Long_hairIntro_Landing") = std::bind(&Layana_LongHair::Complete_IntroLanding, this);
		at->CompleteEvent(L"Long_hairIntro_Landing_End") = std::bind(&Layana_LongHair::Complete_IntroLanding_END, this);
		at->CompleteEvent(L"Long_hairAwaken") = std::bind(&Layana_LongHair::Complete_Awaken, this);
		at->CompleteEvent(L"Long_hairAwakenReadyR") = std::bind(&Layana_LongHair::Complete_Awaken_Ready, this);

		


		at->CompleteEvent(L"Long_hairRush_ReadyR") = std::bind(&Layana_LongHair::Complete_RushReady, this);
		at->CompleteEvent(L"Long_hairRushAR") = std::bind(&Layana_LongHair::Complete_Rush, this);
		at->CompleteEvent(L"Long_hairRushBR") = std::bind(&Layana_LongHair::Complete_Rush, this);
		at->CompleteEvent(L"Long_hairRushCR") = std::bind(&Layana_LongHair::Complete_Rush, this);

		at->CompleteEvent(L"Long_hairRushC1R") = std::bind(&Layana_LongHair::Complete_RushReady, this);
		at->CompleteEvent(L"Long_hairRushC2R") = std::bind(&Layana_LongHair::Complete_RushReady, this);
		at->CompleteEvent(L"Long_hairRushC3R") = std::bind(&Layana_LongHair::Complete_RushReady, this);
		at->CompleteEvent(L"Long_hairRushC4R") = std::bind(&Layana_LongHair::Complete_Rush, this);
		at->CompleteEvent(L"Long_hairRush_EndR") = std::bind(&Layana_LongHair::Complete_RushReady, this);


		at->CompleteEvent(L"Long_hairMeteor_Cross01_ReadyR") = std::bind(&Layana_LongHair::Complete_CrossJump, this);
		at->CompleteEvent(L"Long_hairMeteor_Cross03_EndR") = std::bind(&Layana_LongHair::Complete_CrossEnd, this);
		//at->CompleteEvent(L"Long_hairMeteor_Ground01_ReadyR") = std::bind(&Layana_LongHair::Complete_GroundLanding, this);
		at->CompleteEvent(L"Long_hairMeteor_Ground04_EndR") = std::bind(&Layana_LongHair::Complete_GroundEnd, this);
		at->CompleteEvent(L"Long_hairMeteor_Vertical00_JumpR") = std::bind(&Layana_LongHair::Complete_VerticalJump, this);
		at->CompleteEvent(L"Long_hairMeteor_Vertical01_ReadyR") = std::bind(&Layana_LongHair::Complete_VerticalReady, this);
		at->CompleteEvent(L"Long_hairMeteor_Vertical04_EndR") = std::bind(&Layana_LongHair::Complete_VerticalEnd, this);
		at->CompleteEvent(L"Long_hairSkill_A_Bullet_EndR") = std::bind(&Layana_LongHair::Complete_Skill_A, this);
		at->CompleteEvent(L"Long_hairSkill_B_RisingPierce_EndR") = std::bind(&Layana_LongHair::Complete_Skill_B, this);
		at->CompleteEvent(L"Long_hairIntro_LandingR") = std::bind(&Layana_LongHair::Complete_IntroLanding, this);
		at->CompleteEvent(L"Long_hairIntro_Landing_EndR") = std::bind(&Layana_LongHair::Complete_IntroLanding_END, this);
		at->CompleteEvent(L"Long_hairAwakenR") = std::bind(&Layana_LongHair::Complete_Awaken, this);
		at->CompleteEvent(L"Long_hairAwakenReadyR") = std::bind(&Layana_LongHair::Complete_Awaken_Ready, this);


		{
			Hit_Box = new HitBox_Layana();
			Hit_Box->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetState(eState::Paused);
		}
		
		for (int i = 0; i < 3; i++)
		{
			Homing[i] = new Homing_Pierce_LongHair;
			Homing[i]->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Homing[i]);
			Transform* bullet_tr = Homing[i]->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			Homing[i]->SetState(eState::Paused);
		}
		for (int i = 0; i < 3; i++)
		{
			Homing_EF[i] = new Homing_Impact;
			Homing_EF[i]->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Homing_EF[i]);
			Transform* bullet_tr = Homing_EF[i]->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			Homing_EF[i]->SetState(eState::Paused);
		}


		
		for (int a = 0; a< 19; a++)
		{
			Rising[a] = new Rising_Pierce;
			Rising[a]->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Rising[a]);
			Risingbullet_tr[a] = Rising[a]->GetComponent<Transform>();
			Risingbullet_tr[a]->SetPosition(Vector3(_pos.x, _pos.y, -205));
			Rising[a]->SetState(eState::Paused);
		}

		{
			Dimension_boss_effect = new Dimension_Pierce_BossEffect;
			Dimension_boss_effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Dimension_boss_effect);
			Transform* boss_effect = Dimension_boss_effect->GetComponent<Transform>();
			boss_effect->SetPosition(Vector3(_pos.x, _pos.y, -205));
			Dimension_boss_effect->SetState(eState::Paused);
		}

		{
			Dimension_Bullet = new Dimension_Pierce;
			Dimension_Bullet->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Dimension_Bullet);
			Transform* boss_effect = Dimension_Bullet->GetComponent<Transform>();
			boss_effect->SetPosition(Vector3(_pos.x, _pos.y, -205));
			Dimension_Bullet->SetState(eState::Paused);
		}		

		{
			Dimension_BulletEffect = new Dimension_Pierce_BulletEffect;
			Dimension_BulletEffect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Dimension_BulletEffect);
			Transform* bullte_effect = Dimension_BulletEffect->GetComponent<Transform>();
			bullte_effect->SetPosition(Vector3(_pos.x, _pos.y, -205));
			Dimension_BulletEffect->SetState(eState::Paused);
		}

		{
			TwinMeteor_Impact = new TwinMeteor_Effect;
			TwinMeteor_Impact->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, TwinMeteor_Impact);
			Transform* bullte_effect = TwinMeteor_Impact->GetComponent<Transform>();
			bullte_effect->SetPosition(Vector3(_pos.x, _pos.y, -205));
			TwinMeteor_Impact->SetState(eState::Paused);
		}

		{
			TwinMeteor_BossEffect = new TwinMeteor_Boss;
			TwinMeteor_BossEffect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, TwinMeteor_BossEffect);
			Transform* bullte_effect = TwinMeteor_BossEffect->GetComponent<Transform>();
			bullte_effect->SetPosition(Vector3(_pos.x, _pos.y, -205));
			TwinMeteor_BossEffect->SetState(eState::Paused);
		}

		{
			Intro_SM = new Intro_Somke;
			Intro_SM->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Intro_SM);
			Intro_SM->SetState(eState::Paused);
		}
		{
			Intro_Ar = new Intro_Aura_Layana;
			Intro_Ar->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Intro_Ar);
			Intro_Ar->SetState(eState::Paused);
		}
		{
			Dash_SM = new Layana_Dash_Smoke;
			Dash_SM->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, Dash_SM);
			Dash_SM->SetState(eState::Paused);
		}
		{
			MeteorGR_SM = new Layana_Meteor_GR_Smoke;
			MeteorGR_SM->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, MeteorGR_SM);
			MeteorGR_SM->SetState(eState::Paused);
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
			Player_Hp->SetState(eState::Active);
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

		at->PlayAnimation(L"Long_hairIdle", true);
		GameObject::Initialize();
	}
	void Layana_LongHair::Update()
	{
		bullet_tr1 = Homing[0]->GetComponent<Transform>();
		bullet_tr2 = Homing[1]->GetComponent<Transform>();
		bullet_tr3 = Homing[2]->GetComponent<Transform>();
		bullet_rb1 = Homing[0]->GetComponent<RigidBody>();
		bullet_rb2 = Homing[1]->GetComponent<RigidBody>();
		bullet_rb3 = Homing[2]->GetComponent<RigidBody>();

		_Playerpos = Player::GetPlayer_Pos();
		_velocity = _rigidbody->GetVelocity();
		_Playerdistance.x = _Playerpos.x - _pos.x;
		_Playerdistance.y = _Playerpos.y - _pos.y;
		if (_Playerdistance.x >= 0)
			_Dir = 1;
		else
			_Dir = -1;
		_pos = tr->GetPosition();
		LongHairPos = _pos;

		_MaxHp_LongHair_scale = _Max_LongHair_Hp / 100;
		_CurrenHp_LongHair_scale = _Curren_LongHair_Hp / 100;
		Transform* hp_tr = Player_Hp->GetComponent<Transform>();
		hp_tr->SetPosition(Vector3(_pos.x - (_MaxHp_LongHair_scale - _CurrenHp_LongHair_scale)+200 / 2, 150, _pos.z - 1));
		hp_tr->SetScale(_CurrenHp_LongHair_scale, 10, 0);


		if (Joint_Operation == true)
		{
			switch (_state)
			{
			case jk::Layana_Sisters::Layana_Sisters_State::Idle:
				Layana_LongHair::idle();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Intro_Dash:
				Layana_LongHair::Intro_Dash();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Intro_Fall:
				Layana_LongHair::Intro_Fall();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Intro_Landing:
				Layana_LongHair::Intro_Landing();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Intro_Landing_End:
				Layana_LongHair::Intro_Landing_End();
				break;


			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_Set:
				Layana_LongHair::Sisters_Attack_Set();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_FlyDash:
				Layana_LongHair::Sisters_Attack_FlyDash();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_Fall:
				Layana_LongHair::Sisters_Attack_Fall();
				break;


			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_A_Ready:
				Layana_LongHair::Sisters_Attack_A_Ready();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_A_LandingDash:
				Layana_LongHair::Sisters_Attack_A_LandingDash();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_A:
				Layana_LongHair::Sisters_Attack_A();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_A_End:
				Layana_LongHair::Sisters_Attack_A_End();
				break;


			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_B_Ready:
				Layana_LongHair::Sisters_Attack_B_Ready();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_B_BulletCreate:
				Layana_LongHair::Sisters_Attack_B_BulletCreate();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_B:
				Layana_LongHair::Sisters_Attack_B();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_B_End:
				Layana_LongHair::Sisters_Attack_B_End();
				break;


			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_C_Ready:
				Layana_LongHair::Sisters_Attack_C_Ready();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_C:
				Layana_LongHair::Sisters_Attack_C();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_C_Landing:
				Layana_LongHair::Sisters_Attack_C_Landing();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_C_End:
				Layana_LongHair::Sisters_Attack_C_End();
				break;		

			default:
				break;
			}
		}

		if(LongHair_Operation == true)
		{		
			switch (_LongHair_state)//_LongHair_state
			{
			case jk::Layana_LongHair::Layana_LongHair_State::Idle:
				Layana_LongHair::idle();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Rush_Ready:
				Layana_LongHair::Rushready();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::RushA:
				Layana_LongHair::Rush_A();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::RushB:
				Layana_LongHair::Rush_B();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::RushC:
				Layana_LongHair::Rush_C();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::RushC1:
				Layana_LongHair::Rush_C1();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::RushC2:
				Layana_LongHair::Rush_C2();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::RushC3:
				Layana_LongHair::Rush_C3();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::RushC4:
				Layana_LongHair::Rush_C4();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Rush_End:
				Layana_LongHair::Rush_End();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Dash:
				Layana_LongHair::Dash();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::FlyDash:
				Layana_LongHair::FlyDash();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::LandingDash:
				Layana_LongHair::LandingDash();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::BackStep:
				Layana_LongHair::BackStep();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Meteor_Cross_Ready:
				Layana_LongHair::CrossReady();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Meteor_Cross_Jump:
				Layana_LongHair::CrossJump();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Meteor_Cross_Attack:
				Layana_LongHair::CrossAttack();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Meteor_Cross_Landing:
				Layana_LongHair::CrossLanding();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Meteor_Cross_End:
				Layana_LongHair::CrossEnd();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Meteor_Ground_Ready:
				Layana_LongHair::GroundReady();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Meteor_Ground_Attack:
				Layana_LongHair::GroundAttack();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Meteor_Ground_Landing:
				Layana_LongHair::GroundLanding();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Meteor_Ground_End:
				Layana_LongHair::GroundEnd();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Meteor_Vertical_Jump:
				Layana_LongHair::Vertical_Jump();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Meteor_Vertical_Ready:
				Layana_LongHair::Vertical_Ready();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Meteor_Vertical_Attack:
				Layana_LongHair::Vertical_Attack();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Meteor_Vertical_Landing:
				Layana_LongHair::Vertical_Landing();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Meteor_Vertical_End:
				Layana_LongHair::Vertical_End();
				break;



			case Layana_LongHair::Layana_LongHair_State::Skill_A_Bullet_Ready:
				Layana_LongHair::Skill_A_Ready();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Skill_A_Bullet:
				Layana_LongHair::Skill_A();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Skill_A_Bullet_End:
				Layana_LongHair::Skill_A_End();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Skill_B_RisingPierce:
				Layana_LongHair::Skill_B();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Skill_B_RisingPierce_End:
				Layana_LongHair::Skill_B_End();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Skill_C_DimensionPierce:
				Layana_LongHair::Skill_C();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::AwakenJump:
				Layana_LongHair::AwakenJump();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::AwakenReady:
				Layana_LongHair::AwakenReady();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::Awaken:
				Layana_LongHair::Awaken();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::BackGround_Idle:
				Layana_LongHair::BackGround_Idle();
				break;

			case jk::Layana_LongHair::Layana_LongHair_State::BackGround_Move:
				Layana_LongHair::BackGround_Enter();
				break;

			default:
				break;
			}
		}

		if (ShortHair_Operation == true)
		{
			switch (Background_state)
			{

			case jk::Layana_LongHair::Layana_Long_Background::Idle:
				Layana_LongHair::idle();
				break;

			case jk::Layana_LongHair::Layana_Long_Background::FlyDash:
				Layana_LongHair::FlyDash();
				break;

			case jk::Layana_LongHair::Layana_Long_Background::BackGround_Idle:
				Layana_LongHair::BackGround_Idle();
				break;

			case jk::Layana_LongHair::Layana_Long_Background::BackGround_Enter:
				Layana_LongHair::BackGround_Enter();
				break;

			case jk::Layana_LongHair::Layana_Long_Background::BackGround_Exit:
				Layana_LongHair::BackGround_Exit();
				break;

				//int a = 0;

			default:
				break;
			}

		}


		tr->SetPosition(_pos);
		GameObject::Update();
	}
	void Layana_LongHair::LateUpdate()
	{
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_HitBox_Attack_On == true)
		{
			if (_state == Layana_Sisters_State::Sisters_Attack_A || _LongHair_state == Layana_LongHair_State::Meteor_Ground_Attack)
			{				
				Hit_Box->SetSize(Vector2(55.f, 5.f));
				Hit_Box->SetState(eState::Active);
				if (_HitBox_Dir == 1)	//오른쪽으로 공격할때의 기준
					HitBox_TR->SetPosition(Vector3(_pos.x+50, _pos.y-40, _pos.z));					
				else					//왼쪽으로 공격할때의 기준
					HitBox_TR->SetPosition(Vector3(_pos.x-50, _pos.y-40, _pos.z));				
			}
			else if (_LongHair_state == Layana_LongHair_State::Meteor_Vertical_Landing)
			{
				Hit_Box->SetSize(Vector2(5.f, 55.f));
				Hit_Box->SetState(eState::Active);
				HitBox_TR->SetPosition(Vector3(_pos.x + 5, _pos.y - 50, _pos.z));
			}
			else if (_LongHair_state == Layana_LongHair_State::Meteor_Cross_Landing)
			{
				Hit_Box->SetSize(Vector2(5.f, 55.f));
			
				Hit_Box->SetState(eState::Active);

				if (_HitBox_Dir == 1)	//오른쪽으로 공격할때의 기준
				{
					HitBox_TR->SetPosition(Vector3(_pos.x + 30, _pos.y - 50, _pos.z));
					HitBox_TR->SetRotationZ(45 / (180.f / XM_PI));
				}
				else					//왼쪽으로 공격할때의 기준
				{
					HitBox_TR->SetPosition(Vector3(_pos.x - 30, _pos.y - 50, _pos.z));
					HitBox_TR->SetRotationZ(-45 / (180.f / XM_PI));
				}
			}

			else if (_LongHair_state == Layana_LongHair_State::RushA)
			{
				Hit_Box->SetSize(Vector2(55.f, 5.f));
				Hit_Box->SetState(eState::Active);

				if (_HitBox_Dir == 1)	//오른쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x + 90, _pos.y -25 , _pos.z));				
				else					//왼쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x - 90, _pos.y -25, _pos.z));							
			}
			else if (_LongHair_state == Layana_LongHair_State::RushB)
			{
				Hit_Box->SetSize(Vector2(55.f, 5.f));
				Hit_Box->SetState(eState::Active);

				if (_HitBox_Dir == 1)	//오른쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x + 90, _pos.y - 35, _pos.z));
				else					//왼쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x - 90, _pos.y - 35, _pos.z));
			}
			else if (_LongHair_state == Layana_LongHair_State::RushC1)
			{
				Hit_Box->SetSize(Vector2(55.f, 5.f));
				Hit_Box->SetState(eState::Active);

				if (_HitBox_Dir == 1)	//오른쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x + 90, _pos.y - 15, _pos.z));
				else					//왼쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x - 90, _pos.y - 15, _pos.z));
			}
			else if (_LongHair_state == Layana_LongHair_State::RushC2)
			{
				Hit_Box->SetSize(Vector2(55.f, 5.f));
				Hit_Box->SetState(eState::Active);
				if (_HitBox_Dir == 1)	//오른쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x + 90, _pos.y - 25, _pos.z));
				else					//왼쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x - 90, _pos.y - 25, _pos.z));
			}
			else if (_LongHair_state == Layana_LongHair_State::RushC3)
			{
				Hit_Box->SetSize(Vector2(55.f, 5.f));
				Hit_Box->SetState(eState::Active);
				if (_HitBox_Dir == 1)	//오른쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x + 90, _pos.y - 35, _pos.z));
				else					//왼쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x - 90, _pos.y - 35, _pos.z));
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
	void Layana_LongHair::Render()
	{
		GameObject::Render();
	}


	void Layana_LongHair::OnCollisionEnter(Collider2D* other)
	{
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
			//	_Dammege = random(15, 25);
			//	attack_Cri_Mid = true;
			//}
			//if (_HitType >= 9 && _HitType <= 10)
			//{
			//	_Dammege = random(30, 45);
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
				int a = 0;
				//if (_Diecheck == 0)
				//{
				//	//if (Yggdrasil::_FirstDie == false)
				//	//{
				//	//	Yggdrasil::_FirstDie = true;
				//	//	Yggdrasil::_Change = true;
				//	//	_Diecheck = 1;
				//	//}
				//}
				//else if (_Diecheck == 1)
				//{
				//	//_DieON = true;
				//	//Yggdrasil::_FirstDie = true;
				//}
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
				//if (_Diecheck == 0)
				//{
				//	if (Yggdrasil::_FirstDie == false)
				//	{
				//		Yggdrasil::_FirstDie = true;
				//		Yggdrasil::_Change = true;
				//		_Diecheck = 1;
				//	}
				//}
				//else if (_Diecheck == 1)
				//{
				//	_DieON = true;
				//	Yggdrasil::_FirstDie = true;
				//}
			}
		}
	}
	void Layana_LongHair::OnCollisionStay(Collider2D* other)
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
				if (_LongHair_state == Layana_LongHair_State::Meteor_Cross_Landing)
				{						
					_HitBox_Attack_On = false;
					if (_Dir == 1)
						at->PlayAnimation(L"Long_hairMeteor_Cross02_Landing", true);
					else
						at->PlayAnimation(L"Long_hairMeteor_Cross02_LandingR", true);			
					tr->SetRotationZ(0.f);
					_CrossMeteorLanding = true;
				}
				if (_LongHair_state == Layana_LongHair_State::LandingDash)
				{					
					if (_Dir == 1)
						at->PlayAnimation(L"Long_hairMeteor_Ground01_Ready", true);
					else
						at->PlayAnimation(L"Long_hairMeteor_Ground01_ReadyR", true);		
					_GroundMeteorLanding = true;
				}
				if (_LongHair_state == Layana_LongHair_State::Meteor_Vertical_Landing)
				{
					if (_VerticalMeteorLanding == false)
					{
						if (_Dir == 1)
							at->PlayAnimation(L"Long_hairMeteor_Vertical03_Landing", true);
						else
							at->PlayAnimation(L"Long_hairMeteor_Vertical03_LandingR", true);

						_VerticalMeteorLandingSM = true;
						_VerticalMeteorLanding = true;
					}
				}
				if (_LongHair_state == Layana_LongHair_State::AwakenJump)
					_Awaken_Ready = true;
				//if (_state == Layana_Sisters_State::Skill_A_Bullet_Ready)
				//{
				//	if (_Dir == 1)
				//		at->PlayAnimation(L"Long_hairSkill_A_Bullet_Ready", true);
				//	else
				//		at->PlayAnimation(L"Long_hairSkill_A_Bullet_ReadyR", true);					
				//	_SkillA_Landing = true;
				//}


				if (_state == Layana_Sisters_State::Intro_Fall)
				{					
					//at->PlayAnimation(L"Long_hairIntro_LandingR", true);			
					_Intro_Landing = true;
					Intro_SM->SetState(eState::Active);
					Intro_SM->SetSwitch(true);
					Transform* SMtr = Intro_SM->GetComponent<Transform>();
					SMtr->SetPosition(_pos.x-20, _pos.y-50.f, _pos.z - 1);
				}

				if (_state == Layana_Sisters_State::Sisters_Attack_Fall)
				{
					if (_Sisters_Attack_A == true)
					{						
						if (_pos.x < _LongHairCreatepos.x)
							at->PlayAnimation(L"Long_hairMeteor_Ground01_Ready", false);
						else
							at->PlayAnimation(L"Long_hairMeteor_Ground01_ReadyR", false);								
						_Sisters_Attack_A = false;
					}
					if (_Sisters_Attack_B == true)
					{
						if (_pos.x < _LongHairCreatepos.x)
							at->PlayAnimation(L"Long_hairSkill_A_Bullet_Ready", false);
						else
							at->PlayAnimation(L"Long_hairSkill_A_Bullet_ReadyR", false);			
						_SistersAttack_B_Ready_LongHair = true;
						_Sisters_Attack_B = false;
					}
				}		
				if (_state == Layana_Sisters_State::Sisters_Attack_C)
				{
					if (_pos.x < _LongHairCreatepos.x)
						at->PlayAnimation(L"Long_hairMeteor_Cross02_Landing", false);
					else
						at->PlayAnimation(L"Long_hairMeteor_Cross02_LandingR", false);
					tr->SetRotationZ(0.f);
					_SistersAttack_C_LongHair_LAND = true;
				}
			}
		}
		if (Back_ground* mGround = dynamic_cast<Back_ground*>(other->GetOwner()))
		{
			if (_BackGround_check == false)
			{
				_rigidbody->SetGround(true);
				_BackGround_check = true;		
				_BackGround_Switch = false;
				_rigidbody->ClearVelocity();
			}
			else
			{
				if (Background_state == Layana_Long_Background::BackGround_Enter)
				{					
					if(_BackGround_Idle == false)
					_BackGround_Idle = true;
				}
			}
		}
	}
	void Layana_LongHair::OnCollisionExit(Collider2D* other)
	{
	}	

	
	void Layana_LongHair::idle()
	{
		_time += Time::DeltaTime();
		_SelectAttack = random(0, 6);
		_SelectAttack = 0;


		if (_Intro_On == true)
			Intro_Combo();

		if (ShortHair_Operation == true)
		{
			if(LongHair_First_moving==false)
			BackGround_Combo();
			_time = 0;			
		}

		if (LongHair_Operation == true)
		{			
			if (LongHair_First_moving == true)
			{
				Meteor_Vertical_Combo();
				LongHair_First_moving = false;
			}
			else
			{
				if (_SistersAttack_Number > 5)
				{
					_Joint_Attack = true;
					_LongHair_state = Layana_LongHair_State::FlyDash;
					if (_pos.x > _LongHairCreatepos.x)
						at->PlayAnimation(L"Long_hairDash", true);
					else
						at->PlayAnimation(L"Long_hairDashR", true);
				}
				else
				{
					if (_time >= 2.0)
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
							Skill_A_Combo();
						if (_SelectAttack == 5)
							Skill_B_Combo();
						if (_SelectAttack == 6)
							Skill_C_Combo();
						if (_SelectAttack == 7)
							BackGround_Combo();


						if (_SelectAttack == 9)
							Awaken_Combo();

						if (_SelectAttack == 10)
							Intro_Combo();
						_SistersAttack_Number++;
					}
				}
			}
		}
	}


	void Layana_LongHair::Intro_Dash()
	{
		_Attacktime += Time::DeltaTime();
		if (_Attacktime > 1.5 && _Attacktime < 2)
		{
			_rigidbody->ClearVelocity();
			_rigidbody->SetGround(false);
			_pos = Vector3(_LongHairCreatepos.x + 200, _LongHairCreatepos.y - 50, _LongHairCreatepos.z);

			at->PlayAnimation(L"Long_hairIntro_Fall", false);
			_Intro_Fall_LongHair = true;
			_Ground_check = false;
		}
	}
	void Layana_LongHair::Intro_Fall()
	{
		if (_Intro_Landing == true)
		{
			at->PlayAnimation(L"Long_hairIntro_LandingR", true);
			_Intro_Land_LongHair = true;
		}
	}
	void Layana_LongHair::Intro_Landing()
	{	
	}
	void Layana_LongHair::Intro_Landing_End()
	{
		if (_Intro_LongHair_END == true)
		{
			_Sisters_Attack_A_Switch = true;
			_SistersAttack_A_IntroReady_LongHair = true;
			at->PlayAnimation(L"Long_hairDash", true);
			_Intro_LongHair_END = false;

			Transform* SM_Effect = Dash_SM->GetComponent<Transform>();
			SM_Effect->SetPosition(Vector3(_pos.x - 30, _pos.y - 40, _pos.z - 1));
			Dash_SM->SetDirection(1);
			Dash_SM->SetSwitch(true);
			Dash_SM->SetState(eState::Active);
		}
	}


	void Layana_LongHair::Sisters_Attack_Set()
	{		
		if (_pos.x > _LongHairCreatepos.x)
		{
			at->PlayAnimation(L"Long_hairDash", true);

			Transform* SM_Effect = Dash_SM->GetComponent<Transform>();
			SM_Effect->SetPosition(Vector3(_pos.x - 30, _pos.y - 40, _pos.z - 1));
			Dash_SM->SetDirection(1);
			Dash_SM->SetSwitch(true);
			Dash_SM->SetState(eState::Active);
		}
		else
		{
			at->PlayAnimation(L"Long_hairDashR", true);
		
			Transform* SM_Effect = Dash_SM->GetComponent<Transform>();
			SM_Effect->SetPosition(Vector3(_pos.x + 30, _pos.y - 40, _pos.z - 1));
			Dash_SM->SetDirection(-1);
			Dash_SM->SetSwitch(true);
			Dash_SM->SetState(eState::Active);
		}
		_AttackStageON = true;
		_SistersAttack_Set_LongHair = true;
	}
	void Layana_LongHair::Sisters_Attack_FlyDash()
	{
		_Sisters_Attack_A = _Sisters_Attack_A_Switch;
		_Sisters_Attack_B = _Sisters_Attack_B_Switch;

		if (_AttackStageON == true)
		{
			if (_pos.x < _LongHairCreatepos.x )
			{
				if (_pos.x > _LongHairCreatepos.x - 600)
					_pos.x -= 750.f * Time::DeltaTime();
				if (_pos.y < 100)
					_pos.y += 150.f * Time::DeltaTime();
			}
			else
			{
				if (_pos.x < _LongHairCreatepos.x + 600)
					_pos.x += 750.f * Time::DeltaTime();
				if (_pos.y < 100)
					_pos.y += 150.f * Time::DeltaTime();
			}
			if (_pos.y >=  100.f)
				_AttackStageON = false;
		}
		else
		{
			//if (LongHair_First_moving == true && ShortHair_First_moving == true)			
			if (_Sisters_Attack_C_Switch == true)
			{
				if (_SistersAttack_C_Ready_LongHair == false)
				{
					if (_pos.x >= 0)
					{
						Transform* bullte_effect = TwinMeteor_BossEffect->GetComponent<Transform>();
						bullte_effect->SetPosition(Vector3(_LongHairCreatepos.x + 50, _pos.y - 200, -205));
						float angle = 30;
						float angleInDegrees = angle * (180.0f / XM_PI);
						bullte_effect->SetRotationZ(angleInDegrees);
						TwinMeteor_BossEffect->SetState(eState::Active);
						_SistersAttack_C_Ready_LongHair = true;
					}
					else
					{
						Transform* bullte_effect = TwinMeteor_BossEffect->GetComponent<Transform>();
						bullte_effect->SetPosition(Vector3(_LongHairCreatepos.x - 50, _pos.y - 200, -205));
						float angle = -30;
						float angleInDegrees = angle * (180.0f / XM_PI);
						bullte_effect->SetRotationZ(angleInDegrees);
						TwinMeteor_BossEffect->SetState(eState::Active);
						_SistersAttack_C_Ready_LongHair = true;
					}
				}
				else
				{
					_Attacktime += Time::DeltaTime();
					if (_Attacktime > 1.5)
					{
						TwinMeteor_BossEffect->SetState(eState::Paused);
						if (_pos.x < _LongHairCreatepos.x)
						{							
							_pos = Vector3(-640.f, _pos.y, _pos.z);
							tr->SetPosition(_pos);
							float angle = -210;
							float angleInDegrees = angle * (180.f / XM_PI);
							at->PlayAnimation(L"Long_hairMeteor_Ground02_Attack", true);
							tr->SetRotationZ(angleInDegrees);
							_rigidbody->SetVelocity(Vector2(1200.f, -150.f));
							_rigidbody->SetGround(false);
							_Ground_check = false;
							{
								Transform* bullte_effect = TwinMeteor_Impact->GetComponent<Transform>();
								bullte_effect->SetPosition(Vector3(_LongHairCreatepos.x - 50, _pos.y - 215, -205));
								float angle = -30;
								float angleInDegrees = angle * (180.f / XM_PI);
								bullte_effect->SetRotationZ(angleInDegrees);
								TwinMeteor_Impact->SetState(eState::Active);							
							}
							_SistersAttack_C_DashOn_LongHair = true;
						}
						else
						{							
							_pos = Vector3(640.f, _pos.y, _pos.z);
							tr->SetPosition(_pos);
							float angle = -210;
							float angleInDegrees = angle * (180.f / XM_PI);
							at->PlayAnimation(L"Long_hairMeteor_Ground02_AttackR", true);
							tr->SetRotationZ(angleInDegrees);
							_rigidbody->SetVelocity(Vector2(-1200.f, -150.f));
							_rigidbody->SetGround(false);
							_Ground_check = false;			
							{
								Transform* bullte_effect = TwinMeteor_Impact->GetComponent<Transform>();
								bullte_effect->SetPosition(Vector3(_LongHairCreatepos.x + 50, _pos.y - 215, -205));
								float angle = 30;
								float angleInDegrees = angle * (180.f / XM_PI);
								bullte_effect->SetRotationZ(angleInDegrees);
								TwinMeteor_Impact->SetState(eState::Active);
							}
							_SistersAttack_C_DashOn_LongHair = true;
						}
					}
				}
			}
			else
			{
				_SistersAttack_FlyDash_LongHair = true;
				_Ground_check = false;
				_rigidbody->SetGround(false);
				if (_pos.x < _LongHairCreatepos.x)
				{
					_rigidbody->SetVelocity(Vector2(700.f, -350.f));
					at->PlayAnimation(L"Long_hairDash", true);
					_HitBox_Dir = 1;
				}
				else
				{
					_rigidbody->SetVelocity(Vector2(-700.f, -350.f));
					at->PlayAnimation(L"Long_hairDashR", true);
					_HitBox_Dir = -1;
				}
			}
		}
	}
	void Layana_LongHair::Sisters_Attack_Fall()
	{
		if (_Sisters_Attack_A == false)
		{
			_Attacktime += Time::DeltaTime();
			if (_Attacktime > 0.3)
			{
				_SistersAttack_A_Ready_LongHair = true;
				_Attacktime = 0;
			}
		}
	}


	void Layana_LongHair::Sisters_Attack_A_Ready()
	{
		_Sisters_Attack_A_Switch = true;
		_SistersAttack_A_IntroReady_LongHair = true;		
		if (_pos.x > _LongHairCreatepos.x)
			at->PlayAnimation(L"Long_hairDash", true);
		else
			at->PlayAnimation(L"Long_hairDashR", true);
	}
	void Layana_LongHair::Sisters_Attack_A_LandingDash()
	{
		if (_SistersAttack_A_DashOn == true)
		{
			_Attacktime += Time::DeltaTime();
			if (_Attacktime >= 1.f)
			{
				if (_pos.x < _LongHairCreatepos.x)
				{
					at->PlayAnimation(L"Long_hairMeteor_Ground02_Attack", false);
					_rigidbody->SetVelocity(Vector2(900.f, 0.f));
					_GroundMeteorAttack_Right = true;

					Transform* SM_Effect = MeteorGR_SM->GetComponent<Transform>();
					SM_Effect->SetPosition(Vector3(_pos.x-100, _pos.y - 30, _pos.z-1));
					MeteorGR_SM->SetDirection(1);
					MeteorGR_SM->SetSwitch(true);
					MeteorGR_SM->SetState(eState::Active);
				}
				else
				{
					at->PlayAnimation(L"Long_hairMeteor_Ground02_AttackR", false);
					_rigidbody->SetVelocity(Vector2(-900.f, 0.f));
					_GroundMeteorAttack_Left = true;

					Transform* SM_Effect = MeteorGR_SM->GetComponent<Transform>();
					SM_Effect->SetPosition(Vector3(_pos.x+100, _pos.y - 30, _pos.z-1));
					MeteorGR_SM->SetDirection(-1);
					MeteorGR_SM->SetSwitch(true);
					MeteorGR_SM->SetState(eState::Active);
				}
				_Attacktime = 0;
				_SistersAttack_A_DashOn_LongHair = true;
			}
		}
	}
	void Layana_LongHair::Sisters_Attack_A()
	{
		_HitBox_Attack_On = true;
		if (_GroundMeteorAttack_Right == true)
		{
			if (_pos.x >= _LongHairCreatepos.x + 312)
			{
				_rigidbody->ClearVelocity();
				_GroundMeteorAttack_Right = false;				
				if (_pos.x > _LongHairCreatepos.x)
					at->PlayAnimation(L"Long_hairMeteor_Ground03_Landing", false);
				else
					at->PlayAnimation(L"Long_hairMeteor_Ground03_LandingR", false);			
				_SistersAttack_A_LongHair_END = true;
				_HitBox_Attack_On = false;
			}
		}
		if (_GroundMeteorAttack_Left == true)
		{
			if (_pos.x <= _LongHairCreatepos.x - 312)
			{
				_rigidbody->ClearVelocity();
				_GroundMeteorAttack_Left = false;				
				if (_pos.x > _LongHairCreatepos.x)
					at->PlayAnimation(L"Long_hairMeteor_Ground03_Landing", false);
				else
					at->PlayAnimation(L"Long_hairMeteor_Ground03_LandingR", false);		
				_SistersAttack_A_LongHair_END = true;
				_HitBox_Attack_On = false;
			}			
		}
	}
	void Layana_LongHair::Sisters_Attack_A_End()
	{
		if (_SistersAttack_A_LongHair_END == true)
		{
			if (_pos.x > _LongHairCreatepos.x)
				at->PlayAnimation(L"Long_hairMeteor_Ground04_End", false);
			else
				at->PlayAnimation(L"Long_hairMeteor_Ground04_EndR", false);
			_SistersAttack_A_LongHair_END = false;			
			_SistersAttack_A_Ready_LongHair = false;
			_HitBox_Attack_On = false;
		}
	}


	void Layana_LongHair::Sisters_Attack_B_Ready()
	{
		_SkillHomingON = false;
	}
	void Layana_LongHair::Sisters_Attack_B_BulletCreate()
	{
		if (_SkillHomingON == false)
			CreateHoming();
		else
		{
			_Attacktime += Time::DeltaTime();
			if (_SkillHomingFire == false)
			{
				if (_Dir == 1)
				{
					bullet_tr1->SetPosition(Vector3(_pos.x + 85, _pos.y + -50, -255));
					bullet_tr2->SetPosition(Vector3(_pos.x + 70, _pos.y, -255));
					bullet_tr3->SetPosition(Vector3(_pos.x + 55, _pos.y + 50, -255));
				}
				else
				{
					bullet_tr1->SetPosition(Vector3(_pos.x - 85, _pos.y + -50, -255));
					bullet_tr2->SetPosition(Vector3(_pos.x - 70, _pos.y, -255));
					bullet_tr3->SetPosition(Vector3(_pos.x - 55, _pos.y + 50, -255));
				}
			}
			if (_Attacktime > 1.f)
			{
				_SistersAttack_B_BulletOn_LongHair = true;
				if (_Dir == 1)
					at->PlayAnimation(L"Long_hairSkill_A_Bullet", false);
				else
					at->PlayAnimation(L"Long_hairSkill_A_BulletR", false);
				_Bullet_Switch[0] = false;
				_Bullet_Switch[1] = false;
				_Bullet_Switch[2] = false;
			}
		}
	}
	void Layana_LongHair::Sisters_Attack_B()
	{
		_Attacktime += Time::DeltaTime();

		if (_Attacktime < 5)
		{
			_SkillHomingFire = true;
			if (_Attacktime < 1.5)
				SettingHoming(bullet_tr1, 0);
			if (_Attacktime < 2)
				SettingHoming(bullet_tr2, 1);
			if (_Attacktime < 2.5)
				SettingHoming(bullet_tr3, 2);

			if (_Attacktime >= 1.5 && _Attacktime < 2)
			{
				if (_Bullet_Switch[0] == false)
				{
					bullet_rb1->SetGround(false);
					bullet_rb1->SetGravity(true);
					bullet_rb1->SetFriction(true);				
					bullet_rb1->SetVelocity(Vector2(_HomingVector[0].x * 750, _HomingVector[0].y * 750));
					Vector2 vel = bullet_rb1->GetVelocity();
					_Bullet_Switch[0] = true;
				}
			}
			if (_Attacktime >= 2 && _Attacktime < 2.5)
			{
				if (_Bullet_Switch[1] == false)
				{
					bullet_rb2->SetGround(false);
					bullet_rb2->SetGravity(true);
					bullet_rb2->SetFriction(true);
					bullet_rb2->SetVelocity(Vector2(_HomingVector[1].x * 750, _HomingVector[1].y * 750));
					Vector2 vel = bullet_rb2->GetVelocity();
					_Bullet_Switch[1] = true;
				}
			}
			if (_Attacktime >= 2.5 && _Attacktime < 3)
			{
				if (_Bullet_Switch[2] == false)
				{
					bullet_rb3->SetGround(false);
					bullet_rb3->SetGravity(true);
					bullet_rb3->SetFriction(true);
					bullet_rb3->SetVelocity(Vector2(_HomingVector[2].x * 750, _HomingVector[2].y * 750));
					Vector2 vel = bullet_rb3->GetVelocity();
					_Bullet_Switch[2] = true;
				}
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				RigidBody* bullet_rb1 = Homing[0]->GetComponent<RigidBody>();
				RigidBody* bullet_rb2 = Homing[1]->GetComponent<RigidBody>();
				RigidBody* bullet_rb3 = Homing[2]->GetComponent<RigidBody>();
				bullet_rb1->ClearVelocity();
				bullet_rb1->SetGravity(false);
				bullet_rb1->SetFriction(false);
				bullet_rb1->SetGround(true);

				bullet_rb2->ClearVelocity();
				bullet_rb1->SetGravity(false);
				bullet_rb2->SetFriction(false);
				bullet_rb2->SetGround(true);

				bullet_rb3->ClearVelocity();
				bullet_rb3->SetGravity(false);
				bullet_rb3->SetFriction(false);
				bullet_rb3->SetGround(true);
				_Attacktime = 0;
				Homing[i]->SetState(eState::Paused);	
				_Bullet_Switch[i] = false;
			}

			_SistersAttack_B_LongHair_END = true;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairSkill_A_Bullet_End", false);
			else
				at->PlayAnimation(L"Long_hairSkill_A_Bullet_EndR", false);			
		}
	}
	void Layana_LongHair::Sisters_Attack_B_End()
	{
		_Sisters_Attack_B_Switch = false;
		_SkillHomingON = false;
		_HomingNumber = 0;
		_Attacktime = 0.f;
	}


	void Layana_LongHair::Sisters_Attack_C_Ready()
	{
		_AttackStageON = true;
		_Sisters_Attack_C_Switch = true;
		if (_pos.x > _LongHairCreatepos.x)
			at->PlayAnimation(L"Long_hairDash", true);
		else
			at->PlayAnimation(L"Long_hairDashR", true);
		_SistersAttack_C_IntroReady_LongHair = true;
	}
	void Layana_LongHair::Sisters_Attack_C()
	{
	}
	void Layana_LongHair::Sisters_Attack_C_Landing()
	{
		if (_SistersAttack_C_LongHair_LAND == true)
		{
			{
				if (_Dir == 1)
					at->PlayAnimation(L"Long_hairMeteor_Cross03_End", false);
				else
					at->PlayAnimation(L"Long_hairMeteor_Cross03_EndR", false);

				_Attacktime = 0;
				_SistersAttack_C_LongHair_LAND = false;
			}
		}
	}
	void Layana_LongHair::Sisters_Attack_C_End()
	{
		Transform* bullte_effect = TwinMeteor_BossEffect->GetComponent<Transform>();
		Transform* bullte_imffect = TwinMeteor_Impact->GetComponent<Transform>();
		bullte_effect->SetRotationZ(0);
		bullte_imffect->SetRotationZ(0);
		_AttackStageON = false;
		_Sisters_Attack_C_Switch = false;
	}


	void Layana_LongHair::Sisters_Attack_D()
	{
	}


	//대쉬
	void Layana_LongHair::Dash()
	{
		if (!(_Playerdistance.x <= 80 && _Playerdistance.x >= -80))
		{
			if (_Dir == 1)
				_pos.x += 350.f * Time::DeltaTime();
			else
				_pos.x -= 350.f * Time::DeltaTime();
		}
		else
		{
			if (_RushSwitch == true)
			{				
				_LongHair_state = Layana_LongHair_State::Rush_Ready;
				if (_Dir == 1)
					at->PlayAnimation(L"Long_hairRush_Ready", true);
				else
					at->PlayAnimation(L"Long_hairRush_ReadyR", true);
			}
			if (_CrossMeteorSwitch == true)
			{
				_LongHair_state = Layana_LongHair_State::Meteor_Cross_Jump;
				if (_Dir == 1)
				{
					at->PlayAnimation(L"Long_hairMeteor_Cross00_JumpR", false);
					_rigidbody->SetVelocity(Vector2(250.f, 450.f));
					_rigidbody->SetGround(false);
				}
				else
				{
					at->PlayAnimation(L"Long_hairMeteor_Cross00_Jump", false);
					_rigidbody->SetVelocity(Vector2(-250.f, 450.f));
					_rigidbody->SetGround(false);
				}
			}
		}
	}
	void Layana_LongHair::FlyDash()
	{	
		if (_pos.x < _LongHairCreatepos.x)
		{
			if (_pos.x > _LongHairCreatepos.x - 600)
				_pos.x -= 750.f * Time::DeltaTime();
			if (_pos.y < 100)
				_pos.y += 150.f * Time::DeltaTime();
		}
		else
		{
			if (_pos.x < _LongHairCreatepos.x + 600)
				_pos.x += 750.f * Time::DeltaTime();
			if (_pos.y < 100)
				_pos.y += 150.f * Time::DeltaTime();
		}
		if (_pos.y >= 100.f)
		{			
			if (_GroundMeteorSwitch == true)
			{
				_LongHair_state = Layana_LongHair_State::LandingDash;
				_Ground_check = false;
				_rigidbody->SetGround(false);
				if (_pos.x < _LongHairCreatepos.x)
				{
					_rigidbody->SetVelocity(Vector2(900.f, -350.f));
					at->PlayAnimation(L"Long_hairDash", true);
					_HitBox_Dir = 1;
				}
				else
				{
					_rigidbody->SetVelocity(Vector2(-900.f, -350.f));
					at->PlayAnimation(L"Long_hairDashR", true);
					_HitBox_Dir = -1;
				}
			}
			if (_VerticalMeteorSwitch == true)
			{		
				_LongHair_state = Layana_LongHair_State::Meteor_Vertical_Jump;
				_Ground_check = false;
				_pos.x = _Playerpos.x;
				at->PlayAnimation(L"Long_hairMeteor_Vertical00_Jump", true);
			}

			if (_BackGround_Switch == true)
			{
				_pos = Vector3(_LongHairCreatepos.x + 50, _LongHairCreatepos.y + 100, -150.f);
				tr->SetPosition(_pos);
				at->PlayAnimation(L"Long_hairBackGround_Move", false);
				Background_state = Layana_Long_Background::BackGround_Enter;
				_rigidbody->SetGround(false);
				_Ground_check = false;
				_BackGround_check = false;
				_BackGround_Switch = false;
			}		
			if (_Joint_Attack == true)
			{
				_rigidbody->SetGround(true);
				_Ground_check = false;			
				_BackGround_check = true;
				LongHair_First_moving = true;
				_Joint_Attack = false;
			}
		}
	}
	void Layana_LongHair::LandingDash()
	{
		_Attacktime += Time::DeltaTime();
		if (_GroundMeteorLanding == true)
		{
			if (_Attacktime >= 1.f)
			{
				_LongHair_state = Layana_LongHair_State::Meteor_Ground_Attack;

				if (_Dir == 1)
				{
					at->PlayAnimation(L"Long_hairMeteor_Ground02_Attack", true);
					_rigidbody->SetVelocity(Vector2(900.f, 0.f));
					_GroundMeteorAttack_Right = true;

					Transform* SM_Effect = MeteorGR_SM->GetComponent<Transform>();
					SM_Effect->SetPosition(Vector3(_pos.x + 100, _pos.y - 30, _pos.z - 1));
					MeteorGR_SM->SetDirection(-1);
					MeteorGR_SM->SetSwitch(true);
					MeteorGR_SM->SetState(eState::Active);
				}
				else
				{
					at->PlayAnimation(L"Long_hairMeteor_Ground02_AttackR", true);
					_rigidbody->SetVelocity(Vector2(-900.f, 0.f));
					_GroundMeteorAttack_Left = true;

					Transform* SM_Effect = MeteorGR_SM->GetComponent<Transform>();
					SM_Effect->SetPosition(Vector3(_pos.x + 100, _pos.y - 30, _pos.z - 1));
					MeteorGR_SM->SetDirection(-1);
					MeteorGR_SM->SetSwitch(true);
					MeteorGR_SM->SetState(eState::Active);
				}
				_Attacktime = 0;
			}
		}
	}
	void Layana_LongHair::BackStep()
	{
		//백스텝을 시작으로 뷸렛 시작 코드
		//_Ground_check = false;
		//if (_SkillA_Switch == true)
		//	_state = _state = Layana_Sisters_State::Skill_A_Bullet_Ready;		
		// 이부분이후로 아이들로 가져가면 진행됨
		//	_state = Layana_Sisters_State::BackStep;
		//	_rigidbody->SetGround(false);
		//	if (_Dir == 1)
		//	{
		//		at->PlayAnimation(L"Long_hairBackStepR", true);
		//		_rigidbody->SetVelocity(Vector2(350.f, 250.f));					
		//	}
		//	else
		//	{
		//		at->PlayAnimation(L"Long_hairBackStep", true);
		//		_rigidbody->SetVelocity(Vector2(-350.f, 250.f));								
		//	}									
		//}
	}


	void Layana_LongHair::Rushready()
	{		
	}
	void Layana_LongHair::Rush_A()
	{
	}
	void Layana_LongHair::Rush_B()
	{
	}
	void Layana_LongHair::Rush_C()
	{
	}
	void Layana_LongHair::Rush_C1()
	{
	}
	void Layana_LongHair::Rush_C2()
	{
	}
	void Layana_LongHair::Rush_C3()
	{
	}
	void Layana_LongHair::Rush_C4()
	{
	}
	void Layana_LongHair::Rush_End()
	{
		_RushSwitch = false;
	}


	void Layana_LongHair::CrossJump()
	{	
		if (_velocity.y <= -0.1f)
		{
			_rigidbody->ClearVelocity();
			_rigidbody->SetGround(true);

			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairMeteor_Cross01_Ready", true);			
			else
				at->PlayAnimation(L"Long_hairMeteor_Cross01_ReadyR", true);
			_LongHair_state = Layana_LongHair_State::Meteor_Cross_Ready;
			_Ground_check = false;
		}
	}
	void Layana_LongHair::CrossReady()
	{	
	}
	void Layana_LongHair::CrossAttack()
	{
		//몸뚱이 회전
		{		
			if (_Playerpos.x >= _pos.x)
			{	
				at->PlayAnimation(L"Long_hairMeteor_Cross04_AttackR", false);
				float angle = 45 / (180.0f / XM_PI);
				tr->SetRotationZ(angle);
				_HitBox_Dir = 1;
			}
			else
			{
				at->PlayAnimation(L"Long_hairMeteor_Cross04_AttackR", false);
				float angle = -45 / (180.0f / XM_PI);
				tr->SetRotationZ(angle);
				_HitBox_Dir = -1;
			}		
		}
		//몸땡이 발사
		{				
			_HitBox_Attack_On = true;
			Vector2 attack_pos = Vector2(_Playerpos.x - _pos.x, _Playerpos.y - _pos.y);
			attack_pos.Normalize();
			_rigidbody->SetGround(false);
			_rigidbody->SetVelocity(Vector2(attack_pos.x * 500.f, attack_pos.y * 500));
			_LongHair_state = Layana_LongHair_State::Meteor_Cross_Landing;		
		}

	}
	void Layana_LongHair::CrossLanding()
	{
		if (_CrossMeteorLanding == true)
			Complete_CrossLanding();
	}
	void Layana_LongHair::CrossEnd()
	{
	}


	void Layana_LongHair::GroundReady()
	{
	}
	void Layana_LongHair::GroundAttack()
	{
		_HitBox_Attack_On = true;
		if (_GroundMeteorAttack_Right == true)
		{			
			if (_pos.x >= _LongHairCreatepos.x + 312)
			{
				_rigidbody->ClearVelocity();
				_GroundMeteorAttack_Right = false;
				_LongHair_state = Layana_LongHair_State::Meteor_Ground_End;
				if (_Dir == 1)
					at->PlayAnimation(L"Long_hairMeteor_Ground04_End", true);					
				else
					at->PlayAnimation(L"Long_hairMeteor_Ground04_EndR", true);
				_HitBox_Attack_On = false;
			}
		}
		if (_GroundMeteorAttack_Left == true)
		{	
			if (_pos.x <= _LongHairCreatepos.x - 312)
			{
				_rigidbody->ClearVelocity();
				_GroundMeteorAttack_Left = false;
				_LongHair_state = Layana_LongHair_State::Meteor_Ground_End;
				if (_Dir == 1)
					at->PlayAnimation(L"Long_hairMeteor_Ground04_End", true);
				else
					at->PlayAnimation(L"Long_hairMeteor_Ground04_EndR", true);
				_HitBox_Attack_On = false;
			}
		}			
	}
	void Layana_LongHair::GroundLanding()
	{
	}
	void Layana_LongHair::GroundEnd()
	{
	}


	void Layana_LongHair::Vertical_Jump()
	{
	}
	void Layana_LongHair::Vertical_Ready()
	{
	}
	void Layana_LongHair::Vertical_Attack()
	{		
	}
	void Layana_LongHair::Vertical_Landing()
	{
		_HitBox_Attack_On = true;
		_Attacktime += Time::DeltaTime();
		if (_VerticalMeteorLandingSM == true)
		{
			if (_Dir == 1)
			{
				Intro_SM->SetState(eState::Active);
				Intro_SM->SetSwitch(true);
				Transform* SMtr = Intro_SM->GetComponent<Transform>();
				SMtr->SetPosition(_pos.x + 20, _pos.y - 50.f, _pos.z - 1);
			}
			else
			{
				Intro_SM->SetState(eState::Active);
				Intro_SM->SetSwitch(true);
				Transform* SMtr = Intro_SM->GetComponent<Transform>();
				SMtr->SetPosition(_pos.x - 20, _pos.y - 50.f, _pos.z - 1);
			}
			_VerticalMeteorLandingSM = false;
		}
		if (_VerticalMeteorLanding == true)
		{
			_HitBox_Attack_On = false;
			if (_Attacktime >= 1.f)
			{
				_LongHair_state = Layana_LongHair_State::Meteor_Vertical_End;

				if (_Dir == 1)
					at->PlayAnimation(L"Long_hairMeteor_Vertical04_End", true);				
				else			
					at->PlayAnimation(L"Long_hairMeteor_Vertical04_EndR", true);
				_Attacktime = 0;
				_HitBox_Attack_On = false;
			}
		}
	}
	void Layana_LongHair::Vertical_End()
	{
	}


	void Layana_LongHair::Skill_A_Ready()
	{		
		if (_SkillHomingON == false)
			CreateHoming();
		else
		{
			_Attacktime += Time::DeltaTime();
			if (_SkillHomingFire == false)
			{
				if (_Dir == 1)
				{
					bullet_tr1->SetPosition(Vector3(_pos.x + 85, _pos.y + -50, -255));
					bullet_tr2->SetPosition(Vector3(_pos.x + 70, _pos.y, -255));
					bullet_tr3->SetPosition(Vector3(_pos.x + 55, _pos.y + 50, -255));
				}
				else
				{
					bullet_tr1->SetPosition(Vector3(_pos.x - 85, _pos.y + -50, -255));
					bullet_tr2->SetPosition(Vector3(_pos.x - 70, _pos.y, -255));
					bullet_tr3->SetPosition(Vector3(_pos.x - 55, _pos.y + 50, -255));
				}
			}
			if (_Attacktime > 1.f)
			{
				_LongHair_state = Layana_LongHair_State::Skill_A_Bullet;
				if (_Dir == 1)
					at->PlayAnimation(L"Long_hairSkill_A_Bullet", false);
				else
					at->PlayAnimation(L"Long_hairSkill_A_BulletR", false);
				_Bullet_Switch[0] = false;
				_Bullet_Switch[1] = false;
				_Bullet_Switch[2] = false;
			}
		}

	}
	void Layana_LongHair::Skill_A()
	{		
		_Attacktime += Time::DeltaTime();

		if (_Attacktime < 5)
		{
			_SkillHomingFire = true;
			if (_Attacktime < 1.5)
				SettingHoming(bullet_tr1, 0);
			if (_Attacktime < 2)
				SettingHoming(bullet_tr2, 1);
			if (_Attacktime < 2.5)
				SettingHoming(bullet_tr3, 2);

			if (_Attacktime >= 1.5 && _Attacktime < 2)
			{
				if (_Bullet_Switch[0] == false)
				{
					bullet_rb1->SetGround(false);
					bullet_rb1->SetGravity(true);
					bullet_rb1->SetFriction(true);
					bullet_rb1->SetVelocity(Vector2(_HomingVector[0].x * 750, _HomingVector[0].y * 750));
					Vector2 vel = bullet_rb1->GetVelocity();
					_Bullet_Switch[0] = true;
				}
			}
			if (_Attacktime >= 2 && _Attacktime < 2.5)
			{
				if (_Bullet_Switch[1] == false)
				{
					bullet_rb2->SetGround(false);
					bullet_rb2->SetGravity(true);
					bullet_rb2->SetFriction(true);
					bullet_rb2->SetVelocity(Vector2(_HomingVector[1].x * 750, _HomingVector[1].y * 750));
					Vector2 vel = bullet_rb2->GetVelocity();
					_Bullet_Switch[1] = true;
				}
			}
			if (_Attacktime >= 2.5 && _Attacktime < 3)
			{
				if (_Bullet_Switch[2] == false)
				{
					bullet_rb3->SetGround(false);
					bullet_rb3->SetGravity(true);
					bullet_rb3->SetFriction(true);
					bullet_rb3->SetVelocity(Vector2(_HomingVector[2].x * 750, _HomingVector[2].y * 750));
					Vector2 vel = bullet_rb3->GetVelocity();
					_Bullet_Switch[2] = true;
				}
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				RigidBody* bullet_rb1 = Homing[0]->GetComponent<RigidBody>();
				RigidBody* bullet_rb2 = Homing[1]->GetComponent<RigidBody>();
				RigidBody* bullet_rb3 = Homing[2]->GetComponent<RigidBody>();
				bullet_rb1->ClearVelocity();
				bullet_rb1->SetGravity(false);
				bullet_rb1->SetFriction(false);
				bullet_rb1->SetGround(true);

				bullet_rb2->ClearVelocity();
				bullet_rb1->SetGravity(false);
				bullet_rb2->SetFriction(false);
				bullet_rb2->SetGround(true);

				bullet_rb3->ClearVelocity();
				bullet_rb3->SetGravity(false);
				bullet_rb3->SetFriction(false);
				bullet_rb3->SetGround(true);
				_Attacktime = 0;
				Homing[i]->SetState(eState::Paused);
				_Bullet_Switch[i] = false;
			}

			_LongHair_state = Layana_LongHair_State::Skill_A_Bullet_End;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairSkill_A_Bullet_End", true);
			else
				at->PlayAnimation(L"Long_hairSkill_A_Bullet_EndR", true);
		}


	}
	void Layana_LongHair::Skill_A_End()
	{
		_HomingNumber = 0;
		_Attacktime = 0.f;
	}


	void Layana_LongHair::Skill_B()
	{
		static float editpos = 20;
		static int lastActivatedIndex = 0;
		if (_SkillB_Switch == false)
		{
			_Attacktime += Time::DeltaTime();
			if (_Attacktime >= 0.8 && _Attacktime <= 1)
			{
				Risingbullet_tr[0]->SetPosition(Vector3(_pos.x, _pos.y + 35, -250));
				Rising[0]->SetState(eState::Active);
			}
			if (_Attacktime <= 5)
			{
				for (int i = lastActivatedIndex; i < 9; i++)
				{
					// 0.5초마다 하나씩 처리
					if (_Attacktime >= (1.0f + 0.2f * i))
					{
						Risingbullet_tr[i + 1]->SetPosition(Vector3(_pos.x + editpos, _pos.y + 35, -255));
						Rising[i + 1]->SetState(eState::Active);

						Risingbullet_tr[i + 10]->SetPosition(Vector3(_pos.x - editpos, _pos.y + 35, -255));
						Rising[i + 10]->SetState(eState::Active);

						editpos += 25;
						lastActivatedIndex = i + 1; 
						continue; 
					}
				}
			}
			else
			{
				_SkillB_Switch = true;
				_LongHair_state = Layana_LongHair_State::Skill_B_RisingPierce_End;
				if (_Dir == 1)
					at->PlayAnimation(L"Long_hairSkill_B_RisingPierce_End", true);
				else
					at->PlayAnimation(L"Long_hairSkill_B_RisingPierce_EndR", true);
				_Attacktime = 0;
				editpos = 20;
				lastActivatedIndex = 0;
			}
		}				
	}
	void Layana_LongHair::Skill_B_End()
	{
	}


	void Layana_LongHair::Skill_C()
	{
		if (_SkillC_Switch == false)
		{
			{
				Transform* boss_effect = Dimension_boss_effect->GetComponent<Transform>();
				boss_effect->SetPosition(Vector3(_pos.x, _pos.y - 10, -250));
				Dimension_boss_effect->SetState(eState::Active);
				Dimension_boss_effect->_SwitchOn = true;
				if (_Dir == 1)
					Dimension_boss_effect->SetDirection(1);
				else
					Dimension_boss_effect->SetDirection(-1);
			}
			{
				Transform* boss_bullet = Dimension_Bullet->GetComponent<Transform>();
				Dimension_Bullet->_effect_switch = true;
				int Setrotation = random(1, 2);				
				if (_Dir == 1)
				{					
					Dimension_Bullet->SetDirection(1);
					float anglew = 0.f;
					if (Setrotation == 1)
					{						
						int setangle = random(295, 335);
						float anglew = setangle / (180.0f / XM_PI);
						boss_bullet->SetRotationZ(anglew);
						boss_bullet->SetPosition(Vector3(_Playerpos.x, _Playerpos.y + 25, -250));
					}
					else
					{						
						int setangle = random(25, 65);
						float anglew = setangle / (180.0f / XM_PI);
						boss_bullet->SetRotationZ(anglew);
						boss_bullet->SetPosition(Vector3(_Playerpos.x, _Playerpos.y - 25, -250));
					}					
					Dimension_Bullet->SetState(eState::Active);
				}		
				else
				{					
					Dimension_Bullet->SetDirection(-1);
					if (Setrotation == 1)
					{
						int setangle = random(-335, -295);						
						float anglew = setangle / (180.0f / XM_PI);
						boss_bullet->SetRotationZ(anglew);
						boss_bullet->SetPosition(Vector3(_Playerpos.x, _Playerpos.y + 25, -250));
					}
					else
					{					
						int setangle = random(-65, -25);							
						float anglew = setangle / (180.0f / XM_PI);
						boss_bullet->SetRotationZ(anglew);
						boss_bullet->SetPosition(Vector3(_Playerpos.x, _Playerpos.y - 25, -250));
					}				
					Dimension_Bullet->SetState(eState::Active);
				}				
			}
			_SkillC_Switch = true;
		}
		else
		{
			_Attacktime += Time::DeltaTime();

			if (_Attacktime >= 0.5 && _Attacktime < 1.0)
			{
				Transform* boss_bullet = Dimension_Bullet->GetComponent<Transform>();
				Transform* boss_effect = Dimension_BulletEffect->GetComponent<Transform>();
				boss_effect->SetPosition(Vector3(boss_bullet->GetPositionX(), boss_bullet->GetPositionY(), -250));
				boss_effect->SetRotationZ(boss_bullet->GetRotationZ());
				Dimension_BulletEffect->_SwitchOn = true;
				Dimension_BulletEffect->SetState(eState::Active);

				Dimension_BulletEffect->_SwitchOn = true;
				if (_Dir == 1)
					Dimension_BulletEffect->SetDirection(1);
				else
					Dimension_BulletEffect->SetDirection(-1);
			}
			if (Dimension_BulletEffect->_SwitchOff == true)
			{
				Dimension_Bullet->SetState(eState::Paused);
				Dimension_BulletEffect->_SwitchOff = false;				

				if (_Dir == 1)
					at->PlayAnimation(L"Long_hairIdle", true);
				else
					at->PlayAnimation(L"Long_hairIdleR", true);
				_LongHair_state = Layana_LongHair_State::Idle;
				_Attacktime = 0;
				_SkillC_Switch = false;
			}
		}
	}


	void Layana_LongHair::AwakenJump()
	{
		if (_Awaken_Ready == true)
		{
			_LongHair_state = Layana_LongHair_State::AwakenReady;
			at->PlayAnimation(L"Long_hairAwakenReadyR", true);
			_Awaken_Ready = false;
		}
	}
	void Layana_LongHair::AwakenReady()
	{
	}
	void Layana_LongHair::Awaken()
	{
	}


	void Layana_LongHair::BackGround_Idle()
	{		
		if (_SistersAttack_Number >= 6)
		{
			Background_state = Layana_Long_Background::BackGround_Exit;
			at->PlayAnimation(L"Long_hairBackGround_Move", false);
			_rigidbody->SetVelocity(Vector2(0.f, 1050.f));
			_rigidbody->SetGround(false);
			_BackGround_check = true;
			_Ground_check = false;			
		}
		else
			_pos.z = -100;
	}
	void Layana_LongHair::BackGround_Enter()
	{
		if (_BackGround_Idle == true)
		{
			Background_state = Layana_Long_Background::BackGround_Idle;
			at->PlayAnimation(L"Long_hairBackGround_Idle", true);	
			_BackGround_Idle = false;
		}
	}
	void Layana_LongHair::BackGround_Exit()
	{
		if (_pos.y >= 100)
		{
			_rigidbody->SetGround(true);
			if (ShortHairPos.x >= _LongHairCreatepos.x)
			{
				_pos.x = -600;
				_pos.y = 100;
				_pos.z = -200;
			}
			else
			{
				_pos.x = 600;
				_pos.y = 100;
				_pos.z = -200;
			}
			LongHair_First_moving = true;
			Background_state = Layana_Long_Background::BackGround_Idle;
		}
	}


	void Layana_LongHair::Rush_Combo()
	{
		_RushSwitch = true;
		_Rushnumber = 0;
		if (_Playerdistance.x <= 30 && _Playerdistance.x >= -30)
		{
			_LongHair_state = Layana_LongHair_State::Rush_Ready;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairRush_Ready", true);
			else
				at->PlayAnimation(L"Long_hairRush_ReadyR", true);
		}
		else
		{
			_LongHair_state = Layana_LongHair_State::Dash;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairDash", true);
			else
				at->PlayAnimation(L"Long_hairDashR", true);
		}	
	}
	void Layana_LongHair::Complete_Rush()
	{		
		_HitBox_Attack_On = false;
		if (_Rushnumber >= 3 )
		{
			_LongHair_state = Layana_LongHair_State::Rush_End;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairRush_End", true);
			else
				at->PlayAnimation(L"Long_hairRush_EndR", true);
		}
		else
		{		
			_LongHair_state = Layana_LongHair_State::Dash;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairDash", true);
			else
				at->PlayAnimation(L"Long_hairDashR", true);
		}
	}
	void Layana_LongHair::Complete_RushReady()
	{		
		_HitBox_Attack_On = false;
		if (_Rushnumber == 0)
		{
			_HitBox_Attack_On = true;
			_LongHair_state = Layana_LongHair_State::RushA;
			if (_Dir == 1)
			{
				at->PlayAnimation(L"Long_hairRushA", true);
				_HitBox_Dir = 1;
			}
			else
			{
				at->PlayAnimation(L"Long_hairRushAR", true);
				_HitBox_Dir = -1;
			}
		}
		if (_Rushnumber == 1)
		{
			_HitBox_Attack_On = true;
			_LongHair_state = Layana_LongHair_State::RushB;
			if (_Dir == 1)
			{
				at->PlayAnimation(L"Long_hairRushB", true);
				_HitBox_Dir = 1;
			}
			else
			{
				at->PlayAnimation(L"Long_hairRushBR", true);
				_HitBox_Dir = -1;
			}
		}
		if (_Rushnumber == 2)
		{
			_HitBox_Attack_On = true;
			_LongHair_state = Layana_LongHair_State::RushC1;
			if (_Dir == 1)
			{
				at->PlayAnimation(L"Long_hairRushC1", true);
				_HitBox_Dir = 1;
			}
			else
			{
				at->PlayAnimation(L"Long_hairRushC1R", true);
				_HitBox_Dir = -1;
			}
		}
		if (_Rushnumber == 3)
		{
			_HitBox_Attack_On = true;
			_LongHair_state = Layana_LongHair_State::RushC2;
			if (_Dir == 1)
			{
				at->PlayAnimation(L"Long_hairRushC2", true);
				_HitBox_Dir = 1;
			}
			else
			{
				at->PlayAnimation(L"Long_hairRushC2R", true);
				_HitBox_Dir = -1;
			}
		}
		if (_Rushnumber == 4)
		{
			_HitBox_Attack_On = true;
			_LongHair_state = Layana_LongHair_State::RushC3;
			if (_Dir == 1)
			{
				at->PlayAnimation(L"Long_hairRushC3", true);
				_HitBox_Dir = 1;
			}
			else
			{
				at->PlayAnimation(L"Long_hairRushC3R", true);
				_HitBox_Dir = -1;
			}
		}
		if (_Rushnumber == 5)
		{
			_LongHair_state = Layana_LongHair_State::RushC4;
			if (_Dir == 1)			
				at->PlayAnimation(L"Long_hairRushC4", true);			
			else			
				at->PlayAnimation(L"Long_hairRushC4R", true);				
		}
		if (_Rushnumber >= 6)
		{
			_LongHair_state = Layana_LongHair_State::Idle;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairIdle", true);
			else
				at->PlayAnimation(L"Long_hairIdleR", true);			
			_time = 0;
		}
		_Rushnumber++;
	}


	void Layana_LongHair::Meteor_Cross_Combo()
	{
		_CrossMeteorSwitch = true;
		if (_Playerdistance.x <= 30 && _Playerdistance.x >= -30)
		{
			_LongHair_state = Layana_LongHair_State::Meteor_Cross_Jump;
			if (_Dir == 1)
			{
				at->PlayAnimation(L"Long_hairMeteor_Cross00_JumpR", false);
				_rigidbody->SetVelocity(Vector2(250.f, 450.f));
				_rigidbody->SetGround(false);
			}
			else
			{
				at->PlayAnimation(L"Long_hairMeteor_Cross00_Jump", false);
				_rigidbody->SetVelocity(Vector2(-250.f, 450.f));
				_rigidbody->SetGround(false);
			}
		}
		else
		{
			_LongHair_state = Layana_LongHair_State::Dash;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairDash", true);
			else
				at->PlayAnimation(L"Long_hairDashR", true);
		}
	}
	void Layana_LongHair::Complete_CrossJump()
	{
		_LongHair_state = Layana_LongHair_State::Meteor_Cross_Attack;
		//if (_Dir == 1)
		//at->PlayAnimation(L"Long_hairMeteor_Cross04_Attack", false);		
		//else
		//at->PlayAnimation(L"Long_hairMeteor_Cross04_AttackR", false);
	}
	void Layana_LongHair::Complete_CrossLanding()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairMeteor_Cross03_End", true);
		else
			at->PlayAnimation(L"Long_hairMeteor_Cross03_EndR", true);
		_LongHair_state = Layana_LongHair_State::Meteor_Cross_End;
	}
	void Layana_LongHair::Complete_CrossEnd()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairIdle", true);
		else
			at->PlayAnimation(L"Long_hairIdleR", true);
		_LongHair_state = Layana_LongHair_State::Idle;
		_time = 0;
		_CrossMeteorSwitch = false;
		_CrossMeteorLanding = false;
	}


	void Layana_LongHair::Meteor_Ground_Combo()
	{
		_GroundMeteorSwitch = true; // 이동이 되었을때 공격하는 모션 온
		_LongHair_state = Layana_LongHair_State::FlyDash;
		if (_pos.x > _LongHairCreatepos.x)
		{
			at->PlayAnimation(L"Long_hairDash", true);

			Transform* SM_Effect = Dash_SM->GetComponent<Transform>();
			SM_Effect->SetPosition(Vector3(_pos.x - 30, _pos.y - 40, _pos.z - 1));
			Dash_SM->SetDirection(1);
			Dash_SM->SetSwitch(true);
			Dash_SM->SetState(eState::Active);
		}
		else
		{
			at->PlayAnimation(L"Long_hairDashR", true);

			Transform* SM_Effect = Dash_SM->GetComponent<Transform>();
			SM_Effect->SetPosition(Vector3(_pos.x + 30, _pos.y - 40, _pos.z - 1));
			Dash_SM->SetDirection(-1);
			Dash_SM->SetSwitch(true);
			Dash_SM->SetState(eState::Active);
		}
	}
	void Layana_LongHair::Complete_GroundLanding()
	{				
	}
	void Layana_LongHair::Complete_GroundEnd()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairIdle", true);
		else
			at->PlayAnimation(L"Long_hairIdleR", true);
		_LongHair_state = Layana_LongHair_State::Idle;

			_time = 0;
		_GroundMeteorSwitch = false;
		_GroundMeteorLanding = false;
		_GroundMeteorAttack_Right = false;
		_GroundMeteorAttack_Left = false;
	}


	void Layana_LongHair::Meteor_Vertical_Combo()
	{
		_VerticalMeteorSwitch = true;
		_LongHair_state = Layana_LongHair_State::FlyDash;

		if (_pos.x > _LongHairCreatepos.x)
		{
			at->PlayAnimation(L"Long_hairDash", true);

			Transform* SM_Effect = Dash_SM->GetComponent<Transform>();
			SM_Effect->SetPosition(Vector3(_pos.x - 30, _pos.y - 40, _pos.z - 1));
			Dash_SM->SetDirection(1);
			Dash_SM->SetSwitch(true);
			Dash_SM->SetState(eState::Active);
		}
		else
		{
			at->PlayAnimation(L"Long_hairDashR", true);

			Transform* SM_Effect = Dash_SM->GetComponent<Transform>();
			SM_Effect->SetPosition(Vector3(_pos.x + 30, _pos.y - 40, _pos.z - 1));
			Dash_SM->SetDirection(-1);
			Dash_SM->SetSwitch(true);
			Dash_SM->SetState(eState::Active);
		}
	}	
	void Layana_LongHair::Complete_VerticalJump()
	{
		_Ground_check = false;
		_pos.x = _Playerpos.x;
		_LongHair_state = Layana_LongHair_State::Meteor_Vertical_Ready;
		at->PlayAnimation(L"Long_hairMeteor_Vertical01_Ready", true);
	}
	void Layana_LongHair::Complete_VerticalReady()
	{
		_LongHair_state = Layana_LongHair_State::Meteor_Vertical_Landing;
		_Ground_check = false;
		_pos.x = _Playerpos.x;
		at->PlayAnimation(L"Long_hairMeteor_Vertical02_Attack", false);
		_rigidbody->SetGround(false);
		_rigidbody->SetVelocity(Vector2(0.f, -550.f));
	}
	void Layana_LongHair::Complete_VerticalEnd()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairIdle", true);
		else
			at->PlayAnimation(L"Long_hairIdleR", true);
		_LongHair_state = Layana_LongHair_State::Idle;
		
		_time = 0;
		_VerticalMeteorSwitch = false;
		_VerticalMeteorLanding = false;
	}


	void Layana_LongHair::Skill_A_Combo()
	{
		_SkillA_Switch = true;
		if (_SkillA_Switch == true)
		{
			_LongHair_state = Layana_LongHair_State::Skill_A_Bullet_Ready;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairSkill_A_Bullet_Ready", true);
			else
				at->PlayAnimation(L"Long_hairSkill_A_Bullet_ReadyR", true);
			_SkillA_Landing = true;
		}
	}
	void Layana_LongHair::Complete_Skill_A()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairIdle", true);
		else
			at->PlayAnimation(L"Long_hairIdleR", true);
		_LongHair_state = Layana_LongHair_State::Idle;

		_time = 0.f;
		_SkillA_Switch = false;
		_SkillA_Landing = false;
		_SkillHomingON = false;
		_SkillHomingFire = false;
		_HomingNumber = 0;
		_Attacktime = 0.f;
	}


	void Layana_LongHair::Skill_B_Combo()
	{
		_LongHair_state = Layana_LongHair_State::Skill_B_RisingPierce;
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairSkill_B_RisingPierce", false);
		else
			at->PlayAnimation(L"Long_hairSkill_B_RisingPierceR", false);
	}
	void Layana_LongHair::Complete_Skill_B()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairIdle", true);
		else
			at->PlayAnimation(L"Long_hairIdleR", true);
		_LongHair_state = Layana_LongHair_State::Idle;

		_time = 0.f;
		_SkillB_Switch = false;
	}


	void Layana_LongHair::Skill_C_Combo()
	{
		_LongHair_state = Layana_LongHair_State::Skill_C_DimensionPierce;
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairSkill_C_DimensionPierce", false);
		else
			at->PlayAnimation(L"Long_hairSkill_C_DimensionPierceR", false);
	}


	void Layana_LongHair::Intro_Combo()
	{
		if (_Intro_Switch == false)
		{
			_pos = Vector3(_LongHairCreatepos.x + 150, _LongHairCreatepos.y, _LongHairCreatepos.z);
			tr->SetPosition(_pos);
			_Intro_Switch = true;
		}
		if (_Intro_Switch == true)
		{
			at->PlayAnimation(L"Long_hairIntro_Dash", false);
			_rigidbody->SetGround(false);
			_rigidbody->SetVelocity(Vector2(1050.f, 150.f));
			_Intro_Dash_LongHair = true;
			_Ground_check = false;
			_Intro_Switch = false;
		}
	}
	void Layana_LongHair::Complete_IntroLanding()
	{
		at->PlayAnimation(L"Long_hairIntro_Landing_EndR", true);
		Transform* ImpactTR = Intro_Ar->GetComponent<Transform>();
		ImpactTR->SetPosition(Vector3(_pos.x, _pos.y-20, _pos.z - 1));
		Intro_Ar->SetDirection(-1);
		Intro_Ar->SetSwitch(true);
		Intro_Ar->SetState(eState::Active);
		_Intro_LandEnd_LongHair = true;
		_time = 0.f;
		_Attacktime = 0.f;
		_Intro_Switch = false;
		_Intro_Landing = false;
	}
	void Layana_LongHair::Complete_IntroLanding_END()
	{
		_Intro_LongHair_END = true;
	}


	void Layana_LongHair::Awaken_Combo()
	{
		if (_Awaken_Switch == false)
		{
			_pos = Vector3(_LongHairCreatepos.x + 200, _LongHairCreatepos.y - 50, _LongHairCreatepos.z);
			tr->SetPosition(_pos);
			_rigidbody->SetGround(false);
			_Ground_check = false;
			at->PlayAnimation(L"Long_hairAwakenJumpR", false);
			_LongHair_state = Layana_LongHair_State::AwakenJump;
			_Awaken_Switch = true;
		}
	}
	void Layana_LongHair::Complete_Awaken_Ready()
	{
		_LongHair_state = Layana_LongHair_State::Awaken;
		at->PlayAnimation(L"Long_hairAwakenR", true);
	}
	void Layana_LongHair::Complete_Awaken()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairIdle", true);
		else
			at->PlayAnimation(L"Long_hairIdleR", true);
		_LongHair_state = Layana_LongHair_State::Idle;
	
		// 나중에 각성보스 추가시 여기서 변경코드 넣으면됨
		_time = 0.f;
		_Attacktime = 0.f;
		_Awaken_Switch = false;
		_Awaken_Ready = false;
	}


	void Layana_LongHair::BackGround_Combo()
	{
		_BackGround_Switch = true;
		Background_state = Layana_Long_Background::FlyDash;
		if (_pos.x > _LongHairCreatepos.x)
			at->PlayAnimation(L"Long_hairDash", true);
		else
			at->PlayAnimation(L"Long_hairDashR", true);
	}


	void Layana_LongHair::die()
	{
	}


	void Layana_LongHair::CreateHoming()
	{
		if (_SkillHomingON == false)
		{
			_Attacktime += Time::DeltaTime();
			if (_Attacktime >= 0.5f)
			{
				_Attacktime = 0;
				_HomingNumber++;
			}

			if (_HomingNumber == 0)
			{
				_HomingEditPOS.x = 85;
				_HomingEditPOS.y = -50;
			}
			if (_HomingNumber == 1)
			{
				_HomingEditPOS.x = 70;
				_HomingEditPOS.y = 0;
			}
			if (_HomingNumber == 2)
			{
				_HomingEditPOS.x = 50;
				_HomingEditPOS.y = 50;
			}

			Transform* bullet_tr = Homing[_HomingNumber]->GetComponent<Transform>();
			if (_Dir == 1)
			{
				bullet_tr->SetRotationZ(0);
				Homing[_HomingNumber]->SetDirection(1);
				bullet_tr->SetPosition(Vector3(_pos.x + _HomingEditPOS.x, _pos.y + _HomingEditPOS.y, -251));

				Transform* bullet_tr = Homing_EF[_HomingNumber]->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(_pos.x + _HomingEditPOS.x, _pos.y + _HomingEditPOS.y, -251-1));
				Homing_EF[_HomingNumber]->SetSwitch(true); 
				Homing_EF[_HomingNumber]->SetDirection(1);
				Homing_EF[_HomingNumber]->SetState(eState::Active);
			}
			else
			{
				bullet_tr->SetRotationZ(0);
				Homing[_HomingNumber]->SetDirection(-1);
				bullet_tr->SetPosition(Vector3(_pos.x - _HomingEditPOS.x, _pos.y + _HomingEditPOS.y, -251));

				Transform* bullet_tr = Homing_EF[_HomingNumber]->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(_pos.x - _HomingEditPOS.x, _pos.y + _HomingEditPOS.y, -251-1));
				Homing_EF[_HomingNumber]->SetSwitch(true);
				Homing_EF[_HomingNumber]->SetDirection(-1);
				Homing_EF[_HomingNumber]->SetState(eState::Active);
			}
			Homing[_HomingNumber]->SetState(eState::Active);

			if (_HomingNumber >= 2)
			{
				_SkillHomingON = true;
				_HomingNumber = 0;
				_Attacktime = 0;
			}
		}
	}
	void Layana_LongHair::SettingHoming(Transform* set, int angle_of_number)
	{
		Vector2 attackpoint = {};
		Vector2 rotation = {};

		if (_LongHairCreatepos.x >= _pos.x)
		{
			Homing[_HomingNumber]->SetDirection(1);
			attackpoint = Vector2(_Playerpos.x, _Playerpos.y);
			rotation = Vector2(set->GetPositionX(), set->GetPositionY());

		}
		else
		{
			Homing[_HomingNumber]->SetDirection(-1);
			attackpoint = Vector2(_Playerpos.x, _Playerpos.y);
			rotation = Vector2(set->GetPositionX(), set->GetPositionY());
		}

		Vector2 direction = attackpoint - rotation; // 플레이어를 향하는 방향 벡터
		direction.Normalize();
		float angle = std::atan2(direction.y, direction.x);		
		
		if (_LongHairCreatepos.x < _pos.x) 
		{
			angle += XM_PI; // 180도를 라디안으로 변환하여 더함
		}

		set->SetRotationZ(angle);

		if (angle_of_number == 0)
		{
			_HomingAngle[0] = angle;
			_HomingVector[0] = direction;
		}
		if (angle_of_number == 1)
		{
			_HomingAngle[1] = angle;
			_HomingVector[1] = direction;
		}
		if (angle_of_number == 2)
		{
			_HomingAngle[2] = angle;
			_HomingVector[2] = direction;
		}
	}
}