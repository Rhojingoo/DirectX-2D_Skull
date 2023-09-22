#include "Yggdrasil_Body.h"


namespace jk
{
	bool Yggdrasil_Body::Attack_C_Boddy_Ready = false;
	bool Yggdrasil_Body::Boddy_BulletReady = false;
	

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
		_savepos = Vector3(0.f, -20.f, -199.f);
		tr->SetPosition(_pos);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Body\\YggdrasilBody_Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Body\\YggdrasilBody_Attack_C", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Body\\YggdrasilBody_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Body\\YggdrasilBody_Changing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Body\\YggdrasilBody_Die_Effect", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Body\\YggdrasilBody_Die", this);

		
		//bind ºÎºÐ
		//at->CompleteEvent(L"ArcherAttack_A") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_B") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);


		{
			_Dead_Effect = new Yggdrasil_BoddyDead_Effect();
			_Dead_Effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Dead_Effect);
			Transform* bullet_tr = _Dead_Effect->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			_Dead_Effect->SetState(eState::Paused);
		}
			

		at->PlayAnimation(L"BodyYggdrasilBody_Idle", true);
		if (_Changeon == true)
			at->PlayAnimation(L"BodyYggdrasilBody_Change", true);
		
		GameObject::Initialize();
	}


	void Yggdrasil_Body::Update()
	{
		SetPos(_pos);		

		if (_state == Yggdrasil_State::Attack_A_Ready)
			_pos.x = _savepos.x;

		if (_state == Yggdrasil_State::Attack_B_Ready)
		{		
		}
		if ((_state == Yggdrasil_State::Attack_C_Ready) || (_state == Yggdrasil_State::Attack_C))
		{
			_pos = _savepos;
		}

		if (_state == Yggdrasil_State::Idle)
		{
			if (_Turn_up == false)
			move_down();
			else
			move_up();		
		}

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

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_UP:
			Yggdrasil_Body::attack_c_up();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Down:
			Yggdrasil_Body::attack_c_down();
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

		case jk::Yggdrasil::Yggdrasil_State::Die_Waiting:
			Yggdrasil_Body::die_waiting();
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
		{
			_readytime += Time::DeltaTime();
			if (_readytime < 1.5)
				_pos.x = UpdateVibration(_pos.x, 3, 10.f * 3.14, _readytime);
			else
			{
				_pos.x = _savepos.x;
				Yggdrasil_Chin::_introchin = false;
				Yggdrasil_Chin::_introchinup = true;
				_readytime = 0;
				_AttackA_Boddy = true;
			}
		}
	}
	void Yggdrasil_Body::attack_a_right()
	{
		if (_pos.y > -45)
		{
			_pos.y -= 250 * Time::DeltaTime();
		}
		else
			_AttackA_Boddy = true;
	}
	void Yggdrasil_Body::attack_a_left()
	{
		if (_pos.y > -45)
		{
			_pos.y -= 250 * Time::DeltaTime();
		}
		else
			_AttackA_Boddy = true;
	}
	void Yggdrasil_Body::attack_a_loading()
	{
		if (_pos.y < -20)
		{
			_pos.y += 250 * Time::DeltaTime();
		}
		else
			_AttackA_Boddy = true;
	}
	void Yggdrasil_Body::attack_a_finish()
	{
	}


	void Yggdrasil_Body::attack_b_set()
	{
	}
	void Yggdrasil_Body::attack_b_ready()
	{
		if (_NumberofAttack >= 2)
		{
			{
				if (_BodyRotation.z > 0.f)
					_BodyRotation.z -= 20 * Time::DeltaTime();
				else
				{
					_BodyRotation.z = 0.f;
					_AttackB_FinishBoddy = true;
				}
			}
			{
				if (_BodyRotation.z < 0.f)
					_BodyRotation.z += 20 * Time::DeltaTime();
				else
				{
					_BodyRotation.z = 0.f;
					_AttackB_FinishBoddy = true;
				}
			}
			tr->SetRotation(_BodyRotation);
		}
		else
		{
			if (_AttackB_Boddy == false)
			{
				{
					if (_BodyRotation.z > 0.f)
						_BodyRotation.z -= 20 * Time::DeltaTime();
					else
					{
						_BodyRotation.z = 0.f;
						_AttackB_Boddy = true;
					}
				}
				{
					if (_BodyRotation.z < 0.f)
						_BodyRotation.z += 20 * Time::DeltaTime();
					else
					{
						_BodyRotation.z = 0.f;
						_AttackB_Boddy = true;
					}
				}
				tr->SetRotation(_BodyRotation);
			}
			else
			{
				if (_Attack_Dir == 1)
				{
					if (_pos.x < 50.f)
						_pos.x += 150 * Time::DeltaTime();
					else
						_AttackB_Ready_Boddy = true;
				}
				else
				{
					if (_pos.x > -50.f)
						_pos.x -= 150 * Time::DeltaTime();
					else
						_AttackB_Ready_Boddy = true;
				}
			}
			tr->SetPosition(_pos);
		}
	}
	void Yggdrasil_Body::attack_b_left()
	{	
		if (_BodyRotation.z > -20.f)
			_BodyRotation.z -= 20 * Time::DeltaTime();
		if (_pos.x < 0.f)
			_pos.x += 80 * Time::DeltaTime();
		
		tr->SetPosition(_pos);
		tr->SetRotation(_BodyRotation);
		
	}
	void Yggdrasil_Body::attack_b_right()
	{
		if (_BodyRotation.z < 20.f)
			_BodyRotation.z += 20 * Time::DeltaTime();
		if (_pos.x > 0.f)
			_pos.x -= 80 * Time::DeltaTime();
				
		tr->SetPosition(_pos);
		tr->SetRotation(_BodyRotation);
	}
	void Yggdrasil_Body::attack_b_finish()
	{
	}


	void Yggdrasil_Body::attack_c_set()
	{
		if (_pos.y > -35)
			_pos.y -= 250 * Time::DeltaTime();
		else if (_pos.y < -36)
			_pos.y += 250 * Time::DeltaTime();
		else if (_pos.y >= -36 && _pos.y <= -35)
		{
			_pos.y = -35;
			_SetattackC_boddy = true;
		}
	}
	void Yggdrasil_Body::attack_c_ready()
	{
		Attack_C_Boddy_Ready = true;
	}
	void Yggdrasil_Body::attack_c_up()
	{
		if (_pos.y <= 10.f)
			_pos.y += 250 * Time::DeltaTime();
		else
			Boddy_BulletReady = true;
	}
	void Yggdrasil_Body::attack_c_down()
	{
		if (_pos.y > -30)
		{
			_pos.y -= 250 * Time::DeltaTime();
		}
		else
			_AttackC_Boddy = true;
	}
	void Yggdrasil_Body::attack_c()
	{
	}
	void Yggdrasil_Body::attack_c_finish()
	{
		Attack_C_Boddy_Ready = false;
		Boddy_BulletReady = false;
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
		if (_SetChange_boddy == false)
		{
			_pos.x = 0.f;
			_pos.y = -20.f;
			if (_BodyRotation.z >= 0.f)
				_BodyRotation.z = 0.f;
			if (_BodyRotation.z <= 0.f)						
				_BodyRotation.z = 0.f;			
			
			tr->SetRotation(_BodyRotation);
			tr->SetPosition(_pos);
			_SetChange_boddy = true;
		}
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
		_pos.x = 0.f;
		_pos.y = -20.f;
		if (_BodyRotation.z >= 0.f)
			_BodyRotation.z = 0.f;
		if (_BodyRotation.z <= 0.f)
			_BodyRotation.z = 0.f;

		tr->SetRotation(_BodyRotation);
		tr->SetPosition(_pos);

		Transform* Effect_tr = _Dead_Effect->GetComponent<Transform>();
		Effect_tr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
		_Dead_Effect->SetState(eState::Active);
		_Die_SetBoddy = true;
	}
	void Yggdrasil_Body::die_waiting()
	{
		at->PlayAnimation(L"BodyYggdrasilBody_Die", false);
		_Dead_Effect->SetState(eState::Paused);
		_Die_Waiting_Boddy = true;
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
				_BodyRotation.z += 20.f* Time::DeltaTime();
			tr->SetRotation(_BodyRotation);
			if ((_pos.y >= -100.f) && (_BodyRotation.z >= 35.f))
			{
				if (_Diecheck < 3)
				{
					_Groggy_Body_Down = true;
					_groggy_body = true;
				}
				if (_DieON == true)
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

		if (_Turn_up == true)
		{
			fDist = _savepos.y - _pos.y - _maxdistance;
			_pos.y += _chinspeed * static_cast<float>(Time::DeltaTime());

			if (fDist <= -10.f)
				_Turn_up = false;					
		}
	

		tr->SetPosition(_pos);
	}
	void Yggdrasil_Body::move_down()
	{
		Transform* tr = GetComponent<Transform>();
		if (_Turn_up == false)
		{
			fDist = _savepos.y - _pos.y - _maxdistance;
			_pos.y -= _chinspeed * static_cast<float>(Time::DeltaTime());
			if (fDist >= 10.f)				
				_Turn_up = true;
		}


		tr->SetPosition(_pos);
	}

	float Yggdrasil_Body::UpdateVibration(float originalX, float amplitude, float frequency, float timeElapsed)
	{
		return originalX + amplitude * std::sin(frequency * timeElapsed);
	}

}
