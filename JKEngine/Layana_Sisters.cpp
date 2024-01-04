#include "Layana_Sisters.h"
#include <iostream>
#include <random>
#include "jkFont.h"
#include "Include_Common.h"

#include "..\Engine_SOURCE\jkAudioSource.h"
namespace jk
{
	Layana_Sisters::Layana_Sisters_State Layana_Sisters::_state = Layana_Sisters_State();
	Layana_Sisters::LayanaSisters_List Layana_Sisters::Layana_select = LayanaSisters_List();
	Layana_Sisters::LayanaSisters_List Layana_Sisters::Layana_check = LayanaSisters_List();
	int Layana_Sisters::BossDir = 1;
	
	Vector3 Layana_Sisters::LongHairPos = Vector3();;
	Vector3 Layana_Sisters::ShortHairPos = Vector3();
	Vector3 Layana_Sisters::AwakenDarkmode_Pos = Vector3();
	
	Layana_HpFrame* Layana_Sisters::_HpBarFrame = nullptr;
	float Layana_Sisters::_Max_LongHair_Hp = 2000;
	float Layana_Sisters::_Curren_LongHair_Hp = 2000;
	float Layana_Sisters::_MaxHp_LongHair_scale = 0;
	float Layana_Sisters::_CurrenHp_LongHair_scale = 0;


	float Layana_Sisters::_Max_ShortHair_Hp = 2000;
	float Layana_Sisters::_Curren_ShortHair_Hp = 2000;
	float Layana_Sisters::_MaxHp_ShortHair_scale = 0;
	float Layana_Sisters::_CurrenHp_ShortHair_scale = 0;


	float Layana_Sisters::_Max_Dark_Awaken_Hp = 3000;
	float Layana_Sisters::_Curren_Dark_Awaken_Hp = 3000;
	float Layana_Sisters::_MaxHp_Dark_Awaken_scale = 0;
	float Layana_Sisters::_CurrenHp_Dark_Awaken_scale = 0;



	bool Layana_Sisters::_First_Die = false;
	bool Layana_Sisters::_LongHair_Die = false;
	bool Layana_Sisters::_ShortHair_Die = false;
	bool Layana_Sisters::_DarkLayana_Die = false;
	bool Layana_Sisters::_ShortHair_Awaken = false;
	bool Layana_Sisters::_LongHair_Awaken = false;
	bool Layana_Sisters::_Layana_change = false;
	bool Layana_Sisters::_Awaken_Switch = false;


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
	bool Layana_Sisters::_Intro_LandEnd_LongHair = false;
	bool Layana_Sisters::_Intro_LandEnd_ShortHair = false;
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
		_Gobjs[2] = new Layana_Dark_Awaken;
		_Gobjs[2]->Initialize();


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


		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(eLayerType::Boss, _Gobjs[0]);
		scene->AddGameObject(eLayerType::Boss, _Gobjs[1]);
		scene->AddGameObject(eLayerType::Boss, _Gobjs[2]);
		_Gobjs[2]->SetState(eState::Paused);

		

