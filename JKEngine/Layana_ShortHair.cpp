#include "Layana_ShortHair.h"

namespace jk
{
	bool Layana_ShortHair::_AttackStageON = true;
	Layana_ShortHair::Layana_ShortHair_State Layana_ShortHair::_ShortHair_state = Layana_ShortHair_State();
	Layana_ShortHair::Layana_Short_Background Layana_ShortHair::Background_state = Layana_Short_Background();



	Layana_ShortHair::Layana_ShortHair()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Layana_ShortHair::~Layana_ShortHair()
	{
	}

	void Layana_ShortHair::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);


		tr = GetComponent<Transform>();
		_pos = Vector3(0.f, 90.f, -200.f);
		_ShortHairCreatepos = _pos;
		tr->SetPosition(_pos);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Awaken_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\AwakenJump_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\AwakenReady_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\BackGround_Idle_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\BackGround_Move_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\BackStep_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Dash_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Die_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Idle_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Intro_Dash_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Intro_Fall_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Intro_Landing_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Intro_Landing_End_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Cross00_Jump_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Cross01_Ready_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Cross02_Landing_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Cross03_End_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Cross04_Attack_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Ground01_Ready_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Ground02_Attack_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Ground03_Landing_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Ground04_End_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical00_Jump_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical01_Ready_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical02_Attack_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical03_Landing_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical04_End_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Rush_End_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Rush_Ready_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushA_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushB_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushC_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Skill_A_Bullet_Ready_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Skill_A_Bullet_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Skill_A_Bullet_End_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Skill_B_RisingPierce_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Skill_B_RisingPierce_End_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Skill_C_DimensionPierce_S", this);
		

		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Awaken_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\AwakenJump_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\AwakenReady_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\BackGround_Idle_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\BackGround_Move_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\BackStep_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Dash_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Die_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Idle_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Intro_Dash_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Intro_Fall_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Intro_Landing_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Intro_Landing_End_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Cross00_Jump_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Cross01_Ready_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Cross02_Landing_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Cross03_End_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Cross04_Attack_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Ground01_Ready_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Ground02_Attack_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Ground03_Landing_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Ground04_End_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical00_Jump_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical01_Ready_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical02_Attack_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical03_Landing_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical04_End_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Rush_End_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Rush_Ready_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushA_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushB_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushC_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Skill_A_Bullet_Ready_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Skill_A_Bullet_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Skill_A_Bullet_End_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Skill_B_RisingPierce_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Skill_B_RisingPierce_End_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Skill_C_DimensionPierce_S", this, 1);
		
		
		//bind 부분
		at->CompleteEvent(L"Short_hairRush_Ready_S") = std::bind(&Layana_ShortHair::Complete_RushReady, this);
		at->CompleteEvent(L"Short_hairRushA_S") = std::bind(&Layana_ShortHair::Complete_Rush, this);
		at->CompleteEvent(L"Short_hairRushB_S") = std::bind(&Layana_ShortHair::Complete_Rush, this);
		at->CompleteEvent(L"Short_hairRushC_S") = std::bind(&Layana_ShortHair::Complete_Rush, this);
		at->CompleteEvent(L"Short_hairRush_End_S") = std::bind(&Layana_ShortHair::Complete_RushReady, this);
		at->CompleteEvent(L"Short_hairMeteor_Cross01_Ready_S") = std::bind(&Layana_ShortHair::Complete_CrossJump, this);
		at->CompleteEvent(L"Short_hairMeteor_Cross03_End_S") = std::bind(&Layana_ShortHair::Complete_CrossEnd, this);
		//at->CompleteEvent(L"Short_hairMeteor_Ground01_Ready_S") = std::bind(&Layana_ShortHair::Complete_GroundLanding, this);
		at->CompleteEvent(L"Short_hairMeteor_Ground04_End_S") = std::bind(&Layana_ShortHair::Complete_GroundEnd, this);
		at->CompleteEvent(L"Short_hairMeteor_Vertical00_Jump_S") = std::bind(&Layana_ShortHair::Complete_VerticalJump, this);
		at->CompleteEvent(L"Short_hairMeteor_Vertical01_Ready_S") = std::bind(&Layana_ShortHair::Complete_VerticalReady, this);
		at->CompleteEvent(L"Short_hairMeteor_Vertical04_End_S") = std::bind(&Layana_ShortHair::Complete_VerticalEnd, this);
		at->CompleteEvent(L"Short_hairSkill_A_Bullet_End_S") = std::bind(&Layana_ShortHair::Complete_Skill_A, this);
		at->CompleteEvent(L"Short_hairSkill_B_RisingPierce_End_S") = std::bind(&Layana_ShortHair::Complete_Skill_B, this);
		at->CompleteEvent(L"Short_hairIntro_Landing_S") = std::bind(&Layana_ShortHair::Complete_IntroLanding, this);
		at->CompleteEvent(L"Short_hairIntro_Landing_End_S") = std::bind(&Layana_ShortHair::Complete_IntroLanding_END, this);
		at->CompleteEvent(L"Short_hairAwaken_S") = std::bind(&Layana_ShortHair::Complete_Awaken, this);
		at->CompleteEvent(L"Short_hairAwakenReady_S") = std::bind(&Layana_ShortHair::Complete_Awaken_Ready, this);


		at->CompleteEvent(L"Short_hairRush_Ready_SR") = std::bind(&Layana_ShortHair::Complete_RushReady, this);
		at->CompleteEvent(L"Short_hairRushA_SR") = std::bind(&Layana_ShortHair::Complete_Rush, this);
		at->CompleteEvent(L"Short_hairRushB_SR") = std::bind(&Layana_ShortHair::Complete_Rush, this);
		at->CompleteEvent(L"Short_hairRushC_SR") = std::bind(&Layana_ShortHair::Complete_Rush, this);
		at->CompleteEvent(L"Short_hairRush_End_SR") = std::bind(&Layana_ShortHair::Complete_RushReady, this);
		at->CompleteEvent(L"Short_hairMeteor_Cross01_Ready_SR") = std::bind(&Layana_ShortHair::Complete_CrossJump, this);
		at->CompleteEvent(L"Short_hairMeteor_Cross03_End_SR") = std::bind(&Layana_ShortHair::Complete_CrossEnd, this);
		//at->CompleteEvent(L"Short_hairMeteor_Ground01_Ready_SR") = std::bind(&Layana_ShortHair::Complete_GroundLanding, this);
		at->CompleteEvent(L"Short_hairMeteor_Ground04_End_SR") = std::bind(&Layana_ShortHair::Complete_GroundEnd, this);
		at->CompleteEvent(L"Short_hairMeteor_Vertical00_Jump_SR") = std::bind(&Layana_ShortHair::Complete_VerticalJump, this);
		at->CompleteEvent(L"Short_hairMeteor_Vertical01_Ready_SR") = std::bind(&Layana_ShortHair::Complete_VerticalReady, this);
		at->CompleteEvent(L"Short_hairMeteor_Vertical04_End_SR") = std::bind(&Layana_ShortHair::Complete_VerticalEnd, this);
		at->CompleteEvent(L"Short_hairSkill_A_Bullet_End_SR") = std::bind(&Layana_ShortHair::Complete_Skill_A, this);
		at->CompleteEvent(L"Short_hairSkill_B_RisingPierce_End_SR") = std::bind(&Layana_ShortHair::Complete_Skill_B, this);
		at->CompleteEvent(L"Short_hairIntro_Landing_SR") = std::bind(&Layana_ShortHair::Complete_IntroLanding, this);
		at->CompleteEvent(L"Short_hairIntro_Landing_End_SR") = std::bind(&Layana_ShortHair::Complete_IntroLanding_END, this);
		at->CompleteEvent(L"Short_hairAwaken_SR") = std::bind(&Layana_ShortHair::Complete_Awaken, this);
		at->CompleteEvent(L"Short_hairAwakenReady_SR") = std::bind(&Layana_ShortHair::Complete_Awaken_Ready, this); 


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
			Homing[i] = new Homing_Pierce_ShortHair;
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



		for (int a = 0; a < 19; a++)
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


		at->PlayAnimation(L"Short_hairIdle_S", true);
		GameObject::Initialize();
	}
	void Layana_ShortHair::Update()
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
		ShortHairPos = _pos;

		if (Joint_Operation == true)
		{
			switch (_state)
			{
			case jk::Layana_Sisters::Layana_Sisters_State::Idle:
				Layana_ShortHair::idle();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Intro_Dash:
				Layana_ShortHair::Intro_Dash();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Intro_Fall:
				Layana_ShortHair::Intro_Fall();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Intro_Landing:
				Layana_ShortHair::Intro_Landing();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Intro_Landing_End:
				Layana_ShortHair::Intro_Landing_End();
				break;


			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_Set:
				Layana_ShortHair::Sisters_Attack_Set();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_FlyDash:
				Layana_ShortHair::Sisters_Attack_FlyDash();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_Fall:
				Layana_ShortHair::Sisters_Attack_Fall();
				break;


			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_A_Ready:
				Layana_ShortHair::Sisters_Attack_A_Ready();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_A_LandingDash:
				Layana_ShortHair::Sisters_Attack_A_LandingDash();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_A:
				Layana_ShortHair::Sisters_Attack_A();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_A_End:
				Layana_ShortHair::Sisters_Attack_A_End();
				break;


			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_B_Ready:
				Layana_ShortHair::Sisters_Attack_B_Ready();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_B_BulletCreate:
				Layana_ShortHair::Sisters_Attack_B_BulletCreate();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_B:
				Layana_ShortHair::Sisters_Attack_B();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_B_End:
				Layana_ShortHair::Sisters_Attack_B_End();
				break;


			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_C_Ready:
				Layana_ShortHair::Sisters_Attack_C_Ready();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_C:
				Layana_ShortHair::Sisters_Attack_C();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_C_Landing:
				Layana_ShortHair::Sisters_Attack_C_Landing();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_C_End:
				Layana_ShortHair::Sisters_Attack_C_End();
				break;

			default:
				break;
			}
		}


		if (ShortHair_Operation == true)
		{
			switch (_ShortHair_state)//_LongHair_state
			{
			case jk::Layana_ShortHair::Layana_ShortHair_State::Idle:
				Layana_ShortHair::idle();
				break;
				
			case jk::Layana_ShortHair::Layana_ShortHair_State::Rush_Ready:
				Layana_ShortHair::Rushready();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::RushA:
				Layana_ShortHair::Rush_A();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::RushB:
				Layana_ShortHair::Rush_B();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::RushC:
				Layana_ShortHair::Rush_C();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Rush_End:
				Layana_ShortHair::Rush_End();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Dash:
				Layana_ShortHair::Dash();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::FlyDash:
				Layana_ShortHair::FlyDash();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::LandingDash:
				Layana_ShortHair::LandingDash();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::BackStep:
				Layana_ShortHair::BackStep();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Meteor_Cross_Ready:
				Layana_ShortHair::CrossReady();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Meteor_Cross_Jump:
				Layana_ShortHair::CrossJump();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Meteor_Cross_Attack:
				Layana_ShortHair::CrossAttack();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Meteor_Cross_Landing:
				Layana_ShortHair::CrossLanding();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Meteor_Cross_End:
				Layana_ShortHair::CrossEnd();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Meteor_Ground_Ready:
				Layana_ShortHair::GroundReady();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Meteor_Ground_Attack:
				Layana_ShortHair::GroundAttack();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Meteor_Ground_Landing:
				Layana_ShortHair::GroundLanding();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Meteor_Ground_End:
				Layana_ShortHair::GroundEnd();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Meteor_Vertical_Jump:
				Layana_ShortHair::Vertical_Jump();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Meteor_Vertical_Ready:
				Layana_ShortHair::Vertical_Ready();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Meteor_Vertical_Attack:
				Layana_ShortHair::Vertical_Attack();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Meteor_Vertical_Landing:
				Layana_ShortHair::Vertical_Landing();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Meteor_Vertical_End:
				Layana_ShortHair::Vertical_End();
				break;



			case Layana_ShortHair::Layana_ShortHair_State::Skill_A_Bullet_Ready:
				Layana_ShortHair::Skill_A_Ready();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Skill_A_Bullet:
				Layana_ShortHair::Skill_A();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Skill_A_Bullet_End:
				Layana_ShortHair::Skill_A_End();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Skill_B_RisingPierce:
				Layana_ShortHair::Skill_B();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Skill_B_RisingPierce_End:
				Layana_ShortHair::Skill_B_End();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Skill_C_DimensionPierce:
				Layana_ShortHair::Skill_C();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::AwakenJump:
				Layana_ShortHair::AwakenJump();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::AwakenReady:
				Layana_ShortHair::AwakenReady();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::Awaken:
				Layana_ShortHair::Awaken();
				break;

			default:
				break;
			}
		}


		if (LongHair_Operation == true)
		{
			switch (Background_state)
			{
				case jk::Layana_ShortHair::Layana_Short_Background::Idle:
					Layana_ShortHair::idle();
					break;

				case jk::Layana_ShortHair::Layana_Short_Background::FlyDash:
					Layana_ShortHair::FlyDash();
					break;

				case jk::Layana_ShortHair::Layana_Short_Background::BackGround_Idle:
					Layana_ShortHair::BackGround_Idle();
					break;

				case jk::Layana_ShortHair::Layana_Short_Background::BackGround_Enter:
					Layana_ShortHair::BackGround_Enter();
					break;

				case jk::Layana_ShortHair::Layana_Short_Background::BackGround_Exit:
					Layana_ShortHair::BackGround_Exit();
					break;


				default:
					break;
			}			
		}

		tr->SetPosition(_pos);

		GameObject::Update();
	}
	void Layana_ShortHair::LateUpdate()
	{
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_HitBox_Attack_On == true)
		{
			if (_state == Layana_Sisters_State::Sisters_Attack_A)
			{
				Hit_Box->SetSize(Vector2(55.f, 5.f));
				Hit_Box->SetState(eState::Active);
				if (_HitBox_Dir == 1)	//오른쪽으로 공격할때의 기준
					HitBox_TR->SetPosition(Vector3(_pos.x + 50, _pos.y - 40, _pos.z));
				else					//왼쪽으로 공격할때의 기준
					HitBox_TR->SetPosition(Vector3(_pos.x - 50, _pos.y - 40, _pos.z));
			}
		}
		else
		{
			Hit_Box->SetState(eState::Paused);
		}

		_collider->SetSize(Vector2(0.1f, 0.55f));
		_collider->SetCenter(Vector2(0.0f, -20.5f));
		GameObject::LateUpdate();
	}
	void Layana_ShortHair::Render()
	{
		GameObject::Render();
	}



	void Layana_ShortHair::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_ShortHair::OnCollisionStay(Collider2D* other)
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
				if (_ShortHair_state == Layana_ShortHair_State::Meteor_Cross_Landing)
				{
					if (_Dir == 1)
						at->PlayAnimation(L"Short_hairMeteor_Cross02_Landing_S", true);
					else
						at->PlayAnimation(L"Short_hairMeteor_Cross02_Landing_SR", true);
					tr->SetRotationZ(0.f);
					_CrossMeteorLanding = true;
				}
				if (_ShortHair_state == Layana_ShortHair_State::LandingDash)
				{
					if (_Dir == 1)
						at->PlayAnimation(L"Short_hairMeteor_Ground01_Ready_S", true);
					else
						at->PlayAnimation(L"Short_hairMeteor_Ground01_Ready_SR", true);
					_GroundMeteorLanding = true;
				}
				if (_ShortHair_state == Layana_ShortHair_State::Meteor_Vertical_Landing)
				{
					if (_Dir == 1)
					{
						at->PlayAnimation(L"Short_hairMeteor_Vertical03_Landing_S", true);

						Intro_SM->SetState(eState::Active);
						Intro_SM->SetSwitch(true);
						Transform* SMtr = Intro_SM->GetComponent<Transform>();
						SMtr->SetPosition(_pos.x + 20, _pos.y - 50.f, _pos.z - 1);
					}
					else
					{
						at->PlayAnimation(L"Short_hairMeteor_Vertical03_LandingR_S", true);

						Intro_SM->SetState(eState::Active);
						Intro_SM->SetSwitch(true);
						Transform* SMtr = Intro_SM->GetComponent<Transform>();
						SMtr->SetPosition(_pos.x - 20, _pos.y - 50.f, _pos.z - 1);
					}
					_VerticalMeteorLanding = true;
				}
				if (_ShortHair_state == Layana_ShortHair_State::AwakenJump)
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
					_Intro_Landing = true;
					Intro_SM->SetState(eState::Active);
					Intro_SM->SetSwitch(true);
					Transform* SMtr = Intro_SM->GetComponent<Transform>();
					SMtr->SetPosition(_pos.x + 20, _pos.y - 50.f, _pos.z - 1);
				}

				if (_state == Layana_Sisters_State::Sisters_Attack_Fall)
				{
					if (_Sisters_Attack_A == true)
					{
						if (_pos.x < _ShortHairCreatepos.x)
							at->PlayAnimation(L"Short_hairMeteor_Ground01_Ready_S", false);
						else
							at->PlayAnimation(L"Short_hairMeteor_Ground01_Ready_SR", false);			
						_Sisters_Attack_A = false;
					}
					if (_Sisters_Attack_B == true)
					{
						if (_pos.x < _ShortHairCreatepos.x)
							at->PlayAnimation(L"Short_hairSkill_A_Bullet_Ready_S", false);
						else
							at->PlayAnimation(L"Short_hairSkill_A_Bullet_Ready_SR", false);
						_SistersAttack_B_Ready_ShortHair = true;
						_Sisters_Attack_B = false;
					}			
				}
				if (_state == Layana_Sisters_State::Sisters_Attack_C)
				{
					if (_pos.x < _ShortHairCreatepos.x)
						at->PlayAnimation(L"Short_hairMeteor_Cross02_Landing_S", false);
					else
						at->PlayAnimation(L"Short_hairMeteor_Cross02_Landing_SR", false);
					tr->SetRotationZ(0.f);

					_SistersAttack_C_ShortHair_LAND = true;
				}
			}
		}

		if (Back_ground* mGround = dynamic_cast<Back_ground*>(other->GetOwner()))
		{
			if (_BackGround_check == false)
			{
				_rigidbody->SetGround(true);
				_BackGround_check = true;
				_rigidbody->ClearVelocity();
			}
			else
			{
				if (Background_state == Layana_Short_Background::BackGround_Enter)
				{
					_BackGround_Idle = true;
				}
			}
		}
	}
	void Layana_ShortHair::OnCollisionExit(Collider2D* other)
	{
	}



	void Layana_ShortHair::idle()
	{
		_time += Time::DeltaTime();
		_SelectAttack = random(0, 6);
		//_SelectAttack = 0;

		if (_Intro_On == true)
			Intro_Combo();

		if (LongHair_Operation == true)
		{
			BackGround_Combo();
			_time = 0;
		}
		

		if (ShortHair_Operation == true)
		{

			if (ShortHair_First_moving == true)
			{
				Meteor_Vertical_Combo();
				ShortHair_First_moving = false;
			}
			else
			{
				if (_SistersAttack_Number > 5)
				{
					_Joint_Attack = true;
					_ShortHair_state = Layana_ShortHair_State::FlyDash;
					if (_pos.x > _ShortHairCreatepos.x)
						at->PlayAnimation(L"Short_hairDash_S", true);
					else
						at->PlayAnimation(L"Short_hairDash_SR", true);					
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



	void Layana_ShortHair::Intro_Dash()
	{
		_Attacktime += Time::DeltaTime();
		if (_Attacktime > 1.5 && _Attacktime < 2)
		{
			_rigidbody->ClearVelocity();
			_rigidbody->SetGround(false);
			_pos = Vector3(_ShortHairCreatepos.x - 200, _ShortHairCreatepos.y - 50, _ShortHairCreatepos.z);

			at->PlayAnimation(L"Short_hairIntro_Fall_SR", false);
			_Intro_Fall_ShortHair = true;
			_Ground_check = false;
		}
	}
	void Layana_ShortHair::Intro_Fall()
	{
		if (_Intro_Landing == true)
		{
			at->PlayAnimation(L"Short_hairIntro_Landing_S", true);
			_Intro_Land_ShortHair = true;
		}
	}
	void Layana_ShortHair::Intro_Landing()
	{

	}
	void Layana_ShortHair::Intro_Landing_End()
	{
		if (_Intro_ShortHair_END == true)
		{
			_Sisters_Attack_A_Switch = true;
			_SistersAttack_A_IntroReadyShortHair = true;
			at->PlayAnimation(L"Short_hairDash_SR", true);
			_Intro_ShortHair_END = false;

			Transform* SM_Effect = Dash_SM->GetComponent<Transform>();
			SM_Effect->SetPosition(Vector3(_pos.x + 30, _pos.y - 40, _pos.z - 1));
			Dash_SM->SetDirection(-1);
			Dash_SM->SetSwitch(true);
			Dash_SM->SetState(eState::Active);
		}
	}



	void Layana_ShortHair::Sisters_Attack_Set()
	{
		if (_pos.x > _ShortHairCreatepos.x)
		{
			at->PlayAnimation(L"Short_hairDash_S", true);

			Transform* SM_Effect = Dash_SM->GetComponent<Transform>();
			SM_Effect->SetPosition(Vector3(_pos.x - 30, _pos.y - 40, _pos.z - 1));
			Dash_SM->SetDirection(1);
			Dash_SM->SetSwitch(true);
			Dash_SM->SetState(eState::Active);
		}
		else
		{
			at->PlayAnimation(L"Short_hairDash_SR", true);

			Transform* SM_Effect = Dash_SM->GetComponent<Transform>();
			SM_Effect->SetPosition(Vector3(_pos.x + 30, _pos.y - 40, _pos.z - 1));
			Dash_SM->SetDirection(-1);
			Dash_SM->SetSwitch(true);
			Dash_SM->SetState(eState::Active);
		}
		_AttackStageON = true;
		_SistersAttack_Set_ShortHair = true;

	}
	void Layana_ShortHair::Sisters_Attack_FlyDash()
	{
		_Sisters_Attack_A = _Sisters_Attack_A_Switch;
		_Sisters_Attack_B = _Sisters_Attack_B_Switch;
		if (_AttackStageON == true)
		{
			if (_pos.x < _ShortHairCreatepos.x)
			{
				if (_pos.x > _ShortHairCreatepos.x - 600)
					_pos.x -= 750.f * Time::DeltaTime();
				if (_pos.y < 100)
					_pos.y += 150.f * Time::DeltaTime();
			}
			else
			{
				if (_pos.x < _ShortHairCreatepos.x + 600)
					_pos.x += 750.f * Time::DeltaTime();
				if (_pos.y < 100)
					_pos.y += 150.f * Time::DeltaTime();
			}
			if (_pos.y >=  100.f)
				_AttackStageON = false;
		}
		else
		{
			if (_Sisters_Attack_C_Switch == true)
			{
				if (_SistersAttack_C_Ready_ShortHair == false)
				{
					if (_pos.x >= 0)
					{
						Transform* bullte_effect = TwinMeteor_BossEffect->GetComponent<Transform>();
						bullte_effect->SetPosition(Vector3(_ShortHairCreatepos.x + 50, _pos.y - 200, -205));
						float angle = 30;
						float angleInDegrees = angle * (180.0f / XM_PI);
						bullte_effect->SetRotationZ(angleInDegrees);
						TwinMeteor_BossEffect->SetState(eState::Active);
						_SistersAttack_C_Ready_ShortHair = true;
					}
					else
					{
						Transform* bullte_effect = TwinMeteor_BossEffect->GetComponent<Transform>();
						bullte_effect->SetPosition(Vector3(_ShortHairCreatepos.x - 50, _pos.y - 200, -205));
						float angle = -30;
						float angleInDegrees = angle * (180.0f / XM_PI);
						bullte_effect->SetRotationZ(angleInDegrees);
						TwinMeteor_BossEffect->SetState(eState::Active);
						_SistersAttack_C_Ready_ShortHair = true;
					}
				}
				else
				{
					_Attacktime += Time::DeltaTime();
					if (_Attacktime > 1.5)
					{
						TwinMeteor_BossEffect->SetState(eState::Paused);
						if (_pos.x < _ShortHairCreatepos.x)
						{
							_pos = Vector3(-640.f, _pos.y, _pos.z);
							tr->SetPosition(_pos);							
							float angle = -210;
							float angleInDegrees = angle * (180.0f / XM_PI);
							tr->SetRotationZ(angleInDegrees);
							_rigidbody->SetVelocity(Vector2(1200.f, -150.f));
							_rigidbody->SetGround(false);
							_Ground_check = false;
							at->PlayAnimation(L"Short_hairMeteor_Ground02_Attack_S", true);							
							{
								Transform* bullte_effect = TwinMeteor_Impact->GetComponent<Transform>();
								bullte_effect->SetPosition(Vector3(_ShortHairCreatepos.x - 50, _pos.y - 215, -205));
								float angle = -30;
								float angleInDegrees = angle * (180.0f / XM_PI);								
								bullte_effect->SetRotationZ(angleInDegrees);
								TwinMeteor_Impact->SetState(eState::Active);
							}
							_SistersAttack_C_DashOn_ShortHair = true;
						}
						else
						{
							_pos = Vector3(640.f, _pos.y, _pos.z);
							tr->SetPosition(_pos);
							float angle = -210;
							float angleInDegrees = angle * (180.0f / XM_PI);
							tr->SetRotationZ(angleInDegrees);
							_rigidbody->SetVelocity(Vector2(-1200.f, -150.f));
							_rigidbody->SetGround(false);
							_Ground_check = false;
							at->PlayAnimation(L"Short_hairMeteor_Ground02_Attack_SR", true);							
							{
								Transform* bullte_effect = TwinMeteor_Impact->GetComponent<Transform>();
								bullte_effect->SetPosition(Vector3(_ShortHairCreatepos.x + 50, _pos.y - 215, -205));
								float angle = 30;
								float angleInDegrees = angle * (180.0f / XM_PI);								
								bullte_effect->SetRotationZ(angleInDegrees);
								TwinMeteor_Impact->SetState(eState::Active);
							}
							_SistersAttack_C_DashOn_ShortHair = true;
						}
					}
				}
			}
			if(_Sisters_Attack_C_Switch == false)
			{
				_SistersAttack_FlyDash_ShortHair = true;
				_Ground_check = false;
				_rigidbody->SetGround(false);
				if (_pos.x < _ShortHairCreatepos.x)
				{
					_rigidbody->SetVelocity(Vector2(700.f, -350.f));
					at->PlayAnimation(L"Short_hairDash_S", true);
					_HitBox_Dir = 1;
				}
				else
				{
					_rigidbody->SetVelocity(Vector2(-700.f, -350.f));
					at->PlayAnimation(L"Short_hairDash_SR", true);
					_HitBox_Dir = -1;
				}
			}
		}
		
	}
	void Layana_ShortHair::Sisters_Attack_Fall()
	{
		if (_Sisters_Attack_A == false)
		{
			_Attacktime += Time::DeltaTime();
			if (_Attacktime > 0.3)
			{
				_SistersAttack_A_Ready_ShortHair = true;
				_Attacktime = 0;
			}
		}
	}



	void Layana_ShortHair::Sisters_Attack_A_Ready()
	{
	}
	void Layana_ShortHair::Sisters_Attack_A_LandingDash()
	{
		if (_SistersAttack_A_DashOn == true)
		{	
			_Attacktime += Time::DeltaTime();
			if (_Attacktime >= 1.f)
			{
				if (_pos.x < _ShortHairCreatepos.x)
				{
					at->PlayAnimation(L"Short_hairMeteor_Ground02_Attack_S", false);
					_rigidbody->SetVelocity(Vector2(900.f, 0.f));
					_GroundMeteorAttack_Right = true;

					Transform* SM_Effect = MeteorGR_SM->GetComponent<Transform>();
					SM_Effect->SetPosition(Vector3(_pos.x - 100, _pos.y - 30, _pos.z - 1));
					MeteorGR_SM->SetDirection(1);
					MeteorGR_SM->SetSwitch(true);
					MeteorGR_SM->SetState(eState::Active);
				}
				else
				{
					at->PlayAnimation(L"Short_hairMeteor_Ground02_Attack_SR", false);
					_rigidbody->SetVelocity(Vector2(-900.f, 0.f));
					_GroundMeteorAttack_Left = true;

					Transform* SM_Effect = MeteorGR_SM->GetComponent<Transform>();
					SM_Effect->SetPosition(Vector3(_pos.x + 100, _pos.y - 30, _pos.z - 1));
					MeteorGR_SM->SetDirection(-1);
					MeteorGR_SM->SetSwitch(true);
					MeteorGR_SM->SetState(eState::Active);
				}
				_Attacktime = 0;
				_SistersAttack_A_DashOn_ShortHair = true;
				_SistersAttack_A_IntroReadyShortHair = false;
			}			
		}
	}
	void Layana_ShortHair::Sisters_Attack_A()
	{
		_HitBox_Attack_On = true;
		if (_GroundMeteorAttack_Right == true)
		{
			if (_pos.x >= _ShortHairCreatepos.x + 312)
			{
				_rigidbody->ClearVelocity();
				_GroundMeteorAttack_Right = false;
				if (_pos.x > _ShortHairCreatepos.x)
					at->PlayAnimation(L"Short_hairMeteor_Ground03_Landing_S", false);
				else
					at->PlayAnimation(L"Short_hairMeteor_Ground03_Landing_SR", false);		
				_SistersAttack_A_ShortHair_END = true;
				_HitBox_Attack_On = false;
			}
			
		}
		if (_GroundMeteorAttack_Left == true)
		{
			if (_pos.x <= _ShortHairCreatepos.x - 312)
			{
				_rigidbody->ClearVelocity();
				_GroundMeteorAttack_Left = false;
				if (_pos.x > _ShortHairCreatepos.x)
					at->PlayAnimation(L"Short_hairMeteor_Ground03_Landing_S", false);
				else
					at->PlayAnimation(L"Short_hairMeteor_Ground03_Landing_SR", false);		
				_SistersAttack_A_ShortHair_END = true;
				_HitBox_Attack_On = false;
			}			
		}
	}
	void Layana_ShortHair::Sisters_Attack_A_End()
	{
		if (_SistersAttack_A_ShortHair_END == true)
		{
			if (_pos.x > _ShortHairCreatepos.x)
				at->PlayAnimation(L"Short_hairMeteor_Ground04_End_S", false);
			else
				at->PlayAnimation(L"Short_hairMeteor_Ground04_End_SR", false);
			_SistersAttack_A_ShortHair_END = false;
			_SistersAttack_A_Ready_ShortHair = false;
		}
	}



	void Layana_ShortHair::Sisters_Attack_B_Ready()
	{
		_SkillHomingON = false;
	}
	void Layana_ShortHair::Sisters_Attack_B_BulletCreate()
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
				_SistersAttack_B_BulletOn_ShortHair = true;
				if (_Dir == 1)
					at->PlayAnimation(L"Short_hairSkill_A_Bullet_S", false);
				else
					at->PlayAnimation(L"Short_hairSkill_A_Bullet_SR", false);
				_Bullet_Switch[0] = false;
				_Bullet_Switch[1] = false;
				_Bullet_Switch[2] = false;
			}
		}
	}
	void Layana_ShortHair::Sisters_Attack_B()
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
			_SistersAttack_B_ShortHair_END = true;			
			if (_Dir == 1)
				at->PlayAnimation(L"Short_hairSkill_A_Bullet_End_S", false);
			else
				at->PlayAnimation(L"Short_hairSkill_A_Bullet_End_SR", false);
		}
		
	}
	void Layana_ShortHair::Sisters_Attack_B_End()
	{
		_Sisters_Attack_B_Switch = false;
		_SkillHomingON = false;		
		_HomingNumber = 0;
		_Attacktime = 0.f;
	}



	void Layana_ShortHair::Sisters_Attack_C_Ready()
	{
		_AttackStageON = true;
		_Sisters_Attack_C_Switch = true;
		if (_pos.x > _ShortHairCreatepos.x)
			at->PlayAnimation(L"Short_hairDash_S", true);
		else
			at->PlayAnimation(L"Short_hairDash_SR", true);
		_SistersAttack_C_IntroReadyShortHair = true;
	}
	void Layana_ShortHair::Sisters_Attack_C()
	{
	}
	void Layana_ShortHair::Sisters_Attack_C_Landing()
	{
		if (_SistersAttack_C_ShortHair_LAND == true)
		{
			_Attacktime += Time::DeltaTime();
			if (_Attacktime > 1.5)
			{
				if (_Dir == 1)
					at->PlayAnimation(L"Short_hairMeteor_Cross03_End_S", false);
				else
					at->PlayAnimation(L"Short_hairMeteor_Cross03_End_SR", false);

				_Attacktime = 0;
				_SistersAttack_C_ShortHair_LAND = false;
			}
		}
	}
	void Layana_ShortHair::Sisters_Attack_C_End()
	{
		Transform* bullte_effect = TwinMeteor_BossEffect->GetComponent<Transform>();
		Transform* bullte_imffect = TwinMeteor_Impact->GetComponent<Transform>();
		bullte_effect->SetRotationZ(0);
		bullte_imffect->SetRotationZ(0);
		//if (_Dir == 1)
		//	at->PlayAnimation(L"Short_hairIdle_S", true);
		//else
		//	at->PlayAnimation(L"Short_hairIdle_SR", true);
		_AttackStageON = false;
		_Sisters_Attack_C_Switch = false;
	}



	void Layana_ShortHair::Sisters_Attack_D()
	{
	}



	void Layana_ShortHair::Dash()
	{
		if (!(_Playerdistance.x <= 30 && _Playerdistance.x >= -30))
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
				_ShortHair_state = Layana_ShortHair_State::Rush_Ready;
				if (_Dir == 1)
					at->PlayAnimation(L"Short_hairRush_Ready_S", true);
				else
					at->PlayAnimation(L"Short_hairRush_Ready_SR", true);
			}
			if (_CrossMeteorSwitch == true)
			{
				_ShortHair_state = Layana_ShortHair_State::Meteor_Cross_Jump;
				if (_Dir == 1)
				{
					at->PlayAnimation(L"Short_hairMeteor_Cross00_Jump_SR", false);
					_rigidbody->SetVelocity(Vector2(250.f, 450.f));
					_rigidbody->SetGround(false);
				}
				else
				{
					at->PlayAnimation(L"Short_hairMeteor_Cross00_Jump_S", false);
					_rigidbody->SetVelocity(Vector2(-250.f, 450.f));
					_rigidbody->SetGround(false);
				}
			}
		}
	}
	void Layana_ShortHair::FlyDash()
	{
		if (_pos.x < _ShortHairCreatepos.x)
		{
			if (_pos.x > _ShortHairCreatepos.x - 600)
				_pos.x -= 750.f * Time::DeltaTime();
			if (_pos.y < 100)
				_pos.y += 150.f * Time::DeltaTime();
		}
		else
		{
			if (_pos.x < _ShortHairCreatepos.x + 600)
				_pos.x += 750.f * Time::DeltaTime();
			if (_pos.y < 10)
				_pos.y += 150.f * Time::DeltaTime();
		}
		if (_pos.y >= _ShortHairCreatepos.y + 100.f)
		{
			if (_GroundMeteorSwitch == true)
			{
				_ShortHair_state = Layana_ShortHair_State::LandingDash;
				_Ground_check = false;
				_rigidbody->SetGround(false);
				if (_pos.x < _ShortHairCreatepos.x)
				{
					_rigidbody->SetVelocity(Vector2(700.f, -350.f));
					at->PlayAnimation(L"Short_hairDash_S", true);
					_HitBox_Dir = 1;
				}
				else
				{
					_rigidbody->SetVelocity(Vector2(-700.f, -350.f));
					at->PlayAnimation(L"Short_hairDash_SR", true);
					_HitBox_Dir = -1;
				}
			}

			if (_VerticalMeteorSwitch == true)
			{
				_ShortHair_state = Layana_ShortHair_State::Meteor_Vertical_Jump;
				_Ground_check = false;
				_pos.x = _Playerpos.x;
				at->PlayAnimation(L"Short_hairMeteor_Vertical00_Jump_S", true);

				//if(mDir ==1)
				//	at->PlayAnimation(L"Short_hairMeteor_Vertical00_Jump_S", true);	
				//else
				//	at->PlayAnimation(L"Short_hairMeteor_Vertical00_Jump_SR", true);
			}

			if (_BackGround_Switch == true)
			{
				_pos = Vector3(_ShortHairCreatepos.x - 50, _ShortHairCreatepos.y + 100, -150.f);
				tr->SetPosition(_pos);
				at->PlayAnimation(L"Short_hairBackGround_Move_S", false);
				Background_state = Layana_Short_Background::BackGround_Enter;
				_rigidbody->SetGround(false);
				_Ground_check = false;
				_BackGround_Switch = false;
				_BackGround_check = false;
			}

			if (_Joint_Attack == true)
			{
				_rigidbody->SetGround(true);
				_Ground_check = false;
				_BackGround_check = true;
				ShortHair_First_moving = true;
				_Joint_Attack = false;
			}
		}
	}
	void Layana_ShortHair::LandingDash()
	{
		_Attacktime += Time::DeltaTime();
		if (_GroundMeteorLanding == true)
		{
			if (_Attacktime >= 1.f)
			{
				_ShortHair_state = Layana_ShortHair_State::Meteor_Ground_Attack;

				if (_Dir == 1)
				{
					at->PlayAnimation(L"Short_hairMeteor_Ground02_Attack_S", true);
					_rigidbody->SetVelocity(Vector2(900.f, 0.f));
					_GroundMeteorAttack_Right = true;

					Transform* SM_Effect = MeteorGR_SM->GetComponent<Transform>();
					SM_Effect->SetPosition(Vector3(_pos.x - 100, _pos.y - 30, _pos.z - 1));
					MeteorGR_SM->SetDirection(1);
					MeteorGR_SM->SetSwitch(true);
					MeteorGR_SM->SetState(eState::Active);
				}
				else
				{
					at->PlayAnimation(L"Short_hairMeteor_Ground02_Attack_SR", true);
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
	void Layana_ShortHair::BackStep()
	{
		//백스텝을 시작으로 뷸렛 시작 코드
		//_Ground_check = false;
		//if (_SkillA_Switch == true)
		//	_state = _state = Layana_Sisters_State::Skill_A_Bullet_Ready;		
		// 이부분이후로 아이들로 가져가면 진행됨
		//	_state = Layana_Sisters_State::BackStep;
		//	_rigidbody->SetGround(false);
		//if (_Dir == 1)
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



	void Layana_ShortHair::Rushready()
	{
	}
	void Layana_ShortHair::Rush_A()
	{
	}
	void Layana_ShortHair::Rush_B()
	{
	}
	void Layana_ShortHair::Rush_C()
	{
	}
	void Layana_ShortHair::Rush_End()
	{
		_RushSwitch = false;
	}



	void Layana_ShortHair::CrossJump()
	{

		if (_velocity.y <= -0.1f)
		{
			_rigidbody->ClearVelocity();
			_rigidbody->SetGround(true);

			if (_Dir == 1)
				at->PlayAnimation(L"Short_hairMeteor_Cross01_Ready_S", true);
			else
				at->PlayAnimation(L"Short_hairMeteor_Cross01_Ready_SR", true);
			_ShortHair_state = Layana_ShortHair_State::Meteor_Cross_Ready;
			_Ground_check = false;
		}
	}
	void Layana_ShortHair::CrossReady()
	{
	}
	void Layana_ShortHair::CrossAttack()
	{
		//몸뚱이 회전
		{
			if (_Playerpos.x >= _pos.x)
			{
				at->PlayAnimation(L"Short_hairMeteor_Cross04_Attack_SR", false);
				float angle = 45 / (180.0f / XM_PI);
				tr->SetRotationZ(angle);
			}
			else
			{
				at->PlayAnimation(L"Short_hairMeteor_Cross04_Attack_SR", false);
				float angle = -45 / (180.0f / XM_PI);
				tr->SetRotationZ(angle);
			}
		}
		//몸땡이 발사
		{

			Vector2 attack_pos = Vector2(_Playerpos.x - _pos.x, _Playerpos.y - _pos.y);
			attack_pos.Normalize();
			_rigidbody->SetGround(false);
			_rigidbody->SetVelocity(Vector2(attack_pos.x * 500.f, attack_pos.y * 500));
			_ShortHair_state = Layana_ShortHair_State::Meteor_Cross_Landing;
		}
	}
	void Layana_ShortHair::CrossLanding()
	{
		if (_CrossMeteorLanding == true)
			Complete_CrossLanding();
	}
	void Layana_ShortHair::CrossEnd()
	{
	}



	void Layana_ShortHair::GroundReady()
	{
	}
	void Layana_ShortHair::GroundAttack()
	{
		if (_GroundMeteorAttack_Right == true)
		{
			if (_pos.x >= _ShortHairCreatepos.x + 312)
			{
				_rigidbody->ClearVelocity();
				_GroundMeteorAttack_Right = false;
				_ShortHair_state = Layana_ShortHair_State::Meteor_Ground_End;
				if (_Dir == 1)
					at->PlayAnimation(L"Short_hairMeteor_Ground04_End_S", true);
				else
					at->PlayAnimation(L"Short_hairMeteor_Ground04_End_SR", true);
			}
		}
		if (_GroundMeteorAttack_Left == true)
		{
			if (_pos.x <= _ShortHairCreatepos.x - 312)
			{
				_rigidbody->ClearVelocity();
				_GroundMeteorAttack_Left = false;
				_ShortHair_state = Layana_ShortHair_State::Meteor_Ground_End;
				if (_Dir == 1)
					at->PlayAnimation(L"Short_hairMeteor_Ground04_End_S", true);
				else
					at->PlayAnimation(L"Short_hairMeteor_Ground04_End_SR", true);
			}
		}
	}
	void Layana_ShortHair::GroundLanding()
	{
	}
	void Layana_ShortHair::GroundEnd()
	{
	}



	void Layana_ShortHair::Vertical_Jump()
	{
	}
	void Layana_ShortHair::Vertical_Ready()
	{
	}
	void Layana_ShortHair::Vertical_Attack()
	{
	}
	void Layana_ShortHair::Vertical_Landing()
	{
		_Attacktime += Time::DeltaTime();
		if (_VerticalMeteorLanding == true)
		{
			if (_Attacktime >= 1.f)
			{
				_ShortHair_state = Layana_ShortHair_State::Meteor_Vertical_End;

				if (_Dir == 1)
					at->PlayAnimation(L"Short_hairMeteor_Vertical04_End_S", true);
				else
					at->PlayAnimation(L"Short_hairMeteor_Vertical04_End_SR", true);
				_Attacktime = 0;
			}
		}
	}
	void Layana_ShortHair::Vertical_End()
	{
	}



	void Layana_ShortHair::Skill_A_Ready()
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
				_ShortHair_state = Layana_ShortHair_State::Skill_A_Bullet;
				if (_Dir == 1)
					at->PlayAnimation(L"Short_hairSkill_A_Bullet_S", false);
				else
					at->PlayAnimation(L"Short_hairSkill_A_Bullet_SR", false);
			}
		}
	}
	void Layana_ShortHair::Skill_A()
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

			_ShortHair_state = Layana_ShortHair_State::Skill_A_Bullet_End;
			if (_Dir == 1)
				at->PlayAnimation(L"Short_hairSkill_A_Bullet_End_S", true);
			else
				at->PlayAnimation(L"Short_hairSkill_A_Bullet_End_SR", true);
		}
	}
	void Layana_ShortHair::Skill_A_End()
	{
		_HomingNumber = 0;
		_Attacktime = 0.f;
	}



	void Layana_ShortHair::Skill_B()
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
				_ShortHair_state = Layana_ShortHair_State::Skill_B_RisingPierce_End;
				if (_Dir == 1)
					at->PlayAnimation(L"Short_hairSkill_B_RisingPierce_End_S", true);
				else
					at->PlayAnimation(L"Short_hairSkill_B_RisingPierce_End_SR", true);
				_Attacktime = 0;
				edidpos = 20;
				lastActivatedIndex = 0;
			}
		}
	}
	void Layana_ShortHair::Skill_B_End()
	{
	}



	void Layana_ShortHair::Skill_C()
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

			if (_Attacktime >= 1 && _Attacktime < 1.5)
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
					at->PlayAnimation(L"Short_hairIdle_S", true);
				else
					at->PlayAnimation(L"Short_hairIdle_SR", true);
				_ShortHair_state = Layana_ShortHair_State::Idle;
				_Attacktime = 0;
				_SkillC_Switch = false;
			}
		}
	}



	void Layana_ShortHair::AwakenJump()
	{
		if (_Awaken_Ready == true)
		{
			_ShortHair_state = Layana_ShortHair_State::AwakenReady;
			at->PlayAnimation(L"Short_hairAwakenReady_SR", true);
			_Awaken_Ready = false;
		}
	}
	void Layana_ShortHair::AwakenReady()
	{
	}
	void Layana_ShortHair::Awaken()
	{
	}



	void Layana_ShortHair::BackGround_Idle()
	{
		if (_SistersAttack_Number >= 2)
		{
			Background_state = Layana_Short_Background::BackGround_Exit;
			at->PlayAnimation(L"Short_hairBackGround_Move_S", false);
			_rigidbody->SetVelocity(Vector2(0.f, 1050.f));
			_rigidbody->SetGround(false);
			_BackGround_check = true;
			_Ground_check = false;
		}
		else
		_pos.z = -100;
	}
	void Layana_ShortHair::BackGround_Enter()
	{
		if (_BackGround_Idle == true)
		{
			Background_state = Layana_Short_Background::BackGround_Idle;
			at->PlayAnimation(L"Short_hairBackGround_Idle_S", false);
			_BackGround_Idle = false;
		}
	}
	void Layana_ShortHair::BackGround_Exit()
	{
		if (_pos.y >= _ShortHairCreatepos.y + 150)
		{
			_rigidbody->SetGround(true);
			if (LongHairPos.x >= _ShortHairCreatepos.x)
			{
				_pos.x = -700;
				_pos.y = 150;
				_pos.z = -200;
			}
			else
			{
				_pos.x = 700;
				_pos.y = 150;
				_pos.z = -200;
			}
			ShortHair_First_moving = true;
			Background_state = Layana_Short_Background::BackGround_Idle;
		}
	}



	void Layana_ShortHair::Rush_Combo()
	{
		_RushSwitch = true;
		_Rushnumber = 0;
		if (_Playerdistance.x <= 30 && _Playerdistance.x >= -30)
		{
			_ShortHair_state = Layana_ShortHair_State::Rush_Ready;
			if (_Dir == 1)
				at->PlayAnimation(L"Short_hairRush_Ready_S", true);
			else
				at->PlayAnimation(L"Short_hairRush_Ready_SR", true);
		}
		else
		{
			_ShortHair_state = Layana_ShortHair_State::Dash;
			if (_Dir == 1)
				at->PlayAnimation(L"Short_hairDash_S", true);
			else
				at->PlayAnimation(L"Short_hairDash_SR", true);
		}


	}
	void Layana_ShortHair::Complete_Rush()
	{
		if (_Rushnumber >= 3)
		{
			_ShortHair_state = Layana_ShortHair_State::Rush_End;
			if (_Dir == 1)
				at->PlayAnimation(L"Short_hairRush_End_S", true);
			else
				at->PlayAnimation(L"Short_hairRush_End_SR", true);
		}
		else
		{
			_ShortHair_state = Layana_ShortHair_State::Dash;
			if (_Dir == 1)
				at->PlayAnimation(L"Short_hairDash_S", true);
			else
				at->PlayAnimation(L"Short_hairDash_SR", true);
		}
	}
	void Layana_ShortHair::Complete_RushReady()
	{
		if (_Rushnumber == 0)
		{
			_ShortHair_state = Layana_ShortHair_State::RushA;
			if (_Dir == 1)
				at->PlayAnimation(L"Short_hairRushA_S", true);
			else
				at->PlayAnimation(L"Short_hairRushA_SR", true);
		}
		if (_Rushnumber == 1)
		{
			_ShortHair_state = Layana_ShortHair_State::RushB;
			if (_Dir == 1)
				at->PlayAnimation(L"Short_hairRushB_S", true);
			else
				at->PlayAnimation(L"Short_hairRushB_SR", true);
		}
		if (_Rushnumber == 2)
		{
			_ShortHair_state = Layana_ShortHair_State::RushC;
			if (_Dir == 1)
				at->PlayAnimation(L"Short_hairRushC_S", true);
			else
				at->PlayAnimation(L"Short_hairRushC_SR", true);
		}
		if (_Rushnumber >= 3)
		{
			_ShortHair_state = Layana_ShortHair_State::Idle;
			if (_Dir == 1)
				at->PlayAnimation(L"Short_hairIdle_S", true);
			else
				at->PlayAnimation(L"Short_hairIdle_SR", true);
			_time = 0;
		}
		_Rushnumber++;
	}



	void Layana_ShortHair::Meteor_Cross_Combo()
	{
		_CrossMeteorSwitch = true;
		if (_Playerdistance.x <= 30 && _Playerdistance.x >= -30)
		{
			_ShortHair_state = Layana_ShortHair_State::Meteor_Cross_Jump;
			if (_Dir == 1)
			{
				at->PlayAnimation(L"Short_hairMeteor_Cross00_Jump_SR", false);
				_rigidbody->SetVelocity(Vector2(250.f, 300.f));
				_rigidbody->SetGround(false);
			}
			else
			{
				at->PlayAnimation(L"Short_hairMeteor_Cross00_Jump_S", false);
				_rigidbody->SetVelocity(Vector2(-250.f, 300.f));
				_rigidbody->SetGround(false);
			}
		}
		else
		{
			_ShortHair_state = Layana_ShortHair_State::Dash;
			if (_pos.x > _ShortHairCreatepos.x)
				at->PlayAnimation(L"Short_hairDash_S", true);
			else
				at->PlayAnimation(L"Short_hairDash_SR", true);
		}
	}
	void Layana_ShortHair::Complete_CrossJump()
	{
		_ShortHair_state = Layana_ShortHair_State::Meteor_Cross_Attack;
		if (_Dir == 1)
			at->PlayAnimation(L"Short_hairMeteor_Cross04_Attack_SR", false);
		else
			at->PlayAnimation(L"Short_hairMeteor_Cross04_Attack_S", false);
	}
	void Layana_ShortHair::Complete_CrossLanding()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Short_hairMeteor_Cross03_End_S", true);
		else
			at->PlayAnimation(L"Short_hairMeteor_Cross03_End_SR", true);
		_ShortHair_state = Layana_ShortHair_State::Meteor_Cross_End;
	}
	void Layana_ShortHair::Complete_CrossEnd()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Short_hairIdle_S", true);
		else
			at->PlayAnimation(L"Short_hairIdle_SR", true);
		_ShortHair_state = Layana_ShortHair_State::Idle;
		_time = 0;
		_CrossMeteorSwitch = false;
		_CrossMeteorLanding = false;
	}



	void Layana_ShortHair::Meteor_Ground_Combo()
	{
		_GroundMeteorSwitch = true; // 이동이 되었을때 공격하는 모션 온
		_ShortHair_state = Layana_ShortHair_State::FlyDash;
		if (_pos.x > _ShortHairCreatepos.x)
		{
			at->PlayAnimation(L"Short_hairDash_S", true);

			Transform* SM_Effect = Dash_SM->GetComponent<Transform>();
			SM_Effect->SetPosition(Vector3(_pos.x - 30, _pos.y - 40, _pos.z - 1));
			Dash_SM->SetDirection(1);
			Dash_SM->SetSwitch(true);
			Dash_SM->SetState(eState::Active);
		}
		else
		{
			at->PlayAnimation(L"Short_hairDash_SR", true);

			Transform* SM_Effect = Dash_SM->GetComponent<Transform>();
			SM_Effect->SetPosition(Vector3(_pos.x + 30, _pos.y - 40, _pos.z - 1));
			Dash_SM->SetDirection(-1);
			Dash_SM->SetSwitch(true);
			Dash_SM->SetState(eState::Active);
		}
	}
	void Layana_ShortHair::Complete_GroundLanding()
	{
		
	}
	void Layana_ShortHair::Complete_GroundEnd()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Short_hairIdle_S", true);
		else
			at->PlayAnimation(L"Short_hairIdle_SR", true);
		_ShortHair_state = Layana_ShortHair_State::Idle;
		_time = 0;

		_GroundMeteorSwitch = false;
		_GroundMeteorLanding = false;
		_GroundMeteorAttack_Right = false;
		_GroundMeteorAttack_Left = false;
	}



	void Layana_ShortHair::Meteor_Vertical_Combo()
	{
		_VerticalMeteorSwitch = true;
		_ShortHair_state = Layana_ShortHair_State::FlyDash;
		if (_pos.x > _ShortHairCreatepos.x)
		{
			at->PlayAnimation(L"Short_hairDash_S", true);

			Transform* SM_Effect = Dash_SM->GetComponent<Transform>();
			SM_Effect->SetPosition(Vector3(_pos.x - 30, _pos.y - 40, _pos.z - 1));
			Dash_SM->SetDirection(1);
			Dash_SM->SetSwitch(true);
			Dash_SM->SetState(eState::Active);
		}
		else
		{
			at->PlayAnimation(L"Short_hairDash_SR", true);

			Transform* SM_Effect = Dash_SM->GetComponent<Transform>();
			SM_Effect->SetPosition(Vector3(_pos.x + 30, _pos.y - 40, _pos.z - 1));
			Dash_SM->SetDirection(-1);
			Dash_SM->SetSwitch(true);
			Dash_SM->SetState(eState::Active);
		}
	}
	void Layana_ShortHair::Complete_VerticalJump()
	{
		_Ground_check = false;
		_pos.x = _Playerpos.x;
		_ShortHair_state = Layana_ShortHair_State::Meteor_Vertical_Ready;
		at->PlayAnimation(L"Short_hairMeteor_Vertical01_Ready_S", true);
	}
	void Layana_ShortHair::Complete_VerticalReady()
	{
		_ShortHair_state = Layana_ShortHair_State::Meteor_Vertical_Landing;
		_Ground_check = false;
		_pos.x = _Playerpos.x;
		at->PlayAnimation(L"Short_hairMeteor_Vertical02_Attack_S", false);
		_rigidbody->SetGround(false);
		_rigidbody->SetVelocity(Vector2(0.f, -350.f));
		//if (_Dir == 1)
		//	at->PlayAnimation(L"Long_hairMeteor_Vertical02_Attack", false);
		//else
		//	at->PlayAnimation(L"Long_hairMeteor_Vertical02_AttackR", false);
	}
	void Layana_ShortHair::Complete_VerticalEnd()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Short_hairIdle_S", true);
		else
			at->PlayAnimation(L"Short_hairIdle_SR", true);
		_ShortHair_state = Layana_ShortHair_State::Idle;

		_time = 0;
		_VerticalMeteorSwitch = false;
		_VerticalMeteorLanding = false;
	}



	void Layana_ShortHair::Skill_A_Combo()
	{
		_SkillA_Switch = true;
		if (_SkillA_Switch == true)
		{
			_ShortHair_state = Layana_ShortHair_State::Skill_A_Bullet_Ready;
			if (_Dir == 1)
				at->PlayAnimation(L"Short_hairSkill_A_Bullet_Ready_S", true);
			else
				at->PlayAnimation(L"Short_hairSkill_A_Bullet_Ready_SR", true);
			_SkillA_Landing = true;
		}
	}
	void Layana_ShortHair::Complete_Skill_A()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Short_hairIdle_S", true);
		else
			at->PlayAnimation(L"Short_hairIdle_SR", true);
		_ShortHair_state = Layana_ShortHair_State::Idle;

		_time = 0.f;
		_SkillA_Switch = false;
		_SkillA_Landing = false;
		_SkillHomingON = false;
		_SkillHomingFire = false;
		_HomingNumber = 0;
		_Attacktime = 0.f;
	}



	void Layana_ShortHair::Skill_B_Combo()
	{
		_ShortHair_state = Layana_ShortHair_State::Skill_B_RisingPierce;
		if (_Dir == 1)
			at->PlayAnimation(L"Short_hairSkill_B_RisingPierce_S", false);
		else
			at->PlayAnimation(L"Short_hairSkill_B_RisingPierce_SR", false);
	}
	void Layana_ShortHair::Complete_Skill_B()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Short_hairIdle_S", true);
		else
			at->PlayAnimation(L"Short_hairIdle_SR", true);
		_ShortHair_state = Layana_ShortHair_State::Idle;

		_time = 0.f;
		_SkillB_Switch = false;
	}



	void Layana_ShortHair::Skill_C_Combo()
	{
		_ShortHair_state = Layana_ShortHair_State::Skill_C_DimensionPierce;
		if (_Dir == 1)
			at->PlayAnimation(L"Short_hairSkill_C_DimensionPierce_S", false);
		else
			at->PlayAnimation(L"Short_hairSkill_C_DimensionPierce_SR", false);
	}



	void Layana_ShortHair::Intro_Combo()
	{
		if (_Intro_Switch == false)
		{
			_pos = Vector3(_ShortHairCreatepos.x - 150, _ShortHairCreatepos.y, _ShortHairCreatepos.z);
			tr->SetPosition(_pos);
			_Intro_Switch = true;
		}
		if (_Intro_Switch == true)
		{
			at->PlayAnimation(L"Short_hairIntro_Dash_SR", false);
			_rigidbody->SetGround(false);
			_rigidbody->SetVelocity(Vector2(-1050.f, 150.f));
			_Intro_Dash_ShortHair = true;
			_Ground_check = false;
			_Intro_Switch = false;
		}
	}
	void Layana_ShortHair::Complete_IntroLanding()
	{
		at->PlayAnimation(L"Short_hairIntro_Landing_End_S", true);
		Transform* ImpactTR = Intro_Ar->GetComponent<Transform>();
		ImpactTR->SetPosition(Vector3(_pos.x,_pos.y-20,_pos.z-1));
		Intro_Ar->SetDirection(1);
		Intro_Ar->SetSwitch(true);
		Intro_Ar->SetState(eState::Active);
		_Intro_LandEnd_ShortHair = true;
		_time = 0.f;
		_Attacktime = 0.f;
		_Intro_Switch = false;
		_Intro_Landing = false;
	}



	void Layana_ShortHair::Complete_IntroLanding_END()
	{
		_Intro_ShortHair_END = true;
	}



	void Layana_ShortHair::Awaken_Combo()
	{
		if (_Awaken_Switch == false)
		{
			_pos = Vector3(_ShortHairCreatepos.x + 200, _ShortHairCreatepos.y - 50, _ShortHairCreatepos.z);
			tr->SetPosition(_pos);
			_rigidbody->SetGround(false);
			_Ground_check = false;
			at->PlayAnimation(L"Short_hairAwakenJump_SR", false);
			_ShortHair_state = Layana_ShortHair_State::AwakenJump;
			_Awaken_Switch = true;
		}
	}
	void Layana_ShortHair::Complete_Awaken_Ready()
	{
		_ShortHair_state = Layana_ShortHair_State::Awaken;
		at->PlayAnimation(L"Short_hairAwaken_SR", true);
	}
	void Layana_ShortHair::Complete_Awaken()
	{
		if (_Dir == 1)
			at->PlayAnimation(L"Short_hairIdle_S", true);
		else
			at->PlayAnimation(L"Short_hairIdle_SR", true);
		_ShortHair_state = Layana_ShortHair_State::Idle;

		// 나중에 각성보스 추가시 여기서 변경코드 넣으면됨
		_time = 0.f;
		_Attacktime = 0.f;
		_Awaken_Switch = false;
		_Awaken_Ready = false;
	}



	void Layana_ShortHair::BackGround_Combo()
	{
		_BackGround_Switch = true;
		Background_state = Layana_Short_Background::FlyDash;
		if (_pos.x > _ShortHairCreatepos.x)
			at->PlayAnimation(L"Short_hairDash_S", true);
		else
			at->PlayAnimation(L"Short_hairDash_SR", true);
	}



	void Layana_ShortHair::die()
	{
	}



	void Layana_ShortHair::CreateHoming()
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
				bullet_tr->SetPosition(Vector3(_pos.x + _HomingEditPOS.x, _pos.y + _HomingEditPOS.y, -255));

				Transform* bullet_tr = Homing_EF[_HomingNumber]->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(_pos.x + _HomingEditPOS.x, _pos.y + _HomingEditPOS.y, -251 - 1));
				Homing_EF[_HomingNumber]->SetSwitch(true);
				Homing_EF[_HomingNumber]->SetDirection(1);
				Homing_EF[_HomingNumber]->SetState(eState::Active);
			}
			else
			{
				bullet_tr->SetRotationZ(0);
				Homing[_HomingNumber]->SetDirection(-1);
				bullet_tr->SetPosition(Vector3(_pos.x - _HomingEditPOS.x, _pos.y + _HomingEditPOS.y, -255));

				Transform* bullet_tr = Homing_EF[_HomingNumber]->GetComponent<Transform>();
				bullet_tr->SetPosition(Vector3(_pos.x - _HomingEditPOS.x, _pos.y + _HomingEditPOS.y, -251 - 1));
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
	void Layana_ShortHair::SettingHoming(Transform* set, int angle_of_number)
	{
		Vector2 attackpoint = {};
		Vector2 rotation = {};

		if (_ShortHairCreatepos.x >= _pos.x)
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

		if (_ShortHairCreatepos.x < _pos.x)
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















