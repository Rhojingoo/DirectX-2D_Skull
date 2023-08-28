#include "Layana_Dark_Awaken.h"


namespace jk
{
	bool Layana_Dark_Awaken::_AttackStageON = true;
	Layana_Dark_Awaken::Layana_Dark_Awaken_State Layana_Dark_Awaken::_DarkMode_state = Layana_Dark_Awaken_State();


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
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Die", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Death", this);
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
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_C_DimensionPierce", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_B_RisingPierce_End", this);

		
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\AwakenEnd", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Backstep", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Dash", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Die", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Death", this,1);
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
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_C_DimensionPierce", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_B_RisingPierce_End", this,1);


		
		//bind 부분
		//at->CompleteEvent(L"Awaken_PowerAwakenEnd") = std::bind(&Layana_Dark_Awaken::Complete_RushReady, this);
		at->CompleteEvent(L"Awaken_PowerRush_Ready") = std::bind(&Layana_Dark_Awaken::Complete_RushReady, this);
		at->CompleteEvent(L"Awaken_PowerRushC_1") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C1, this);
		at->CompleteEvent(L"Awaken_PowerRushC_2") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C2, this);
		at->CompleteEvent(L"Awaken_PowerRushC_3") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C3, this);
		at->CompleteEvent(L"Awaken_PowerRushC_4") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C4, this);
		at->CompleteEvent(L"Awaken_PowerRushC_5") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C5, this);
		at->CompleteEvent(L"Awaken_PowerRushC_6") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C6, this);
		at->CompleteEvent(L"Awaken_PowerRushC_7") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C7, this);
		at->CompleteEvent(L"Awaken_PowerRush_End") = std::bind(&Layana_Dark_Awaken::Complete_RushReady, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Cross01_Ready") = std::bind(&Layana_Dark_Awaken::Complete_CrossJump, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Cross03_End") = std::bind(&Layana_Dark_Awaken::Complete_CrossEnd, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Ground04_End") = std::bind(&Layana_Dark_Awaken::Complete_GroundEnd, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Vertical00_Jump") = std::bind(&Layana_Dark_Awaken::Complete_VerticalJump, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Vertical01_Ready") = std::bind(&Layana_Dark_Awaken::Complete_VerticalReady, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Vertical04_End") = std::bind(&Layana_Dark_Awaken::Complete_VerticalEnd, this);
		at->CompleteEvent(L"Awaken_PowerSkill_A_Bullet_End") = std::bind(&Layana_Dark_Awaken::Complete_Skill_A, this);
		at->CompleteEvent(L"Awaken_PowerSkill_B_RisingPierce") = std::bind(&Layana_Dark_Awaken::Complete_Skill_B, this);


		//at->CompleteEvent(L"Awaken_PowerAwakenEndR") = std::bind(&Layana_Dark_Awaken::Complete_RushReady, this);
		at->CompleteEvent(L"Awaken_PowerRush_ReadyR") = std::bind(&Layana_Dark_Awaken::Complete_RushReady, this);
		at->CompleteEvent(L"Awaken_PowerRushC_1R") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C1, this);
		at->CompleteEvent(L"Awaken_PowerRushC_2R") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C2, this);
		at->CompleteEvent(L"Awaken_PowerRushC_3R") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C3, this);
		at->CompleteEvent(L"Awaken_PowerRushC_4R") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C4, this);
		at->CompleteEvent(L"Awaken_PowerRushC_5R") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C5, this);
		at->CompleteEvent(L"Awaken_PowerRushC_6R") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C6, this);
		at->CompleteEvent(L"Awaken_PowerRushC_7R") = std::bind(&Layana_Dark_Awaken::Complete_Rush_C7, this);
		at->CompleteEvent(L"Awaken_PowerRush_EndR") = std::bind(&Layana_Dark_Awaken::Complete_RushReady, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Cross01_ReadyR") = std::bind(&Layana_Dark_Awaken::Complete_CrossJump, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Cross03_EndR") = std::bind(&Layana_Dark_Awaken::Complete_CrossEnd, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Ground04_EndR") = std::bind(&Layana_Dark_Awaken::Complete_GroundEnd, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Vertical00_JumpR") = std::bind(&Layana_Dark_Awaken::Complete_VerticalJump, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Vertical01_ReadyR") = std::bind(&Layana_Dark_Awaken::Complete_VerticalReady, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Vertical04_EndR") = std::bind(&Layana_Dark_Awaken::Complete_VerticalEnd, this);
		at->CompleteEvent(L"Awaken_PowerSkill_A_Bullet_EndR") = std::bind(&Layana_Dark_Awaken::Complete_Skill_A, this);
		at->CompleteEvent(L"Awaken_PowerSkill_B_RisingPierceR") = std::bind(&Layana_Dark_Awaken::Complete_Skill_B, this);



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
			scene->AddGameObject(eLayerType::Effect, Rush_Bullet[i]);
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

		//{
		//	Dimension_Bullet = new Dimension_Pierce;
		//	Dimension_Bullet->Initialize();
		//	Scene* scene = SceneManager::GetActiveScene();
		//	scene->AddGameObject(eLayerType::Bullet, Dimension_Bullet);
		//	Transform* boss_effect = Dimension_Bullet->GetComponent<Transform>();
		//	boss_effect->SetPosition(Vector3(_pos.x, _pos.y, -205));
		//	Dimension_Bullet->SetState(eState::Paused);
		//}

		//{
		//	Dimension_BulletEffect = new Dimension_Pierce_BulletEffect;
		//	Dimension_BulletEffect->Initialize();
		//	Scene* scene = SceneManager::GetActiveScene();
		//	scene->AddGameObject(eLayerType::Bullet, Dimension_BulletEffect);
		//	Transform* bullte_effect = Dimension_BulletEffect->GetComponent<Transform>();
		//	bullte_effect->SetPosition(Vector3(_pos.x, _pos.y, -205));
		//	Dimension_BulletEffect->SetState(eState::Paused);
		//}

		//{
		//	TwinMeteor_Impact = new TwinMeteor_Effect;
		//	TwinMeteor_Impact->Initialize();
		//	Scene* scene = SceneManager::GetActiveScene();
		//	scene->AddGameObject(eLayerType::Bullet, TwinMeteor_Impact);
		//	Transform* bullte_effect = TwinMeteor_Impact->GetComponent<Transform>();
		//	bullte_effect->SetPosition(Vector3(_pos.x, _pos.y, -205));
		//	TwinMeteor_Impact->SetState(eState::Paused);
		//}

		//{
		//	TwinMeteor_BossEffect = new TwinMeteor_Boss;
		//	TwinMeteor_BossEffect->Initialize();
		//	Scene* scene = SceneManager::GetActiveScene();
		//	scene->AddGameObject(eLayerType::Bullet, TwinMeteor_BossEffect);
		//	Transform* bullte_effect = TwinMeteor_BossEffect->GetComponent<Transform>();
		//	bullte_effect->SetPosition(Vector3(_pos.x, _pos.y, -205));
		//	TwinMeteor_BossEffect->SetState(eState::Paused);
		//}

		at->PlayAnimation(L"Awaken_PowerIdle", true);
		GameObject::Initialize();
	}
	void Layana_Dark_Awaken::Update()
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



		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Dash:
			Layana_Dark_Awaken::Dash();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::FlyDash:
			Layana_Dark_Awaken::FlyDash();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::LandingDash:
			Layana_Dark_Awaken::LandingDash();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::BackStep:
			Layana_Dark_Awaken::BackStep();
			break;




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

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Skill_B_RisingPierce:
			Layana_Dark_Awaken::Skill_B();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Skill_B_RisingPierce_End:
			Layana_Dark_Awaken::Skill_B_End();
			break;

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::Skill_C_DimensionPierce:
			Layana_Dark_Awaken::Skill_C();
			break;


		default:
			break;
		}		


		tr->SetPosition(_pos);
		GameObject::Update();
	}
	void Layana_Dark_Awaken::LateUpdate()
	{
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
				if 	(_DarkMode_state == Layana_Dark_Awaken_State::Meteor_Cross_Landing)
				{
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
		//_SelectAttack = random(0, 6);
		_SelectAttack = 1;

		//if (Input::GetKeyDown(eKeyCode::K))
		//{
		//	_SelectAttack = 9;
		//}

		//if (_Intro_On == true) // 어웨이큰 On 만들어야함.★★★★★★★★★★★★★★★★★★★★
		//	Awaken_Combo();
		//else
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


				if (_SelectAttack == 7)  //지울것
					BackGround_Combo();


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
					_pos.x = _Playerpos.x - 15;
					_teleport_Rush = false;
				}
				else
				{
					_pos.x = _Playerpos.x + 15;					
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
					_teleport_Rush = false;
				}
				else
				{
					_pos.x = _Playerpos.x + 15;
					_pos.y = _Createpos.y + 150;
					_teleport_Rush = false;
				}
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
	}


	void Layana_Dark_Awaken::Dash()
	{
		if (!(_Playerdistance.x <= 30 && _Playerdistance.x >= -30))
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
			if (_GroundMeteorSwitch == true)
			{
				_DarkMode_state = Layana_Dark_Awaken_State::LandingDash;
				_Ground_check = false;
				_rigidbody->SetGround(false);
				if (_pos.x < _Createpos.x)
				{
					_rigidbody->SetVelocity(Vector2(650.f, -150.f));
					at->PlayAnimation(L"Awaken_PowerDash", true);
				}
				else
				{
					_rigidbody->SetVelocity(Vector2(-650.f, -150.f));
					at->PlayAnimation(L"Awaken_PowerDashR", true);
				}
			}
			if (_VerticalMeteorSwitch == true)
			{
				_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Vertical_Jump;
				_Ground_check = false;
				_pos.x = _Playerpos.x;
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
		_Attacktime += Time::DeltaTime();
		if (_GroundMeteorLanding == true)
		{
			if (_Attacktime >= 1.f)
			{
				_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Ground_Attack;

				if (_Dir == 1)
				{
					at->PlayAnimation(L"Awaken_PowerMeteor_Ground02_Attack", true);
					_rigidbody->SetVelocity(Vector2(700.f, 0.f));
					_GroundMeteorAttack_Right = true;
				}
				else
				{
					at->PlayAnimation(L"Awaken_PowerMeteor_Ground02_AttackR", true);
					_rigidbody->SetVelocity(Vector2(-700.f, 0.f));
					_GroundMeteorAttack_Left = true;
				}
				_Attacktime = 0;
			}
		}
	}
	void Layana_Dark_Awaken::BackStep()
	{
	}


	void Layana_Dark_Awaken::Rushready()
	{
	}
	void Layana_Dark_Awaken::Rush_A()
	{
		_Attacktime += Time::DeltaTime();
		if (_Attacktime > 0.5)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::Rush_End;
			if (_Dir == 1)
				at->PlayAnimation(L"Awaken_PowerRush_End", true);
			else
				at->PlayAnimation(L"Awaken_PowerRush_EndR", true);
			_Rushnumber = 1;
			_Attacktime = 0;
		}		
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
		if (_Rushnumber >= 3)
		{
			_RushSwitch = false;
			_DarkMode_state = Layana_Dark_Awaken_State::Rush_Ready;
		}
		else
			_DarkMode_state = Layana_Dark_Awaken_State::Telleport_In;
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
			}
			else
			{
				at->PlayAnimation(L"Awaken_PowerMeteor_Cross04_AttackR", false);
				float angle = -15 / (180.0f / XM_PI);
				tr->SetRotationZ(angle);
			}
		}
		//몸땡이 발사
		{
			Vector2 attack_pos = Vector2(_Playerpos.x - _pos.x, _Playerpos.y - _pos.y);
			attack_pos.Normalize();
			_rigidbody->SetGround(false);
			_Ground_check = false;
			_rigidbody->SetVelocity(Vector2(attack_pos.x * 550.f, attack_pos.y * 650));
			_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Cross_Landing;
		}
	}
	void Layana_Dark_Awaken::CrossLanding()
	{
		if (_CrossMeteorLanding == true)
			Complete_CrossLanding();
	}
	void Layana_Dark_Awaken::CrossEnd()
	{
	}


	void Layana_Dark_Awaken::GroundReady()
	{
	}
	void Layana_Dark_Awaken::GroundAttack()
	{
		if (_GroundMeteorAttack_Right == true)
		{
			if (_pos.x >= _Createpos.x + 312)
			{
				_rigidbody->ClearVelocity();
				_GroundMeteorAttack_Right = false;
				_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Ground_End;
				if (_Dir == 1)
					at->PlayAnimation(L"Awaken_PowerMeteor_Ground04_End", true);
				else
					at->PlayAnimation(L"Awaken_PowerMeteor_Ground04_EndR", true);
			}
		}
		if (_GroundMeteorAttack_Left == true)
		{
			if (_pos.x <= _Createpos.x - 312)
			{
				_rigidbody->ClearVelocity();
				_GroundMeteorAttack_Left = false;
				_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Ground_End;
				if (_Dir == 1)
					at->PlayAnimation(L"Awaken_PowerMeteor_Ground04_End", true);
				else
					at->PlayAnimation(L"Awaken_PowerMeteor_Ground04_EndR", true);
			}
		}
	}
	void Layana_Dark_Awaken::GroundLanding()
	{
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
	void Layana_Dark_Awaken::Skill_B()
	{
	}
	void Layana_Dark_Awaken::Skill_B_End()
	{
	}
	void Layana_Dark_Awaken::Skill_C()
	{
	}
	void Layana_Dark_Awaken::die()
	{
	}
	void Layana_Dark_Awaken::death()
	{
	}


	void Layana_Dark_Awaken::Complete_Telleport_In()
	{
	}
	void Layana_Dark_Awaken::Complete_Telleport_Out()
	{
	}


	void Layana_Dark_Awaken::Complete_Skill_A()
	{
	}
	void Layana_Dark_Awaken::Complete_Skill_B()
	{
	}


	void Layana_Dark_Awaken::Awaken_Combo()
	{
	}


	void Layana_Dark_Awaken::Rush_Combo()
	{
		_RushSwitch = true;
		_Rushnumber = 0;
		if (_Playerdistance.x <= 30 && _Playerdistance.x >= -30)
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
				at->PlayAnimation(L"Awaken_PowerRushA", false);
			else
				at->PlayAnimation(L"Awaken_PowerRushAR", false);
		}
		if (_Rushnumber == 1)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::RushB;
			if (_Dir == 1)
			{
				_BulletDir = 1;
				at->PlayAnimation(L"Awaken_PowerRushB", false);
			}
			else
			{
				_BulletDir = -1;
				at->PlayAnimation(L"Awaken_PowerRushBR", false);
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
		_DarkMode_state = Layana_Dark_Awaken_State::FlyDash;
		if (_pos.x > _Createpos.x)
			at->PlayAnimation(L"Awaken_PowerDash", true);
		else
			at->PlayAnimation(L"Awaken_PowerDashR", true);
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
		_DarkMode_state = Layana_Dark_Awaken_State::FlyDash;
		if (_pos.x > _Createpos.x)
			at->PlayAnimation(L"Awaken_PowerDash", true);
		else
			at->PlayAnimation(L"Awaken_PowerDashR", true);
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
		_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Vertical_Landing;
		_Ground_check = false;
		_pos.x = _Playerpos.x;
		at->PlayAnimation(L"Awaken_PowerMeteor_Vertical02_Attack", false);
		_rigidbody->SetGround(false);
		_rigidbody->SetVelocity(Vector2(0.f, -450.f));
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
	void Layana_Dark_Awaken::Skill_B_Combo()
	{
	}
	void Layana_Dark_Awaken::Skill_C_Combo()
	{
	}


	void Layana_Dark_Awaken::BackGround_Combo()
	{
	}


	void Layana_Dark_Awaken::CreateHoming()
	{
	}
	void Layana_Dark_Awaken::SettingHoming(Transform* set, int angle_of_number)
	{
	}
}