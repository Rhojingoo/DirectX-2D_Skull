#include "Yggdrasil.h"
#include <iostream>
#include <random>

namespace jk
{
	Yggdrasil::Yggdrasil_State Yggdrasil::_state = Yggdrasil_State();
	Vector3 Yggdrasil::_playerpos = Vector3(0.f, 0.f, 0.f);
	Vector3 Yggdrasil::_pos = Vector3(0.f, 0.f, 0.f);
	float Yggdrasil::_time = 0.f;

	bool Yggdrasil::_SetattackA_r = false;
	bool Yggdrasil::_SetattackA_l = false;
	bool Yggdrasil::_AttackA_Readyr = false;
	bool Yggdrasil::_AttackA_Readyl = false;
	bool Yggdrasil::_SetattackB_r = false;
	bool Yggdrasil::_SetattackB_l = false;
	bool Yggdrasil::_AttackB_Readyr = false;
	bool Yggdrasil::_AttackB_Readyl = false;
	int	Yggdrasil::_NumberofAttack = 0;



	Yggdrasil::Yggdrasil()		
	{
	}
	Yggdrasil::~Yggdrasil()
	{
	}
	void Yggdrasil::Initialize()
	{
		_Gobjs[0] = new Yggdrasil_Body;
		_Gobjs[0]->Initialize();
		_Gobjs[1] = new Yggdrasil_Face;
		_Gobjs[1]->Initialize();
		_Gobjs[2] = new Yggdrasil_Chin;
		_Gobjs[2]->Initialize();
		_Gobjs[3] = new Yggdrasil_Hand_Right;
		_Gobjs[3]->Initialize();
		_Gobjs[4] = new Yggdrasil_Hand_Left;
		_Gobjs[4]->Initialize();

		for (int i = 0; i < 5; i++)
		{
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Boss, _Gobjs[i]);
			//Transform* tr = _Gobjs[i]->GetComponent<Transform>();
			//tr->SetPosition(Vector3(0.f, 0.f, -250.f));

			//if (0 == i)
			//	_Gobjs[i]->SetState(eState::Paused);
			//if (_minibosschoice != i)
			//	_Gobjs[i]->SetState(eState::Paused);
		}

		GameObject::Initialize();
	}
	void Yggdrasil::Update()
	{
		_playerpos;
		_Playerdistance.x = _playerpos.x - _pos.x;
		if (_Playerdistance.x >= 0.f)
			mDir = 1;
		else
			mDir = -1;


		switch (_state)
		{
		case jk::Yggdrasil::Yggdrasil_State::Idle:idle();
			break;	

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Set:
			attack_a_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Ready:
			attack_a_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Right:
			attack_a_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Left:
			attack_a_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Loading:
			attack_a_loading();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Finish:
			attack_a_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Set:
			attack_b_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Ready:
			attack_b_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Right:
			attack_b_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Left:
			attack_b_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Finish:
			attack_b_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C:
			attack_c();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro:
			intro();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Die:
			die();
			break;

		default:
			break;
		}

		GameObject::Update();
	}
	void Yggdrasil::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Yggdrasil::Render()
	{
		GameObject::Render();
	}

	void Yggdrasil::OnCollisionEnter(Collider2D* other)
	{
	}

	void Yggdrasil::OnCollisionStay(Collider2D* other)
	{
	}

	void Yggdrasil::OnCollisionExit(Collider2D* other)
	{
	}

	void Yggdrasil::idle()
	{
		_time += Time::DeltaTime();
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(0, 1);
		Attack_Sellect = distribution(gen);
		_NumberofAttack = 0;
		if (_time > 3)
		{
			if (Attack_Sellect == 0)
			{
				Yggdrasil_Hand_Left::_Attackswitch = true;
				Yggdrasil_Hand_Right::_Attackswitch = true;
				_state = Yggdrasil_State::Attack_A_Set;
			}

			if (Attack_Sellect == 1)
			{
				Yggdrasil_Hand_Right::_Attackswitch = true;
				Yggdrasil_Hand_Left::_Attackswitch = true;
				_state = Yggdrasil_State::Attack_B_Set;
			}
		}
	}

	void Yggdrasil::die()
	{
	}

	void Yggdrasil::attack_a_set()
	{
		if (_SetattackA_r == true && _SetattackA_l)
			_state = Yggdrasil_State::Attack_A_Ready;
	}
	void Yggdrasil::attack_a_ready()
	{
		if (_AttackA_Readyr == true && _AttackA_Readyr == true)
		{
			if (mDir == 1)
			{
				_state = Yggdrasil_State::Attack_A_Right;
				Yggdrasil_Hand_Right::_Attackswitch = true;
			}
			else
			{
				_state = Yggdrasil_State::Attack_A_Left;
				Yggdrasil_Hand_Left::_Attackswitch = true;
			}
		}
	}
	void Yggdrasil::attack_a_right()
	{
		if (Yggdrasil_Hand_Right::_Attackswitch == true)
		{
			_attackatime += Time::DeltaTime();
			if (_attackatime > 2.5f)
			{
				_state = Yggdrasil_State::Attack_A_Loading;
				_attackatime = 0.f;
			}			
		}
	}
	void Yggdrasil::attack_a_left()
	{
		if (Yggdrasil_Hand_Left::_Attackswitch == true) 
		{			
			_attackatime += Time::DeltaTime();
			if (_attackatime > 2.5f)
			{
				_state = Yggdrasil_State::Attack_A_Loading;
				_attackatime = 0.f;
			}
		}
	}
	void Yggdrasil::attack_a_loading()
	{
	}
	void Yggdrasil::attack_a_finish()
	{
		Yggdrasil_Hand_Right::_Attackswitch = false;
		Yggdrasil_Hand_Left::_Attackswitch = false;
		_SetattackA_r = false;
		_SetattackA_l = false;
		_AttackA_Readyr = false;
		_AttackA_Readyl = false;

	}

	void Yggdrasil::attack_b_set()
	{
		if ((_SetattackB_r == true) && (_SetattackB_l == true))
			_state = Yggdrasil_State::Attack_B_Ready;		
	}
	void Yggdrasil::attack_b_ready()
	{
		if (_NumberofAttack >= 2)
		{
			int a = 0;
			_state = Yggdrasil_State::Attack_B_Finish;
			Yggdrasil_Hand_Right::_Attackswitch = false;
			Yggdrasil_Hand_Left::_Attackswitch = false;
			_SetattackB_r = false;
			_SetattackB_l = false;
			_AttackB_Readyr = false;
			_AttackB_Readyl = false;
		}
		else
		{
			if ((_AttackB_Readyr == true) && (_AttackB_Readyl == true))
			{
				if (mDir == 1)
				{
					_state = Yggdrasil_State::Attack_B_Right;
					Yggdrasil_Hand_Right::_Attackswitch = true;
				}
				else
				{
					_state = Yggdrasil_State::Attack_B_Left;
					Yggdrasil_Hand_Left::_Attackswitch = true;
				}
			}
		}
	}
	void Yggdrasil::attack_b_left()
	{
	}
	void Yggdrasil::attack_b_right()
	{
	}
	void Yggdrasil::attack_b_finish()
	{
	}

	void Yggdrasil::attack_c()
	{
	}

	void Yggdrasil::intro()
	{
	}
}