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
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_A_Bullet", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_A_Bullet_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_B_RisingPierce", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_C_DimensionPierce", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Awaken_Power\\Skill_B_RisingPierce_End", this,1);



		//bind 부분
		//at->CompleteEvent(L"Awaken_PowerAwakenEnd") = std::bind(&Layana_Dark_Awaken::Complete_RushReady, this);
		at->CompleteEvent(L"Awaken_PowerRush_Ready") = std::bind(&Layana_Dark_Awaken::Complete_RushReady, this);
		at->CompleteEvent(L"Awaken_PowerRushA") = std::bind(&Layana_Dark_Awaken::Complete_Rush, this);
		at->CompleteEvent(L"Awaken_PowerRushB") = std::bind(&Layana_Dark_Awaken::Complete_Rush, this);
		at->CompleteEvent(L"Awaken_PowerRushC") = std::bind(&Layana_Dark_Awaken::Complete_Rush, this);
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
		at->CompleteEvent(L"Awaken_PowerRushAR") = std::bind(&Layana_Dark_Awaken::Complete_Rush, this);
		at->CompleteEvent(L"Awaken_PowerRushBR") = std::bind(&Layana_Dark_Awaken::Complete_Rush, this);
		at->CompleteEvent(L"Awaken_PowerRushCR") = std::bind(&Layana_Dark_Awaken::Complete_Rush, this);
		at->CompleteEvent(L"Awaken_PowerRush_EndR") = std::bind(&Layana_Dark_Awaken::Complete_RushReady, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Cross01_ReadyR") = std::bind(&Layana_Dark_Awaken::Complete_CrossJump, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Cross03_EndR") = std::bind(&Layana_Dark_Awaken::Complete_CrossEnd, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Ground04_EndR") = std::bind(&Layana_Dark_Awaken::Complete_GroundEnd, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Vertical00_JumpR") = std::bind(&Layana_Dark_Awaken::Complete_VerticalJump, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Vertical01_ReadyR") = std::bind(&Layana_Dark_Awaken::Complete_VerticalReady, this);
		at->CompleteEvent(L"Awaken_PowerMeteor_Vertical04_EndR") = std::bind(&Layana_Dark_Awaken::Complete_VerticalEnd, this);
		at->CompleteEvent(L"Awaken_PowerSkill_A_Bullet_EndR") = std::bind(&Layana_Dark_Awaken::Complete_Skill_A, this);
		at->CompleteEvent(L"Awaken_PowerSkill_B_RisingPierceR") = std::bind(&Layana_Dark_Awaken::Complete_Skill_B, this);



		//for (int i = 0; i < 3; i++)
		//{
		//	Homing[i] = new Homing_Pierce_LongHair;
		//	Homing[i]->Initialize();
		//	Scene* scene = SceneManager::GetActiveScene();
		//	scene->AddGameObject(eLayerType::Bullet, Homing[i]);
		//	Transform* bullet_tr = Homing[i]->GetComponent<Transform>();
		//	bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
		//	Homing[i]->SetState(eState::Paused);
		//}
		//bullet_tr1 = Homing[0]->GetComponent<Transform>();
		//bullet_tr2 = Homing[1]->GetComponent<Transform>();
		//bullet_tr3 = Homing[2]->GetComponent<Transform>();
		//bullet_rb1 = Homing[0]->GetComponent<RigidBody>();
		//bullet_rb2 = Homing[1]->GetComponent<RigidBody>();
		//bullet_rb3 = Homing[2]->GetComponent<RigidBody>();

		//for (int a = 0; a < 19; a++)
		//{
		//	Rising[a] = new Rising_Pierce;
		//	Rising[a]->Initialize();
		//	Scene* scene = SceneManager::GetActiveScene();
		//	scene->AddGameObject(eLayerType::Bullet, Rising[a]);
		//	Risingbullet_tr[a] = Rising[a]->GetComponent<Transform>();
		//	Risingbullet_tr[a]->SetPosition(Vector3(_pos.x, _pos.y, -205));
		//	Rising[a]->SetState(eState::Paused);
		//}

		//{
		//	Dimension_boss_effect = new Dimension_Pierce_BossEffect;
		//	Dimension_boss_effect->Initialize();
		//	Scene* scene = SceneManager::GetActiveScene();
		//	scene->AddGameObject(eLayerType::Effect, Dimension_boss_effect);
		//	Transform* boss_effect = Dimension_boss_effect->GetComponent<Transform>();
		//	boss_effect->SetPosition(Vector3(_pos.x, _pos.y, -205));
		//	Dimension_boss_effect->SetState(eState::Paused);
		//}

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

		case jk::Layana_Dark_Awaken::Layana_Dark_Awaken_State::RushC:
			Layana_Dark_Awaken::Rush_C();
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
		_SelectAttack = 3;

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
	}
	void Layana_Dark_Awaken::Rush_B()
	{
	}
	void Layana_Dark_Awaken::Rush_C()
	{
	}
	void Layana_Dark_Awaken::Rush_End()
	{
		_RushSwitch = false;
	}


	void Layana_Dark_Awaken::CrossJump()
	{
		if (_velocity.y <= -0.1f)
		{
			_rigidbody->ClearVelocity();
			_rigidbody->SetGround(true);

			if (_Dir == 1)
				at->PlayAnimation(L"Awaken_PowerMeteor_Cross01_Ready", true);
			else
				at->PlayAnimation(L"Awaken_PowerMeteor_Cross01_ReadyR", true);
			_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Cross_Ready;
			_Ground_check = false;
		}
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
				float angle = 45 / (180.0f / XM_PI);
				tr->SetRotationZ(angle);
			}
			else
			{
				at->PlayAnimation(L"Awaken_PowerMeteor_Cross04_AttackR", false);
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
			_DarkMode_state = Layana_Dark_Awaken_State::Dash;
			if (_Dir == 1)
				at->PlayAnimation(L"Awaken_PowerDash", true);
			else
				at->PlayAnimation(L"Awaken_PowerDashR", true);
		}
	}
	void Layana_Dark_Awaken::Complete_Rush()
	{
		if (_Rushnumber >= 3)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::Rush_End;
			if (_Dir == 1)
				at->PlayAnimation(L"Awaken_PowerRush_End", true);
			else
				at->PlayAnimation(L"Awaken_PowerRush_EndR", true);
		}
		else
		{
			_DarkMode_state = Layana_Dark_Awaken_State::Dash;
			if (_Dir == 1)
				at->PlayAnimation(L"Awaken_PowerDash", true);
			else
				at->PlayAnimation(L"Awaken_PowerDashR", true);
		}
	}
	void Layana_Dark_Awaken::Complete_RushReady()
	{
		if (_Rushnumber == 0)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::RushA;
			if (_Dir == 1)
				at->PlayAnimation(L"Awaken_PowerRushA", true);
			else
				at->PlayAnimation(L"Awaken_PowerRushAR", true);
		}
		if (_Rushnumber == 1)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::RushB;
			if (_Dir == 1)
				at->PlayAnimation(L"Awaken_PowerRushB", true);
			else
				at->PlayAnimation(L"Awaken_PowerRushBR", true);
		}
		if (_Rushnumber == 2)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::RushC;
			if (_Dir == 1)
				at->PlayAnimation(L"Awaken_PowerRushC", true);
			else
				at->PlayAnimation(L"Awaken_PowerRushCR", true);
		}
		if (_Rushnumber >= 3)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::Idle;
			if (_Dir == 1)
				at->PlayAnimation(L"Awaken_PowerIdle", true);
			else
				at->PlayAnimation(L"Awaken_PowerIdleR", true);
			_time = 0;
		}
		_Rushnumber++;
	}


	void Layana_Dark_Awaken::Meteor_Cross_Combo()
	{
		_CrossMeteorSwitch = true;
		if (_Playerdistance.x <= 30 && _Playerdistance.x >= -30)
		{
			_DarkMode_state = Layana_Dark_Awaken_State::Meteor_Cross_Jump;
			if (_Dir == 1)
			{
				at->PlayAnimation(L"Awaken_PowerMeteor_Cross00_Jump", false);
				_rigidbody->SetVelocity(Vector2(250.f, 450.f));
				_rigidbody->SetGround(false);
			}
			else
			{
				at->PlayAnimation(L"Awaken_PowerMeteor_Cross00_JumpR", false);
				_rigidbody->SetVelocity(Vector2(-250.f, 450.f));
				_rigidbody->SetGround(false);
			}
		}
		else
		{
			_DarkMode_state = Layana_Dark_Awaken_State::Dash;
			if (_Dir == 1)
				at->PlayAnimation(L"Awaken_PowerDash", true);
			else
				at->PlayAnimation(L"Awaken_PowerDashR", true);
		}
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