#include "Yggdrasil_Hand_Right.h"

namespace jk
{
	bool Yggdrasil_Hand_Right::_Attackswitch = false;
	Yggdrasil_Hand_Right::Yggdrasil_Hand_Right()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Yggdrasil_Hand_Right::~Yggdrasil_Hand_Right()
	{
	}
	void Yggdrasil_Hand_Right::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		
		_pos = Vector3(GetPos().x + 150.f, GetPos().y-100, -203.f);
		_Savepointpos = _pos;
		tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(_pos));

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandIdle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandRock", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandAttack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandAntlion", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandBullet", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_Bullet_off", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_Bullet_on", this, 1);

		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandIdle_Change", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandRock_Change", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandAttack_Change", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandAntlion_Change", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandBullet_Change", this, 1);

		//bind �κ�
		//at->CompleteEvent(L"Hand1_HandAttackR") = std::bind(&Yggdrasil_Hand_Right::attackbstart, this);
		//at->EndEvent(L"Hand1_HandAttackR") = std::bind(&Yggdrasil_Hand_Right::attackbstart, this);
		//at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);
		

		at->PlayAnimation(L"Hand1_HandIdleR", true);

		GameObject::Initialize();
	}
	void Yggdrasil_Hand_Right::Update()
	{
		tr = GetComponent<Transform>();
		_pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		

		_Yggdrasildistance = GetPos()- _pos;
		_Playerdistance = _playerpos - _pos;			

		switch (_state)
		{
		case jk::Yggdrasil::Yggdrasil_State::Idle:
			Yggdrasil_Hand_Right::idle();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Set:
			Yggdrasil_Hand_Right::attack_a_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Ready:
			Yggdrasil_Hand_Right::attack_a_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Right:
			Yggdrasil_Hand_Right::attack_a_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Loading:
			Yggdrasil_Hand_Right::attack_a_loading();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Finish:
			Yggdrasil_Hand_Right::attack_a_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Set:
			Yggdrasil_Hand_Right::attack_b_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Ready:
			Yggdrasil_Hand_Right::attack_b_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Right:
			Yggdrasil_Hand_Right::attack_b_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Left:
			Yggdrasil_Hand_Right::attack_b_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Finish:
			Yggdrasil_Hand_Right::attack_b_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Set:
			Yggdrasil_Hand_Right::attack_c_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Ready:
			Yggdrasil_Hand_Right::attack_c_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C:
			Yggdrasil_Hand_Right::attack_c();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Finish:
			Yggdrasil_Hand_Right::attack_c_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Groggy_Start:
			Yggdrasil_Hand_Right::groggy_start();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Groggy_End:
			Yggdrasil_Hand_Right::groggy_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro:
			Yggdrasil_Hand_Right::intro();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Die:
			Yggdrasil_Hand_Right::die();
			break;

		default:
			break;
		}

		tr->SetPosition(_pos);
		GameObject::Update();
	}

	void Yggdrasil_Hand_Right::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}

	void Yggdrasil_Hand_Right::Render()
	{
		GameObject::Render();
	}

	void Yggdrasil_Hand_Right::OnCollisionEnter(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{

			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_rigidbody->ClearVelocity();
				_Ground_check = true;
				_Attackswitch = true;
				_NumberofAttack++;
			}
			else
			{				
			}
		}
	}

	void Yggdrasil_Hand_Right::OnCollisionStay(Collider2D* other)
	{
	}

	void Yggdrasil_Hand_Right::OnCollisionExit(Collider2D* other)
	{
	}

	void Yggdrasil_Hand_Right::idle()
	{
		_pos = Vector3(GetPos().x + 150.f, GetPos().y - 100, -203.f);
	}



	void Yggdrasil_Hand_Right::attack_a_set()
	{
		if (_Attackswitch == true)
		{
			_rigidbody->SetVelocity(Vector2(10.f, 0.f));
			_Attackswitch = false;
		}
		else
		{
			_SetattackA_r = true;
			at->PlayAnimation(L"Hand1_HandRockR", true);
		}
	}
	void Yggdrasil_Hand_Right::attack_a_ready()
	{
		if (_SetattackA_r == true)
		{
			at->PlayAnimation(L"Hand1_HandRockR", true);
			_rigidbody->SetVelocity(Vector2(0.f, 500.f));
			_rigidbody->SetGround(false);
			_Attackswitch = false;
			_Ground_check = false;
		}
		if (_Yggdrasildistance.y <= -137.f)
		{
			_rigidbody->ClearVelocity();
			_rigidbody->SetGround(true);
			_AttackA_SavePos = _pos;
			_AttackA_Readyr = true;
		}

	}
	void Yggdrasil_Hand_Right::attack_a_right()
	{
		if (_AttackA_Readyr == true)
		{	
			_Ground_check = false;
			_rigidbody->SetGround(false);
			_rigidbody->SetVelocity(Vector2(-250.f, -150.f));
			_AttackA_Readyr = false;
		}
	}
	void Yggdrasil_Hand_Right::attack_a_left()
	{
	}
	void Yggdrasil_Hand_Right::attack_a_loading()
	{
		if (_Attackswitch == true && _Ground_check == true)
		{
			if (_NumberofAttack <= 2)
			{
				if (_pos.x < _AttackA_SavePos.x)
					_pos.x += 150.0f * Time::DeltaTime();
				if (_pos.y < _AttackA_SavePos.y)
					_pos.y += 250.0f * Time::DeltaTime();
				tr->SetPosition(Vector3(_pos));

				if (_AttackA_SavePos.x <= _pos.x)
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
	void Yggdrasil_Hand_Right::attack_a_finish()
	{	
		if (_NumberofAttack >= 2)
		{
			_Savepointpos.x;
			if (_pos.x < _Savepointpos.x)
				_pos.x += 150.0f * Time::DeltaTime();
			if (_pos.y > _Savepointpos.y)
				_pos.y -= 150.0f * Time::DeltaTime();
			//tr->SetPosition(Vector3(_pos));

			if (_Savepointpos.x <= _pos.x)
				_pos.x = _Savepointpos.x;
			if (_Savepointpos.y >= _pos.y)		
				_pos.y = _Savepointpos.y;				
		
			at->PlayAnimation(L"Hand1_HandIdleR", true);
			if ((_pos.x == _Savepointpos.x) && (_pos.y == _Savepointpos.y))
			{
				//at->PlayAnimation(L"Hand1_HandIdleR", true);
				//_state = Yggdrasil_State::Idle;
			}
		}
	}



	void Yggdrasil_Hand_Right::attack_b_set()
	{
		if (_Attackswitch == true)
		{			
			_rigidbody->SetVelocity(Vector2(10.f, 0.f));			
			_Attackswitch = false;
		}
		else
		{
			_SetattackB_r = true;
			at->PlayAnimation(L"Hand1_HandAttackR", false);
		}
	}
	void Yggdrasil_Hand_Right::attack_b_ready()
	{
		if (_SetattackB_r == true)
			attackb_setting();
	}
	void Yggdrasil_Hand_Right::attack_b_right()
	{		
		{
			if (_attackon == true)
				_rigidbody->SetVelocity(Vector2(-350.f, 0.f));
			else
			{
				_NumberofAttack++;
				_state = Yggdrasil_State::Attack_B_Set;
				if (_NumberofAttack >= 2)
				{
					at->PlayAnimation(L"Hand1_HandIdleR", true);
					_rigidbody->ClearVelocityX();
					_pos.x = _Savepointpos.x;
					_pos.y = _Savepointpos.y - 300;
				}
			}

			if (_Yggdrasildistance.x >= 1000)
			{
				_rigidbody->ClearVelocityX();
				_pos.x = _AttackB_SavePos.x;
				_pos.y = _AttackB_SavePos.y;				
				_attackon = false;
			}		
		}
	}
	void Yggdrasil_Hand_Right::attack_b_left()
	{
		//if (_NumberofAttack >= 2)
		//{
		//	at->PlayAnimation(L"Hand1_HandIdleR", true);
		//	_rigidbody->ClearVelocityX();
		//	_pos.x = _Savepointpos.x;
		//	_pos.y = _Savepointpos.y - 300;
		//}
	}
	void Yggdrasil_Hand_Right::attack_b_finish()
	{
		//������ ������
		if (_NumberofAttack >= 2)
		{
			_attackon = false;
			_pos.x = _Savepointpos.x;
			_pos.y = _Savepointpos.y - 300;
			_NumberofAttack = 3;
			at->PlayAnimation(L"Hand1_HandIdleR", true);
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
				at->PlayAnimation(L"Hand1_HandIdleR", true);
				//_state = Yggdrasil_State::Idle;
				//Yggdrasil::_time = 0.f;
				_attackready = false;
				_attackon = false;
			}
		}
	}


	void Yggdrasil_Hand_Right::attack_c_set()
	{
		if (_Attackswitch == true)
		_Attackswitch = false;		
		else
		{
			at->PlayAnimation(L"Hand1_Bullet_onR", false);
			_SetattackC_r = true;
		}
	}
	void Yggdrasil_Hand_Right::attack_c_ready()
	{
	}
	void Yggdrasil_Hand_Right::attack_c()
	{
	}
	void Yggdrasil_Hand_Right::attack_c_finish()
	{

	}

	void Yggdrasil_Hand_Right::groggy_start()
	{
	}

	void Yggdrasil_Hand_Right::groggy_end()
	{
		if (_Groggy_RightHand_Up == false)
		{
			at->PlayAnimation(L"Hand1_HandIdleR", true);
			_Groggy_RightHand_Up = true;
		}
	}


	void Yggdrasil_Hand_Right::intro()
	{
	}
	void Yggdrasil_Hand_Right::die()
	{
	}

	void Yggdrasil_Hand_Right::attackb_setting()
	{		
		if (_attackready == false)
		{
			if (_Yggdrasildistance.x <= -500)
			{
				_pos.x = _pos.x;
				_AttackB_Readyr = true;
				_AttackB_SavePos = _pos;
				_attackon = true;
			}
			else			
				_pos.x += 150.0f * Time::DeltaTime();
				
			tr->SetPosition(Vector3(_pos));			
		}	
	}
}

