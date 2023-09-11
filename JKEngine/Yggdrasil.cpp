#include "Yggdrasil.h"
#include <iostream>
#include <random>

namespace jk
{
	Yggdrasil::Yggdrasil_State Yggdrasil::_state = Yggdrasil_State();
	Vector3 Yggdrasil::_playerpos = Vector3(0.f, 0.f, 0.f);
	Vector3 Yggdrasil::_pos = Vector3(0.f, 0.f, 0.f);
	Vector3 Yggdrasil::_Rotation = Vector3(0.f, 0.f, 0.f);
	float Yggdrasil::_time = 0.f;
	int	Yggdrasil::mDir = 1;
	int	Yggdrasil::_Attack_Dir = 1;
	

	int Yggdrasil::_Diecheck = 0;  //Diecheck = 1일때 Change = true, Diecheck = 2일때 Change = false, Diecheck = 3일때 _DieON = true -> change상태임
	bool Yggdrasil::_DieON = false;
	


	bool Yggdrasil::_Intro = false;
	bool Yggdrasil::_Intro_SetR = false;
	bool Yggdrasil::_Intro_SetL = false;
	bool Yggdrasil::_Intro_Ready = false;
	bool Yggdrasil::_Intro_StartCHIN = false;
	bool Yggdrasil::_Intro_StartR = false;
	bool Yggdrasil::_Intro_StartL = false;
	bool Yggdrasil::_Intro_EndR = false;
	bool Yggdrasil::_Intro_EndL = false;


	bool Yggdrasil::_SetattackA_r = false;
	bool Yggdrasil::_SetattackA_l = false;
	bool Yggdrasil::_AttackA_Readyr = false;
	bool Yggdrasil::_AttackA_Readyl = false;
	bool Yggdrasil::_AttackA_Boddy = false;
	bool Yggdrasil::_AttackA_Chin = false;

	bool Yggdrasil::_AttackA_LoadingR = false;
	bool Yggdrasil::_AttackA_LoadingL = false;
	bool Yggdrasil::_AttackA_FinishR = false;
	bool Yggdrasil::_AttackA_FinishL = false;
	

	bool Yggdrasil::_SetattackB_r = false;
	bool Yggdrasil::_SetattackB_l = false;
	bool Yggdrasil::_AttackB_Ready_Boddy = false;	
	bool Yggdrasil::_AttackB_Readyr = false;
	bool Yggdrasil::_AttackB_Readyl = false;
	bool Yggdrasil::_AttackB_Boddy = false;
	bool Yggdrasil::_AttackB_Finishr = false;
	bool Yggdrasil::_AttackB_Finishl = false;
	bool Yggdrasil::_AttackB_FinishBoddy = false;



	bool Yggdrasil::_SetattackC_r = false;
	bool Yggdrasil::_SetattackC_l = false;
	bool Yggdrasil::_SetattackC_face = false;
	bool Yggdrasil::_SetattackC_chin = false;
	bool Yggdrasil::_SetattackC_boddy = false;
	bool Yggdrasil::_AttackC_Readyr = false;
	bool Yggdrasil::_AttackC_Readyl = false;
	bool Yggdrasil::_AttackC_Face = false;
	bool Yggdrasil::_AttackC_Boddy = false;		
	bool Yggdrasil::_AttackC_Finish = false;

	int Yggdrasil::_NumberofAttack = 0;


	bool Yggdrasil::_SetattackD_r = false;
	bool Yggdrasil::_SetattackD_l = false;
	bool Yggdrasil::_AttackD_Readyr = false;
	bool Yggdrasil::_AttackD_Readyl = false;
	bool Yggdrasil:: _AttackD_Loadingr = false;
	bool Yggdrasil:: _AttackD_Loadingl = false;
	bool Yggdrasil::_AttackD_Finishr = false;
	bool Yggdrasil::_AttackD_Finishl = false;


	bool  Yggdrasil::_Change = false;
	bool  Yggdrasil::_SetChange_r = false;
	bool  Yggdrasil::_SetChange_l = false;
	bool  Yggdrasil::_Change_Readyr = false;
	bool  Yggdrasil::_Change_Readyl = false;


