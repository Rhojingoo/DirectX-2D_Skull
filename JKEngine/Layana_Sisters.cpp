#include "Layana_Sisters.h"
#include <iostream>
#include <random>

namespace jk
{
	Layana_Sisters::Layana_Sisters_State Layana_Sisters::_state = Layana_Sisters_State();

	bool Layana_Sisters::_Intro_On = true;
	bool Layana_Sisters::_Intro_Dash_LongHair = false;
	bool Layana_Sisters::_Intro_Dash_ShortHair = false;
	bool Layana_Sisters::_Intro_Fall_LongHair = false;
	bool Layana_Sisters::_Intro_Fall_ShortHair = false;
	bool Layana_Sisters::_Intro_Land_LongHair = false;
	bool Layana_Sisters::_Intro_Land_ShortHair = false;
	bool Layana_Sisters::_Intro_LongHair_END = false;
	bool Layana_Sisters::_Intro_ShortHair_END = false;

	
	int Layana_Sisters::_Sisters_AttackType = 0;
	bool Layana_Sisters::_SistersAttack_A_IntroReady_LongHair = false;
	bool Layana_Sisters::_SistersAttack_A_IntroReadyShortHair = false;
	bool Layana_Sisters::_SistersAttack_FlyDash_LongHair = false;
	bool Layana_Sisters::_SistersAttack_FlyDash_ShortHair = false;
	bool Layana_Sisters::_SistersAttack_A_Ready_LongHair = false;
	bool Layana_Sisters::_SistersAttack_A_Ready_ShortHair = false;
	bool Layana_Sisters::_SistersAttack_A_DashOn = false;
	bool Layana_Sisters::_SistersAttack_A_DashOn_LongHair = false;
	bool Layana_Sisters::_SistersAttack_A_DashOn_ShortHair = false;
	bool Layana_Sisters::_SistersAttack_A_LongHair_END = false;
	bool Layana_Sisters::_SistersAttack_A_ShortHair_END = false;



	bool Layana_Sisters::_SistersAttack_B_IntroReady_LongHair = false;
	bool Layana_Sisters::_SistersAttack_B_IntroReadyShortHair = false;
	bool Layana_Sisters::_SistersAttack_B_Ready_LongHair = false;
	bool Layana_Sisters::_SistersAttack_B_Ready_ShortHair = false;
	bool Layana_Sisters::_SistersAttack_B_BulletOn_LongHair = false;
	bool Layana_Sisters::_SistersAttack_B_BulletOn_ShortHair = false;
	bool Layana_Sisters::_SistersAttack_B_LongHair_END = false;
	bool Layana_Sisters::_SistersAttack_B_ShortHair_END = false;


	bool Layana_Sisters::_SistersAttack_C_IntroReady_LongHair = false;
	bool Layana_Sisters::_SistersAttack_C_IntroReadyShortHair = false;
	bool Layana_Sisters::_SistersAttack_C_Ready_LongHair = false;
	bool Layana_Sisters::_SistersAttack_C_Ready_ShortHair = false;
	bool Layana_Sisters::_SistersAttack_C_DashOn_LongHair = false;
	bool Layana_Sisters::_SistersAttack_C_DashOn_ShortHair = false;
	bool Layana_Sisters::_SistersAttack_C_LongHair_LAND = false;
	bool Layana_Sisters::_SistersAttack_C_ShortHair_LAND = false;




	Layana_Sisters::Layana_Sisters()
	{
	}
	Layana_Sisters::~Layana_Sisters()
	{
	}

