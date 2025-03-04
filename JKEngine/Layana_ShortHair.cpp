#include "Layana_ShortHair.h"
#include "Include_Common.h"
#include "Homing_Pierce_ShortHair.h"
#include "Homing_Impact.h"
#include "Rising_Pierce.h"
#include "Dimension_Pierce.h"
#include "Dimension_Pierce_BossEffect.h"
#include "Dimension_Pierce_BulletEffect.h"
#include "TwinMeteor_Boss.h"
#include "TwinMeteor_Effect.h"
#include "HitBox_Layana.h"
#include "Intro_Somke.h"
#include "Intro_Aura_Layana.h"
#include "Layana_Dash_Smoke.h"
#include "Layana_Meteor_GR_Smoke.h"
#include "RisingPierce_Ready.h"
#include "Golden_Meteor_Bullet.h"
#include "Golden_Meteor_Effect_End.h"
#include "Awaken_Ready_ElectricA.h"
#include "Awaken_Ready_ElectricB.h"
#include "Awaken_SmokeEffect.h"
#include "Awaken_Electric.h"
#include "Monster_Hp_Bar.h"
#include "..\Engine_SOURCE\jkAudioSource.h"


#include "Player_Hit_Effect.h"
#include "Hit_Sword.h"
#include "Hit_Critical_Middle.h"
#include "Hit_Critical_High.h"
#include "Monster_Death_Effect.h"
#include "Monster_Hit_Effect.h"
#include "Alpha_Blend.h"

namespace jk
{
	bool Layana_ShortHair::_AttackStageON = true;
	Layana_ShortHair::Layana_ShortHair_State Layana_ShortHair::_ShortHair_state = Layana_ShortHair_State();
	Layana_ShortHair::Layana_Short_Background Layana_ShortHair::Background_state = Layana_Short_Background();


	int	Layana_ShortHair::_HitType = 0;
	float	Layana_ShortHair::_Damage = 0;
	Monster_Hp_Bar* Layana_ShortHair::ShortHair_Hp = nullptr;
	Monster_Hp_Bar* Layana_ShortHair::ShortHair_Hp_Damage = nullptr;

	Monster_Hit_Effect* Layana_ShortHair::_Hit_Effect = nullptr;
	Player_Hit_Effect* Layana_ShortHair::_Hit_Effect_player = nullptr;
	Hit_Sword* Layana_ShortHair::_Hit_Sword = nullptr;
	Hit_Critical_Middle* Layana_ShortHair::_Critical_Middle = nullptr;
	Hit_Critical_High* Layana_ShortHair::_Critical_High = nullptr;
	Monster_Death_Effect* Layana_ShortHair::_Death_Effect = nullptr;


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


