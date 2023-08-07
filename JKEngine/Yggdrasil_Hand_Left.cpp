#include "Yggdrasil_Hand_Left.h"

namespace jk
{
	bool Yggdrasil_Hand_Left::_Attackswitch = false;

	Yggdrasil_Hand_Left::Yggdrasil_Hand_Left()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Yggdrasil_Hand_Left::~Yggdrasil_Hand_Left()
	{
	}
	void Yggdrasil_Hand_Left::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		_pos = Vector3(GetPos().x - 150.f, GetPos().y, -203.f);
		_Savepointpos = _pos;
		tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(_pos));


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandIdle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandRock", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandAttack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandAntlion", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandBullet", this);

		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandIdle_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandRock_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandAttack_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandAntlion_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandBullet_Change", this);

		//bind 부분
		//at->CompleteEvent(L"ArcherAttack_A") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_B") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);

		at->PlayAnimation(L"Hand1_HandIdle", true);

		GameObject::Initialize();
	}
	void Yggdrasil_Hand_Left::Update()
	{
		tr = GetComponent<Transform>();
		_pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();

		_Yggdrasildistance = GetPos() - _pos;
		_Playerdistance = _playerpos - _pos;


		switch (_state)
		{
		case jk::Yggdrasil::Yggdrasil_State::Idle:
			Yggdrasil_Hand_Left::idle();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Set:
			Yggdrasil_Hand_Left::attack_a_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Ready:
			Yggdrasil_Hand_Left::attack_a_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Loading:
			Yggdrasil_Hand_Left::attack_a_loading();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Left:
			Yggdrasil_Hand_Left::attack_a_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Finish:
			Yggdrasil_Hand_Left::attack_a_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Set:
			Yggdrasil_Hand_Left::attack_b_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Ready:
			Yggdrasil_Hand_Left::attack_b_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Right:
			Yggdrasil_Hand_Left::attack_b_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Left:
			Yggdrasil_Hand_Left::attack_b_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Finish:
			Yggdrasil_Hand_Left::attack_b_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C:
			Yggdrasil_Hand_Left::attack_c();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro:
			Yggdrasil_Hand_Left::intro();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Die:
			Yggdrasil_Hand_Left::die();
			break;

		default:
			break;
		}

		tr->SetPosition(_pos);	
		GameObject::Update();
	}
	void Yggdrasil_Hand_Left::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}

	void Yggdrasil_Hand_Left::Render()
	{
		GameObject::Render();
	}

	void Yggdrasil_Hand_Left::OnCollisionEnter(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_rigidbody->ClearVelocity();
				_Ground_check = true;

				_time += Time::DeltaTime();
				_Attackswitch = true;
				_NumberofAttack++;
			}
			else
			{

			}
		}
	}

	void Yggdrasil_Hand_Left::OnCollisionStay(Collider2D* other)
	{
	}

	void Yggdrasil_Hand_Left::OnCollisionExit(Collider2D* other)
	{
	}

	void Yggdrasil_Hand_Left::idle()
	{		
	}

	void Yggdrasil_Hand_Left::attack_a_set()
	{
		if (_Attackswitch == true)
		{
			_rigidbody->SetVelocity(Vector2(-10.f, 0.f));
			_Attackswitch = false;
		}
		else
		{
			_SetattackA_l = true;
			at->PlayAnimation(L"Hand1_HandRock", true);
		}
	}
	void Yggdrasil_Hand_Left::attack_a_ready()
	{
		if (_SetattackA_l == true)
		{
			//_Yggdrasildistance;
			//int a = 0;
			at->PlayAnimation(L"Hand1_HandRock", true);
			_rigidbody->SetGround(false);
			_rigidbody->SetVelocity(Vector2(0.f, 500.f));
			_Attackswitch = false;
			_Ground_check = false;
		}

		if (_Yggdrasildistance.y <= -137.f)
		{
			_rigidbody->ClearVelocity();
			_rigidbody->SetGround(true);
			if(_AttackA_SavePos.y<_pos.y)
			_AttackA_SavePos = _pos;
			_AttackA_Readyl = true;
		}
	}
	void Yggdrasil_Hand_Left::attack_a_left()
	{
		if (_AttackA_Readyl == true)
		{
			_Ground_check = false;
			_rigidbody->SetGround(false);
			_rigidbody->SetVelocity(Vector2(250.f, -150.f));
			_AttackA_Readyl = false;
		}
	}
	void Yggdrasil_Hand_Left::attack_a_loading()
	{
		if (_Attackswitch == true && _Ground_check == true)
		{
			if (_NumberofAttack <= 2)
			{
				if (_pos.x > _AttackA_SavePos.x)
					_pos.x -= 150.0f * Time::DeltaTime();
				if (_pos.y < _AttackA_SavePos.y)
					_pos.y += 250.0f * Time::DeltaTime();
				tr->SetPosition(Vector3(_pos));

				if (_AttackA_SavePos.x >= _pos.x)
					_pos.x = _AttackA_SavePos.x;
				if (_AttackA_SavePos.y <= _pos.y)
					_pos.y = _AttackA_SavePos.y;

				if ((_pos.x == _AttackA_SavePos.x) && (_pos.y == _AttackA_SavePos.y))
				{
					if (_NumberofAttack < 2)
						_state = Yggdrasil_State::Attack_A_Set;
					else					
						_state = Yggdrasil_State::Attack_A_Finish;					
				}
			}
		}
	}
	void Yggdrasil_Hand_Left::attack_a_finish()
	{
		int a = 0;
		if (_NumberofAttack == 2)
		 {
			_Savepointpos.x;
			if (_pos.x > _Savepointpos.x)
				_pos.x -= 150.0f * Time::DeltaTime();
			if (_pos.y > _Savepointpos.y)
				_pos.y -= 150.0f * Time::DeltaTime();
			tr->SetPosition(Vector3(_pos));

			if (_Savepointpos.x >= _pos.x)
				_pos.x = _Savepointpos.x;
			if (_Savepointpos.y >= _pos.y)
				_pos.y = _Savepointpos.y;

			at->PlayAnimation(L"Hand1_HandIdle", true);
			if ((_pos.x == _Savepointpos.x) && (_pos.y == _Savepointpos.y))
			{
				//at->PlayAnimation(L"Hand1_HandIdle", true);
				_state = Yggdrasil_State::Idle;
				Yggdrasil::_time = 0.f;
				_NumberofAttack = 0;
			}
		}
	}



	void Yggdrasil_Hand_Left::attack_b_set()
	{
		if (_Attackswitch == true)
		{
			_rigidbody->SetVelocity(Vector2(-10.f, 0.f));
			_Attackswitch = false;
		}
		else
		{
			_SetattackB_l = true;
			at->PlayAnimation(L"Hand1_HandAttack", false);
		}
	}
	void Yggdrasil_Hand_Left::attack_b_ready()
	{
		if(_SetattackB_l ==true)
			attackb_setting();
	}
	void Yggdrasil_Hand_Left::attack_b_right()
	{				
	}
	void Yggdrasil_Hand_Left::attack_b_left()
	{	
		{
			if (_attackon == true)
				_rigidbody->SetVelocity(Vector2(+350.f, 0.f));
			else
			{
				_NumberofAttack++;
				_state = Yggdrasil_State::Attack_B_Set;
				if (_NumberofAttack >= 2)
				{
					at->PlayAnimation(L"Hand1_HandIdle", true);
					_rigidbody->ClearVelocityX();
					_pos.x = _Savepointpos.x;
					_pos.y = _Savepointpos.y - 300;
				}
			}
			if (_Yggdrasildistance.x <= -1000)
			{
				_rigidbody->ClearVelocityX();				
				_pos.x = _AttackB_SavePos.x;
				_pos.y = _AttackB_SavePos.y;
				_attackon = false;
			}
		}
	}
	void Yggdrasil_Hand_Left::attack_b_finish()
	{
		//공격끝난후
		if (Yggdrasil::_NumberofAttack >= 3)
		{
			_attackon = false;
			_pos.x = _Savepointpos.x;
			_pos.y = _Savepointpos.y - 300;
			Yggdrasil::_NumberofAttack = 0;
			at->PlayAnimation(L"Hand1_HandIdle", true);
		}

		if (_attackon == false)
		{
			if (_pos.y < _Savepointpos.y)
				_pos.y += 150.0f * Time::DeltaTime();

			if (_Savepointpos.x <= _pos.x)
				_pos.x = _Savepointpos.x;
			if (_Savepointpos.y <= _pos.y)
				_pos.y = _Savepointpos.y;

			tr->SetPosition(Vector3(_pos));

			if ((_pos.x == _Savepointpos.x) && (_pos.y == _Savepointpos.y))
			{
				at->PlayAnimation(L"Hand1_HandIdle", true);
				_state = Yggdrasil_State::Idle;
				Yggdrasil::_time = 0.f;
				_attackready = false;
				_attackon = false;
			}
		}
	}

	void Yggdrasil_Hand_Left::attack_c()
	{
	}
	void Yggdrasil_Hand_Left::intro()
	{
	}
	void Yggdrasil_Hand_Left::die()
	{
	}


	void Yggdrasil_Hand_Left::attackb_setting()
	{
		if (_attackready == false) 
		{
			if (_Yggdrasildistance.x >= 500)
			{
				_pos.x = _pos.x; 
				_AttackB_Readyl = true;
				_AttackB_SavePos = _pos;
				_attackon = true;
			}
			else	
				_pos.x -= 150.0f * Time::DeltaTime();	
			
			tr->SetPosition(Vector3(_pos));
		}		
	}

}