	void Layana_Sisters::Initialize()
	{
		_Gobjs[0] = new Layana_LongHair;
		_Gobjs[0]->Initialize();
		_Gobjs[1] = new Layana_ShortHair;
		_Gobjs[1]->Initialize();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(eLayerType::Boss, _Gobjs[0]);
		scene->AddGameObject(eLayerType::Boss, _Gobjs[1]);

		GameObject::Initialize();
	}
	void Layana_Sisters::Update()
	{
		switch (_state)
		{
		case jk::Layana_Sisters::Layana_Sisters_State::Idle:
			idle();
			break;	

		case jk::Layana_Sisters::Layana_Sisters_State::Intro_Dash:
			Intro_Dash();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Intro_Fall:
			Intro_Fall();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Intro_Landing:
			Intro_Landing();
			break;




		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_A_Ready:
			Sisters_Attack_A_Ready();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_FlyDash:
			Sisters_Attack_FlyDash();
			break; 
	
		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_Fall:
			Sisters_Attack_Fall();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_A_LandingDash:
			Sisters_Attack_A_LandingDash();
			break;
			
		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_A:
			Sisters_Attack_A();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_A_End:
			Sisters_Attack_A_End();
			break;




		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_B_Ready:
			Sisters_Attack_B_Ready();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_B_BulletCreate:
			Sisters_Attack_B_BulletCreate();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_B:
			Sisters_Attack_B();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_B_End:
			Sisters_Attack_B_End();
			break;


			

		
		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_C_Ready:
			Sisters_Attack_C_Ready();
			break;		
		
		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_C:
			Sisters_Attack_C();
			break;		
		
		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_C_Landing:
			Sisters_Attack_C_Landing();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_C_End:
			Sisters_Attack_C_End();
			break;





		case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_D:
			Sisters_Attack_D();
			break;






		case jk::Layana_Sisters::Layana_Sisters_State::BackGround_Idle:
			BackGround_Idle();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::BackGround_Move:
			BackGround_Move();
			break;






		case jk::Layana_Sisters::Layana_Sisters_State::Rush_Ready:
			Rushready();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::RushA:
			Rush_A();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::RushB:
			Rush_B();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::RushC:
			Rush_C();
			break;		

		case jk::Layana_Sisters::Layana_Sisters_State::Rush_End:
			Rush_End();
			break;



		case jk::Layana_Sisters::Layana_Sisters_State::Dash:
			Dash();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::FlyDash:
			FlyDash();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::LandingDash:
			LandingDash();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::BackStep:
			BackStep();
			break;





		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Ready:
			CrossReady();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Jump:
			CrossJump();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Attack:
			CrossAttack();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Landing:
			CrossLanding();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_End:
			CrossEnd();
			break;




		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_Ready:
			GroundReady();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_Attack:
			GroundAttack();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_Landing:
			GroundLanding();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_End:
			GroundEnd();
			break;




		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_Jump:
			Vertical_Jump();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_Ready:
			Vertical_Ready();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_Attack:
			Vertical_Attack();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_Landing:
			Vertical_Landing();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_End:
			Vertical_End();
			break;




		case jk::Layana_Sisters::Layana_Sisters_State::Skill_A_Bullet_Ready:
			Skill_A_Ready();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Skill_A_Bullet:
			Skill_A();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Skill_A_Bullet_End:
			Skill_A_End();
			break;




		case jk::Layana_Sisters::Layana_Sisters_State::Skill_B_RisingPierce:
			Skill_B();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Skill_B_RisingPierce_End:
			Skill_B_End();
			break;
			


		case jk::Layana_Sisters::Layana_Sisters_State::Skill_C_DimensionPierce:
			Skill_C();
			break;


	


		case jk::Layana_Sisters::Layana_Sisters_State::Awaken:
			Awaken();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::AwakenJump:
			AwakenJump();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::AwakenReady:
			AwakenReady();
			break;




		case jk::Layana_Sisters::Layana_Sisters_State::Die:
			
			break;

		default:
			break;
		}

		GameObject::Update();
	}
	void Layana_Sisters::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Layana_Sisters::Render()
	{
		GameObject::Render();
	}

	void Layana_Sisters::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_Sisters::OnCollisionStay(Collider2D* other)
	{
	}
	void Layana_Sisters::OnCollisionExit(Collider2D* other)
	{
	}


	void Layana_Sisters::idle()
	{
		if(_Intro_On == true)
		{
			if (_Intro_Dash_ShortHair == true && _Intro_Dash_LongHair == true)
				_state = Layana_Sisters_State::Intro_Dash;		
		}
		else
		{
			if (_Sisters_Attack_On == true)
			{
				if(_Sisters_AttackType == 0)
				_state = Layana_Sisters_State::Sisters_Attack_A_Ready;
				if (_Sisters_AttackType == 1)
				_state = Layana_Sisters_State::Sisters_Attack_B_Ready;		
				if (_Sisters_AttackType == 2)
				_state = Layana_Sisters_State::Sisters_Attack_C_Ready;
			}			
		}
	}


	void Layana_Sisters::Intro_Dash()
	{
		if (_Intro_Fall_ShortHair == true && _Intro_Fall_LongHair == true)
			_state = Layana_Sisters_State::Intro_Fall;
	}
	void Layana_Sisters::Intro_Fall()
	{
		if (_Intro_Land_ShortHair == true && _Intro_Land_LongHair == true)
			_state = Layana_Sisters_State::Intro_Landing;
	}
	void Layana_Sisters::Intro_Landing()
	{
		if (_Intro_ShortHair_END == true && _Intro_LongHair_END == true)
		{
			_Intro_On = false;
			_Intro_Dash_LongHair = false;
			_Intro_Dash_ShortHair = false;
			_Intro_Fall_LongHair = false;
			_Intro_Fall_ShortHair = false;
			_Intro_Land_LongHair = false;
			_Intro_Land_ShortHair = false;
			_Intro_LongHair_END = false;
			_Intro_ShortHair_END = false;
			_Sisters_Attack_On = true;
			_state = Layana_Sisters_State::Idle;
		}
	}