		{
			_HpBarFrame = new Layana_HpFrame();
			_HpBarFrame->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _HpBarFrame);
			Transform* bullet_tr = _HpBarFrame->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(0.f, 170.f, -205.f));
			_HpBarFrame->SetState(eState::Active);
		}

		GameObject::Initialize();
	}


	void Layana_Sisters::Update()
	{
		if (_Layana_change == true)
		{
			_HpBarFrame->Set_Animation(true);
			_HpBarFrame->ChoicetHp_bar(1);
			if (Layana_select == LayanaSisters_List::Awaken_Darkmode)
			{
				if (Layana_check == LayanaSisters_List::LonaHair)
				{
					_Gobjs[(UINT)LayanaSisters_List::LonaHair]->SetState(eState::Paused);
				}
				else if (Layana_check == LayanaSisters_List::ShortHair)
				{
					_Gobjs[(UINT)LayanaSisters_List::ShortHair]->SetState(eState::Paused);
				}

				_Gobjs[(UINT)LayanaSisters_List::Awaken_Darkmode]->SetState(eState::Active);
				Transform* tr = _Gobjs[(UINT)LayanaSisters_List::Awaken_Darkmode]->GetComponent<Transform>();
				tr->SetPosition(AwakenDarkmode_Pos); Layana_Dark_Awaken::SetDirection(BossDir);
			}
			_Awaken_Switch = true;
			_LongHair_Awaken = false;
			_ShortHair_Awaken = false;
			_Layana_change = false;
		}

		if(_First_Die == true)		
			Joint_Operation = false;

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

			case jk::Layana_Sisters::Layana_Sisters_State::Intro_Landing_End:
				Intro_Landing_End();
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
			if (_First_Die == false)
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
		}
		
		if (LongHair_Operation == true)
		{
			if (_First_Die == false)
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
			{
				_state = Layana_Sisters_State::Intro_Dash;
				as->Play("Leiana_Enter");				
			}
			_SistersAttack_Number = 0;
		}
		else
		{
			if (_Sisters_Attack_On == true)
			{
				if(_Sisters_AttackType == 0)
				_state = Layana_Sisters_State::Sisters_Attack_A_Ready;
				//if (_Sisters_AttackType == 1)
				//_state = Layana_Sisters_State::Sisters_Attack_B_Ready;		
				//if (_Sisters_AttackType == 2)
				//_state = Layana_Sisters_State::Sisters_Attack_C_Ready;
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
		{
			_state = Layana_Sisters_State::Intro_Landing;
			as->Play("Leiana_Landing");
		}
	}
	void Layana_Sisters::Intro_Landing()
	{		
		if (_Intro_LandEnd_LongHair == true && _Intro_LandEnd_ShortHair == true)
		{
			_state = Layana_Sisters_State::Intro_Landing_End;
			as->Play("Leiana_Intro_Impact");			
		}		
	}
	void Layana_Sisters::Intro_Landing_End()
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
		{
			_state = Layana_Sisters_State::Sisters_Attack_FlyDash;
			as->Play("Leiana_Enter");
		}
	}


	void Layana_Sisters::Sisters_Attack_Set()
	{	
			_Sisters_AttackType = random(0, 2);
			//_Sisters_AttackType = 2;
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
			{
				_state = Layana_Sisters_State::Sisters_Attack_FlyDash;
				as->Play("Leiana_Enter");
			}
			_SistersAttack_Number++;
	}	
	void Layana_Sisters::Sisters_Attack_FlyDash()
	{		
		if (_SistersAttack_FlyDash_ShortHair == true && _SistersAttack_FlyDash_LongHair == true)		
			_state = Layana_Sisters_State::Sisters_Attack_Fall;
		
		if (_SistersAttack_C_DashOn_ShortHair == true && _SistersAttack_C_DashOn_LongHair == true)			
			_state = Layana_Sisters_State::Sisters_Attack_C;		
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
		if (_SistersAttack_A_DashOn_ShortHair == true && _SistersAttack_A_DashOn_LongHair == true)
		{			
			as->Play("Leiana_MeteorGround");
			_state = Layana_Sisters_State::Sisters_Attack_A;
		}
	}
	void Layana_Sisters::Sisters_Attack_A()
	{
		if(_SistersAttack_A_LongHair_END ==true && _SistersAttack_A_ShortHair_END ==true)
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

		_Attacktime += static_cast<float>(Time::DeltaTime());
		if (_Attacktime > 1.0)
		{
			AttackSwap();
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
			_Attacktime += static_cast<float>(Time::DeltaTime());
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


		_Attacktime += static_cast<float>(Time::DeltaTime());
		if (_Attacktime > 1)
		{
			AttackSwap();
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
			_Attacktime += static_cast<float>(Time::DeltaTime());
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

		_Attacktime += static_cast<float>(Time::DeltaTime());
		if (_Attacktime > 1)
		{
			AttackSwap();
		}		
	}


	void Layana_Sisters::Sisters_Attack_D()
	{
	}


	void Layana_Sisters::longhair_change()
	{
		LongHair_Operation = true;
		LongHair_First_moving = true;

		_SistersAttack_Number = 0;
		Layana_ShortHair::Background_state = Layana_ShortHair::Layana_Short_Background::Idle;
		Layana_LongHair::_LongHair_state = Layana_LongHair::Layana_LongHair_State::Idle;
	}
	void Layana_Sisters::shorthair_change()
	{
		ShortHair_Operation = true;
		ShortHair_First_moving = true;

		_SistersAttack_Number = 0;
		Layana_LongHair::Background_state = Layana_LongHair::Layana_Long_Background::Idle;
		Layana_ShortHair::_ShortHair_state = Layana_ShortHair::Layana_ShortHair_State::Idle;
	}


	void Layana_Sisters::AttackSwap()
	{
		if (_SistersAttack_Number >= 3)
		{
			_Sisters_Attack_On = false;
			Joint_Operation = false;
			int select = random(0, 1);
			//select = 1;

			if (select == 0)
				longhair_change();
			if (select == 1)
				shorthair_change();
			_Attacktime = 0;
			_SistersAttack_Number = 0;
		}
		else
		{
			_state = Layana_Sisters_State::Sisters_Attack_Set;
			_Attacktime = 0;
		}
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