	bool  Yggdrasil::_Change_Chin = false;
	bool  Yggdrasil::_Change_Face = false;
	bool  Yggdrasil::_Change_Body = false;
	bool  Yggdrasil::_Change_HandR = false;
	bool  Yggdrasil::_Change_HandL = false;	
	bool  Yggdrasil::_Changeon = false;


	bool  Yggdrasil::_Change_FinishR = false; 
	bool  Yggdrasil::_Change_FinishL = false;
	bool  Yggdrasil::_Change_Finish = false;


	bool Yggdrasil::_Groggy_Bulletready = false;
	bool Yggdrasil::_Groggy_Body_Down = false;
	bool Yggdrasil::_Groggy_Face_Down = false;
	bool Yggdrasil::_Groggy_Chin_Down = false;
	bool Yggdrasil::_Groggy_Body_Up = false;
	bool Yggdrasil::_Groggy_Face_Up = false;
	bool Yggdrasil::_Groggy_Chin_Up = false;
	bool Yggdrasil::_Groggy_RightHand_Up = false;
	bool Yggdrasil::_Groggy_LeftHand_Up = false;


	bool Yggdrasil::_Die_SetR = false;
	bool Yggdrasil::_Die_SetL = false;
	bool Yggdrasil::_Die_READY_R = false;
	bool Yggdrasil::_Die_READY_L = false;
	bool Yggdrasil::_Die_Body_Down = false;
	bool Yggdrasil::_Die_Face_Down = false;
	bool Yggdrasil::_Die_Chin_Down = false;


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
	
