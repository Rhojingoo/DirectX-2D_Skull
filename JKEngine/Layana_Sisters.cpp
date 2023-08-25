#include "Layana_Sisters.h"
#include <iostream>
#include <random>

namespace jk
{
	Layana_Sisters::Layana_Sisters_State Layana_Sisters::_state = Layana_Sisters_State();
	Vector3 Layana_Sisters::LongHairPos = Vector3();;
	Vector3 Layana_Sisters::ShortHairPos = Vector3();

	int Layana_Sisters::_SistersAttack_Number = 0;
	bool Layana_Sisters::Joint_Operation = true;
	bool Layana_Sisters::LongHair_Operation = false;
	bool Layana_Sisters::ShortHair_Operation = false;
	bool Layana_Sisters::LongHair_First_moving = false;
	bool Layana_Sisters::ShortHair_First_moving = false;

	bool Layana_Sisters::_Sisters_Attack_A_Switch = false;
	bool Layana_Sisters::_Sisters_Attack_B_Switch = false;
	bool Layana_Sisters::_Sisters_Attack_C_Switch = false;
	bool Layana_Sisters::_Sisters_Attack_D_Switch = false;

	bool Layana_Sisters::_Intro_On = true;
	bool Layana_Sisters::_Intro_Dash_LongHair = false;
	bool Layana_Sisters::_Intro_Dash_ShortHair = false;
	bool Layana_Sisters::_Intro_Fall_LongHair = false;
	bool Layana_Sisters::_Intro_Fall_ShortHair = false;
	bool Layana_Sisters::_Intro_Land_LongHair = false;
	bool Layana_Sisters::_Intro_Land_ShortHair = false;
	bool Layana_Sisters::_Intro_LongHair_END = false;
	bool Layana_Sisters::_Intro_ShortHair_END = false;



	bool Layana_Sisters::_SistersAttack_Set_LongHair = false;
	bool Layana_Sisters::_SistersAttack_Set_ShortHair = false;
	bool Layana_Sisters::_SistersAttack_FlyDash_LongHair = false;
	bool Layana_Sisters::_SistersAttack_FlyDash_ShortHair = false;


	
	int Layana_Sisters::_Sisters_AttackType = 0;
	bool Layana_Sisters::_SistersAttack_A_IntroReady_LongHair = false;
	bool Layana_Sisters::_SistersAttack_A_IntroReadyShortHair = false;
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
		if (Joint_Operation == true)
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



			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_Set:
				Sisters_Attack_Set();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_FlyDash:
				Sisters_Attack_FlyDash();
				break;

			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_Fall:
				Sisters_Attack_Fall();
				break;
					



			case jk::Layana_Sisters::Layana_Sisters_State::Sisters_Attack_A_Ready:
				Sisters_Attack_A_Ready();
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


			default:
				break;
			}
		}

		if (ShortHair_Operation == true)
		{
			if (LongHair_First_moving == true && ShortHair_First_moving == true)
			{
				_state = Layana_Sisters_State::Sisters_Attack_FlyDash;
				ShortHair_Operation = false;
				LongHair_Operation = false;				
				Joint_Operation = true;
				LongHair_First_moving = false;
				ShortHair_First_moving = false;
			}
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
			_SistersAttack_Number = 0;
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
			else
			{

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
			_Sisters_Attack_On = true;
			//_state = Layana_Sisters_State::Idle;
		}
		if (_SistersAttack_A_IntroReadyShortHair == true && _SistersAttack_A_IntroReady_LongHair == true)
			_state = Layana_Sisters_State::Sisters_Attack_FlyDash;
	}


	void Layana_Sisters::Sisters_Attack_Set()
	{	
			_Sisters_AttackType = random(0, 2);
			if (_Sisters_AttackType == 0)
			{
				_Sisters_Attack_A_Switch = true;
			}
			if (_Sisters_AttackType == 1)
			{
				_Sisters_Attack_B_Switch = true;
			}
			if (_Sisters_AttackType == 2)
			{
				_Sisters_Attack_C_Switch = true;
			}
			if (_SistersAttack_Set_LongHair == true && _SistersAttack_Set_ShortHair == true)
				_state = Layana_Sisters_State::Sisters_Attack_FlyDash;			
			_SistersAttack_Number++;
	}	
	void Layana_Sisters::Sisters_Attack_FlyDash()
	{		
		if (_SistersAttack_FlyDash_ShortHair == true && _SistersAttack_FlyDash_LongHair == true)
		{
			_state = Layana_Sisters_State::Sisters_Attack_Fall;
		}

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
		if (_Attacktime > 1)
		{
			if (_SistersAttack_Number >= 1)
			{				
				_Sisters_Attack_On = false;
				Joint_Operation = false;		
				int select = random(0, 1);

				if (select == 0)
					longhair_change();
				if (select == 1)
					shorthair_change();
			}
			else
			{
				_state = Layana_Sisters_State::Sisters_Attack_Set;
				_Attacktime = 0;
			}
		}
	}


	void Layana_Sisters::Sisters_Attack_B_Ready()
	{		

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
		_SistersAttack_FlyDash_LongHair = false;
		_SistersAttack_FlyDash_ShortHair = false;
		_SistersAttack_B_IntroReady_LongHair = false;
		_SistersAttack_B_IntroReadyShortHair = false;
		_SistersAttack_B_Ready_LongHair = false;
		_SistersAttack_B_Ready_ShortHair = false;
		_SistersAttack_B_BulletOn_LongHair = false;
		_SistersAttack_B_BulletOn_ShortHair = false;
		_SistersAttack_B_LongHair_END = false;
		_SistersAttack_B_ShortHair_END = false;


		_Attacktime += Time::DeltaTime();
		if (_Attacktime > 1)
		{
			if (_SistersAttack_Number > 1)
			{				
				_Sisters_Attack_On = false;
				Joint_Operation = false;		
				int select = random(0, 1);

				if (select == 0)
					longhair_change();				
				if (select == 1)
					shorthair_change();
			}
			else
			{
				_state = Layana_Sisters_State::Sisters_Attack_Set;
				_Attacktime = 0;
			}
		}
	}


	void Layana_Sisters::Sisters_Attack_C_Ready()
	{		
		if(_SistersAttack_C_IntroReadyShortHair == true && _SistersAttack_C_IntroReady_LongHair == true)
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
		if (_Attacktime > 1)
		{
			if (_SistersAttack_Number > 1)
			{
				_Sisters_Attack_On = false;
				Joint_Operation = false;
				int select = random(0, 1);

				if (select == 0)
					longhair_change();
				if (select == 1)
					shorthair_change();
			}
			else
			{
				_state = Layana_Sisters_State::Sisters_Attack_Set;
				_Attacktime = 0;				
			}
		}		
	}



	void Layana_Sisters::Sisters_Attack_D()
	{
	}



	void Layana_Sisters::longhair_change()
	{
		LongHair_Operation = true;
		LongHair_First_moving = true;
		_Attacktime = 0;
		_SistersAttack_Number = 0;
		Layana_ShortHair::Background_state = Layana_ShortHair::Layana_Short_Background::Idle;
		Layana_LongHair::_LongHair_state = Layana_LongHair::Layana_LongHair_State::Idle;
	}

	void Layana_Sisters::shorthair_change()
	{
		ShortHair_Operation = true;
		ShortHair_First_moving = true;
		_Attacktime = 0;
		_SistersAttack_Number = 0;
		Layana_LongHair::Background_state = Layana_LongHair::Layana_Long_Background::Idle;
		Layana_ShortHair::_ShortHair_state = Layana_ShortHair::Layana_ShortHair_State::Idle;
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