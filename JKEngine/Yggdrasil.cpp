#include "Yggdrasil.h"

namespace jk
{
	Yggdrasil::Yggdrasil_State Yggdrasil::_state = Yggdrasil_State();
	Vector3 Yggdrasil::_playerpos = Vector3(0.f, 0.f, 0.f);
	Vector3 Yggdrasil::_pos = Vector3(0.f, 0.f, 0.f);
	float Yggdrasil::_time = 0.f;

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

		case jk::Yggdrasil::Yggdrasil_State::Attack_A:attack_a();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B:attack_b();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C:attack_c();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro:intro();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Die:die();
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

		if (_time > 3)
		{
			//_state = Yggdrasil_State::Attack_A;
			////if (mDir == 1)				
			//Yggdrasil_Hand_Right::_Attackswitch = true;			
			////else			
			////Yggdrasil_Hand_Left::_Attackswitch = true;

			_state = Yggdrasil_State::Attack_B;
			Yggdrasil_Hand_Right::_Attackswitch = true;
		}
	}

	void Yggdrasil::die()
	{
	}

	void Yggdrasil::attack_a()
	{
	}

	void Yggdrasil::attack_b()
	{
	}

	void Yggdrasil::attack_c()
	{
	}

	void Yggdrasil::intro()
	{
	}
}