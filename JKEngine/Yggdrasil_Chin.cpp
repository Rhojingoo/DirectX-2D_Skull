#include "Yggdrasil_Chin.h"
#include "Include_Common.h"
#include "Yggdrasil_ChinDead_Effect.h"

namespace jk
{
	//int Yggdrasil_Chin:: _Dir = 1;		
	bool Yggdrasil_Chin::_introchin = false;
	bool Yggdrasil_Chin::_introchinup = false;

	Yggdrasil_Chin::Yggdrasil_Chin()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Yggdrasil_Chin::~Yggdrasil_Chin()
	{
	}

	void Yggdrasil_Chin::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		//턱관리 포지션
		//_pos.y = YggdrasilFace_pos.y - 55.f;	// 에너지볼 공격전 기모을때
		//_pos.y = YggdrasilFace_pos.y - 65.f;	// 보통상태의 입다물기
		//_pos.y = YggdrasilFace_pos.y - 75.f;	// 보통상태의 입벌리기
		//_pos.y = YggdrasilFace_pos.y - 80.f;	// 공격시 입벌리기
		//_pos.y = YggdrasilFace_pos.y - 95.f;	// 인트로 및 변신 및 그로기단계
		Yggdrasil_pos = Yggdrasil::GetPos();
		YggdrasilFace_pos = Yggdrasil_Face::FaceGetpos();
		_pos.x = YggdrasilFace_pos.x + 12.5f;
		_pos.y = YggdrasilFace_pos.y - 65.f;
		_pos.z = -198.f;
		mCenterpos = _pos;
		tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(_pos));



		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Chind\\YggdrasilChin_Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Chind\\YggdrasilChin_Attac_C", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Chind\\YggdrasilChin_Change", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Chind\\YggdrasilChin_Change_Die_Effect", this);
		
		//bind 부분
		//at->CompleteEvent(L"ArcherAttack_A") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_B") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);

		
		{
			_Dead_Effect = new Yggdrasil_ChinDead_Effect;
			_Dead_Effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Dead_Effect);
			Transform* bullet_tr = _Dead_Effect->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			_Dead_Effect->SetState(eState::Paused);
		}


		at->PlayAnimation(L"ChindYggdrasilChin_Idle", true);		
		if (_Changeon == true)
			at->PlayAnimation(L"ChindYggdrasilChin_Change", true);

		GameObject::Initialize();
	}
	void Yggdrasil_Chin::Update()
	{
		Yggdrasil_pos = Yggdrasil::GetPos();
		YggdrasilFace_pos = Yggdrasil_Face::FaceGetpos();
		Yggdrasil_rotation = GetRotations();
		Intro_chinplay();

		if (_state == Yggdrasil_State::Attack_C_Ready)
		{
			YggdrasilFace_pos = Yggdrasil_Face::FaceGetpos();
			_pos.x = YggdrasilFace_pos.x + 12.5f;
		}


		if (_state != Yggdrasil_State::Intro_End && _state != Yggdrasil_State::Intro && _state != Yggdrasil_State::Attack_C && _state != Yggdrasil_State::Attack_C_Ready 
			&& _state != Yggdrasil_State::Attack_C_UP && _state != Yggdrasil_State::Attack_C_Down && _state != Yggdrasil_State::Attack_C_Finish 
			&& _state != Yggdrasil_State::Change && _state != Yggdrasil_State::Change_End && _state != Yggdrasil_State::DieSet &&_state != Yggdrasil_State::DieReady 
			&& _state != Yggdrasil_State::Die &&_state != Yggdrasil_State::Die_Waiting)
		{
			if (_state == Yggdrasil_State::Groggy_Start || _state == Yggdrasil_State::Groggy_End || _state == Yggdrasil_State::Die ||_state == Yggdrasil_State::DieReady|| _state == Yggdrasil_State::DieSet)
			{
				_pos.y = YggdrasilFace_pos.y - 65.f;
			}
			else if (_state == Yggdrasil_State::Attack_A_Ready || _state == Yggdrasil_State::Attack_A_Left || _state == Yggdrasil_State::Attack_A_Right|| _state == Yggdrasil_State::Attack_A_Loading)
			{
				
			}
			else if ((_state == Yggdrasil_State::Attack_B_Ready) || (_state == Yggdrasil_State::Attack_B_Left) || (_state == Yggdrasil_State::Attack_B_Right))
			{
			}				

			else
			{
				if (_Groggy_Finish == true)
				{
					_Groggy_Finish = false;
					_pos.y = YggdrasilFace_pos.y - 65.f;
					mDir = 1;
				}
				else
				{
					if (mDir == 1)
						Lmove_down();
					else
						Lmove_up();
				}
			}
		}


		switch (_state)
		{
		case jk::Yggdrasil::Yggdrasil_State::Idle:
			Yggdrasil_Chin::idle();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Set:
			Yggdrasil_Chin::attack_a_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Ready:
			Yggdrasil_Chin::attack_a_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Right:
			Yggdrasil_Chin::attack_a_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Loading:
			Yggdrasil_Chin::attack_a_loading();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Finish:
			Yggdrasil_Chin::attack_a_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Set:
			Yggdrasil_Chin::attack_b_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Ready:
			Yggdrasil_Chin::attack_b_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Right:
			Yggdrasil_Chin::attack_b_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Left:
			Yggdrasil_Chin::attack_b_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Finish:
			Yggdrasil_Chin::attack_b_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Set:
			Yggdrasil_Chin::attack_c_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Ready:
			Yggdrasil_Chin::attack_c_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_UP:
			Yggdrasil_Chin::attack_c_up();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C:
			Yggdrasil_Chin::attack_c();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Down:
			Yggdrasil_Chin::attack_c_down();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Finish:
			Yggdrasil_Chin::attack_c_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Groggy_Start:
			Yggdrasil_Chin::groggy_start();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Groggy_End:
			Yggdrasil_Chin::groggy_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_Set_Right:
			Yggdrasil_Chin::intro_set_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_Set_Left:
			Yggdrasil_Chin::intro_set_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_Ready:
			Yggdrasil_Chin::intro_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro:
			Yggdrasil_Chin::intro();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_End:
			Yggdrasil_Chin::intro_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change_Set:
			Yggdrasil_Chin::change_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change_Ready:
			Yggdrasil_Chin::change_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change:
			Yggdrasil_Chin::change();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change_End:
			Yggdrasil_Chin::change_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::DieSet:
			Yggdrasil_Chin::die_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Die_Waiting:
			Yggdrasil_Chin::die_waiting();
			break;

		case jk::Yggdrasil::Yggdrasil_State::DieReady:
			Yggdrasil_Chin::die_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Die:
			Yggdrasil_Chin::die();
			break;

		default:
			break;
		}	
		tr->SetPosition(_pos);
		tr->SetRotation(Yggdrasil_rotation);
		GameObject::Update();
	}
	void Yggdrasil_Chin::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));

		GameObject::LateUpdate();
	}
	void Yggdrasil_Chin::Render()
	{
		GameObject::Render();
	}


	void Yggdrasil_Chin::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_Chin::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_Chin::OnCollisionExit(Collider2D* other)
	{
	}


	void Yggdrasil_Chin::idle()
	{
		at->PlayAnimation(L"ChindYggdrasilChin_Idle", true);
		if (_Changeon == true)
			at->PlayAnimation(L"ChindYggdrasilChin_Change", true);
	}	

	void Yggdrasil_Chin::attack_a_set()
	{
	}
	void Yggdrasil_Chin::attack_a_ready()
	{
		if (_Chin_Attack_Ready == false)
		{
			if (_pos.y < YggdrasilFace_pos.y - 55.f)			
				_pos.y += 50.f * static_cast<float>(Time::DeltaTime());
			else
			{
				if (_pos.y >= YggdrasilFace_pos.y - 55.f)
				{
					_pos.y = YggdrasilFace_pos.y - 55.f;
					_Chin_Attack_Ready = true;
				}
			}			
		}
		else
		{
			if (_pos.y > YggdrasilFace_pos.y - 80.f)			
				_pos.y -= 50.f * static_cast<float>(Time::DeltaTime());
			else
			{
				_pos.y = YggdrasilFace_pos.y - 80.f;
				_AttackA_Chin = true;
			}					
		}		
	}
	void Yggdrasil_Chin::attack_a_right()
	{
	}
	void Yggdrasil_Chin::attack_a_left()
	{
	}
	void Yggdrasil_Chin::attack_a_loading()
	{
		_Chin_Attack_Ready = false;
	}
	void Yggdrasil_Chin::attack_a_finish()
	{
	}


	void Yggdrasil_Chin::attack_b_set()
	{
	}
	void Yggdrasil_Chin::attack_b_ready()
	{
		if(_pos.x > (YggdrasilFace_pos.x + 12.5f))
			_pos.x -=  150.f* static_cast<float>(Time::DeltaTime());
		else if(_pos.x < (YggdrasilFace_pos.x + 12.5f))
			_pos.x += 150.f * static_cast<float>(Time::DeltaTime());
	

		if (_pos.y < (YggdrasilFace_pos.y - 60.f))
			_pos.y += 50.f * static_cast<float>(Time::DeltaTime());
	}
	void Yggdrasil_Chin::attack_b_left()
	{
		if (_pos.x > (YggdrasilFace_pos.x -5.5f))
			_pos.x -= 150.f * static_cast<float>(Time::DeltaTime());
		else if (_pos.x < (YggdrasilFace_pos.x - 5.5f))
			_pos.x += 150.f * static_cast<float>(Time::DeltaTime());

		if (_pos.y > (YggdrasilFace_pos.y - 80.f))
			_pos.y -= 150.f * static_cast<float>(Time::DeltaTime());
	}
	void Yggdrasil_Chin::attack_b_right()
	{
		if (_pos.x < (YggdrasilFace_pos.x + 35.5f))
			_pos.x += 150.f * static_cast<float>(Time::DeltaTime());
		else if (_pos.x > (YggdrasilFace_pos.x + 35.5f))
			_pos.x -= 150.f * static_cast<float>(Time::DeltaTime());

		if (_pos.y > (YggdrasilFace_pos.y - 80.f))
			_pos.y -= 150.f * static_cast<float>(Time::DeltaTime());
	}
	void Yggdrasil_Chin::attack_b_finish()
	{
	}


	void Yggdrasil_Chin::attack_c_set()
	{
		_pos.y = YggdrasilFace_pos.y - 65.f;
	}
	void Yggdrasil_Chin::attack_c_ready()
	{		
		_pos.y = YggdrasilFace_pos.y - 65.f;
	}
	void Yggdrasil_Chin::attack_c_up()
	{
		if(_pos.y<-15)
			_pos.y = YggdrasilFace_pos.y - 65.f;
	}
	void Yggdrasil_Chin::attack_c()
	{
	}
	void Yggdrasil_Chin::attack_c_down()
	{
	}
	void Yggdrasil_Chin::attack_c_finish()
	{
		_pos.y = YggdrasilFace_pos.y - 65.f;
	}


	void Yggdrasil_Chin::groggy_start()
	{
		groggy_down();
	}
	void Yggdrasil_Chin::groggy_end()
	{
		groggy_up();
	}		


	void Yggdrasil_Chin::intro_set_right()
	{
	}
	void Yggdrasil_Chin::intro_set_left()
	{
	}
	void Yggdrasil_Chin::intro_ready()
	{	
	}
	void Yggdrasil_Chin::intro()
	{		
		if (_Intro_Ready == true)
		{
			_introchin = true;
			_pos.y -= 80.f * static_cast<float>(Time::DeltaTime());
			if (YggdrasilFace_pos.y - 95 >= _pos.y)
			{
				_pos.y = YggdrasilFace_pos.y - 95;
				_Intro_Ready = false;
			}
		}
		else
			_pos.x = YggdrasilFace_pos.x + 12.5f;
	}
	void Yggdrasil_Chin::intro_end()
	{
	}


	void Yggdrasil_Chin::change_set()
	{
		if (_SetChange_chin == false)
		{
			_pos.x = 12.5f;
			_pos.y = -65.f;
			_SetChange_chin = true;
		}
	}
	void Yggdrasil_Chin::change_ready()
	{
	}
	void Yggdrasil_Chin::change()
	{
		if (_Changeon == false)
		{
			if (_Change_HandL == true && _Change_HandR == true)
			{
				_pos.y -= 80.f * static_cast<float>(Time::DeltaTime());
				if (YggdrasilFace_pos.y - 95 >= _pos.y)
				{
					_pos.y = YggdrasilFace_pos.y - 95;
					_Change_HandL = false;
					_Change_HandR = false;
				}
			}
			else
				_pos.x = YggdrasilFace_pos.x + 12.5f;
		}
		if (_Changeon == true)
		{
			at->PlayAnimation(L"ChindYggdrasilChin_Change", false);
			_Change_Chin = true;	
		}
	}
	void Yggdrasil_Chin::change_end()
	{
		if (_Change_Finish == false)
		{
			change_chinplay_end();
		}		
	}


	void Yggdrasil_Chin::die_set()
	{
		_pos.x = YggdrasilFace_pos.x + 12.5f;
		_pos.y = YggdrasilFace_pos.y - 65.f;
		Transform* bullet_tr = _Dead_Effect->GetComponent<Transform>();
		bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
		_Dead_Effect->SetState(eState::Active);
		_Die_SetChin = true;
	}
	void Yggdrasil_Chin::die_waiting()
	{
		at->PlayAnimation(L"ChindYggdrasilChin_Idle", false);
		_Dead_Effect->SetState(eState::Paused);
		_Die_Waiting_Chin = true;
	}
	void Yggdrasil_Chin::die_ready()
	{
		Die_Down();			
	}
	void Yggdrasil_Chin::die()
	{
	}


	void Yggdrasil_Chin::Lmove_up()
	{
		Transform* tr = GetComponent<Transform>();

		_pos.x = YggdrasilFace_pos.x + 12.5f;
		fDist = (YggdrasilFace_pos.y - 50.f) - _pos.y - _maxdistance;
		_pos.y += _chinspeed * static_cast<float>(Time::DeltaTime());

		if (fDist <= -5.f)
			mDir *= -1;

		tr->SetPosition(_pos);
	}
	void Yggdrasil_Chin::Lmove_down()
	{
			Transform* tr = GetComponent<Transform>();

			_pos.x = YggdrasilFace_pos.x + 12.5f;
			fDist = (YggdrasilFace_pos.y-50.f) - _pos.y - _maxdistance;
			_pos.y -= _chinspeed * static_cast<float>(Time::DeltaTime());

			if (fDist >= 5.0f)
				mDir *= -1;

			tr->SetPosition(_pos);
	}

	void Yggdrasil_Chin::Intro_chinplay()
	{
		if (_Intro == false)
		{
			if (_introchin == false)
			{
				YggdrasilFace_pos = Yggdrasil_Face::FaceGetpos();
				_pos.x = YggdrasilFace_pos.x + 12.5f;
				_pos.z = -199.5f;

				if (_introchinup == true)
				{
					_pos.z = -203.f;
					if (_pos.y < YggdrasilFace_pos.y - 65.f)
					{
						_pos.y += 80.f * static_cast<float>(Time::DeltaTime());
						if (_pos.y >= YggdrasilFace_pos.y - 65.f)
						{
							_pos.y = YggdrasilFace_pos.y - 65.f;
							_Intro_StartCHIN = true;
						}			
					}
				}
				else
					_pos.y = YggdrasilFace_pos.y - 65.f;
			}
		}
	}
	void Yggdrasil_Chin::change_chinplay()
	{
		if (_Change_Finish == false)
		{
			if (_introchin == false)
			{
				YggdrasilFace_pos = Yggdrasil_Face::FaceGetpos();
				_pos.x = YggdrasilFace_pos.x + 12.5f;
				_pos.z = -199.5f;

				if (_introchinup == true)
				{
					_pos.z = -203.f;
					if (_pos.y < YggdrasilFace_pos.y - 65.f)
					{
						_pos.y += 80.f * static_cast<float>(Time::DeltaTime());
						if (_pos.y >= YggdrasilFace_pos.y - 65.f)
						{
							_pos.y = YggdrasilFace_pos.y - 65.f;
							_Intro_StartCHIN = true;
						}
					}
				}
				else
					_pos.y = YggdrasilFace_pos.y - 65.f;
			}
		}
	}
	void Yggdrasil_Chin::change_chinplay_end()
	{
		if (_pos.y < YggdrasilFace_pos.y - 65.f)
		{
			_pos.y += 80.f * static_cast<float>(Time::DeltaTime());
			if (_pos.y >= YggdrasilFace_pos.y - 65.f)
			{
				_pos.y = YggdrasilFace_pos.y - 65.f;
				_Change_Finish = true;
			}
		}	
	}

	void Yggdrasil_Chin::groggy_down()
	{
		if (_Groggy_Chin_Down == false)
		{
			if (_pos.y >= -150.f)
				_pos.y -= 40.f * static_cast<float>(Time::DeltaTime());
			if (_pos.x >= 7.f)
				_pos.x -= 7.f * static_cast<float>(Time::DeltaTime());
			if ((_pos.y < -150.f) && (_pos.x < 7.f))
				_Groggy_Chin_Down = true;			
		}
	}
	void Yggdrasil_Chin::groggy_up()
	{
		if (_Groggy_Chin_Up == false)
		{
			if (_pos.y <= -65.f)
				_pos.y += 40.f * static_cast<float>(Time::DeltaTime());
			if (_pos.x <= 12.5f)
				_pos.x += 7.f * static_cast<float>(Time::DeltaTime());
			if ((_pos.y >= -65.f) && (_pos.x >= 12.5f))
			{
				_pos.x = 12.5f;
				_pos.y = -65.f;
				_Groggy_Chin_Up = true;
				_Groggy_Finish = true;
			}
		}
	}

	void Yggdrasil_Chin::Die_Down()
	{
		if (_Die_Chin_Down == false)
		{
			if (_pos.y >= -150.f)
				_pos.y -= 40.f * static_cast<float>(Time::DeltaTime());
			if (_pos.x >= 7.f)
				_pos.x -= 7.f * static_cast<float>(Time::DeltaTime());
			if ((_pos.y < -150.f) && (_pos.x < 7.f))
				_Die_Chin_Down = true;
		}
	}

}
