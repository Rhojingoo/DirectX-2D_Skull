#include "Layana_LongHair.h"


namespace jk
{
	bool Layana_LongHair:: _AttackStageON = true;

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
		_pos = Vector3(0.f, 0.f, -200.f);		
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
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross00_Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross01_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross02_Landing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross03_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross04_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground01_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground02_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground03_Landing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground04_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical00_Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical01_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical02_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical03_Landing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical04_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Rush_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Rush_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushA", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushB", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushC", this);
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
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross00_Jump", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross01_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross02_Landing", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross03_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross04_Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground01_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground02_Attack", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground03_Landing", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground04_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical00_Jump", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical01_Ready", this,1);	
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical02_Attack", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical03_Landing", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical04_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Rush_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Rush_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushA", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushB", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushC", this,1);
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
		at->CompleteEvent(L"Long_hairIntro_Landing") = std::bind(&Layana_LongHair::Complete_IntroRanding, this);
		at->CompleteEvent(L"Long_hairAwaken") = std::bind(&Layana_LongHair::Complete_Awaken, this);
		at->CompleteEvent(L"Long_hairAwakenReadyR") = std::bind(&Layana_LongHair::Complete_Awaken_Ready, this);

		


		at->CompleteEvent(L"Long_hairRush_ReadyR") = std::bind(&Layana_LongHair::Complete_RushReady, this);
		at->CompleteEvent(L"Long_hairRushAR") = std::bind(&Layana_LongHair::Complete_Rush, this);
		at->CompleteEvent(L"Long_hairRushBR") = std::bind(&Layana_LongHair::Complete_Rush, this);
		at->CompleteEvent(L"Long_hairRushCR") = std::bind(&Layana_LongHair::Complete_Rush, this);
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
		at->CompleteEvent(L"Long_hairIntro_LandingR") = std::bind(&Layana_LongHair::Complete_IntroRanding, this);
		at->CompleteEvent(L"Long_hairAwakenR") = std::bind(&Layana_LongHair::Complete_Awaken, this);
		at->CompleteEvent(L"Long_hairAwakenReadyR") = std::bind(&Layana_LongHair::Complete_Awaken_Ready, this);


		
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
		bullet_tr1 = Homing[0]->GetComponent<Transform>();
		bullet_tr2 = Homing[1]->GetComponent<Transform>();
		bullet_tr3 = Homing[2]->GetComponent<Transform>();
		bullet_rb1 = Homing[0]->GetComponent<RigidBody>();
		bullet_rb2 = Homing[1]->GetComponent<RigidBody>();
		bullet_rb3 = Homing[2]->GetComponent<RigidBody>();


		
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
			scene->AddGameObject(eLayerType::Bullet, TwinMeteor_BossEffect);
			Transform* bullte_effect = TwinMeteor_BossEffect->GetComponent<Transform>();
			bullte_effect->SetPosition(Vector3(_pos.x, _pos.y, -205));
			TwinMeteor_BossEffect->SetState(eState::Paused);
		}

		at->PlayAnimation(L"Long_hairIdle", true);
		GameObject::Initialize();
	}
	void Layana_LongHair::Update()
	{
		_Playerpos = Player::GetPlayer_Pos();
		_velocity = _rigidbody->GetVelocity();
		_Playerdistance.x = _Playerpos.x - _pos.x;
		_Playerdistance.y = _Playerpos.y - _pos.y;
		if (_Playerdistance.x >= 0)
			_Dir = 1;
		else
			_Dir = -1;
		_pos = tr->GetPosition();

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

		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_A_Ready:
			Layana_LongHair::Sisters_Attack_A_Ready();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_FlyDash:
			Layana_LongHair::Sisters_Attack_FlyDash();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_Fall:
			Layana_LongHair::Sisters_Attack_Fall();
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





		case jk::Layana_Sisters::Layana_Sisters_State::Rush_Ready:
			Layana_LongHair::Rushready();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::RushA:
			Layana_LongHair::Rush_A();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::RushB:
			Layana_LongHair::Rush_B();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::RushC:
			Layana_LongHair::Rush_C();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Rush_End:
			Layana_LongHair::Rush_End();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Dash:
			Layana_LongHair::Dash();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::FlyDash:
			Layana_LongHair::FlyDash();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::LandingDash:
			Layana_LongHair::LandingDash();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::BackStep:
			Layana_LongHair::BackStep();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Ready:
			Layana_LongHair::CrossReady();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Jump:
			Layana_LongHair::CrossJump();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Attack:
			Layana_LongHair::CrossAttack();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Landing:
			Layana_LongHair::CrossLanding();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_End:
			Layana_LongHair::CrossEnd();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_Ready:
			Layana_LongHair::GroundReady();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_Attack:
			Layana_LongHair::GroundAttack();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_Landing:
			Layana_LongHair::GroundLanding();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_End:
			Layana_LongHair::GroundEnd();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_Jump:
			Layana_LongHair::Vertical_Jump();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_Ready:
			Layana_LongHair::Vertical_Ready();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_Attack:
			Layana_LongHair::Vertical_Attack();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_Landing:
			Layana_LongHair::Vertical_Landing();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_End:
			Layana_LongHair::Vertical_End();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Skill_A_Bullet_Ready:
			Layana_LongHair::Skill_A_Ready();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Skill_A_Bullet:
			Layana_LongHair::Skill_A();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Skill_A_Bullet_End:
			Layana_LongHair::Skill_A_End();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Skill_B_RisingPierce:
			Layana_LongHair::Skill_B();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Skill_B_RisingPierce_End:
			Layana_LongHair::Skill_B_End();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Skill_C_DimensionPierce:
			Layana_LongHair::Skill_C();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::AwakenJump:
			Layana_LongHair::AwakenJump();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::AwakenReady:
			Layana_LongHair::AwakenReady();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Awaken:
			Layana_LongHair::Awaken();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::BackGround_Idle:
			Layana_LongHair::BackGround_Idle();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::BackGround_Move:
			Layana_LongHair::BackGround_Move();
			break;

		default:
			break;
		}

		tr->SetPosition(_pos);
		GameObject::Update();
	}
	void Layana_LongHair::LateUpdate()
	{
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
	}
	void Layana_LongHair::OnCollisionStay(Collider2D* other)
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
				if (_state == Layana_Sisters_State::Meteor_Cross_Landing)
				{						
					if (_Dir == 1)
						at->PlayAnimation(L"Long_hairMeteor_Cross02_Landing", true);
					else
						at->PlayAnimation(L"Long_hairMeteor_Cross02_LandingR", true);			
					tr->SetRotationZ(0.f);
					_CrossMeteorLanding = true;
				}
				if (_state == Layana_Sisters_State::LandingDash)
				{					
					if (_Dir == 1)
						at->PlayAnimation(L"Long_hairMeteor_Ground01_Ready", true);
					else
						at->PlayAnimation(L"Long_hairMeteor_Ground01_ReadyR", true);		
					_GroundMeteorLanding = true;
				}
				if (_state == Layana_Sisters_State::Meteor_Vertical_Landing)
				{
					if (_Dir == 1)
						at->PlayAnimation(L"Long_hairMeteor_Vertical03_Landing", true);
					else
						at->PlayAnimation(L"Long_hairMeteor_Vertical03_LandingR", true);
					_VerticalMeteorLanding = true;
				}
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
				}

				if (_state == Layana_Sisters_State::AwakenJump)				
					_Awaken_Ready = true;

				if (_state == Layana_Sisters_State::Sisters_Attack_Fall)
				{
					if (_Sisters_Attack_A_Switch == true)
					{
						if (_pos.x < _LongHairCreatepos.x)
							at->PlayAnimation(L"Long_hairMeteor_Ground01_Ready", false);
						else
							at->PlayAnimation(L"Long_hairMeteor_Ground01_ReadyR", false);
						_SistersAttack_A_Ready_LongHair = true;			
						_Sisters_Attack_A_Switch = false;
					}
					if (_Sisters_Attack_B_Switch == true)
					{
						if (_pos.x < _LongHairCreatepos.x)
							at->PlayAnimation(L"Long_hairSkill_A_Bullet_Ready", false);
						else
							at->PlayAnimation(L"Long_hairSkill_A_Bullet_ReadyR", false);			
						_SistersAttack_B_Ready_LongHair = true;
						_Sisters_Attack_B_Switch = false;
					}
				}		

				if (_state == Layana_Sisters_State::Sisters_Attack_C)
				{
					if (_pos.x < _LongHairCreatepos.x)
						at->PlayAnimation(L"Long_hairMeteor_Cross02_Landing", true);
					else
						at->PlayAnimation(L"Long_hairMeteor_Cross02_LandingR", true);
					tr->SetRotationZ(0.f);
				}
			}
		}

		if (Back_ground* mGround = dynamic_cast<Back_ground*>(other->GetOwner()))
		{
			if (_BackGround_check == false)
			{
				_rigidbody->SetGround(true);
				_BackGround_check = true;
				_BackGround_check = _rigidbody->GetGround();
				_rigidbody->ClearVelocity();
			}
			else
			{
				if (_state == Layana_Sisters_State::BackGround_Move)
				{					
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
		//_time += Time::DeltaTime();
		//_SelectAttack = random(0, 2);
		//_SelectAttack = 9;

		if (_Intro_On == true)
			Intro_Combo();
		else
		{

		}
		if (_time >= 3.0)
		{
			if(_SelectAttack == 0)
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
				Intro_Combo();
			if (_SelectAttack == 8)			
				Awaken_Combo();			
			if (_SelectAttack == 9)
				BackGround_Combo();
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


	void Layana_LongHair::Sisters_Attack_FlyDash()
	{
		if (_AttackStageON == true)
		{
			if (_pos.x < _LongHairCreatepos.x )
			{
				if (_pos.x > _LongHairCreatepos.x - 700)
					_pos.x -= 750.f * Time::DeltaTime();
				if (_pos.y < _LongHairCreatepos.y + 150)
					_pos.y += 150.f * Time::DeltaTime();
			}
			else
			{
				if (_pos.x < _LongHairCreatepos.x + 700)
					_pos.x += 750.f * Time::DeltaTime();
				if (_pos.y < _LongHairCreatepos.y + 155)
					_pos.y += 150.f * Time::DeltaTime();
			}
			if (_pos.y >= _LongHairCreatepos.y + 150.f)
				_AttackStageON = false;
		}
		else
		{
			if (_Sisters_Attack_C_Switch == true)
			{
				if (_SistersAttack_C_Ready_LongHair == false)
				{
					if (_pos.x >= 0)
					{
						Transform* bullte_effect = TwinMeteor_BossEffect->GetComponent<Transform>();
						bullte_effect->SetPosition(Vector3(_LongHairCreatepos.x + 250, _pos.y - 200, -205));
						float angle = 30;
						float angleInDegrees = angle * (180.0f / XM_PI);
						//bullte_effect->SetRotationZ(angleInDegrees);
						bullte_effect->AddRotationZ(angleInDegrees);
						TwinMeteor_BossEffect->SetState(eState::Active);
						_SistersAttack_C_Ready_LongHair = true;
					}
					else
					{
						Transform* bullte_effect = TwinMeteor_BossEffect->GetComponent<Transform>();
						bullte_effect->SetPosition(Vector3(_LongHairCreatepos.x - 250, _pos.y - 200, -205));
						float angle = -30;
						float angleInDegrees = angle * (180.0f / XM_PI);
						//bullte_effect->SetRotationZ(angleInDegrees);
						bullte_effect->AddRotationZ(angleInDegrees);
						TwinMeteor_BossEffect->SetState(eState::Active);
						_SistersAttack_C_Ready_LongHair = true;
					}
				}
				else
				{
					_Attacktime += Time::DeltaTime();
					if (_Attacktime > 1.5)
					{
						//TwinMeteor_BossEffect->SetState(eState::Paused);
						if (_pos.x < _LongHairCreatepos.x)
						{							
							_pos = Vector3(-640.f, _pos.y, _pos.z);
							tr->SetPosition(_pos);
							float angle = -210;
							float angleInDegrees = angle * (180.0f / XM_PI);
							//tr->SetRotationZ(-angleInDegrees);
							at->PlayAnimation(L"Long_hairMeteor_Ground02_Attack", true);
							tr->AddRotationZ(angleInDegrees);
							_rigidbody->SetVelocity(Vector2(800.f, -150.f));
							_rigidbody->SetGround(false);
							_Ground_check = false;
							{
								Transform* bullte_effect = TwinMeteor_Impact->GetComponent<Transform>();
								bullte_effect->SetPosition(Vector3(_LongHairCreatepos.x - 250, _pos.y - 200, -205));
								float angle = -30;
								float angleInDegrees = angle * (180.0f / XM_PI);
								//bullte_effect->SetRotationZ(angleInDegrees);
								bullte_effect->AddRotationZ(angleInDegrees);
								TwinMeteor_Impact->SetState(eState::Active);							
							}
							_SistersAttack_C_DashOn_LongHair = true;
						}
						else
						{							
							_pos = Vector3(640.f, _pos.y, _pos.z);
							tr->SetPosition(_pos);
							float angle = -210;
							float angleInDegrees = angle * (180.0f / XM_PI);
						   //tr->SetRotationZ(angleInDegrees);
							at->PlayAnimation(L"Long_hairMeteor_Ground02_AttackR", true);
							tr->AddRotationZ(angleInDegrees);
							_rigidbody->SetVelocity(Vector2(-800.f, -150.f));
							_rigidbody->SetGround(false);
							_Ground_check = false;			
							{
								Transform* bullte_effect = TwinMeteor_Impact->GetComponent<Transform>();
								bullte_effect->SetPosition(Vector3(_LongHairCreatepos.x + 250, _pos.y - 200, -205));
								float angle = 30;
								float angleInDegrees = angle * (180.0f / XM_PI);
								//bullte_effect->SetRotationZ(angleInDegrees);
								bullte_effect->AddRotationZ(angleInDegrees);
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
					_rigidbody->SetVelocity(Vector2(650.f, -150.f));
					at->PlayAnimation(L"Long_hairDash", true);
				}
				else
				{
					_rigidbody->SetVelocity(Vector2(-650.f, -150.f));
					at->PlayAnimation(L"Long_hairDashR", true);
				}
			}
		}
	}
	void Layana_LongHair::Sisters_Attack_Fall()
	{
	}


	void Layana_LongHair::Sisters_Attack_A_Ready()
	{
		_Sisters_Attack_A_Switch = true;
		_SistersAttack_A_IntroReady_LongHair = true;		
		at->PlayAnimation(L"Long_hairDash", true);
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
					_rigidbody->SetVelocity(Vector2(700.f, 0.f));
					_GroundMeteorAttack_Right = true;
				}
				else
				{
					at->PlayAnimation(L"Long_hairMeteor_Ground02_AttackR", false);
					_rigidbody->SetVelocity(Vector2(-700.f, 0.f));
					_GroundMeteorAttack_Left = true;
				}
				_Attacktime = 0;
				_SistersAttack_A_DashOn_LongHair = true;
			}
		}
	}
	void Layana_LongHair::Sisters_Attack_A()
	{
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
			_Sisters_Attack_A_Switch = false;
		}
	}


	void Layana_LongHair::Sisters_Attack_B_Ready()
	{
		_Sisters_Attack_B_Switch = true;	
		if (_pos.x > _LongHairCreatepos.x)		
			at->PlayAnimation(L"Long_hairDash", true);		
		else		
			at->PlayAnimation(L"Long_hairDashR", true);
		_SistersAttack_B_IntroReady_LongHair = true;
		_AttackStageON = true;
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

			if (_Attacktime >= 1.5)
			{
				//레이아나 크로스공격시 참고용
				Vector2 attackrotation_PLAYER = Vector2(_Playerpos.x - _pos.x, _Playerpos.y - _pos.y);
				attackrotation_PLAYER.Normalize();
				bullet_rb1->SetGround(false);
				bullet_rb1->SetVelocity(Vector2(attackrotation_PLAYER.x * 650.f, attackrotation_PLAYER.y * 350));
				Vector2 vel = bullet_rb1->GetVelocity();
				int a = 0;
			}

			if (_Attacktime >= 2)
			{
				//레이아나 크로스공격시 참고용
				Vector2 attackrotation_PLAYER = Vector2(_Playerpos.x - _pos.x, _Playerpos.y - _pos.y);
				attackrotation_PLAYER.Normalize();
				bullet_rb2->SetGround(false);
				bullet_rb2->SetVelocity(Vector2(attackrotation_PLAYER.x * 650.f, attackrotation_PLAYER.y * 1250));
				Vector2 vel = bullet_rb2->GetVelocity();
				int a = 0;

			}

			if (_Attacktime >= 2.5)
			{
				//레이아나 크로스공격시 참고용
				Vector2 attackrotation_PLAYER = Vector2(_Playerpos.x - _pos.x, _Playerpos.y - _pos.y);
				attackrotation_PLAYER.Normalize();
				bullet_rb3->SetGround(false);
				bullet_rb3->SetVelocity(Vector2(attackrotation_PLAYER.x * 650.f, attackrotation_PLAYER.y * 1400));
				Vector2 vel = bullet_rb3->GetVelocity();
				int a = 0;
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
				bullet_rb2->ClearVelocity();
				bullet_rb3->ClearVelocity();
				bullet_rb1->SetGround(true);
				bullet_rb2->SetGround(true);
				bullet_rb3->SetGround(true);
				_Attacktime = 0;
				Homing[i]->SetState(eState::Paused);
			}


			_SistersAttack_B_LongHair_END = true;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairSkill_A_Bullet_End", false);
			else
				at->PlayAnimation(L"Long_hairSkill_A_Bullet_EndR", false);
			int a = 0;
		}
	}
	void Layana_LongHair::Sisters_Attack_B_End()
	{
		_Sisters_Attack_B_Switch = false;
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
	}
	void Layana_LongHair::Sisters_Attack_C_End()
	{
	}


	void Layana_LongHair::Sisters_Attack_D()
	{
	}



	//대쉬
	void Layana_LongHair::Dash()
	{
		if (!(_Playerdistance.x <= 30 && _Playerdistance.x >= -30))
		{
			if (_Dir == 1)
				_pos.x += 250.f * Time::DeltaTime();
			else
				_pos.x -= 250.f * Time::DeltaTime();
		}
		else
		{
			if (_RushSwitch == true)
			{
				_state = Layana_Sisters_State::Rush_Ready;
				if (_Dir == 1)
					at->PlayAnimation(L"Long_hairRush_Ready", true);
				else
					at->PlayAnimation(L"Long_hairRush_ReadyR", true);
			}
			if (_CrossMeteorSwitch == true)
			{
				_state = Layana_Sisters_State::Meteor_Cross_Jump;
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
		if (_Dir == 1)
		{
			if (_pos.x > _LongHairCreatepos.x - 700)
				_pos.x -= 750.f * Time::DeltaTime();
			if (_pos.y < _LongHairCreatepos.y + 150)
				_pos.y += 150.f * Time::DeltaTime();
		}
		else
		{
			if (_pos.x < _LongHairCreatepos.x + 700)
				_pos.x += 750.f * Time::DeltaTime();
			if (_pos.y < _LongHairCreatepos.y + 150)
				_pos.y += 150.f * Time::DeltaTime();
		}
		if (_pos.y >= _LongHairCreatepos.y + 150.f)
		{			
			if (_GroundMeteorSwitch == true)
			{
				_state = Layana_Sisters_State::LandingDash;
				_Ground_check = false;
				_rigidbody->SetGround(false);
				if (_Dir == 1)
				{
					_rigidbody->SetVelocity(Vector2(650.f, -150.f));
					at->PlayAnimation(L"Long_hairDashR", true);
				}
				else
				{
					_rigidbody->SetVelocity(Vector2(-650.f, -150.f));
					at->PlayAnimation(L"Long_hairDash", true);
				}
			}
			if (_VerticalMeteorSwitch == true)
			{
				_state = Layana_Sisters_State::Meteor_Vertical_Jump;
				_Ground_check = false;
				_pos.x = _Playerpos.x;
				at->PlayAnimation(L"Long_hairMeteor_Vertical00_Jump", true);

				//if (_Dir == 1)
				//	at->PlayAnimation(L"Long_hairMeteor_Vertical00_Jump", true);	
				//else
				//	at->PlayAnimation(L"Long_hairMeteor_Vertical00_JumpR", true);
			}
			if (_BackGround_Switch == true)
			{
				_pos = Vector3(_LongHairCreatepos.x + 50, _LongHairCreatepos.y + 100, -150.f);
				tr->SetPosition(_pos);
				at->PlayAnimation(L"Long_hairBackGround_Move", false);
				_state = Layana_Sisters_State::BackGround_Move;
				_rigidbody->SetGround(false);
				_Ground_check = false;
				_BackGround_check = false;
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
				_state = Layana_Sisters_State::Meteor_Ground_Attack;

				if (_Dir == 1)
				{
					at->PlayAnimation(L"Long_hairMeteor_Ground02_Attack", true);
					_rigidbody->SetVelocity(Vector2(700.f, 0.f));
					_GroundMeteorAttack_Right = true;
				}
				else
				{
					at->PlayAnimation(L"Long_hairMeteor_Ground02_AttackR", true);
					_rigidbody->SetVelocity(Vector2(-700.f, 0.f));
					_GroundMeteorAttack_Left = true;
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
			_state = Layana_Sisters_State::Meteor_Cross_Ready;
			_Ground_check = false;
		}
	}
	void Layana_LongHair::CrossReady()
	{	
	}
	void Layana_LongHair::CrossAttack()
	{
		Vector2 attackrotation_PLAYER = Vector2(_Playerpos.x, _Playerpos.y);
		Vector2 rotation = Vector2(_pos.x, _pos.y);
		attackrotation_PLAYER.Normalize();
		rotation.Normalize();

		//if(mDir ==1)
		//	tr->SetRotation(Vector3(0.f, 0.f, 45));
		//else
		//	tr->SetRotation(Vector3(0.f, 0.f, 135));

		float dotProduct = attackrotation_PLAYER.Dot(rotation);
		dotProduct = std::clamp(dotProduct, -1.0f, 1.0f);
		float angle = std::acos(dotProduct);
		float angleInDegrees = angle * (180.0f / XM_PI);
		//tr->SetRotation(Vector3(0.f,0.f, angleInDegrees));
		if (_Dir == 1)
			tr->AddRotationZ(45);
		else
			tr->AddRotationZ(-45);		
		
		_rigidbody->SetGround(false);
		_rigidbody->SetVelocity(Vector2(attackrotation_PLAYER.x * -300.f, attackrotation_PLAYER.y * 200));
		_state = Layana_Sisters_State::Meteor_Cross_Landing;
		
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
		if (_GroundMeteorAttack_Right == true)
		{
			if (_pos.x >= _LongHairCreatepos.x + 312)
			{
				_rigidbody->ClearVelocity();
				_GroundMeteorAttack_Right = false;
				_state = Layana_Sisters_State::Meteor_Ground_End;
				if (_Dir == 1)
					at->PlayAnimation(L"Long_hairMeteor_Ground04_End", true);					
				else
					at->PlayAnimation(L"Long_hairMeteor_Ground04_EndR", true);
			}
		}
		if (_GroundMeteorAttack_Left == true)
		{
			if (_pos.x <= _LongHairCreatepos.x - 312)
			{
				_rigidbody->ClearVelocity();
				_GroundMeteorAttack_Left = false;
				_state = Layana_Sisters_State::Meteor_Ground_End;
				if (_Dir == 1)
					at->PlayAnimation(L"Long_hairMeteor_Ground04_End", true);
				else
					at->PlayAnimation(L"Long_hairMeteor_Ground04_EndR", true);
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
		_Attacktime += Time::DeltaTime();
		if (_VerticalMeteorLanding == true)
		{
			if (_Attacktime >= 1.f)
			{
				_state = Layana_Sisters_State::Meteor_Vertical_End;

				if (_Dir == 1)
					at->PlayAnimation(L"Long_hairMeteor_Vertical04_End", true);				
				else			
					at->PlayAnimation(L"Long_hairMeteor_Vertical04_EndR", true);
				_Attacktime = 0;
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
				_state = Layana_Sisters_State::Skill_A_Bullet;
				if (_Dir == 1)
					at->PlayAnimation(L"Long_hairSkill_A_Bullet", false);
				else
					at->PlayAnimation(L"Long_hairSkill_A_BulletR", false);
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

			if (_Attacktime >= 1.5)
			{
				//레이아나 크로스공격시 참고용
				Vector2 attackrotation_PLAYER = Vector2(_Playerpos.x-_pos.x, _Playerpos.y-_pos.y);
				attackrotation_PLAYER.Normalize();
				bullet_rb1->SetGround(false);
				bullet_rb1->SetVelocity(Vector2(attackrotation_PLAYER.x * 650.f, attackrotation_PLAYER.y * 350));
				Vector2 vel = bullet_rb1->GetVelocity();
				int a = 0;
			}

			if (_Attacktime >= 2)
			{
				//레이아나 크로스공격시 참고용
				Vector2 attackrotation_PLAYER = Vector2(_Playerpos.x - _pos.x, _Playerpos.y - _pos.y);
				attackrotation_PLAYER.Normalize();
				bullet_rb2->SetGround(false);
				bullet_rb2->SetVelocity(Vector2(attackrotation_PLAYER.x * 650.f, attackrotation_PLAYER.y * 1250));
				Vector2 vel = bullet_rb2->GetVelocity();
				int a = 0;

			}

			if (_Attacktime >= 2.5)
			{
				//레이아나 크로스공격시 참고용
				Vector2 attackrotation_PLAYER = Vector2(_Playerpos.x - _pos.x, _Playerpos.y - _pos.y);
				attackrotation_PLAYER.Normalize();
				bullet_rb3->SetGround(false);
				bullet_rb3->SetVelocity(Vector2(attackrotation_PLAYER.x * 650.f, attackrotation_PLAYER.y * 1400));
				Vector2 vel = bullet_rb3->GetVelocity();
				int a = 0;
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
				bullet_rb2->ClearVelocity();
				bullet_rb3->ClearVelocity();
				bullet_rb1->SetGround(true);
				bullet_rb2->SetGround(true);
				bullet_rb3->SetGround(true);
				_Attacktime = 0;
				Homing[i]->SetState(eState::Paused);
			}

			_state = Layana_Sisters_State::Skill_A_Bullet_End;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairSkill_A_Bullet_End", true);
			else
				at->PlayAnimation(L"Long_hairSkill_A_Bullet_EndR", true);
			int a = 0;
		}
	}
	void Layana_LongHair::Skill_A_End()
	{

	}


	void Layana_LongHair::Skill_B()
	{
		static float edidpos = 20;
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
						Risingbullet_tr[i + 1]->SetPosition(Vector3(_pos.x + edidpos, _pos.y + 35, -255));
						Rising[i + 1]->SetState(eState::Active);

						Risingbullet_tr[i + 10]->SetPosition(Vector3(_pos.x - edidpos, _pos.y + 35, -255));
						Rising[i + 10]->SetState(eState::Active);

						edidpos += 25;
						lastActivatedIndex = i + 1; 
						continue; 
					}
				}
			}
			else
			{
				_SkillB_Switch = true;
				_state = _state = Layana_Sisters_State::Skill_B_RisingPierce_End;
				if (_Dir == 1)
					at->PlayAnimation(L"Long_hairSkill_B_RisingPierce_End", true);
				else
					at->PlayAnimation(L"Long_hairSkill_B_RisingPierce_EndR", true);
				_Attacktime = 0;
				edidpos = 20;
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
					Dimension_Bullet->SetState(eState::Active);
				}		
				else
				{					
					Dimension_Bullet->SetDirection(-1);
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
					Dimension_Bullet->SetState(eState::Active);
				}				
			}
			_SkillC_Switch = true;
		}
		else
		{
			_Attacktime += Time::DeltaTime();

			if (_Attacktime >= 2 && _Attacktime < 3)
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
				_state = Layana_Sisters_State::Idle;
				_Attacktime = 0;
				_SkillC_Switch = false;
			}
		}
	}


	void Layana_LongHair::AwakenJump()
	{
		if (_Awaken_Ready == true)
		{
			_state = Layana_Sisters_State::AwakenReady;
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


	void Layana_LongHair::BackGround_Move()
	{
		if (_BackGround_Idle == true)
		{
			_state = Layana_Sisters_State::BackGround_Idle;
			at->PlayAnimation(L"Long_hairBackGround_Idle", false);
		}
	}
	void Layana_LongHair::BackGround_Idle()
	{
		_pos.z = -100;		
	}


	void Layana_LongHair::Rush_Combo()
	{
		_RushSwitch = true;
		_Rushnumber = 0;
		if (_Playerdistance.x <= 30 && _Playerdistance.x >= -30)
		{
			_state = Layana_Sisters_State::Rush_Ready;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairRush_Ready", true);
			else
				at->PlayAnimation(L"Long_hairRush_ReadyR", true);
		}
		else
		{
			_state = Layana_Sisters_State::Dash;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairDash", true);
			else
				at->PlayAnimation(L"Long_hairDashR", true);
		}	
	}
	void Layana_LongHair::Complete_Rush()
	{
		
		if (_Rushnumber >= 3)
		{
			_state = Layana_Sisters_State::Rush_End;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairRush_End", true);
			else
				at->PlayAnimation(L"Long_hairRush_EndR", true);
		}
		else
		{		
			_state = Layana_Sisters_State::Rush_Ready;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairRush_Ready", true);
			else
				at->PlayAnimation(L"Long_hairRush_ReadyR", true);
		}
	}
	void Layana_LongHair::Complete_RushReady()
	{		
		if (_Rushnumber == 0)
		{
			_state = Layana_Sisters_State::RushA;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairRushA", true);
			else
				at->PlayAnimation(L"Long_hairRushAR", true);
		}
		if (_Rushnumber == 1)
		{
			_state = Layana_Sisters_State::RushB;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairRushB", true);
			else
				at->PlayAnimation(L"Long_hairRushBR", true);
		}
		if (_Rushnumber == 2)
		{
			_state = Layana_Sisters_State::RushC;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairRushC", true);
			else
				at->PlayAnimation(L"Long_hairRushCR", true);
		}
		if (_Rushnumber >= 3)
		{
			_state = Layana_Sisters_State::Idle;
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
			_state = Layana_Sisters_State::Meteor_Cross_Jump;
			if (_Dir == 1)
			{
				at->PlayAnimation(L"Long_hairMeteor_Cross00_JumpR", false);
				_rigidbody->SetVelocity(Vector2(250.f, 300.f));
				_rigidbody->SetGround(false);
			}
			else
			{
				at->PlayAnimation(L"Long_hairMeteor_Cross00_Jump", false);
				_rigidbody->SetVelocity(Vector2(-250.f, 300.f));
				_rigidbody->SetGround(false);
			}
		}
		else
		{
			_state = Layana_Sisters_State::Dash;
			if (_Dir == 1)
				at->PlayAnimation(L"Long_hairDash", true);
			else
				at->PlayAnimation(L"Long_hairDashR", true);
		}
	}
	void Layana_LongHair::Complete_CrossJump()
	{
		_state = Layana_Sisters_State::Meteor_Cross_Attack;
		if (_Dir == 1)
		at->PlayAnimation(L"Long_hairMeteor_Cross04_AttackR", false);		
		else
		at->PlayAnimation(L"Long_hairMeteor_Cross04_Attack", false);
	}
	void Layana_LongHair::Complete_CrossLanding()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairMeteor_Cross03_End", true);
		else
			at->PlayAnimation(L"Long_hairMeteor_Cross03_EndR", true);
		_state = Layana_Sisters_State::Meteor_Cross_End;		
	}
	void Layana_LongHair::Complete_CrossEnd()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairIdle", true);
		else
			at->PlayAnimation(L"Long_hairIdleR", true);
		_state = Layana_Sisters_State::Idle;
		_time = 0;
		_CrossMeteorSwitch = false;
		_CrossMeteorLanding = false;
	}


	void Layana_LongHair::Meteor_Ground_Combo()
	{
		_GroundMeteorSwitch = true; // 이동이 되었을때 공격하는 모션 온
		_state = Layana_Sisters_State::FlyDash;
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairDash", true);
		else
			at->PlayAnimation(L"Long_hairDashR", true);
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
			_state = Layana_Sisters_State::Idle;

			_time = 0;
		_GroundMeteorSwitch = false;
		_GroundMeteorLanding = false;
		_GroundMeteorAttack_Right = false;
		_GroundMeteorAttack_Left = false;
	}


	void Layana_LongHair::Meteor_Vertical_Combo()
	{
		_VerticalMeteorSwitch = true;
		_state = Layana_Sisters_State::FlyDash;
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairDash", true);
		else
			at->PlayAnimation(L"Long_hairDashR", true);
	}	
	void Layana_LongHair::Complete_VerticalJump()
	{
		_Ground_check = false;
		_pos.x = _Playerpos.x;
		_state = Layana_Sisters_State::Meteor_Vertical_Ready;
		at->PlayAnimation(L"Long_hairMeteor_Vertical01_Ready", true);
	}
	void Layana_LongHair::Complete_VerticalReady()
	{
		_state = Layana_Sisters_State::Meteor_Vertical_Landing;
		_Ground_check = false;
		_pos.x = _Playerpos.x;
		at->PlayAnimation(L"Long_hairMeteor_Vertical02_Attack", false);
		_rigidbody->SetGround(false);
		_rigidbody->SetVelocity(Vector2(0.f, -350.f));
		//if (_Dir == 1)
		//	at->PlayAnimation(L"Long_hairMeteor_Vertical02_Attack", false);
		//else
		//	at->PlayAnimation(L"Long_hairMeteor_Vertical02_AttackR", false);
	}
	void Layana_LongHair::Complete_VerticalEnd()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairIdle", true);
		else
			at->PlayAnimation(L"Long_hairIdleR", true);
		_state = Layana_Sisters_State::Idle;
		
		_time = 0;
		_VerticalMeteorSwitch = false;
		_VerticalMeteorLanding = false;
	}


	void Layana_LongHair::Skill_A_Combo()
	{
		_SkillA_Switch = true;
		if (_SkillA_Switch == true)
		{
			_state =  Layana_Sisters_State::Skill_A_Bullet_Ready;
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
		_state = Layana_Sisters_State::Idle;

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
		_state = Layana_Sisters_State::Skill_B_RisingPierce;
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
		_state = Layana_Sisters_State::Idle;

		_time = 0.f;
		_SkillB_Switch = false;
	}


	void Layana_LongHair::Skill_C_Combo()
	{
		_state =  Layana_Sisters_State::Skill_C_DimensionPierce;
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairSkill_C_DimensionPierce", false);
		else
			at->PlayAnimation(L"Long_hairSkill_C_DimensionPierceR", false);
	}


	void Layana_LongHair::Intro_Combo()
	{
		if (_Intro_Switch == false)
		{
			_pos = Vector3(_LongHairCreatepos.x + 150, _LongHairCreatepos.y + 200, _LongHairCreatepos.z);
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
	void Layana_LongHair::Complete_IntroRanding()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairIdle", true);
		else
			at->PlayAnimation(L"Long_hairIdleR", true);
		_Intro_LongHair_END = true;
		_time = 0.f;
		_Attacktime = 0.f;
		_Intro_Switch = false;
		_Intro_Landing = false;
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
			_state = Layana_Sisters_State::AwakenJump;
			_Awaken_Switch = true;
		}
	}
	void Layana_LongHair::Complete_Awaken_Ready()
	{
		_state = Layana_Sisters_State::Awaken;
		at->PlayAnimation(L"Long_hairAwakenR", true);
	}
	void Layana_LongHair::Complete_Awaken()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairIdle", true);
		else
			at->PlayAnimation(L"Long_hairIdleR", true);
		_state = Layana_Sisters_State::Idle;
	
		// 나중에 각성보스 추가시 여기서 변경코드 넣으면됨
		_time = 0.f;
		_Attacktime = 0.f;
		_Awaken_Switch = false;
		_Awaken_Ready = false;
	}


	void Layana_LongHair::BackGround_Combo()
	{
		_BackGround_Switch = true;
		_state = Layana_Sisters_State::FlyDash;
		if (_Dir == 1)
			at->PlayAnimation(L"Long_hairDash", true);
		else
			at->PlayAnimation(L"Long_hairDashR", true);
	}


	void Layana_LongHair::die()
	{
	}


	void Layana_LongHair::CreateHoming()
	{
		if (_Attacktime >= 0.5f)
		{
			if (_HomingNumber < 2)
				_HomingNumber++;
			_Attacktime = 0;
		}

		_Attacktime += Time::DeltaTime();
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
			Homing[_HomingNumber]->SetDirection(-1);
			bullet_tr->SetPosition(Vector3(_pos.x + _HomingEditPOS.x, _pos.y + _HomingEditPOS.y, -255));
		}
		else
		{
			bullet_tr->SetRotationZ(0);
			Homing[_HomingNumber]->SetDirection(1);
			bullet_tr->SetPosition(Vector3(_pos.x - _HomingEditPOS.x, _pos.y + _HomingEditPOS.y, -255));
		}
		Homing[_HomingNumber]->SetState(eState::Active);

		if (_HomingNumber >= 2)
		{
			_SkillHomingON = true;
			_HomingNumber = 0;
			_Attacktime = 0;
		}
	}
	void Layana_LongHair::SettingHoming(Transform* set, int angle_of_number)
	{
		Vector2 attackpoint;
		Vector2 rotation;

		if (_LongHairCreatepos.x >= _pos.x)
		{
			//_LongHairCreatepos
			Homing[_HomingNumber]->SetDirection(-1);
			if (_Playerpos.x > 0)			
				Homing[_HomingNumber]->SetDirection(1);			
			attackpoint = Vector2(set->GetPositionX() - _Playerpos.x, set->GetPositionY() + _Playerpos.y);
			rotation = Vector2(_Playerpos.x, _Playerpos.y);
		}
		else
		{
			Homing[_HomingNumber]->SetDirection(1);
			if (_Playerpos.x > 0)
				Homing[_HomingNumber]->SetDirection(-1);
			attackpoint = Vector2(set->GetPositionX() - _Playerpos.x, set->GetPositionY() + _Playerpos.y);
			rotation = Vector2(_Playerpos.x, _Playerpos.y);
		}

		attackpoint.Normalize();
		rotation.Normalize();

		Vector2 direction = attackpoint - rotation; // 플레이어를 향하는 방향 벡터
		float angle = std::atan2(direction.y, direction.x);
		set->SetRotationZ(angle);

		//float dotProduct = attackpoint.Dot(rotation);
		//dotProduct = std::clamp(dotProduct, -1.0f, 1.0f);
		//float angle = std::acos(dotProduct);
		//float angleInDegrees = angle * (180.0f / XM_PI);
		//// 각도방향 결정을 위해 외적사용.
		//float crossProduct = attackpoint.x * rotation.y - attackpoint.y * rotation.x;
		//if (crossProduct < 0)
		//	angleInDegrees = -angleInDegrees;
		//// 0~ 360도 범위로 조정.
		//angleInDegrees = fmod(angleInDegrees + 360.0f, 360.0f);
		//float anglew = angleInDegrees / (180.0f / XM_PI);
		//set->SetRotationZ(anglew);

		if (angle_of_number == 0)
			_HomingAngle[0] = angle;
		if (angle_of_number == 1)
			_HomingAngle[1] = angle;
		if (angle_of_number == 2)
			_HomingAngle[2] = angle;
	}



}