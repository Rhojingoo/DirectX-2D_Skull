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

		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Ygdrasil\\ElderEnt_Impact(Legacy).wav", "ElderEnt_Impact(Legacy)");//인트로시
		//1번공격
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Ygdrasil\\ElderEnt_FistSlam.wav", "ElderEnt_FistSlam");//바닥충돌
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Ygdrasil\\ElderEnt_FistSlam_Recovery.wav", "ElderEnt_FistSlam_Recovery");//바닥충돌후 손올리기
		//2번공격
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Ygdrasil\\ElderEnt_Sweeping.wav", "ElderEnt_Sweeping"); //손공격시 입사운드
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Ygdrasil\\ElderEnt_Sweeping_Roar.wav", "ElderEnt_Sweeping_Roar"); //손공격사운드
	

		_Savepointpos = Vector3(-150.f, -120.f, -203.f);
		_pos = Vector3(GetPos().x - 150.f, -300.f, -199.f);
		tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(_pos));


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandIdle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandRock", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandAttack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandAntlion", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_Handintro", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_HandBullet", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_Bullet_off", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\1_Bullet_on", this);

		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandIdle_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandRock_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandAttack_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandAntlion_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandBullet_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\Bullet_off_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\Bullet_on_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\HandDie_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Hand\\Hand_DIE", this);		
		
		//bind 부분
		//at->CompleteEvent(L"ArcherAttack_A") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_B") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);


		{
			FistSlam_Smoke = new Yggdrasil_FistSlam_Effect;
			FistSlam_Smoke->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, FistSlam_Smoke);
			Transform* effect_tr = FistSlam_Smoke->GetComponent<Transform>();
			effect_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));	
			FistSlam_Smoke->SetState(eState::Paused);
		}
		{
			_Sweeping = new Yggdrasil_Sweeping;
			_Sweeping->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, _Sweeping);
			Transform* effect_tr = _Sweeping->GetComponent<Transform>();
			effect_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			_Sweeping->SetState(eState::Paused);
		}

		{
			Hit_Box = new HitBox_YggDrasil();
			Hit_Box->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Hitbox, Hit_Box);
			Hit_Box->SetState(eState::Paused);
		}
		{
			_Dead_Effect = new Yggdrasil_HandDead_Effect;
			_Dead_Effect->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, _Dead_Effect);
			Transform* bullet_tr = _Dead_Effect->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
			_Dead_Effect->SetState(eState::Paused);
		}


		at->PlayAnimation(L"Hand1_HandIdle", true);
		at->PlayAnimation(L"Hand1_Handintro", true);		
			
		GameObject::Initialize();
	}
	void Yggdrasil_Hand_Left::Update()
	{
		tr = GetComponent<Transform>();
		_pos = tr->GetPosition();
		_velocity = _rigidbody->GetVelocity();
		_Yggdrasildistance = GetPos() - _pos;
		_Playerdistance = _playerpos - _pos;

		if (_state == Yggdrasil_State::Attack_B_Finish)
		{
		}

		if (_Change_AttackD_HitgrOn == true)
		{
			Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
			Hit_Box->SetSize(Vector2(350.f, 35.f));
			HitBox_TR->SetPosition(Vector3(0.f, -160.f, _pos.z));
			Hit_Box->SetState(eState::Active);

			_hitboxtime += static_cast<float>(Time::DeltaTime());
			if (_hitboxtime > 0.3)
			{
				_Change_AttackD_HitgrOn = false;
				Hit_Box->SetState(eState::Paused);
				_hitboxtime = 0;
			}
		}


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


		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Set:
			Yggdrasil_Hand_Left::attack_c_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Ready:
			Yggdrasil_Hand_Left::attack_c_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C:
			Yggdrasil_Hand_Left::attack_c();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Finish:
			Yggdrasil_Hand_Left::attack_c_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Groggy_Start:
			Yggdrasil_Hand_Left::groggy_start();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Groggy_End:
			Yggdrasil_Hand_Left::groggy_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_D_Set:
			Yggdrasil_Hand_Left::attack_d_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_D_Ready:
			Yggdrasil_Hand_Left::attack_d_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_D:
			Yggdrasil_Hand_Left::attack_d();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_D_Loading:
			Yggdrasil_Hand_Left::attack_d_loading();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_D_Finish:
			Yggdrasil_Hand_Left::attack_d_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_Set_Right:
			Yggdrasil_Hand_Left::intro_set_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_Set_Left:
			Yggdrasil_Hand_Left::intro_set_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_Ready:
			Yggdrasil_Hand_Left::intro_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro:
			Yggdrasil_Hand_Left::intro();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro_End:
			Yggdrasil_Hand_Left::intro_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change_Set:
			Yggdrasil_Hand_Left::change_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change_Ready:
			Yggdrasil_Hand_Left::change_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change:
			Yggdrasil_Hand_Left::change();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Change_End:
			Yggdrasil_Hand_Left::change_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::DieSet:
			Yggdrasil_Hand_Left::die_set();
			break;


		case jk::Yggdrasil::Yggdrasil_State::Die_Waiting:
			Yggdrasil_Hand_Left::die_waiting();
			break;


		case jk::Yggdrasil::Yggdrasil_State::DieReady:
			Yggdrasil_Hand_Left::die_ready();
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
		Transform* HitBox_TR = Hit_Box->GetComponent<Transform>();
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));

		if (_HitBox_Attack_On == true)
		{
			_collider->SetSize(Vector2(0.5f, 0.5f));
			_collider->SetCenter(Vector2(0.0f, -0.05f));

			Hit_Box->SetSize(Vector2(115.f,95.f));
			HitBox_TR->SetPosition(Vector3(_pos.x, _pos.y, _pos.z));
			Hit_Box->SetState(eState::Active);
		}
		else if (_Change_AttackD_On == true)
		{
			_collider->SetSize(Vector2(0.5f, 0.5f));
			_collider->SetCenter(Vector2(0.0f, -0.05f));
		}
		else if (_Change_AttackD_HitgrOn == true)
		{
			Hit_Box->SetSize(Vector2(350.f, 35.f));
			HitBox_TR->SetPosition(Vector3(0.f, -160.f, _pos.z));
			Hit_Box->SetState(eState::Active);

			_hitboxtime += static_cast<float>(Time::DeltaTime());
			if (_hitboxtime > 0.3)
			{
				_Change_AttackD_HitgrOn = false;
				Hit_Box->SetState(eState::Paused);
				_hitboxtime = 0;
			}
		}
		else
		{
			Hit_Box->SetState(eState::Paused);
		}

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
				_time += static_cast<float>(Time::DeltaTime());
				_Attackswitch = true;
				_NumberofAttack++;

				if (_state == Yggdrasil_State::Attack_A_Left)
				{
					FistSlam_Smoke->SetState(eState::Active);
					FistSlam_Smoke->_EffectOn = true;
					Transform* Effect = FistSlam_Smoke->GetComponent<Transform>();
					Effect->SetPosition(Vector3(_pos.x, _pos.y + 60, _playerpos.z-1));
					_HitBox_Attack_On = false;
				}				
				if (_state == Yggdrasil_State::Attack_D)
				{
					_Change_AttackD_HitgrOn = true;
					FistSlam_Smoke->SetState(eState::Active);
					FistSlam_Smoke->_EffectOn = true;
					Transform* Effect = FistSlam_Smoke->GetComponent<Transform>();
					Effect->SetPosition(Vector3(_pos.x, _pos.y + 75, _pos.z-1));
				}
			}
			else
			{			
				if(FistSlam_Smoke->_EffectOn == false)
					FistSlam_Smoke->SetState(eState::Paused);
			}
		}

		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_rigidbody->ClearVelocity();
				_Ground_check = true;
				_time += static_cast<float>(Time::DeltaTime());
				_NumberofAttack++;

				if (_state == Yggdrasil_State::Attack_A_Left)
				{
					_Attackswitch = true;
					as->Play("ElderEnt_FistSlam");
					FistSlam_Smoke->SetState(eState::Active);
					FistSlam_Smoke->_EffectOn = true;
					Transform* Effect = FistSlam_Smoke->GetComponent<Transform>();
					Effect->SetPosition(Vector3(_pos.x, _pos.y + 60, _playerpos.z - 1));
					_HitBox_Attack_On = false;
				}
				if (_state == Yggdrasil_State::Attack_D)
				{								
					_Attackswitch = true;
					FistSlam_Smoke->SetState(eState::Active);
					FistSlam_Smoke->_EffectOn = true;
					Transform* Effect = FistSlam_Smoke->GetComponent<Transform>();
					Effect->SetPosition(Vector3(_pos.x, _pos.y +75, _pos.z - 1));
				}
			}
			else
			{
				if (FistSlam_Smoke->_EffectOn == false)
					FistSlam_Smoke->SetState(eState::Paused);
			}
		}
	}

	void Yggdrasil_Hand_Left::OnCollisionStay(Collider2D* other)
	{
		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			if (_state == Yggdrasil_State::Attack_D)
			{
				_Change_AttackD_HitgrOn = true;
			}
		}
	}

	void Yggdrasil_Hand_Left::OnCollisionExit(Collider2D* other)
	{

	}


	void Yggdrasil_Hand_Left::idle()
	{		
		_pos = Vector3(GetPos().x - 150.f, GetPos().y - 100, -203.f);
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
			if (_Changeon == true)
				at->PlayAnimation(L"HandHandRock_Change", true);
		}
	}
	void Yggdrasil_Hand_Left::attack_a_ready()
	{
		if (_SetattackA_l == true)
		{	
			at->PlayAnimation(L"Hand1_HandRock", true);
			if (_Changeon == true)
				at->PlayAnimation(L"HandHandRock_Change", true);

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
			_HitBox_Attack_On = true;
			_Ground_check = false;
			_playerpos.x;
			_playerpos.y;

			Vector2 attack_pos = Vector2(_playerpos.x - _pos.x, _playerpos.y - _pos.y);
			attack_pos.Normalize();
			_rigidbody->SetGround(false);
			_rigidbody->SetVelocity(Vector2(attack_pos.x * 400.f, attack_pos.y * 400));
			_AttackA_Readyl = false;	
		}
	}
	void Yggdrasil_Hand_Left::attack_a_loading()
	{
		if (_Attackswitch == true && _Ground_check == true)
		{
			if (_NumberofAttack <= 2)
			{
				if (_attackloading == false)
				{
					if (_pos.x > _AttackA_SavePos.x)
						_pos.x -= 150.0f * static_cast<float>(Time::DeltaTime());
					else if (_pos.x < _AttackA_SavePos.x)
						_pos.x += 150.0f * static_cast<float>(Time::DeltaTime());
					if (_pos.y < _AttackA_SavePos.y)
						_pos.y += 250.0f * static_cast<float>(Time::DeltaTime());
					tr->SetPosition(Vector3(_pos));
					
					if (_AttackA_SavePos.y <= _pos.y)
						_attackloading = true;				
				}
				else
				{
					if (_AttackA_SavePos.x >= _pos.x)
						_pos.x = _AttackA_SavePos.x;
					else if (_AttackA_SavePos.x <= _pos.x)
						_pos.x = _AttackA_SavePos.x;
					if (_AttackA_SavePos.y <= _pos.y)
						_pos.y = _AttackA_SavePos.y;

					if ((_pos.x == _AttackA_SavePos.x) && (_pos.y == _AttackA_SavePos.y))
					{
						if (_NumberofAttack < 2)
						{
							_state = Yggdrasil_State::Attack_A_Set;
							_attackloading = false;
						}
						else
						{
							_AttackA_LoadingL = true;
							_attackloading = false;
						}
					}				
				}
			}
		}
		if (_NumberofAttack >= 2 && _AttackA_LoadingR == true)
		{
			_AttackA_LoadingL = true;
			_attackloading = false;
		}
	}
	void Yggdrasil_Hand_Left::attack_a_finish()
	{
		if (_NumberofAttack >= 2)
		 {
			_Savepointpos.x;
			if (_pos.x > _Savepointpos.x)
				_pos.x -= 150.0f * static_cast<float>(Time::DeltaTime());
			if (_pos.y > _Savepointpos.y)
				_pos.y -= 150.0f * static_cast<float>(Time::DeltaTime());
			tr->SetPosition(Vector3(_pos));

			if (_Savepointpos.x >= _pos.x)
				_pos.x = _Savepointpos.x;
			if (_Savepointpos.y >= _pos.y)
				_pos.y = _Savepointpos.y;
		
			if ((_pos.x == _Savepointpos.x) && (_pos.y == _Savepointpos.y))
			{
				at->PlayAnimation(L"Hand1_HandIdle", true);
				if (_Changeon == true)
					at->PlayAnimation(L"HandHandIdle_Change", true);
				_AttackA_FinishL = true;
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
			if (_Changeon == true)
				at->PlayAnimation(L"HandHandAttack_Change", false);
		}
	}
	void Yggdrasil_Hand_Left::attack_b_ready()
	{
		if (_SetattackB_l == true)
		{
			attackb_setting();
		}
	}
	void Yggdrasil_Hand_Left::attack_b_right()
	{				
	}
	void Yggdrasil_Hand_Left::attack_b_left()
	{	
		if(_AttackB_Boddy == true)
		{
			if (_attackon == true)
			{
				_HitBox_Attack_On = true;
				_rigidbody->SetVelocity(Vector2(750.f, 0.f));
				_Sweeping->SetState(eState::Active);
				_Sweeping->SetDirection(1);
				Transform* _SweepingTR = _Sweeping->GetComponent<Transform>();
				_SweepingTR->SetPosition(Vector3(_pos.x - 150.f, _pos.y - 15, _pos.z - 1));
			}
			if (_Yggdrasildistance.x <= -1000)
			{
				_Sweeping->SetState(eState::Paused);
				_rigidbody->ClearVelocityX();				
				_pos.x = _AttackB_SavePos.x;
				_pos.y = _AttackB_SavePos.y;
				_attackon = false;
				_AttackB_Boddy = false;
				_HitBox_Attack_On = false;
				_state = Yggdrasil_State::Attack_B_Ready;
				_NumberofAttack++;
			
				if (_NumberofAttack >= 2)
				{
					at->PlayAnimation(L"Hand1_HandIdle", true);
					if (_Changeon == true)
						at->PlayAnimation(L"HandHandIdle_Change", true);
					_rigidbody->ClearVelocityX();
					_pos.x = _Savepointpos.x;
					_pos.y = _Savepointpos.y - 300;
				}
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
			_pos.z = -199.f;
			_NumberofAttack = 0;
			at->PlayAnimation(L"Hand1_HandIdle", true);
			if (_Changeon == true)
				at->PlayAnimation(L"HandHandIdle_Change", true);
		}

		if (_attackon == false)
		{
			_pos.x = _Savepointpos.x;
			if (_pos.y < _Savepointpos.y)
				_pos.y += 150.0f * static_cast<float>(Time::DeltaTime());
			
			{
				if (_Savepointpos.x <= _pos.x)
					_pos.x = _Savepointpos.x;
				if (_Savepointpos.y <= _pos.y)
					_pos.y = _Savepointpos.y;
			}
			tr->SetPosition(Vector3(_pos));

			if ((_pos.x == _Savepointpos.x) && (_pos.y == _Savepointpos.y))
			{
				at->PlayAnimation(L"Hand1_HandIdle", true);
				if (_Changeon == true)
					at->PlayAnimation(L"HandHandIdle_Change", true);
				_attackready = false;
				_attackon = false;
				_AttackB_Finishl = true;
				_pos.z = -203.f;
			}
		}
	}


	void Yggdrasil_Hand_Left::attack_c_set()
	{
		if (_Attackswitch == true)		
			_Attackswitch = false;		
		else
		{
			at->PlayAnimation(L"Hand1_Bullet_on", false);
			if (_Changeon == true)
			at->PlayAnimation(L"HandBullet_on_Change", false);
			_SetattackC_l = true;
		}
	}
	void Yggdrasil_Hand_Left::attack_c_ready()
	{
	}
	void Yggdrasil_Hand_Left::attack_c()
	{
	}
	void Yggdrasil_Hand_Left::attack_c_finish()
	{

	}


	void Yggdrasil_Hand_Left::groggy_start()
	{
	}
	void Yggdrasil_Hand_Left::groggy_end()
	{
		if (_Groggy_LeftHand_Up == false)
		{
			at->PlayAnimation(L"Hand1_HandIdle", true);
			if (_Changeon == true)
				at->PlayAnimation(L"HandHandIdle_Change", true);
			_Groggy_LeftHand_Up = true;
		}
	}


	void Yggdrasil_Hand_Left::attack_d_set()
	{
		if (_Attackswitch == true)
		{
			_rigidbody->ClearVelocity();
			_rigidbody->SetVelocity(Vector2(-10.f, 0.f));
			_Attackswitch = false;
		}
		else
		{
			_Change_AttackD_On = true;
			_SetattackD_l = true;
			at->PlayAnimation(L"Hand1_HandRock", true);
			if (_Changeon == true)
				at->PlayAnimation(L"HandHandRock_Change", true);
		}
	}
	void Yggdrasil_Hand_Left::attack_d_ready()
	{
		if (_SetattackD_l == true)
		{
			at->PlayAnimation(L"Hand1_HandRock", true);
			if (_Changeon == true)
				at->PlayAnimation(L"HandHandRock_Change", true);

			_rigidbody->ClearVelocity();
			_rigidbody->SetGround(false);
			_rigidbody->SetVelocity(Vector2(0.f, 200.f));	
			_Attackswitch = false;
			_Ground_check = false;
		}

		if (_Yggdrasildistance.y <= -137.f)
		{
			_SetattackD_l = false;
			_rigidbody->ClearVelocity();
			_rigidbody->SetGround(true);
			if (_AttackA_SavePos.y < _pos.y)
				_AttackA_SavePos = _pos;
			_AttackD_Readyl = true;
		}
	}
	void Yggdrasil_Hand_Left::attack_d()
	{
		if (_AttackD_Readyl == true)
		{	
			_Ground_check = false;
			_rigidbody->SetGround(false);
			_rigidbody->SetVelocity(Vector2(0.F, -350.f));
			_AttackD_Readyl = false;
		}
	}
	void Yggdrasil_Hand_Left::attack_d_loading()
	{
		if (_Attackswitch == true && _Ground_check == true)
		{
			_Change_AttackD_HitgrOn = true;
			if (_NumberofAttack < 4)
			{
				if (_pos.x > _AttackA_SavePos.x)
					_pos.x -= 150.0f * static_cast<float>(Time::DeltaTime());
				if (_pos.y < _AttackA_SavePos.y)
					_pos.y += 250.0f * static_cast<float>(Time::DeltaTime());
				tr->SetPosition(Vector3(_pos));

				if (_AttackA_SavePos.x >= _pos.x)
					_pos.x = _AttackA_SavePos.x;
				if (_AttackA_SavePos.y <= _pos.y)
					_pos.y = _AttackA_SavePos.y;
				if ((_pos.x == _AttackA_SavePos.x) && (_pos.y == _AttackA_SavePos.y))
				{
					if (_NumberofAttack < 4)
						_AttackD_Loadingl = true;

					if (_NumberofAttack >= 6)
					{
						_AttackD_Loadingl = false;
						_AttackD_Finishl = true;
					}
				}
			}
			if (_NumberofAttack < 5)
			{
				if (_pos.x > _AttackA_SavePos.x)
					_pos.x -= 150.0f * static_cast<float>(Time::DeltaTime());
				if (_pos.y < _AttackA_SavePos.y)
					_pos.y += 180.0f * static_cast<float>(Time::DeltaTime());
				tr->SetPosition(Vector3(_pos));

				if (_AttackA_SavePos.x >= _pos.x)
					_pos.x = _AttackA_SavePos.x;
				if (_AttackA_SavePos.y <= _pos.y)
					_pos.y = _AttackA_SavePos.y;

				if ((_pos.x == _AttackA_SavePos.x) && (_pos.y == _AttackA_SavePos.y))
				{
					if (_NumberofAttack < 6)
						_AttackD_Loadingl = true;			
				}
			}
			if (_NumberofAttack >= 6)
			{
				_AttackD_Loadingl = false;
				_AttackD_Finishl = true;
			}
		}
	}
	void Yggdrasil_Hand_Left::attack_d_finish()
	{	
		if (_NumberofAttack >= 3)
		{
			_Change_AttackD_On = false;
			_Savepointpos.x;
			if (_pos.x > _Savepointpos.x)
				_pos.x -= 150.0f * static_cast<float>(Time::DeltaTime());
			if (_pos.y > _Savepointpos.y)
				_pos.y -= 150.0f * static_cast<float>(Time::DeltaTime());
			tr->SetPosition(Vector3(_pos));

			if (_Savepointpos.x >= _pos.x)
				_pos.x = _Savepointpos.x;
			if (_Savepointpos.y >= _pos.y)
				_pos.y = _Savepointpos.y;

			
			if ((_pos.x == _Savepointpos.x) && (_pos.y == _Savepointpos.y))
			{
				_AttackD_Finishl = false;
				at->PlayAnimation(L"Hand1_HandIdle", true);
				if (_Changeon == true)
					at->PlayAnimation(L"HandHandIdle_Change", true);
			}
		}
	}


	void Yggdrasil_Hand_Left::intro_set_right()
	{
	}
	void Yggdrasil_Hand_Left::intro_set_left()
	{
		hand_intro_up();
	}
	void Yggdrasil_Hand_Left::intro_ready()
	{
	}
	void Yggdrasil_Hand_Left::intro()
	{
		if (_Intro_StartCHIN == true)
		{
			at->PlayAnimation(L"Hand1_Bullet_off", false);
			_Intro_StartL = true;
		}
	}
	void Yggdrasil_Hand_Left::intro_end()
	{
		at->PlayAnimation(L"Hand1_HandIdle", true);
		_Intro_EndL = true;
	}


	void Yggdrasil_Hand_Left::change_set()
	{
		if (_Attackswitch == true)
		{
			_pos = Vector3(GetPos().x - 150.f, GetPos().y - 100, -203.f);
			_rigidbody->ClearVelocity();
			_rigidbody->SetVelocity(Vector2(-10.f, 0.f));
			_Attackswitch = false;
			_Sweeping->SetState(eState::Paused);
			at->PlayAnimation(L"Hand1_HandRock", false);
			_HitBox_Attack_On = false;
		}
		else
		{
			_SetChange_l = true;
			//at->PlayAnimation(L"Hand1_HandRock", true);
		}
	}
	void Yggdrasil_Hand_Left::change_ready()
	{
		if (_SetChange_l == true)
		{
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
			if (_AttackA_SavePos.y < _pos.y)
				_AttackA_SavePos = _pos;
			_Change_Readyl = true;
		}
	}
	void Yggdrasil_Hand_Left::change()
	{
		if (_Change_Readyl == true)
		{
			_Ground_check = false;
			_rigidbody->SetGround(false);
			_rigidbody->SetVelocity(Vector2(0.F, -250.f));
			_Change_Readyl = false;
			_Change_HandL = true;
		}
		if (_Changeon == true)
		{
			at->PlayAnimation(L"HandHandRock_Change", false);			
			_Change_HandL = true;
		}
	}
	void Yggdrasil_Hand_Left::change_end()
	{
		if (_Change_FinishL == false)
		{
			at->PlayAnimation(L"HandHandIdle_Change", true);
			_Change_FinishL = true;
		}		
	}



	void Yggdrasil_Hand_Left::die_set()
	{
		_HitBox_Attack_On = false;
		_Attackswitch = false;
		_Sweeping->SetState(eState::Paused);
		_rigidbody->ClearVelocity();
		_pos = Vector3(GetPos().x - 150.f, GetPos().y - 100, -203.f);
		at->PlayAnimation(L"HandHandDie_Change", false);
		Transform* bullet_tr = _Dead_Effect->GetComponent<Transform>();
		bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z - 1));
		_Dead_Effect->SetDirection(1);
		_Dead_Effect->SetDirectionBool(true);
		_Dead_Effect->SetState(eState::Active);

		_Die_SetL = true;
	}
	void Yggdrasil_Hand_Left::die_waiting()
	{		
		at->PlayAnimation(L"HandHand_DIE", false);
		_Dead_Effect->SetState(eState::Paused);
		_Die_Waiting_L = true;
	}
	void Yggdrasil_Hand_Left::die_ready()
	{
	}
	void Yggdrasil_Hand_Left::die()
	{
	}


	void Yggdrasil_Hand_Left::hand_intro_up()
	{
		if (_pos.y < _Savepointpos.y)
			_pos.y += 150.f * static_cast<float>(Time::DeltaTime());
		if (_pos.y >= _Savepointpos.y)
		{
			_pos.y = _Savepointpos.y;
			_pos.z = _Savepointpos.z;
			_Intro_SetL = true;
			at->PlayAnimation(L"Hand1_HandAntlion", false);
			as->Play("ElderEnt_Impact(Legacy)");
		}
	}
	void Yggdrasil_Hand_Left::attackb_setting()
	{
		if (_attackready == false) 
		{
			if (_Yggdrasildistance.x >= 600)
			{
				_pos.x = _pos.x; 
				_AttackB_Readyl = true;
				_AttackB_SavePos = _pos;
				_attackon = true;		
			}
			else	
				_pos.x -= 550.0f * static_cast<float>(Time::DeltaTime());
			
			tr->SetPosition(Vector3(_pos));
		}		
	}

}
