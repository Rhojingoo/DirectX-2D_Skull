#include "Yggdrasil_Body.h"


namespace jk
{
	Yggdrasil_Body::Yggdrasil_Body()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Yggdrasil_Body::~Yggdrasil_Body()
	{
	}
	void Yggdrasil_Body::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		

		tr = GetComponent<Transform>();
		_pos = Vector3(0.f, -380.f, -199.f);		
		_savepos = Vector3(0.f, -20.f, -200.f);
		tr->SetPosition(_pos);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Body\\YggdrasilBody_Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Body\\YggdrasilBody_Attack_C", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Body\\YggdrasilBody_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Body\\YggdrasilBody_Changing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Body\\YggdrasilBody_Die_Effect", this);
		
		//bind ºÎºÐ
		//at->CompleteEvent(L"ArcherAttack_A") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_B") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);


		at->PlayAnimation(L"BodyYggdrasilBody_Idle", true);
		if (_Changeon == true)
			at->PlayAnimation(L"BodyYggdrasilBody_Change", true);
		
		GameObject::Initialize();
	}


	void Yggdrasil_Body::Update()
	{
		SetPos(_pos);		

		//if (_state != Yggdrasil_State::Intro_End && _state != Yggdrasil_State::Intro && _state != Yggdrasil_State::Attack_C && _state != Yggdrasil_State::Attack_C_Ready && _state != Yggdrasil_State::Attack_C_UP && _state != Yggdrasil_State::Attack_C_Down && _state != Yggdrasil_State::Attack_C_Finish && _state != Yggdrasil_State::Change && _state != Yggdrasil_State::Change_End)
		//{
		//	{				
		//		if (mDir == 1)
		//			move_down();
		//		else
		//			move_up();				
		//	}
		//}



		switch (_state)
		{
		case jk::Yggdrasil::Yggdrasil_State::Idle:
			Yggdrasil_Body::idle();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Set:
			Yggdrasil_Body::attack_a_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Ready:
			Yggdrasil_Body::attack_a_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Right:
			Yggdrasil_Body::attack_a_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Left:
			Yggdrasil_Body::attack_a_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Loading:
			Yggdrasil_Body::attack_a_loading();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Finish:
			Yggdrasil_Body::attack_a_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Set:
			Yggdrasil_Body::attack_b_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Ready:
			Yggdrasil_Body::attack_b_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Right:
			Yggdrasil_Body::attack_b_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Left:
			Yggdrasil_Body::attack_b_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Finish:
			Yggdrasil_Body::attack_b_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Set:
			attack_c_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Ready:
			Yggdrasil_Body::attack_c_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C:
			Yggdrasil_Body::attack_c();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Finish:
			Yggdrasil_Body::attack_c_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Groggy_Start:
			Yggdrasil_Body::groggy_start();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Groggy_End:
			Yggdrasil_Body::groggy_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_Set_Right:
			Yggdrasil_Body::intro_set_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_Set_Left:
			Yggdrasil_Body::intro_set_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_Ready:
			Yggdrasil_Body::intro_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro:
			Yggdrasil_Body::intro();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_End:
			Yggdrasil_Body::intro_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change_Set:
			Yggdrasil_Body::change_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change_Ready:
			Yggdrasil_Body::change_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change:
			Yggdrasil_Body::change();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change_End:
			Yggdrasil_Body::change_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::DieSet:
			Yggdrasil_Body::die_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::DieReady:
			Yggdrasil_Body::die_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Die:
			Yggdrasil_Body::die();
			break;

		default:
			break;
		}
		Yggdrasil::SetRotation(_BodyRotation);
		tr->SetPosition(_pos);
		GameObject::Update();
	}


	void Yggdrasil_Body::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}


	void Yggdrasil_Body::Render()
	{
		GameObject::Render();
	}


	void Yggdrasil_Body::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_Body::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_Body::OnCollisionExit(Collider2D* other)
	{
	}

	void Yggdrasil_Body::idle()
	{
		at->PlayAnimation(L"BodyYggdrasilBody_Idle", true);
		if (_Changeon == true)
			at->PlayAnimation(L"BodyYggdrasilBody_Change", true);
	}


	void Yggdrasil_Body::attack_a_set()
	{
	}
	void Yggdrasil_Body::attack_a_ready()
	{
	}
	void Yggdrasil_Body::attack_a_right()
	{
	}
	void Yggdrasil_Body::attack_a_left()
	{
	}
	void Yggdrasil_Body::attack_a_loading()
	{
	}
	void Yggdrasil_Body::attack_a_finish()
	{
	}


	void Yggdrasil_Body::attack_b_set()
	{
	}
	void Yggdrasil_Body::attack_b_ready()
	{
	}
	void Yggdrasil_Body::attack_b_left()
	{
	}
	void Yggdrasil_Body::attack_b_right()
	{
	}
	void Yggdrasil_Body::attack_b_finish()
	{
	}


	void Yggdrasil_Body::attack_c_set()
	{
	}
	void Yggdrasil_Body::attack_c_ready()
	{
	}
	void Yggdrasil_Body::attack_c()
	{
	}
	void Yggdrasil_Body::attack_c_finish()
	{
	}


	void Yggdrasil_Body::groggy_start()
	{
		if (_groggy_body == false)		
			body_down();		
	}
	void Yggdrasil_Body::groggy_end()
	{
		if(_groggy_body==true)
			body_up();
	}

	void Yggdrasil_Body::intro_set_right()
	{
	}
	void Yggdrasil_Body::intro_set_left()
	{
	}
	void Yggdrasil_Body::intro_ready()
	{
		if (introbody_ordernumber == 0)
		{			
			_pos.y += 150 * Time::DeltaTime();
			if (_pos.y >= _savepos.y + 40)
				introbody_ordernumber = 1;
		}
		if (introbody_ordernumber == 1)
		{
			if (_pos.y > _savepos.y)
				_pos.y -= 150 * Time::DeltaTime();
			if (_pos.y <= _savepos.y)
			{
				_pos.y = _savepos.y;
				_Intro_Ready = true;
			}
		}
	}
	void Yggdrasil_Body::intro()
	{
	}
	void Yggdrasil_Body::intro_end()
	{
	}


	void Yggdrasil_Body::change_set()
	{
	}
	void Yggdrasil_Body::change_ready()
	{
	}
	void Yggdrasil_Body::change()
	{
		if (_Changeon == true)
		{
			at->PlayAnimation(L"BodyYggdrasilBody_Change", true);
			_Change_Body = true;
		}
	}
	void Yggdrasil_Body::change_end()
	{
	}


	void Yggdrasil_Body::die_set()
	{
	}
	void Yggdrasil_Body::die_ready()
	{
		if (_groggy_body == false)
			body_down();
	}
	void Yggdrasil_Body::die()
	{
	}



	void Yggdrasil_Body::body_down()
	{
		if (_Groggy_Body_Down == false)
		{
			if (_pos.y >= -100.f)
				_pos.y -= 25 * Time::DeltaTime();
			if (_BodyRotation.z < 35.f)
				_BodyRotation.z += 20 * Time::DeltaTime();
			tr->SetRotation(_BodyRotation);
			if ((_pos.y >= -100.f) && (_BodyRotation.z >= 35.f))
			{
				if (_Diecheck < 3)
				{
					_Groggy_Body_Down = true;
					_groggy_body = true;
				}
				if (_Diecheck == 3)
					_Die_Body_Down = true;
			}
		}
	}
	void Yggdrasil_Body::body_up()
	{
		if (_Groggy_Body_Up == false)
		{
			if (_pos.y < -20.f)
				_pos.y += 25 * Time::DeltaTime();
			if (_BodyRotation.z >= 0.f)
				_BodyRotation.z -= 20 * Time::DeltaTime();
			tr->SetRotation(_BodyRotation);
			if ((_pos.y >= -50.f) && (_BodyRotation.z <= 0.f))
			{
				_BodyRotation.z = 0.f;
				_pos.y = -20.f;
				_Groggy_Body_Up = true;
				_groggy_body = false;
			}
		}
	}

	void Yggdrasil_Body::move_up()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = _savepos.y - _pos.y - _maxdistance;
		_pos.y += _chinspeed * static_cast<float>(Time::DeltaTime());

		if (fDist <= -3.f)
			mDir *= -1;

		tr->SetPosition(_pos);
	}

	void Yggdrasil_Body::move_down()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = _savepos.y - _pos.y - _maxdistance;
		_pos.y -= _chinspeed * static_cast<float>(Time::DeltaTime());

		if (fDist >= 3.0f)
			mDir *= -1;

		tr->SetPosition(_pos);
	}



}