		as = AddComponent<AudioSource>();
		//인트로
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_Enter.wav", "Leiana_Enter");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_Intro_Impact.wav", "Leiana_Intro_Impact");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_Intro_TakeOff.wav", "Leiana_Intro_TakeOff");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_Landing.wav", "Leiana_Landing");
		//그라운드메테오
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_MeteorGround_Ready.wav", "Leiana_MeteorGround_Ready");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_Outro_ArmorStep.wav", "Leiana_Outro_ArmorStep");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_MeteorGround.wav", "Leiana_MeteorGround");
		//골든메테오
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_GoldenMeteor.wav", "Leiana_GoldenMeteor");
		//러쉬 & 디미전
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_DarkDimensionRush_Sign.wav", "rush1");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_DarkDimensionRush_Sign.wav", "rush2");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_DarkDimensionRush_Sign.wav", "rush3");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_DarkDimensionRush_Sign.wav", "rush4");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_DarkDimensionRush_Sign.wav", "rush5");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_DarkDimensionRush_Sign.wav", "rush6");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Hardmode_Leiana_Rush_Impact.wav", "Hardmode_Leiana_Rush_Impact");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_DarkDimensionRush_Sign.wav", "Leiana_DarkDimensionRush_Sign");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_DarkDimensionRush_Impact.wav", "Leiana_DarkDimensionRush_Impact");
		//호밍피서
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_HomingPierce_Ready.wav", "Leiana_HomingPierce_Ready");//생성
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_TwinMeteor.wav", "Homing_Fire1");//발사
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_TwinMeteor.wav", "Homing_Fire2");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_TwinMeteor.wav", "Homing_Fire3");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_DimensionPierce_Impact.wav", "Homing_Hit");//타격시		
		//트윈메테오(크로스)
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_TwinMeteor_Sign.wav", "Leiana_TwinMeteor_Sign");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_TwinMeteor.wav", "Leiana_TwinMeteor");
		//디미전(타격필요)
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_DimensionPierce_Sign.wav", "Leiana_DimensionPierce_Sign");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_DimensionPierce_Impact.wav", "Leiana_DimensionPierce_Impact");
		//죽을때
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_Dead.wav", "Leiana_Dead");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_Awakening_Sign.wav", "Leiana_Awakening_Sign");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_Awakening_Impact.wav", "Leiana_Awakening_Impact");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_Awakening_Outro.wav", "Leiana_Awakening_Outro");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_Awakening.wav", "Leiana_Awakening");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_Scream.wav", "Leiana_Scream");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_Sign.wav", "Leiana_Sign");
			


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
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical00_Jump_S", this,0,0.065f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical01_Ready_S", this,0,0.065f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical02_Attack_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical03_Landing_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical04_End_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Rush_End_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Rush_Ready_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushA_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushB_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushC_S", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushC_S1", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushC_S2", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushC_S3", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushC_S4", this);
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
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical00_Jump_S", this, 1,0.065f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical01_Ready_S", this, 1,0.065f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical02_Attack_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical03_Landing_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Meteor_Vertical04_End_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Rush_End_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\Rush_Ready_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushA_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushB_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushC_S", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushC_S1", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushC_S2", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushC_S3", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Short_hair\\RushC_S4", this, 1);
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
		at->CompleteEvent(L"Short_hairRushC_S1") = std::bind(&Layana_ShortHair::Complete_RushReady, this);
		at->CompleteEvent(L"Short_hairRushC_S2") = std::bind(&Layana_ShortHair::Complete_RushReady, this);
		at->CompleteEvent(L"Short_hairRushC_S3") = std::bind(&Layana_ShortHair::Complete_RushReady, this);
		at->CompleteEvent(L"Short_hairRushC_S4") = std::bind(&Layana_ShortHair::Complete_Rush, this);
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
		at->CompleteEvent(L"Short_hairRushC_S1R") = std::bind(&Layana_ShortHair::Complete_RushReady, this);
		at->CompleteEvent(L"Short_hairRushC_S2R") = std::bind(&Layana_ShortHair::Complete_RushReady, this);
		at->CompleteEvent(L"Short_hairRushC_S3R") = std::bind(&Layana_ShortHair::Complete_RushReady, this);
		at->CompleteEvent(L"Short_hairRushC_S4R") = std::bind(&Layana_ShortHair::Complete_Rush, this);
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
		
		Scene* scene = SceneManager::GetInitializeScene();
		//hp관련
		{
			ShortHair_Hp = new Monster_Hp_Bar(L"BossHealthBar_FirstPhase");
			scene->AddGameObject(eLayerType::Effect, ShortHair_Hp);
			Transform* hp_tr = ShortHair_Hp->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(-65, _pos.y + 50, _pos.z - 1));
			hp_tr->SetScale(127.5, 10, 0);
			ShortHair_Hp->Set_Max_Hp(_Max_ShortHair_Hp);
			ShortHair_Hp->Set_Current_Hp(_Max_ShortHair_Hp);
			ShortHair_Hp->SetState(eState::Active);
		}
		{
			ShortHair_Hp_Damage = new Monster_Hp_Bar(L"EnemyHealthBar_Damage");
			scene->AddGameObject(eLayerType::Effect, ShortHair_Hp_Damage);
			Transform* hp_tr = ShortHair_Hp_Damage->GetComponent<Transform>();
			hp_tr->SetPosition(Vector3(-65.f, _pos.y + 50.f, _pos.z - 1.5f));
			hp_tr->SetScale(127.5f, 10.f, 0.f);
			ShortHair_Hp_Damage->Set_Max_Hp(_Max_ShortHair_Hp);
			ShortHair_Hp_Damage->Set_Current_Hp(_Max_ShortHair_Hp);
			ShortHair_Hp_Damage->Set_Type(1);
			ShortHair_Hp_Damage->SetState(eState::Active);
		}





		{
			Hit_Box = new HitBox_Layana();
			Hit_Box->Initialize();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetState(eState::Paused);
		}

		for (int i = 0; i < 3; i++)
		{
			Homing[i] = new Homing_Pierce_ShortHair;
			Homing[i]->Initialize();
			scene->AddGameObject(eLayerType::Bullet, Homing[i]);
			Transform* bullet_tr = Homing[i]->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			Homing[i]->SetState(eState::Paused);
		}
		for (int i = 0; i < 3; i++)
		{
			Homing_EF[i] = new Homing_Impact;
			Homing_EF[i]->Initialize();
			scene->AddGameObject(eLayerType::Effect, Homing_EF[i]);
			Transform* bullet_tr = Homing_EF[i]->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			Homing_EF[i]->SetState(eState::Paused);
		}



		for (int a = 0; a < 19; a++)
		{
			Rising[a] = new Rising_Pierce;
			Rising[a]->Initialize();
			scene->AddGameObject(eLayerType::Bullet, Rising[a]);
			Risingbullet_tr[a] = Rising[a]->GetComponent<Transform>();
			Risingbullet_tr[a]->SetPosition(Vector3(_pos.x, _pos.y, -205));
			Rising[a]->SetState(eState::Paused);
		}

		{
			Dimension_boss_effect = new Dimension_Pierce_BossEffect;
			Dimension_boss_effect->Initialize();
			scene->AddGameObject(eLayerType::Effect, Dimension_boss_effect);
			Transform* boss_effect = Dimension_boss_effect->GetComponent<Transform>();
			boss_effect->SetPosition(Vector3(_pos.x, _pos.y, -205));
			Dimension_boss_effect->SetState(eState::Paused);
		}


		{
			Dimension_Bullet = new Dimension_Pierce;
			Dimension_Bullet->Initialize();
			scene->AddGameObject(eLayerType::Bullet, Dimension_Bullet);
			Transform* boss_effect = Dimension_Bullet->GetComponent<Transform>();
			boss_effect->SetPosition(Vector3(_pos.x, _pos.y, -205));
			Dimension_Bullet->SetState(eState::Paused);
		}


		{
			Dimension_BulletEffect = new Dimension_Pierce_BulletEffect;
			Dimension_BulletEffect->Initialize();
			scene->AddGameObject(eLayerType::Bullet, Dimension_BulletEffect);
			Transform* bullte_effect = Dimension_BulletEffect->GetComponent<Transform>();
			bullte_effect->SetPosition(Vector3(_pos.x, _pos.y, -205));
			Dimension_BulletEffect->SetState(eState::Paused);
		}
		{
			TwinMeteor_Impact = new TwinMeteor_Effect;
			TwinMeteor_Impact->Initialize();
			scene->AddGameObject(eLayerType::Bullet, TwinMeteor_Impact);
			Transform* bullte_effect = TwinMeteor_Impact->GetComponent<Transform>();
			bullte_effect->SetPosition(Vector3(_pos.x, _pos.y, -205));
			TwinMeteor_Impact->SetState(eState::Paused);
		}
		{
			TwinMeteor_BossEffect = new TwinMeteor_Boss;
			TwinMeteor_BossEffect->Initialize();
			scene->AddGameObject(eLayerType::Bullet, TwinMeteor_BossEffect);
			Transform* bullte_effect = TwinMeteor_BossEffect->GetComponent<Transform>();
			bullte_effect->SetPosition(Vector3(_pos.x, _pos.y, -205));
			TwinMeteor_BossEffect->SetState(eState::Paused);
		}

		{
			Intro_SM = new Intro_Somke;
			Intro_SM->Initialize();
			scene->AddGameObject(eLayerType::Effect, Intro_SM);
			Intro_SM->SetState(eState::Paused);
		}
		{
			Intro_Ar = new Intro_Aura_Layana;
			Intro_Ar->Initialize();
			scene->AddGameObject(eLayerType::Effect, Intro_Ar);
			Intro_Ar->SetState(eState::Paused);
		}

		{
			Dash_SM = new Layana_Dash_Smoke;
			Dash_SM->Initialize();
			scene->AddGameObject(eLayerType::Effect, Dash_SM);
			Dash_SM->SetState(eState::Paused);
		}
		{
			MeteorGR_SM = new Layana_Meteor_GR_Smoke;
			MeteorGR_SM->Initialize();
			scene->AddGameObject(eLayerType::Effect, MeteorGR_SM);
			MeteorGR_SM->SetState(eState::Paused);
		}
		{
			RisingPierce_EF = new RisingPierce_Ready;
			RisingPierce_EF->Initialize();
			scene->AddGameObject(eLayerType::Effect, RisingPierce_EF);
			RisingPierce_EF->SetState(eState::Paused);
		}
		{
			Golden_Meteor_Bl = new Golden_Meteor_Bullet;
			Golden_Meteor_Bl->Initialize();
			scene->AddGameObject(eLayerType::Bullet, Golden_Meteor_Bl);
			Golden_Meteor_Bl->SetState(eState::Paused);
		}
		{
			Golden_Meteor_Ef = new Golden_Meteor_Effect_End;
			Golden_Meteor_Ef->Initialize();
			scene->AddGameObject(eLayerType::Effect, Golden_Meteor_Ef);
			Golden_Meteor_Ef->SetState(eState::Paused);
		}
	


		{
			_Hit_Effect = new Monster_Hit_Effect;
			_Hit_Effect->Initialize();
			scene->AddGameObject(eLayerType::Effect, _Hit_Effect);
			_Hit_Effect->SetState(eState::Paused);
		}

		{
			_Hit_Effect_player = new Player_Hit_Effect;
			_Hit_Effect_player->Initialize();
			scene->AddGameObject(eLayerType::Effect, _Hit_Effect_player);
			_Hit_Effect_player->SetState(eState::Paused);
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


		// 체인지 이펙트관련
		{
			Awaken_Rd_ElectricA = new Awaken_Ready_ElectricA;
			Awaken_Rd_ElectricA->Initialize();
			scene->AddGameObject(eLayerType::Effect, Awaken_Rd_ElectricA);
			Awaken_Rd_ElectricA->SetState(eState::Paused);
		}
		{
			Awaken_Rd_ElectricB = new Awaken_Ready_ElectricB;
			Awaken_Rd_ElectricB->Initialize();
			scene->AddGameObject(eLayerType::Effect, Awaken_Rd_ElectricB);
			Awaken_Rd_ElectricB->SetState(eState::Paused);
		}
		{
			Awaken_Smoke_EF = new Awaken_SmokeEffect;
			Awaken_Smoke_EF->Initialize();
			scene->AddGameObject(eLayerType::Effect, Awaken_Smoke_EF);
			Awaken_Smoke_EF->SetState(eState::Paused);
		}
		{
			Awaken_Elec_EF = new Awaken_Electric;
			Awaken_Elec_EF->Initialize();
			scene->AddGameObject(eLayerType::Effect, Awaken_Elec_EF);
			Awaken_Elec_EF->SetState(eState::Paused);
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

		HitEffect();

		Transform* _HpFrame_tr = _HpBarFrame->GetComponent<Transform>();
		Transform* hp_tr = ShortHair_Hp->GetComponent<Transform>();
		Transform* hp_trDamege = ShortHair_Hp_Damage->GetComponent<Transform>();
		{			
			hp_tr->SetPosition(Vector3(-73.5f, _HpFrame_tr->GetPosition().y - 2.5f, _HpFrame_tr->GetPosition().z - 2.f));
			hp_trDamege->SetPosition(Vector3(-73.5f, _HpFrame_tr->GetPosition().y - 2.5f, _HpFrame_tr->GetPosition().z - 1.f));
		}



		Transform* BulletTR = Golden_Meteor_Bl->GetComponent<Transform>();
		BulletTR->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
	


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

			case jk::Layana_ShortHair::Layana_ShortHair_State::RushC1:
				Layana_ShortHair::Rush_C1();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::RushC2:
				Layana_ShortHair::Rush_C2();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::RushC3:
				Layana_ShortHair::Rush_C3();
				break;

			case jk::Layana_ShortHair::Layana_ShortHair_State::RushC4:
				Layana_ShortHair::Rush_C4();
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

				case jk::Layana_ShortHair::Layana_Short_Background::Die:
					Layana_ShortHair::die();
					break;


				default:
					break;
			}			
		}

		if (_ShortHair_Die == true)
		{
			if (LongHair_Operation == true)
			{
				if (_DieOn == false)
				{
					Background_state = Layana_Short_Background::Die;
					if (_pos.x < _ShortHairCreatepos.x)
						at->PlayAnimation(L"Short_hairDie_S", false);
					else
						at->PlayAnimation(L"Short_hairDie_SR", false);
					_DieOn = true;
				}
			}
		}
		if (_LongHair_Die == true)
		{
			ShortHair_Hp->SetState(eState::Paused);
			ShortHair_Hp_Damage->SetState(eState::Paused);
			ShortHair_Operation = true;
			Awaken_Combo();
			_ShortHair_Awaken = false;
		}


		tr->SetPosition(_pos);

		GameObject::Update();
	}
	void Layana_ShortHair::LateUpdate()
	{
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		if (_HitBox_Attack_On == true)
		{
			if (_state == Layana_Sisters_State::Sisters_Attack_A|| _ShortHair_state == Layana_ShortHair_State::Meteor_Ground_Attack)
			{
				Hit_Box->SetSize(Vector2(55.f, 5.f));
				Hit_Box->SetState(eState::Active);
				if (_HitBox_Dir == 1)	//오른쪽으로 공격할때의 기준
					HitBox_TR->SetPosition(Vector3(_pos.x + 50, _pos.y - 40, _pos.z));
				else					//왼쪽으로 공격할때의 기준
					HitBox_TR->SetPosition(Vector3(_pos.x - 50, _pos.y - 40, _pos.z));
			}
			else if (_ShortHair_state == Layana_ShortHair_State::Meteor_Cross_Landing)
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
			else if (_ShortHair_state == Layana_ShortHair_State::RushA)
			{
				Hit_Box->SetSize(Vector2(55.f, 5.f));
				Hit_Box->SetState(eState::Active);

				if (_HitBox_Dir == 1)	//오른쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x + 90, _pos.y - 25, _pos.z));
				else					//왼쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x - 90, _pos.y - 25, _pos.z));
			}
			else if (_ShortHair_state == Layana_ShortHair_State::RushB)
			{
				Hit_Box->SetSize(Vector2(55.f, 5.f));
				Hit_Box->SetState(eState::Active);

				if (_HitBox_Dir == 1)	//오른쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x + 90, _pos.y - 35, _pos.z));
				else					//왼쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x - 90, _pos.y - 35, _pos.z));
			}
			else if (_ShortHair_state == Layana_ShortHair_State::RushC1)
			{
				Hit_Box->SetSize(Vector2(55.f, 5.f));
				Hit_Box->SetState(eState::Active);

				if (_HitBox_Dir == 1)	//오른쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x + 90, _pos.y - 15, _pos.z));
				else					//왼쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x - 90, _pos.y - 15, _pos.z));
			}
			else if (_ShortHair_state == Layana_ShortHair_State::RushC2)
			{
				Hit_Box->SetSize(Vector2(55.f, 5.f));
				Hit_Box->SetState(eState::Active);
				if (_HitBox_Dir == 1)	//오른쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x + 90, _pos.y - 25, _pos.z));
				else					//왼쪽으로 공격할때의 기준				
					HitBox_TR->SetPosition(Vector3(_pos.x - 90, _pos.y - 25, _pos.z));
			}
			else if (_ShortHair_state == Layana_ShortHair_State::RushC3)
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
	void Layana_ShortHair::Render()
	{
		GameObject::Render();
	}



	void Layana_ShortHair::OnCollisionEnter(Collider2D* other)
	{
		if (Background_state != Layana_Short_Background::Die && Background_state != Layana_Short_Background::BackGround_Idle)
		{
			if (HitBox_Player* player = dynamic_cast<HitBox_Player*>(other->GetOwner()))
			{
				_Damage = player->GetDamage();
				bool attack = player->Geteffect();
				bool attack_Cri_Mid = player->Geteffect_Mid();
				bool attack_Cri_High = player->Geteffect_Hight();
				_Damage = 1000;
				
				_Curren_ShortHair_Hp = _Curren_ShortHair_Hp - _Damage;
				ShortHair_Hp->_HitOn = true;
				ShortHair_Hp->SetHitDamage(_Damage);
				ShortHair_Hp_Damage->_HitOn = true;
				ShortHair_Hp_Damage->Set_Target(_Curren_ShortHair_Hp);				


				{
					_Hit_Effect->_effect_animation = true;
					_Critical_Middle->_effect_animation = true;
					_Critical_High->_effect_animation = true;
					if (_Dir == 1)
					{
						_Hit_Effect->SetDirection(-1);
						_Critical_Middle->SetDirection(-1);
						_Critical_High->SetDirection(-1);
					}
					else
					{
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
				if (_Curren_ShortHair_Hp <= 0)
				{
					if (_First_Die == false)
					{
						as->Play("Leiana_Dead");
						_First_Die = true;
						_ShortHair_Die = true;
					}
				}
			}

			if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
			{
				if (player->_Head_Attack == false && _bulletcheck == 0)
				{
					if (player->_Ground_check == true)
						return;

					_Damage = player->GetDamage();
					bool attack = player->Geteffect();
					bool attack_Cri_Mid = player->Geteffect_Mid();
					bool attack_Cri_High = player->Geteffect_Hight();

					_Curren_ShortHair_Hp = _Curren_ShortHair_Hp - _Damage;
					ShortHair_Hp->_HitOn = true;
					ShortHair_Hp->SetHitDamage(_Damage);
					ShortHair_Hp_Damage->_HitOn = true;
					ShortHair_Hp_Damage->Set_Target(_Curren_ShortHair_Hp);


					_Hit_Effect->_effect_animation = true;
					_Critical_Middle->_effect_animation = true;
					_Critical_High->_effect_animation = true;
					if (_Dir == 1)
					{
						_Hit_Effect->SetDirection(-1);
						_Critical_Middle->SetDirection(-1);
						_Critical_High->SetDirection(-1);
					}
					else
					{
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

					if (_Curren_LongHair_Hp <= 0)
					{
						if (_First_Die == false)
						{
							as->Play("Leiana_Dead");
							_First_Die = true;
							_ShortHair_Die = true;
						}
					}
					_bulletcheck++;
				}
			}
		}
	}
	void Layana_ShortHair::OnCollisionStay(Collider2D* other)
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
					_pos.y = GRpos.y + 95;
					tr->SetPosition(_pos);
				}


				if (_ShortHair_state == Layana_ShortHair_State::Meteor_Cross_Landing)
				{
					as->Play("Leiana_Landing");
					_HitBox_Attack_On = false;
					if (_Dir == 1)
						at->PlayAnimation(L"Short_hairMeteor_Cross02_Landing_S", true);
					else
						at->PlayAnimation(L"Short_hairMeteor_Cross02_Landing_SR", true);
					tr->SetRotationZ(0.f);
					_CrossMeteorLanding = true;
				}
				if (_ShortHair_state == Layana_ShortHair_State::LandingDash)
				{
					as->Play("Leiana_Landing");
					if (_Dir == 1)
						at->PlayAnimation(L"Short_hairMeteor_Ground01_Ready_S", true);
					else
						at->PlayAnimation(L"Short_hairMeteor_Ground01_Ready_SR", true);
					_GroundMeteorLanding = true;
				}
				if (_ShortHair_state == Layana_ShortHair_State::Meteor_Vertical_Landing)
				{
					if (_VerticalMeteorLanding == false)
					{
						as->Play("Leiana_Landing");
						if (_Dir == 1)
							at->PlayAnimation(L"Short_hairMeteor_Vertical03_Landing_S", true);
						else
							at->PlayAnimation(L"Short_hairMeteor_Vertical03_Landing_SR", true);

						_VerticalMeteorLandingSM = true;
						_VerticalMeteorLanding = true;
					}
				}
				if (_ShortHair_state == Layana_ShortHair_State::AwakenJump)
				{
					if (_Awaken_Ready == false)
					{
						if (_Awaken_Dir == 1)
						{
							Awaken_Rd_ElectricA->SetDirection(1);
							Awaken_Rd_ElectricA->SetSwitch(true);
							Transform* ElecA_Tr = Awaken_Rd_ElectricA->GetComponent<Transform>();
							ElecA_Tr->SetPosition(Vector3(_pos.x, _pos.y - 15, -249));
							Awaken_Rd_ElectricA->SetState(eState::Active);

							Awaken_Rd_ElectricB->SetDirection(1);
							Awaken_Rd_ElectricB->SetSwitch(true);
							Transform* ElecB_Tr = Awaken_Rd_ElectricB->GetComponent<Transform>();
							ElecB_Tr->SetPosition(Vector3(_pos.x + 10, _pos.y - 50, _pos.z - 1));
							Awaken_Rd_ElectricB->SetState(eState::Active);
						}
						else
						{

							Awaken_Rd_ElectricA->SetDirection(-1);
							Awaken_Rd_ElectricA->SetSwitch(true);
							Transform* ElecA_Tr = Awaken_Rd_ElectricA->GetComponent<Transform>();
							ElecA_Tr->SetPosition(Vector3(_pos.x, _pos.y - 15, -249));
							Awaken_Rd_ElectricA->SetState(eState::Active);

							Awaken_Rd_ElectricB->SetDirection(-1);
							Awaken_Rd_ElectricB->SetSwitch(true);
							Transform* ElecB_Tr = Awaken_Rd_ElectricB->GetComponent<Transform>();
							ElecB_Tr->SetPosition(Vector3(_pos.x - 10, _pos.y - 50, _pos.z - 1));
							Awaken_Rd_ElectricB->SetState(eState::Active);
						}
						_Awaken_Ready = true;
						as->Play("Leiana_Scream");
						as->Play("Leiana_Awakening_Sign");
					}
				}		

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
					as->Play("Leiana_Landing");
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
					as->Play("Leiana_Landing");
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
		if (Skul_head* player = dynamic_cast<Skul_head*>(other->GetOwner()))
		{
			_bulletcheck = 0;
		}
	}



	void Layana_ShortHair::idle()
	{
		_time += static_cast<float>(Time::DeltaTime());
		_SelectAttack = random(0, 6);
		//_SelectAttack = 6;

		if (_Intro_On == true)
			Intro_Combo();

		if (_First_Die == false)
		{
			if (LongHair_Operation == true)
			{
				BackGround_Combo();
				_time = 0;
			}
		}

		if (ShortHair_Operation == true)
		{
			if (_First_Die == false)
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
						as->Play("Leiana_Enter");
						_ShortHair_state = Layana_ShortHair_State::FlyDash;
						if (_pos.x > _ShortHairCreatepos.x)
							at->PlayAnimation(L"Short_hairDash_S", true);
						else
							at->PlayAnimation(L"Short_hairDash_SR", true);
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
	}

	void Layana_ShortHair::Intro_Dash()
	{
		_Attacktime += static_cast<float>(Time::DeltaTime());
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
					_pos.x -= 750.f * static_cast<float>(Time::DeltaTime());
				if (_pos.y < 100)
					_pos.y += 150.f * static_cast<float>(Time::DeltaTime());
			}
			else
			{
				if (_pos.x < _ShortHairCreatepos.x + 600)
					_pos.x += 750.f * static_cast<float>(Time::DeltaTime());
				if (_pos.y < 100)
					_pos.y += 150.f * static_cast<float>(Time::DeltaTime());
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
					as->Play("Leiana_TwinMeteor_Sign");
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
					_Attacktime += static_cast<float>(Time::DeltaTime());
					if (_Attacktime > 1.5)
					{
						as->Play("Leiana_TwinMeteor");
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
					_rigidbody->SetVelocity(Vector2(850.f, -350.f));
					at->PlayAnimation(L"Short_hairDash_S", true);
					_HitBox_Dir = 1;
				}
				else
				{
					_rigidbody->SetVelocity(Vector2(-850.f, -350.f));
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
			_Attacktime += static_cast<float>(Time::DeltaTime());
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
			_Attacktime += static_cast<float>(Time::DeltaTime());
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
			_HitBox_Attack_On = false;
		}
	}


	void Layana_ShortHair::Sisters_Attack_B_Ready()
	{
		_SkillHomingON = false;
	}
	void Layana_ShortHair::Sisters_Attack_B_BulletCreate()
	{
		if (_SkillHomingON == false)
		{
			CreateHoming();
			as->Play("Leiana_HomingPierce_Ready");
		}
		else
		{
			_Attacktime += static_cast<float>(Time::DeltaTime());
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
		_Attacktime += static_cast<float>(Time::DeltaTime());

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
					as->Play("Homing_Fire1");
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
					as->Play("Homing_Fire2");
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
					as->Play("Homing_Fire3");
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
			_Attacktime += static_cast<float>(Time::DeltaTime());
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
		if (_SkillB_Dash == true)
		{
			if (!(_Playerdistance.x <= 30 && _Playerdistance.x >= -30))
			{
				if (_Dir == 1)
					_pos.x += 350.f * static_cast<float>(Time::DeltaTime());
				else
					_pos.x -= 350.f * static_cast<float>(Time::DeltaTime());
			}
			else
			{
				_ShortHair_state = Layana_ShortHair_State::Skill_B_RisingPierce;
				if (_Dir == 1)
					at->PlayAnimation(L"Short_hairSkill_B_RisingPierce_S", false);
				else
					at->PlayAnimation(L"Short_hairSkill_B_RisingPierce_SR", false);

				_SkillB_Dash = false;

				Transform* EFtr = RisingPierce_EF->GetComponent<Transform>();
				EFtr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
				RisingPierce_EF->SetDirection(1);
				RisingPierce_EF->SetSwitch(true);
				RisingPierce_EF->SetState(eState::Active);
				as->Play("Leiana_DimensionPierce_Sign");
			}
		}
		else
		{

			if (!(_Playerdistance.x <= 80 && _Playerdistance.x >= -80))
			{
				if (_Dir == 1)
					_pos.x += 350.f * static_cast<float>(Time::DeltaTime());
				else
					_pos.x -= 350.f * static_cast<float>(Time::DeltaTime());
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
	}
	void Layana_ShortHair::FlyDash()
	{
		if (_pos.x < _ShortHairCreatepos.x)
		{
			if (_pos.x > _ShortHairCreatepos.x - 600)
				_pos.x -= 750.f * static_cast<float>(Time::DeltaTime());
			if (_pos.y < 100)
				_pos.y += 150.f * static_cast<float>(Time::DeltaTime());
		}
		else
		{
			if (_pos.x < _ShortHairCreatepos.x + 600)
				_pos.x += 750.f * static_cast<float>(Time::DeltaTime());
			if (_pos.y < 100)
				_pos.y += 150.f * static_cast<float>(Time::DeltaTime());
		}
		if (_pos.y >= 100.f)
		{
			if (_GroundMeteorSwitch == true)
			{
				_ShortHair_state = Layana_ShortHair_State::LandingDash;
				_Ground_check = false;
				_rigidbody->SetGround(false);
				if (_pos.x < _ShortHairCreatepos.x)
				{
					_rigidbody->SetVelocity(Vector2(850.f, -350.f));
					at->PlayAnimation(L"Short_hairDash_S", true);
					_HitBox_Dir = 1;
				}
				else
				{
					_rigidbody->SetVelocity(Vector2(-850.f, -350.f));
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
				_SistersAttack_Number = 0;
			}
		}
	}
	void Layana_ShortHair::LandingDash()
	{
		_Attacktime += static_cast<float>(Time::DeltaTime());
		if (_GroundMeteorLanding == true)
		{
			if (_Attacktime >= 1.f)
			{
				as->Play("Leiana_MeteorGround");
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
	void Layana_ShortHair::Rush_C1()
	{
	}
	void Layana_ShortHair::Rush_C2()
	{
	}
	void Layana_ShortHair::Rush_C3()
	{
	}
	void Layana_ShortHair::Rush_C4()
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
				_HitBox_Dir = 1;
			}
			else
			{
				at->PlayAnimation(L"Short_hairMeteor_Cross04_Attack_SR", false);
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
		_HitBox_Attack_On = true;
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
				_HitBox_Attack_On = false;
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
				_HitBox_Attack_On = false;
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
		_HitBox_Attack_On = true;
		if (_VerticalMeteor_Bullet == false)
		{
			Golden_Meteor_Bl->SetState(eState::Active);
			_VerticalMeteor_Bullet = true;
		}

		_Attacktime += static_cast<float>(Time::DeltaTime());
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

			Golden_Meteor_Ef->SetState(eState::Active);
			Transform* effectTR = Golden_Meteor_Ef->GetComponent<Transform>();
			effectTR->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			Golden_Meteor_Ef->SetSwitch(true);

			_VerticalMeteorLandingSM = false;
		}

		if (_VerticalMeteorLanding == true)
		{		
			if (_Attacktime >= 0.5f)
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
		{
			CreateHoming();
			as->Play("Leiana_HomingPierce_Ready");
		}
		else
		{
			_Attacktime += static_cast<float>(Time::DeltaTime());
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
		_Attacktime += static_cast<float>(Time::DeltaTime());

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
					as->Play("Homing_Fire1");
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
					as->Play("Homing_Fire2");
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
					as->Play("Homing_Fire3");
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
			_Attacktime += static_cast<float>(Time::DeltaTime());
			if (_Attacktime >= 0.8 && _Attacktime <= 1)
			{
				Risingbullet_tr[0]->SetPosition(Vector3(_pos.x, _pos.y + 35, -250));
				Rising[0]->SetState(eState::Active);
				as->Play("Leiana_DimensionPierce_Impact");
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
				as->Play("Leiana_DimensionPierce_Impact");
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
			_Attacktime += static_cast<float>(Time::DeltaTime());

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
			if (_Awaken_Dir == 1)	
				at->PlayAnimation(L"Short_hairAwakenReady_S", true);
			else			
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
		if (_SistersAttack_Number >= 6)
		{
			Background_state = Layana_Short_Background::BackGround_Exit;
			at->PlayAnimation(L"Short_hairBackGround_Move_S", false);
			_rigidbody->SetVelocity(Vector2(0.f, 1050.f));
			_rigidbody->SetGround(false);
			_BackGround_check = true;
			_Ground_check = false;			
		}
		else
		{
			if (_First_Die == false)
				_pos.z = -100;
			else
				_pos.z = -200;
		}
	}
	void Layana_ShortHair::BackGround_Enter()
	{
		if (_BackGround_Idle == true)
		{
			Background_state = Layana_Short_Background::BackGround_Idle;
			at->PlayAnimation(L"Short_hairBackGround_Idle_S", true);
			_BackGround_Idle = false;
		}
	}
	void Layana_ShortHair::BackGround_Exit()
	{
		if (_pos.y >= 100)
		{
			_rigidbody->SetGround(true);
			if (LongHairPos.x >= _ShortHairCreatepos.x)
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
			ShortHair_First_moving = true;
			//Background_state = Layana_Short_Background::BackGround_Idle;
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
		_HitBox_Attack_On = false;
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
		_HitBox_Attack_On = false;
		if (_Rushnumber == 0)
		{
			_HitBox_Attack_On = true;
			as->Play("rush1");
			_ShortHair_state = Layana_ShortHair_State::RushA;
			if (_Dir == 1)
			{
				at->PlayAnimation(L"Short_hairRushA_S", true);
				_HitBox_Dir = 1;
			}
			else
			{
				at->PlayAnimation(L"Short_hairRushA_SR", true);
				_HitBox_Dir = -1;
			}
		}
		if (_Rushnumber == 1)
		{
			_HitBox_Attack_On = true;
			as->Play("rush2");
			_ShortHair_state = Layana_ShortHair_State::RushB;
			if (_Dir == 1)
			{
				at->PlayAnimation(L"Short_hairRushB_S", true);
				_HitBox_Dir = 1;
			}
			else
			{
				at->PlayAnimation(L"Short_hairRushB_SR", true);
				_HitBox_Dir = -1;
			}
		}
		if (_Rushnumber == 2)
		{
			_HitBox_Attack_On = true;
			as->Play("rush3");
			_ShortHair_state = Layana_ShortHair_State::RushC1;
			if (_Dir == 1)
			{
				at->PlayAnimation(L"Short_hairRushC_S1", true);
				_HitBox_Dir = 1;
			}
			else
			{
				at->PlayAnimation(L"Short_hairRushC_S1R", true);
				_HitBox_Dir = -1;
			}
		}
		if (_Rushnumber == 3)
		{
			_HitBox_Attack_On = true;
			as->Play("rush4");
			_ShortHair_state = Layana_ShortHair_State::RushC2;
			if (_Dir == 1)
			{
				at->PlayAnimation(L"Short_hairRushC_S2", true);
				_HitBox_Dir = 1;
			}
			else
			{
				at->PlayAnimation(L"Short_hairRushC_S2R", true);
				_HitBox_Dir = -1;
			}
		}
		if (_Rushnumber == 4)
		{
			_HitBox_Attack_On = true;
			as->Play("rush5");
			_ShortHair_state = Layana_ShortHair_State::RushC3;
			if (_Dir == 1)
			{
				at->PlayAnimation(L"Short_hairRushC_S3", true);
				_HitBox_Dir = 1;
			}
			else
			{
				at->PlayAnimation(L"Short_hairRushC_S3R", true);
				_HitBox_Dir = -1;
			}
		}
		if (_Rushnumber == 5)
		{
			as->Play("rush6");
			_ShortHair_state = Layana_ShortHair_State::RushC4;
			if (_Dir == 1)
				at->PlayAnimation(L"Short_hairRushC_S4", true);
			else
				at->PlayAnimation(L"Short_hairRushC_S4R", true);
		}
		if (_Rushnumber >= 6)
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
		as->Play("Leiana_Enter");
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
			if (_Dir == 1)
				at->PlayAnimation(L"Short_hairDash_S", true);
			else
				at->PlayAnimation(L"Short_hairDash_SR", true);
		}
	}
	void Layana_ShortHair::Complete_CrossJump()
	{
		as->Play("Leiana_GoldenMeteor");
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
		as->Play("Leiana_Enter");
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
		as->Play("Leiana_Enter");
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
		as->Play("Leiana_GoldenMeteor");
		at->PlayAnimation(L"Short_hairMeteor_Vertical02_Attack_S", false);
		_rigidbody->SetGround(false);
		_rigidbody->SetVelocity(Vector2(0.f, -550.f));
		_VerticalMeteorLanding = false;
		_VerticalMeteor_Bullet = false;
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
		if (_Playerdistance.x <= 30 && _Playerdistance.x >= -30)
		{
			_ShortHair_state = Layana_ShortHair_State::Skill_B_RisingPierce;
			if (_Dir == 1)
				at->PlayAnimation(L"Short_hairSkill_B_RisingPierce_S", false);
			else
				at->PlayAnimation(L"Short_hairSkill_B_RisingPierce_SR", false);

			Transform* EFtr = RisingPierce_EF->GetComponent<Transform>();
			EFtr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			RisingPierce_EF->SetDirection(1);
			RisingPierce_EF->SetSwitch(true);
			RisingPierce_EF->SetState(eState::Active);
			as->Play("Leiana_DimensionPierce_Sign");
		}
		else
		{
			_SkillB_Dash = true;
			_ShortHair_state = Layana_ShortHair_State::Dash;
			if (_Dir == 1)
				at->PlayAnimation(L"Short_hairDash_S", true);
			else
				at->PlayAnimation(L"Short_hairDash_SR", true);
		}
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
		as->Play("Leiana_DimensionPierce_Sign");
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
			if (LongHairPos.x < _ShortHairCreatepos.x)
			{
				_pos = Vector3(_ShortHairCreatepos.x + 200, _ShortHairCreatepos.y - 50, -200);
				at->PlayAnimation(L"Short_hairAwakenJump_SR", false);
				_Awaken_Dir = -1;
			}
			else
			{
				_pos = Vector3(_ShortHairCreatepos.x - 200, _ShortHairCreatepos.y - 50, -200);
				at->PlayAnimation(L"Short_hairAwakenJump_S", false); 
				_Awaken_Dir = 1;
			}		
			tr->SetPosition(_pos);
			_rigidbody->SetGround(false);
			_Ground_check = false;
			_ShortHair_state = Layana_ShortHair_State::AwakenJump;
			_Awaken_Switch = true;
		}
	}
	void Layana_ShortHair::Complete_Awaken_Ready()
	{
		as->Play("Leiana_Awakening"); 
		_ShortHair_state = Layana_ShortHair_State::Awaken;
		if (_Awaken_Dir == 1)
		{
			at->PlayAnimation(L"Short_hairAwaken_S", true);

			Awaken_Smoke_EF->SetSwitch(true);
			Awaken_Smoke_EF->SetDirection(1);
			Awaken_Smoke_EF->SetState(eState::Active);
			Transform* Smoke_EFtr = Awaken_Smoke_EF->GetComponent<Transform>();
			Smoke_EFtr->SetPosition(Vector3(_pos.x, _pos.y - 50, _pos.z - 1));



			Awaken_Elec_EF->SetSwitch(true);
			Awaken_Elec_EF->SetDirection(1);
			Awaken_Elec_EF->SetState(eState::Active);
			Transform* Elec_EFtr = Awaken_Elec_EF->GetComponent<Transform>();
			Elec_EFtr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
		}
		else
		{
			at->PlayAnimation(L"Short_hairAwaken_SR", true);

			Awaken_Smoke_EF->SetSwitch(true);
			Awaken_Smoke_EF->SetDirection(-1);
			Awaken_Smoke_EF->SetState(eState::Active);
			Transform* Smoke_EFtr = Awaken_Smoke_EF->GetComponent<Transform>();
			Smoke_EFtr->SetPosition(Vector3(_pos.x, _pos.y - 50, _pos.z - 1));


			Awaken_Elec_EF->SetSwitch(true);
			Awaken_Elec_EF->SetDirection(1);
			Awaken_Elec_EF->SetState(eState::Active);
			Transform* Elec_EFtr = Awaken_Elec_EF->GetComponent<Transform>();
			Elec_EFtr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
		}
	}
	void Layana_ShortHair::Complete_Awaken()
	{
		_Layana_change = true;
		_ShortHair_Awaken = true;
		Awaken_Smoke_EF->SetState(eState::Paused);	
		as->Play("Leiana_Awakening_Impact");
		if (_ChangeFadein == false)
		{
			Alpha_Blend* _Alpha = object::InstantiateActive<Alpha_Blend>(Vector3(0.f, 0.f, -251.f), eLayerType::Map_Effect);
			_Alpha->GetComponent<Transform>()->SetScale(Vector3(10000.f, 10000.f, 0.f));
			_Alpha->FadeIn_White_Transparent();
			_Fadecheck = true;
			_ChangeFadein = true;
		}
		if (_Fadecheck == true)
		{
			_Fadetime += 2.75f * static_cast<float>(Time::DeltaTime());
			if (_Fadetime > 3)
			{
				_Fadecheck = false;
				_Fadetime = 0;
			}
		}

		if (_ShortHair_Awaken == true && _Layana_change == true)
		{
			SetLayana_List(LayanaSisters_List::Awaken_Darkmode, LayanaSisters_List::ShortHair, true, _Dir);
			SetPos(_pos);
		}

		//// 나중에 각성보스 추가시 여기서 변경코드 넣으면됨
		_time = 0.f;
		_Attacktime = 0.f;
		_Awaken_Switch = true;
	}



	void Layana_ShortHair::BackGround_Combo()
	{
		_BackGround_Switch = true;
		Background_state = Layana_Short_Background::FlyDash;
		as->Play("Leiana_Enter");
		if (_pos.x > _ShortHairCreatepos.x)
			at->PlayAnimation(L"Short_hairDash_S", true);
		else
			at->PlayAnimation(L"Short_hairDash_SR", true);
	}

	void Layana_ShortHair::HitEffect()
	{
		{
			Transform* _Hit_Effect_TR = _Hit_Effect->GetComponent<Transform>();
			if (_Dir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(_pos.x + 20, _pos.y - 30, _pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(_pos.x - 20, _pos.y - 30, _pos.z - 1));
		}
		{
			Transform* _Hit_Effect_TR = _Critical_Middle->GetComponent<Transform>();
			if (_Dir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(_pos.x + 20, _pos.y - 30, _pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(_pos.x - 20, _pos.y - 30, _pos.z - 1));
		}
		{
			Transform* _Hit_Effect_TR = _Critical_High->GetComponent<Transform>();
			if (_Dir == 1)
				_Hit_Effect_TR->SetPosition(Vector3(_pos.x + 20, _pos.y - 30, _pos.z - 1));
			else
				_Hit_Effect_TR->SetPosition(Vector3(_pos.x - 20, _pos.y - 30, _pos.z - 1));
		}
		{
			Transform* _Effect_TR = _Death_Effect->GetComponent<Transform>();
			_Effect_TR->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
		}
	}



	void Layana_ShortHair::die()
	{
	}



	void Layana_ShortHair::CreateHoming()
	{
		if (_SkillHomingON == false)
		{
			_Attacktime += static_cast<float>(Time::DeltaTime());
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















