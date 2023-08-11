#include "Yggdrasil_Face.h"

namespace jk
{
	Vector3 Yggdrasil_Face::_pos = Vector3(0.f, 0.f, 0.f);;
	Yggdrasil_Face::Yggdrasil_Face()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Yggdrasil_Face::~Yggdrasil_Face()
	{
	}
	void Yggdrasil_Face::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		Yggdrasil_pos = Yggdrasil::GetPos();
		//_pos.y = Yggdrasil_pos.y - 5.f;
		tr = GetComponent<Transform>();
		_pos.z = -201.f;
		tr->SetPosition(Vector3(_pos.x, _pos.y, _pos.z));

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_groggy", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_Die", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Face\\YggdrasilFace_Die_Effect", this);

		//bind 부분
		//at->CompleteEvent(L"ArcherAttack_A") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_B") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);

		{
			Energy_Bomb = new Yggdrasil_Energy_Bomb;
			Energy_Bomb->Initialize();			
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Energy_Bomb);
			Transform* bullet_tr = Energy_Bomb->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			basic_save_pos = Vector3(_pos.x + 10, _pos.y, -205);
			Energy_Bomb->SetState(eState::Paused);
		}

		for (int i = 0; i < 8; i++)
		{
			Bullet[i] = new Yggdrasil_BasicBullet;
			Bullet[i]->Initialize();		
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Bullet[i]);
			Transform* bullet_tr = Bullet[i]->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(_pos.x, _pos.y, -205));
			bullet_tr->SetScale(Vector3(35.f, 36.f, 0.f));
			Bullet[i]->SetState(eState::Paused);
		}
		
		for (int i = 0; i < 15; i++)
		{
			Energy_Corps[i] = new Yggdrsil_Energy_Corps;
			Energy_Corps[i]->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Bullet, Energy_Corps[i]);
			Transform* bullet_tr = Energy_Corps[i]->GetComponent<Transform>();
			bullet_tr->SetPosition(Vector3(random(-250, 250), random(_pos.y, _pos.y + 100), -206.f));
			Energy_Corps[i]->SetState(eState::Paused);
		}

		at->PlayAnimation(L"FaceYggdrasilFace_Idle", true);

		GameObject::Initialize();
	}
	void Yggdrasil_Face::Update()
	{
		_playerpos;
		Yggdrasil_rotation = GetRotations();
		Yggdrasil_pos = GetPos();
		_pos = (Vector3(_pos.x, _pos.y, -201));


		_distance = _playerpos.x - _pos.x;
		if (_distance >= 0.f)
			mDir = 1;
		else
			mDir = -1;

		switch (_state)
		{
		case jk::Yggdrasil::Yggdrasil_State::Idle:
			Yggdrasil_Face::idle();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Set:
			Yggdrasil_Face::attack_a_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Ready:
			Yggdrasil_Face::attack_a_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Right:
			Yggdrasil_Face::attack_a_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Loading:
			Yggdrasil_Face::attack_a_loading();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_A_Finish:
			Yggdrasil_Face::attack_a_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Set:
			Yggdrasil_Face::attack_b_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Ready:
			Yggdrasil_Face::attack_b_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Right:
			Yggdrasil_Face::attack_b_right();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Left:
			Yggdrasil_Face::attack_b_left();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_B_Finish:
			Yggdrasil_Face::attack_b_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Set:
			Yggdrasil_Face::attack_c_set();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Ready:
			Yggdrasil_Face::attack_c_ready();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C:
			Yggdrasil_Face::attack_c();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Attack_C_Finish:
			Yggdrasil_Face::attack_c_finish();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Groggy_Start:
			Yggdrasil_Face::groggy_start();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Groggy_End:
			Yggdrasil_Face::groggy_end();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Intro:
			Yggdrasil_Face::intro();
			break;

		case jk::Yggdrasil::Yggdrasil_State::Die:
			Yggdrasil_Face::die();
			break;

		default:
			break;
		}

		tr->SetPosition(_pos);
		tr->SetRotation(Yggdrasil_rotation);
		GameObject::Update();
	}
	void Yggdrasil_Face::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_Face::Render()
	{
		GameObject::Render();
	}

	void Yggdrasil_Face::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_Face::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_Face::OnCollisionExit(Collider2D* other)
	{
	}
	void Yggdrasil_Face::idle()
	{
	}
	void Yggdrasil_Face::attack_a_set()
	{
	}
	void Yggdrasil_Face::attack_a_ready()
	{
	}
	void Yggdrasil_Face::attack_a_right()
	{
	}
	void Yggdrasil_Face::attack_a_left()
	{
	}
	void Yggdrasil_Face::attack_a_loading()
	{
	}
	void Yggdrasil_Face::attack_a_finish()
	{
	}
	void Yggdrasil_Face::attack_b_set()
	{
	}
	void Yggdrasil_Face::attack_b_ready()
	{
	}
	void Yggdrasil_Face::attack_b_left()
	{
	}
	void Yggdrasil_Face::attack_b_right()
	{
	}

	void Yggdrasil_Face::attack_b_finish()
	{
	}

	void Yggdrasil_Face::attack_c_set()
	{
		set_basicbuulet();
	}

	void Yggdrasil_Face::attack_c_ready()
	{
		Yggdrasil_Effect::_effect_switch = true;
		_time = 0;
		_NumberofAttack++;
	}

	void Yggdrasil_Face::attack_c()
	{
		_time += Time::DeltaTime();
		if (_time <= 7.f)
		{
			for (int i = 0; i < 8; i++)
			{
				Bullet[i]->SetState(eState::Active);
			}
			Energy_Bomb->SetState(eState::Active);
			basicattack();
			Energy_Bombattack();		
		}
		else
		{
			for (int i = 0; i < 8; i++)
			{
				Bullet[i]->SetState(eState::Paused);
				Bullet[i]->GetComponent<Transform>()->SetPosition(basic_save_pos);
				
			}
			{
				Energy_Bomb->SetState(eState::Paused);
				Energy_Bomb->GetComponent<Transform>()->SetPosition(basic_save_pos);				
			}
			for (int i = 0; i < 15; i++)
			{
				Energy_Corps[i]->SetState(eState::Paused);
				Energy_Corps[i]->GetComponent<Transform>()->SetPosition(Vector3(random(-250, 250), random(_pos.y, _pos.y + 100), -205.f));
			}
			if (_NumberofAttack >= 3)
				_state = Yggdrasil_State::Attack_C_Finish;
			else
				_state = Yggdrasil_State::Attack_C_Ready;
		}

		// 2차 체인지 미사일
		//if (_time <= 15.f)
		//{
		//	if (_time >= 1.f)
		//	{
		//		for (int i = 0; i < 5; i++)
		//		{
		//			Energy_Corps[i]->SetState(eState::Active);
		//			Energy_Corpsattack();
		//		}
		//	}
		//	if (_time >= 5.f)
		//	{
		//		for (int i = 5; i < 10; i++)
		//		{
		//			Energy_Corps[i]->SetState(eState::Active);
		//			Energy_Corpsattack();
		//		}
		//	}
		//	if (_time >= 10.f)
		//	{
		//		for (int i = 10; i < 15; i++)
		//		{
		//			Energy_Corps[i]->SetState(eState::Active);
		//			Energy_Corpsattack();
		//		}
		//	}
		//}
		//else
		//{
		//	for (int i = 0; i < 8; i++)
		//	{
		//		Bullet[i]->SetState(eState::Paused);
		//		Bullet[i]->GetComponent<Transform>()->SetPosition(basic_save_pos);

		//	}
		//	{
		//		Energy_Bomb->SetState(eState::Paused);
		//		Energy_Bomb->GetComponent<Transform>()->SetPosition(basic_save_pos);
		//	}
		//	for (int i = 0; i < 15; i++)
		//	{
		//		Energy_Corps[i]->SetState(eState::Paused);
		//		Energy_Corps[i]->GetComponent<Transform>()->SetPosition(Vector3(random(-250, 250), random(_pos.y, _pos.y + 100), -205.f));
		//	}
		//	if (_NumberofAttack >= 3)
		//		_state = Yggdrasil_State::Attack_C_Finish;
		//	else
		//		_state = Yggdrasil_State::Attack_C_Ready;
		//}
	}

	void Yggdrasil_Face::attack_c_finish()
	{
		_time = 0;
		_NumberofAttack = 0;
		_AttackC_Finish = true;
	}

	void Yggdrasil_Face::groggy_start()
	{
		groggy_down();
	}

	void Yggdrasil_Face::groggy_end()
	{
		groggy_up();
	}

	void Yggdrasil_Face::intro()
	{
	}

	void Yggdrasil_Face::die()
	{
	}

	void Yggdrasil_Face::basicattack()
	{
		for (int i = 0; i < 8; i++)
		{
			Transform* bullet_tr = Bullet[i]->GetComponent<Transform>();

			Vector3 bulletattack = bullet_tr->GetPosition();
			bulletattack.x += basic_pos[i].x * Time::DeltaTime();
			bulletattack.y += basic_pos[i].y * Time::DeltaTime();
			bullet_tr->SetPosition(Vector3(bulletattack.x, bulletattack.y, -205));
		}
	}
	void Yggdrasil_Face::set_basicbuulet()
	{
		basic_pos[0] = Vector2(0.f, 150.f);
		basic_pos[1] = Vector2(110.f, 110.f);
		basic_pos[2] = Vector2(150.f, 0.f);
		basic_pos[3] = Vector2(110.f, -110.f);
		basic_pos[4] = Vector2(0.f, -150.f);
		basic_pos[5] = Vector2(-110.f, -110.f);
		basic_pos[6] = Vector2(-150.f, 0.f);
		basic_pos[7] = Vector2(-110.f, 110.f);
	}
	void Yggdrasil_Face::Energy_Bombattack()
	{
		Transform* bullet_tr = Energy_Bomb->GetComponent<Transform>();
		RigidBody* bullet_Rb = Energy_Bomb->GetComponent<RigidBody>();

		_playerpos.x;
		_playerpos.y;		
		Vector2 attack_pos = Vector2(_playerpos.x, _playerpos.y);
		attack_pos.Normalize();
		bullet_Rb->SetGround(false);
		bullet_Rb->SetVelocity(Vector2(attack_pos.x * 300.f, attack_pos.y*200));
	}

	void Yggdrasil_Face::Energy_Corpsattack()
	{
		for (int i = 0; i < 15; i++)
		{						
			RigidBody* bullet_Rb = Energy_Corps[i]->GetComponent<RigidBody>();
			_playerpos.x;
			_playerpos.y;
			Vector2 attack_pos = Vector2(_playerpos.x, _playerpos.y);
			attack_pos.Normalize();
			bullet_Rb->SetGround(false);
			bullet_Rb->SetVelocity(Vector2(attack_pos.x * 50.f, attack_pos.y * 250));
		}
	}


	void Yggdrasil_Face::groggy_down()
	{
		if (_Groggy_Face_Down == false)
		{
			if (_pos.y >= -100.f)
				_pos.y -= 50 * Time::DeltaTime();
			if (_pos.x >= -40.f)
				_pos.x -= 35 * Time::DeltaTime();
			if ((_pos.y < -100.f) && (_pos.x < -40.f))
				_Groggy_Face_Down = true;
		}
	}
	void Yggdrasil_Face::groggy_up()
	{
		if (_Groggy_Face_Up == false)
		{
			if (_pos.y <= 0.f)
				_pos.y += 50 * Time::DeltaTime();
			if (_pos.x <= 0.f)
				_pos.x += 35 * Time::DeltaTime();
			if ((_pos.y >= 0.f) && (_pos.x >= 0.f))
			{
				_pos.x = 0;
				_pos.y = 0;
				_Groggy_Face_Up = true;
			}
		}
	}
}