		//_Change = true;
		GameObject::Initialize();
	}
	void Yggdrasil::Update()
	{
		_playerpos = Player::GetPlayer_Pos();
		_Playerdistance.x = _playerpos.x - _pos.x;
		if (_Playerdistance.x >= 0.f)
			mDir = 1;
		else
			mDir = -1;	


		// 체인지 상태의 변환을 관리하며, 이미지의 변화를주는 변수->_Changeon
		if (_Changeon == true)
		{
			_Change = false;
			//_Diecheck = 2;
		}
		//Diecheck = 1일때 Change = true, Diecheck = 2일때 Change = false, Diecheck = 3일때 _DieON = true -> change상태임
		if (_Diecheck == 1)
			_Change = true;
		if (_Diecheck == 2)
			_Change = false;
		if (_Diecheck == 3)
			_DieON = true;


		switch (_state)
		{
		case jk::Yggdrasil::Yggdrasil_State::Idle:
			idle();
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

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Set:
			attack_c_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Ready:
			attack_c_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_UP:
			attack_c_up();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C:
			attack_c();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Down:
			attack_c_down();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Finish:
			attack_c_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Groggy_Start:
			groggy_start();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Groggy_End:
			groggy_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_D_Set:
			attack_d_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_D_Ready:
			attack_d_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_D:
			attack_d();
			break; 

		case jk::Yggdrasil::Yggdrasil_State::Attack_D_Loading:
			attack_d_loading();
			break; 

		case jk::Yggdrasil::Yggdrasil_State::Attack_D_Finish:
			attack_d_finish();
			break;	

		case jk::Yggdrasil::Yggdrasil_State::Intro_Set_Right:
			intro_set_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_Set_Left:
			intro_set_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_Ready:
			intro_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro:
			intro();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_End:
			intro_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change_Set:
			change_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change_Ready:
			change_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change:
			change();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change_End:
			change_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::DieSet:
			die_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::DieReady:
			die_ready();
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
		_NumberofAttack = 0;
		_playerpos = Player::GetPlayer_Pos();

		if (_Changeon == false)
			Attack_Sellect = random(0, 2);
		else
			Attack_Sellect = random(0, 3);
		

		if (_Intro == false)
		{
			_state = Yggdrasil_State::Intro_Set_Left;
		}
		if (_Intro == true)
		{				
			if (test == 0) //시험용
				{
					Attack_Sellect = 1;
					//test = 1;
				}
			_AttackA_FinishR = false;
			_AttackA_FinishL = false;
			_Groggy_Chin_Up = false;
			_Groggy_Body_Up = false;
			_Groggy_Face_Up = false;
			_Groggy_RightHand_Up = false;
			_Groggy_LeftHand_Up = false;

			if (_Change == true)
			{
				Yggdrasil_Hand_Right::_Attackswitch = true;
				Yggdrasil_Hand_Left::_Attackswitch = true;
				_state = Yggdrasil_State::Change_Set;
			}

			if (_DieON == true)
			{
				Yggdrasil_Hand_Right::_Attackswitch = true;
				Yggdrasil_Hand_Left::_Attackswitch = true;
				_state = Yggdrasil_State::DieSet;
			}
	
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

				if (Attack_Sellect == 2)
				{
					Yggdrasil_Hand_Right::_Attackswitch = false;
					Yggdrasil_Hand_Left::_Attackswitch = false;
					_state = Yggdrasil_State::Attack_C_Set;
				}

				if (Attack_Sellect == 3)
				{
					Yggdrasil_Hand_Right::_Attackswitch = true;
					Yggdrasil_Hand_Left::_Attackswitch = true;
					_state = Yggdrasil_State::Attack_D_Set;
				}
			}			
		}
	}


	void Yggdrasil::attack_a_set()
	{
		if (_SetattackA_r == true && _SetattackA_l == true)
			_state = Yggdrasil_State::Attack_A_Ready;
	}
	void Yggdrasil::attack_a_ready()
	{
		if (_AttackA_Readyr == true && _AttackA_Readyr == true && _AttackA_Boddy == true && _AttackA_Chin ==true)
		{
			if (mDir == 1)
			{
				_state = Yggdrasil_State::Attack_A_Right;
				Yggdrasil_Hand_Right::_Attackswitch = true;
				_AttackA_Boddy = false;
				_AttackA_Chin = false;
			}
			else
			{
				_state = Yggdrasil_State::Attack_A_Left;
				Yggdrasil_Hand_Left::_Attackswitch = true;
				_AttackA_Boddy = false;
				_AttackA_Chin = false;
			}
		}
	}
	void Yggdrasil::attack_a_right()
	{
		if (Yggdrasil_Hand_Right::_Attackswitch == true && _AttackA_Boddy == true)
		{
			_attackatime += Time::DeltaTime();
			if (_attackatime > 2.5f)
			{
				_state = Yggdrasil_State::Attack_A_Loading;
				_attackatime = 0.f;
				_AttackA_Boddy = false;
			}			
		}
	}
	void Yggdrasil::attack_a_left()
	{
		if (Yggdrasil_Hand_Left::_Attackswitch == true && _AttackA_Boddy == true)
		{			
			_attackatime += Time::DeltaTime();
			if (_attackatime > 2.5f)
			{
				_state = Yggdrasil_State::Attack_A_Loading;
				_attackatime = 0.f;
				_AttackA_Boddy = false;
			}
		}
	}
	void Yggdrasil::attack_a_loading()
	{
		if (_AttackA_LoadingL == true && _AttackA_LoadingR == true && _AttackA_Boddy == true)
			_state = Yggdrasil_State::Attack_A_Finish;	
	}
	void Yggdrasil::attack_a_finish()
	{
		Yggdrasil_Hand_Right::_Attackswitch = false;
		Yggdrasil_Hand_Left::_Attackswitch = false;
		_SetattackA_r = false;
		_SetattackA_l = false;
		_AttackA_Readyr = false;
		_AttackA_Readyl = false;
		_AttackA_LoadingL = false;
		_AttackA_LoadingR = false;
		_AttackA_Boddy = false;

		if (_AttackA_FinishR == true && _AttackA_FinishL == true)
		{
			_state = Yggdrasil_State::Idle;
			Yggdrasil::_time = 0.f;
			_NumberofAttack = 0;
		}
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
			if (_AttackB_FinishBoddy == true)
			{
				_state = Yggdrasil_State::Attack_B_Finish;
				Yggdrasil_Hand_Right::_Attackswitch = false;
				Yggdrasil_Hand_Left::_Attackswitch = false;
				_SetattackB_r = false;
				_SetattackB_l = false;
				_AttackB_Readyr = false;
				_AttackB_Readyl = false;
			}
		}
		else
		{
			if ((_AttackB_Readyr == true) && (_AttackB_Readyl == true))
			{
				if (mDir == 1)
				{
					_Attack_Dir = 1;
					if (_AttackB_Ready_Boddy == true)
					{
						_state = Yggdrasil_State::Attack_B_Right;
						Yggdrasil_Hand_Right::_Attackswitch = true;
						_AttackB_Ready_Boddy = false;
					}
				}
				else
				{
					_Attack_Dir = -1;
					if (_AttackB_Ready_Boddy == true)
					{
						_state = Yggdrasil_State::Attack_B_Left;
						Yggdrasil_Hand_Left::_Attackswitch = true;
						_AttackB_Ready_Boddy = false;
					}
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
		if (_AttackB_Finishr == true && _AttackB_Finishl == true && _AttackB_FinishBoddy == true)
		{
			_state = Yggdrasil_State::Idle;
			Yggdrasil::_NumberofAttack = 0;
			_time = 0;
		}
	}


	void Yggdrasil::attack_c_set()
	{
		if ((_SetattackC_r == true) && (_SetattackC_l == true)&&(_SetattackC_face == true)&&(_SetattackC_chin ==true)&& _SetattackC_boddy == true)
			_state = Yggdrasil_State::Attack_C_Ready;		
	}
	void Yggdrasil::attack_c_ready()
	{
		if ((Yggdrasil_Face::_Firstbullet == true) && (Yggdrasil_Body::Attack_C_Boddy_Ready == true))
			_state = Yggdrasil_State::Attack_C_UP;
	}
	void Yggdrasil::attack_c_up()
	{
		if ((Yggdrasil_Face::_BulletReady == true) && (Yggdrasil_Body::Boddy_BulletReady == true))
			_state = Yggdrasil_State::Attack_C;
	}
	void Yggdrasil::attack_c()
	{
	}
	void Yggdrasil::attack_c_down()
	{
		if (_NumberofAttack >= 2) 
		{
			if (_Groggy_Bulletready == true)
			{
				_state = Yggdrasil_State::Attack_C_Finish;
				_NumberofAttack = 0;
				_Groggy_Bulletready = false;
			}
		}
		else
		{
			if ((_AttackC_Face == true) && (_AttackC_Boddy == true))
			{
				_state = Yggdrasil_State::Attack_C_Ready;
				_AttackC_Face = false;
				_AttackC_Boddy = false;
				_NumberofAttack++;
			}
		}
	}
	void Yggdrasil::attack_c_finish()
	{
	}


	void Yggdrasil::groggy_start()
	{
		if ((_Groggy_Chin_Down == true) && (_Groggy_Body_Down == true) && (_Groggy_Face_Down == true))
		{
			_attackatime += Time::DeltaTime();
			if (_attackatime > 3)
			{
				_state = Yggdrasil_State::Groggy_End;
				_attackatime = 0;
			}
		}
	}
	void Yggdrasil::groggy_end()
	{
		_Groggy_Chin_Down = false; _Groggy_Body_Down = false; _Groggy_Face_Down = false; _time = 0;
		if ((_Groggy_Chin_Up == true) && (_Groggy_Body_Up == true) && (_Groggy_Face_Up == true) && (_Groggy_RightHand_Up == true) && (_Groggy_LeftHand_Up == true))
			_state = Yggdrasil_State::Idle;		
	}


	void Yggdrasil::attack_d_set()
	{
		if (_SetattackD_r == true && _SetattackD_l == true)
			_state = Yggdrasil_State::Attack_D_Ready;		
	}
	void Yggdrasil::attack_d_ready()
	{
		if (_AttackD_Readyr == true && _AttackD_Readyr == true)
		{
			if (_NumberofAttack == 0)
			{
				_attackatime += Time::DeltaTime();
				if (_attackatime > 1.5f)
				{
					_state = Yggdrasil_State::Attack_D;
					_attackatime = 0.f;
				}
			}
			else
				_state = Yggdrasil_State::Attack_D;
		}
	}
	void Yggdrasil::attack_d()
	{
		if ((Yggdrasil_Hand_Left::_Attackswitch == true) && (Yggdrasil_Hand_Right::_Attackswitch == true))		
		{
			_state = Yggdrasil_State::Attack_D_Loading;
		}
	}
	void Yggdrasil::attack_d_loading()
	{		
		if (_NumberofAttack < 6)
		{
			if ((_AttackD_Loadingl == true) && (_AttackD_Loadingr == true))
				_state = Yggdrasil_State::Attack_D_Set;
		}

		if (_NumberofAttack >= 6)
		{
			if ((_AttackD_Finishr == true) && (_AttackD_Finishl == true))
				_state = Yggdrasil_State::Attack_D_Finish;
		}
	}
	void Yggdrasil::attack_d_finish()
	{
		_SetattackD_r = false; _SetattackD_l = false;
		_AttackD_Readyr = false;_AttackD_Readyl = false;
		_AttackD_Loadingr = false;_AttackD_Loadingl = false;		
		if (_AttackD_Finishr == false && _AttackD_Finishl == false)
		{
			_state = Yggdrasil_State::Idle;
			_time = 0;					
		}
	}


	void Yggdrasil::intro_set_right()
	{
		if (_Intro_SetR == true)
			_state = Yggdrasil_State::Intro_Ready;
	}
	void Yggdrasil::intro_set_left()
	{
		if(_Intro_SetL == true)
			_state = Yggdrasil_State::Intro_Set_Right;
	}
	void Yggdrasil::intro_ready()
	{
		if(_Intro_Ready ==true)
			_state = Yggdrasil_State::Intro;
	}
	void Yggdrasil::intro()
	{
		if(_Intro_StartCHIN==true && _Intro_StartR==true && _Intro_StartL==true)
			_state = Yggdrasil_State::Intro_End;
	}
	void Yggdrasil::intro_end()
	{
		_Intro = true;
		if (_Intro_EndR == true && _Intro_EndL == true )
			_state = Yggdrasil_State::Idle;
	}	
	
	
	void Yggdrasil::change_set()
	{
		if (_SetChange_r == true && _SetChange_l == true)
			_state = Yggdrasil_State::Change_Ready;
	}
	void Yggdrasil::change_ready()
	{
		if (_Change_Readyr == true && _Change_Readyl == true)
		{
			_attackatime += Time::DeltaTime();
			if (_attackatime > 1.5f)
			{
				_state = Yggdrasil_State::Change;
				_attackatime = 0.f;
			}			
		}
	}
	void Yggdrasil::change()
	{
		if (_Change_Chin == true && _Change_Face == true && _Change_HandR == true && _Change_HandL == true && _Change_Body ==true)
		{
			_state = Yggdrasil_State::Change_End;
		}
	}
	void Yggdrasil::change_end()
	{
		_Change_HandL = false;	_Change_HandR = false;	_Change_Face = false; _Change_Chin = false; 
		_Change_Body = false; _Change_Readyl = false; _Change_Readyr = false; _SetChange_l = false; _SetChange_r = false;
		if (_Change_FinishR == true && _Change_FinishL == true && _Change_Finish == true )
		{
			_Change = false;
			_state = Yggdrasil_State::Idle;
			//_Diecheck = 3;
		}
	}


	void Yggdrasil::die_set()
	{
		if (_Die_SetR == true && _Die_SetL == true)
			_state = Yggdrasil_State::DieReady;
	}
	void Yggdrasil::die_ready()
	{
		if (_Die_Body_Down == true && _Die_Face_Down == true&& _Die_Chin_Down ==true)
			_state = Yggdrasil_State::Die;
	}
	void Yggdrasil::die()
	{
	}


	int Yggdrasil::random(int a, int b)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(a, b);
		int abc = distribution(gen);
		return abc;
	}
}