	void Layana_Sisters::BackGround_Idle()
	{
	}
	void Layana_Sisters::BackGround_Move()
	{
	}


	void Layana_Sisters::Sisters_Attack_FlyDash()
	{
		if (_SistersAttack_FlyDash_ShortHair == true && _SistersAttack_FlyDash_LongHair == true)
			_state = Layana_Sisters_State::Sisters_Attack_Fall;		

		if (_SistersAttack_C_DashOn_ShortHair == true && _SistersAttack_C_DashOn_LongHair == true)
		{
			int a = 0;
			_state = Layana_Sisters_State::Sisters_Attack_C;
		}
	}
	void Layana_Sisters::Sisters_Attack_Fall()
	{
		if (_SistersAttack_A_Ready_ShortHair == true && _SistersAttack_A_Ready_LongHair == true)
		{
			_SistersAttack_A_DashOn = true;
			_state = Layana_Sisters_State::Sisters_Attack_A_LandingDash;
		}

		if (_SistersAttack_B_Ready_ShortHair == true && _SistersAttack_B_Ready_LongHair == true)
			_state = Layana_Sisters_State::Sisters_Attack_B_BulletCreate;
	}


	void Layana_Sisters::Sisters_Attack_A_Ready()
	{
		
		if (_SistersAttack_A_IntroReadyShortHair == true && _SistersAttack_A_IntroReady_LongHair == true)
			_state = Layana_Sisters_State::Sisters_Attack_FlyDash;
	}
	void Layana_Sisters::Sisters_Attack_A_LandingDash()
	{
		if(_SistersAttack_A_DashOn_ShortHair == true && _SistersAttack_A_DashOn_LongHair == true)
			_state = Layana_Sisters_State::Sisters_Attack_A;
	}
	void Layana_Sisters::Sisters_Attack_A()
	{
		if(_SistersAttack_A_ShortHair_END ==true && _SistersAttack_A_ShortHair_END ==true)
			_state = Layana_Sisters_State::Sisters_Attack_A_End;
	}
	void Layana_Sisters::Sisters_Attack_A_End()
	{
		_SistersAttack_A_IntroReady_LongHair = false;
		_SistersAttack_A_IntroReadyShortHair = false;
		_SistersAttack_FlyDash_LongHair = false;
		_SistersAttack_FlyDash_ShortHair = false;
		_SistersAttack_A_Ready_LongHair = false;
		_SistersAttack_A_Ready_ShortHair = false;
		_SistersAttack_A_DashOn = false;
		_SistersAttack_A_DashOn_LongHair = false;
		_SistersAttack_A_DashOn_ShortHair = false;
		_SistersAttack_A_LongHair_END = false;
		_SistersAttack_A_ShortHair_END = false;
		
		_Attacktime += Time::DeltaTime();
		if (_Attacktime > 1.5)
		{
			_state = Layana_Sisters_State::Idle;
			_Attacktime = 0;
			_Intro_On = false; 
			_Sisters_AttackType =1;
		}		
	}


	void Layana_Sisters::Sisters_Attack_B_Ready()
	{			
		if(_SistersAttack_B_IntroReady_LongHair == true && _SistersAttack_B_IntroReadyShortHair == true)
		_state = Layana_Sisters_State::Sisters_Attack_FlyDash;
	}
	void Layana_Sisters::Sisters_Attack_B_BulletCreate()
	{
		if(_SistersAttack_B_BulletOn_LongHair = true && _SistersAttack_B_BulletOn_ShortHair ==true)
		_state = Layana_Sisters_State::Sisters_Attack_B;
	}
	void Layana_Sisters::Sisters_Attack_B()
	{
		if (_SistersAttack_B_LongHair_END == true && _SistersAttack_B_ShortHair_END == true)
		{
			_Attacktime += Time::DeltaTime();
			if (_Attacktime >= 1.5)
			{
				_state = Layana_Sisters_State::Sisters_Attack_B_End;
				_Attacktime = 0;
			}
		}
	}
	void Layana_Sisters::Sisters_Attack_B_End()
	{
		_SistersAttack_B_IntroReady_LongHair = false;
		_SistersAttack_B_IntroReadyShortHair = false;
		_SistersAttack_B_Ready_LongHair = false;
		_SistersAttack_B_Ready_ShortHair = false;
		_SistersAttack_B_BulletOn_LongHair = false;
		_SistersAttack_B_BulletOn_ShortHair = false;
		_SistersAttack_B_LongHair_END = false;
		_SistersAttack_B_ShortHair_END = false;

		_Attacktime += Time::DeltaTime();
		if (_Attacktime > 1.5)
		{
			_state = Layana_Sisters_State::Idle;
			_Attacktime = 0;
			_Sisters_AttackType = 0;
		}
	}


