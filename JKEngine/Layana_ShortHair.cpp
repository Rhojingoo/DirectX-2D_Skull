#include "Layana_ShortHair.h"

jk::Layana_ShortHair::Layana_ShortHair()
{
	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
}
jk::Layana_ShortHair::~Layana_ShortHair()
{
}



void jk::Layana_ShortHair::Initialize()
{
	_collider = AddComponent<Collider2D>();
	_rigidbody = AddComponent<RigidBody>();
	_rigidbody->SetMass(1.f);
	_rigidbody->SetGround(false);


	tr = GetComponent<Transform>();
	_pos = Vector3(0.f, 0.f, -200.f);
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


	//bind ºÎºÐ
	//at->CompleteEvent(L"Short_hairRush_Ready_S") = std::bind(&Layana_ShortHair::Complete_RushReady, this);
	//at->CompleteEvent(L"Short_hairRushA_S") = std::bind(&Layana_ShortHair::Complete_Rush, this);
	//at->CompleteEvent(L"Short_hairRushB_S") = std::bind(&Layana_ShortHair::Complete_Rush, this);
	//at->CompleteEvent(L"Short_hairRushC_S") = std::bind(&Layana_ShortHair::Complete_Rush, this);
	//at->CompleteEvent(L"Short_hairRush_End_S") = std::bind(&Layana_ShortHair::Complete_RushReady, this);
	//at->CompleteEvent(L"Short_hairMeteor_Cross01_Ready_S") = std::bind(&Layana_ShortHair::Complete_CrossJump, this);
	//at->CompleteEvent(L"Short_hairMeteor_Cross03_End_S") = std::bind(&Layana_ShortHair::Complete_CrossEnd, this);
	//at->CompleteEvent(L"Short_hairMeteor_Ground01_Ready_S") = std::bind(&Layana_ShortHair::Complete_GroundLanding, this);
	//at->CompleteEvent(L"Short_hairMeteor_Ground04_End_S") = std::bind(&Layana_ShortHair::Complete_GroundEnd, this);
	//at->CompleteEvent(L"Short_hairMeteor_Vertical00_Jump_S") = std::bind(&Layana_ShortHair::Complete_VerticalJump, this);
	//at->CompleteEvent(L"Short_hairMeteor_Vertical01_Ready_S") = std::bind(&Layana_ShortHair::Complete_VerticalReady, this);
	//at->CompleteEvent(L"Short_hairMeteor_Vertical04_End_S") = std::bind(&Layana_ShortHair::Complete_VerticalEnd, this);
	//at->CompleteEvent(L"Short_hairSkill_A_Bullet_End_S") = std::bind(&Layana_ShortHair::Complete_Skill_A, this);
	//at->CompleteEvent(L"Short_hairSkill_B_RisingPierce_End_S") = std::bind(Layana_ShortHair::Complete_Skill_B, this);
	//at->CompleteEvent(L"Short_hairIntro_Landing_S") = std::bind(&Layana_ShortHair::Complete_IntroRanding, this);
	//at->CompleteEvent(L"Short_hairAwaken_S") = std::bind(&Layana_ShortHair::Complete_Awaken, this);
	//at->CompleteEvent(L"Short_hairAwakenReadyR_S") = std::bind(&Layana_ShortHair::Complete_Awaken_Ready, this);


	//at->CompleteEvent(L"Short_hairRush_Ready_SR") = std::bind(&Layana_ShortHair::Complete_RushReady, this);
	//at->CompleteEvent(L"Short_hairRushA_SR") = std::bind(&Layana_ShortHair::Complete_Rush, this);
	//at->CompleteEvent(L"Short_hairRushB_SR") = std::bind(&Layana_ShortHair::Complete_Rush, this);
	//at->CompleteEvent(L"Short_hairRushC_SR") = std::bind(&Layana_ShortHair::Complete_Rush, this);
	//at->CompleteEvent(L"Short_hairRush_End_SR") = std::bind(&Layana_ShortHair::Complete_RushReady, this);
	//at->CompleteEvent(L"Short_hairMeteor_Cross01_Ready_SR") = std::bind(&Layana_ShortHair::Complete_CrossJump, this);
	//at->CompleteEvent(L"Short_hairMeteor_Cross03_End_SR") = std::bind(&Layana_ShortHair::Complete_CrossEnd, this);
	//at->CompleteEvent(L"Short_hairMeteor_Ground01_Ready_SR") = std::bind(&Layana_ShortHair::Complete_GroundLanding, this);
	//at->CompleteEvent(L"Short_hairMeteor_Ground04_End_SR") = std::bind(&Layana_ShortHair::Complete_GroundEnd, this);
	//at->CompleteEvent(L"Short_hairMeteor_Vertical00_Jump_SR") = std::bind(&Layana_ShortHair::Complete_VerticalJump, this);
	//at->CompleteEvent(L"Short_hairMeteor_Vertical01_Ready_SR") = std::bind(&Layana_ShortHair::Complete_VerticalReady, this);
	//at->CompleteEvent(L"Short_hairMeteor_Vertical04_End_SR") = std::bind(&Layana_ShortHair::Complete_VerticalEnd, this);
	//at->CompleteEvent(L"Short_hairSkill_A_Bullet_End_SR") = std::bind(&Layana_ShortHair::Complete_Skill_A, this);
	//at->CompleteEvent(L"Short_hairSkill_B_RisingPierce_End_SR") = std::bind(Layana_ShortHair::Complete_Skill_B, this);
	//at->CompleteEvent(L"Short_hairIntro_Landing_SR") = std::bind(&Layana_ShortHair::Complete_IntroRanding, this);
	//at->CompleteEvent(L"Short_hairAwaken_SR") = std::bind(&Layana_ShortHair::Complete_Awaken, this);
	//at->CompleteEvent(L"Short_hairAwakenReadyR_SR") = std::bind(&Layana_ShortHair::Complete_Awaken_Ready, this);
	

	for (int i = 0; i < 3; i++)
	{
		Homing[i] = new Homing_Pierce;
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


	at->PlayAnimation(L"Short_hairIdle_S", true);
	GameObject::Initialize();
}
void jk::Layana_ShortHair::Update()
{
	_Playerpos = Player::GetPlayer_Pos();
	_velocity = _rigidbody->GetVelocity();
	_Playerdistance.x = _Playerpos.x - _pos.x;
	_Playerdistance.y = _Playerpos.y - _pos.y;
	if (_Playerdistance.x >= 0)
		mDir = 1;
	else
		mDir = -1;
	_pos = tr->GetPosition();

	switch (_state)
	{
	case jk::Layana_Sisters::Layana_Sisters_State::Idle:
		Layana_ShortHair::idle();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Rush_Ready:
		Layana_ShortHair::Rushready();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::RushA:
		Layana_ShortHair::Rush_A();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::RushB:
		Layana_ShortHair::Rush_B();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::RushC:
		Layana_ShortHair::Rush_C();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Rush_End:
		Layana_ShortHair::Rush_End();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Dash:
		Layana_ShortHair::Dash();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::FlyDash:
		Layana_ShortHair::FlyDash();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::LandingDash:
		Layana_ShortHair::LandingDash();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::BackStep:
		Layana_ShortHair::BackStep();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Ready:
		Layana_ShortHair::CrossReady();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Jump:
		Layana_ShortHair::CrossJump();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Attack:
		Layana_ShortHair::CrossAttack();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Landing:
		Layana_ShortHair::CrossLanding();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_End:
		Layana_ShortHair::CrossEnd();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_Ready:
		Layana_ShortHair::GroundReady();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_Attack:
		Layana_ShortHair::GroundAttack();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_Landing:
		Layana_ShortHair::GroundLanding();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_End:
		Layana_ShortHair::GroundEnd();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_Jump:
		Layana_ShortHair::Vertical_Jump();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_Ready:
		Layana_ShortHair::Vertical_Ready();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_Attack:
		Layana_ShortHair::Vertical_Attack();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_Landing:
		Layana_ShortHair::Vertical_Landing();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_End:
		Layana_ShortHair::Vertical_End();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Skill_A_Bullet_Ready:
		Layana_ShortHair::Skill_A_Ready();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Skill_A_Bullet:
		Layana_ShortHair::Skill_A();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Skill_A_Bullet_End:
		Layana_ShortHair::Skill_A_End();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Skill_B_RisingPierce:
		Layana_ShortHair::Skill_B();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Skill_B_RisingPierce_End:
		Layana_ShortHair::Skill_B_End();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Skill_C_DimensionPierce:
		Layana_ShortHair::Skill_C();
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

	case jk::Layana_Sisters::Layana_Sisters_State::AwakenJump:
		Layana_ShortHair::AwakenJump();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::AwakenReady:
		Layana_ShortHair::AwakenReady();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::Awaken:
		Layana_ShortHair::Awaken();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::BackGround_Idle:
		Layana_ShortHair::BackGround_Idle();
		break;

	case jk::Layana_Sisters::Layana_Sisters_State::BackGround_Move:
		Layana_ShortHair::BackGround_Move();
		break;

	default:
		break;
	}

	tr->SetPosition(_pos);

	GameObject::Update();
}
void jk::Layana_ShortHair::LateUpdate()
{
	_collider->SetSize(Vector2(0.1f, 0.55f));
	_collider->SetCenter(Vector2(0.0f, -20.5f));
	GameObject::LateUpdate();
}
void jk::Layana_ShortHair::Render()
{
	GameObject::Render();
}



void jk::Layana_ShortHair::OnCollisionEnter(Collider2D* other)
{
}
void jk::Layana_ShortHair::OnCollisionStay(Collider2D* other)
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
			//if (_state == Layana_Sisters_State::Meteor_Cross_Landing)
			//{
			//	if (mDir == 1)
			//		at->PlayAnimation(L"Long_hairMeteor_Cross02_Landing", true);
			//	else
			//		at->PlayAnimation(L"Long_hairMeteor_Cross02_LandingR", true);
			//	tr->SetRotationZ(0.f);
			//	_CrossMeteorLanding = true;
			//}
			//if (_state == Layana_Sisters_State::LandingDash)
			//{
			//	if (mDir == 1)
			//		at->PlayAnimation(L"Long_hairMeteor_Ground01_Ready", true);
			//	else
			//		at->PlayAnimation(L"Long_hairMeteor_Ground01_ReadyR", true);
			//	_GroundMeteorLanding = true;
			//}
			//if (_state == Layana_Sisters_State::Meteor_Vertical_Landing)
			//{
			//	if (mDir == 1)
			//		at->PlayAnimation(L"Long_hairMeteor_Vertical03_Landing", true);
			//	else
			//		at->PlayAnimation(L"Long_hairMeteor_Vertical03_LandingR", true);
			//	_VerticalMeteorLanding = true;
			//}
			////if (_state == Layana_Sisters_State::Skill_A_Bullet_Ready)
			////{
			////	if (mDir == 1)
			////		at->PlayAnimation(L"Long_hairSkill_A_Bullet_Ready", true);
			////	else
			////		at->PlayAnimation(L"Long_hairSkill_A_Bullet_ReadyR", true);					
			////	_SkillA_Landing = true;
			////}
			//if (_state == Layana_Sisters_State::Intro_Fall)
			//{
			//	at->PlayAnimation(L"Long_hairIntro_Landing", false);
			//	_Intro_Landing = true;
			//}
			//if (_state == Layana_Sisters_State::AwakenJump)
			//	_Awaken_Ready = true;


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
void jk::Layana_ShortHair::OnCollisionExit(Collider2D* other)
{
}



void jk::Layana_ShortHair::idle()
{
}

void jk::Layana_ShortHair::die()
{
}