	void Layana_Sisters::Sisters_Attack_C_Ready()
	{		
		if(_SistersAttack_C_IntroReadyShortHair == true && _SistersAttack_C_IntroReady_LongHair)
			_state = Layana_Sisters_State::Sisters_Attack_FlyDash;
	}
	void Layana_Sisters::Sisters_Attack_C()
	{
		if (_SistersAttack_C_LongHair_LAND == true && _SistersAttack_C_ShortHair_LAND == true)
		{
			_Attacktime += Time::DeltaTime();
			if (_Attacktime > 1)
			{
				_state = Layana_Sisters_State::Sisters_Attack_C_Landing;
				_Attacktime = 0;
			}
		}
	}
	void Layana_Sisters::Sisters_Attack_C_Landing()
	{
		if (_SistersAttack_C_LongHair_LAND == false && _SistersAttack_C_ShortHair_LAND == false)
		_state = Layana_Sisters_State::Sisters_Attack_C_End;
	}
	void Layana_Sisters::Sisters_Attack_C_End()
	{
		_SistersAttack_C_IntroReady_LongHair = false;
		_SistersAttack_C_IntroReadyShortHair = false;
		_SistersAttack_C_Ready_LongHair = false;
		_SistersAttack_C_Ready_ShortHair = false;
		_SistersAttack_C_DashOn_LongHair = false;
		_SistersAttack_C_DashOn_ShortHair = false;
		_SistersAttack_C_LongHair_LAND = false;
		_SistersAttack_C_ShortHair_LAND = false;


		_Attacktime += Time::DeltaTime();
		if (_Attacktime > 1.5)
		{
			_state = Layana_Sisters_State::Idle;
			_Attacktime = 0;
			_Sisters_AttackType = 0;
		}
	}




	void Layana_Sisters::Sisters_Attack_D()
	{
	}



	void Layana_Sisters::Rushready()
	{
	}
	void Layana_Sisters::Rush_A()
	{
	}
	void Layana_Sisters::Rush_B()
	{
	}
	void Layana_Sisters::Rush_C()
	{
	}
	void Layana_Sisters::Rush_End()
	{
	}



	void Layana_Sisters::Dash()
	{
	}
	void Layana_Sisters::FlyDash()
	{
	}
	void Layana_Sisters::LandingDash()
	{
	}
	void Layana_Sisters::BackStep()
	{
	}



	void Layana_Sisters::CrossJump()
	{
	}
	void Layana_Sisters::CrossReady()
	{
	}
	void Layana_Sisters::CrossAttack()
	{
	}
	void Layana_Sisters::CrossLanding()
	{
	}
	void Layana_Sisters::CrossEnd()
	{
	}



	void Layana_Sisters::GroundReady()
	{
	}
	void Layana_Sisters::GroundAttack()
	{
	}
	void Layana_Sisters::GroundLanding()
	{
	}
	void Layana_Sisters::GroundEnd()
	{
	}



	void Layana_Sisters::Vertical_Jump()
	{
	}
	void Layana_Sisters::Vertical_Ready()
	{
	}
	void Layana_Sisters::Vertical_Attack()
	{
	}
	void Layana_Sisters::Vertical_Landing()
	{
	}
	void Layana_Sisters::Vertical_End()
	{
	}



	void Layana_Sisters::Skill_A_Ready()
	{
	}
	void Layana_Sisters::Skill_A()
	{
	}
	void Layana_Sisters::Skill_A_End()
	{
	}


	void Layana_Sisters::Skill_B()
	{
	}
	void Layana_Sisters::Skill_B_End()
	{
	}
	void Layana_Sisters::Skill_C()
	{
	}



	void Layana_Sisters::Awaken()
	{
	}
	void Layana_Sisters::AwakenJump()
	{
	}
	void Layana_Sisters::AwakenReady()
	{
	}



	void Layana_Sisters::die()
	{
	}


	int Layana_Sisters::random(int a, int b)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(a, b);
		int abc = distribution(gen);
		return abc;
	}

}