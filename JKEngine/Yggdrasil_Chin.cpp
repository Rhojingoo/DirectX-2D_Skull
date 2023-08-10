#include "Yggdrasil_Chin.h"


namespace jk
{
	int Yggdrasil_Chin:: mDir = 1;		
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

		Yggdrasil_pos = Yggdrasil::GetPos();
		YggdrasilFace_pos = Yggdrasil_Face::FaceGetpos();
		//_pos.x = Yggdrasil_pos.x + 12.5f;
		//_pos.y = Yggdrasil_pos.y - 65.f;
		_pos.x = YggdrasilFace_pos.x + 12.5f;
		_pos.y = YggdrasilFace_pos.y - 65.f;
		
		//턱관리 포지션
		//_pos.y = YggdrasilFace_pos.y - 55.f;	// 에너지볼 공격전 기모을때
		//_pos.y = YggdrasilFace_pos.y - 65.f;	// 보통상태의 입다물기
		//_pos.y = YggdrasilFace_pos.y - 75.f;	// 보통상태의 입벌리기
		//_pos.y = YggdrasilFace_pos.y - 80.f;	// 공격시 입벌리기
		//_pos.y = YggdrasilFace_pos.y - 95.f;	// 인트로 및 변신 및 그로기단계


		_pos.z = -202.f;
		mCenterpos = _pos;
		tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(_pos));


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Chind\\YggdrasilChin_Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Chind\\YggdrasilChin_Attac_C", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Chind\\YggdrasilChin_Change", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Chind\\YggdrasilChin_Change_Die_Effect", this);

		//bind 부분
		//at->CompleteEvent(L"ArcherAttack_A") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_B") = std::bind(&Archer::choicecombo, this);
		//at->CompleteEvent(L"ArcherAttack_C") = std::bind(&Archer::choicecombo, this);


		at->PlayAnimation(L"ChindYggdrasilChin_Idle", true);

		GameObject::Initialize();
	}
	void Yggdrasil_Chin::Update()
	{
		Yggdrasil_pos = Yggdrasil::GetPos();
		YggdrasilFace_pos = Yggdrasil_Face::FaceGetpos();
		Yggdrasil_rotation = GetRotations();

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

		case jk::Yggdrasil::Yggdrasil_State::Attack_C:
			Yggdrasil_Chin::attack_c();
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

		case jk::Yggdrasil::Yggdrasil_State::Intro:
			Yggdrasil_Chin::intro();
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
		//if (mDir == 1)
		//	Lmove_down();
		//else
		//	Lmove_up();
	}	

	void Yggdrasil_Chin::attack_a_set()
	{
	}
	void Yggdrasil_Chin::attack_a_ready()
	{
	}
	void Yggdrasil_Chin::attack_a_right()
	{
	}
	void Yggdrasil_Chin::attack_a_left()
	{
	}
	void Yggdrasil_Chin::attack_a_loading()
	{
	}
	void Yggdrasil_Chin::attack_a_finish()
	{
	}


	void Yggdrasil_Chin::attack_b_set()
	{
	}
	void Yggdrasil_Chin::attack_b_ready()
	{
	}
	void Yggdrasil_Chin::attack_b_left()
	{
	}
	void Yggdrasil_Chin::attack_b_right()
	{
	}
	void Yggdrasil_Chin::attack_b_finish()
	{
	}


	void Yggdrasil_Chin::attack_c_set()
	{
	}
	void Yggdrasil_Chin::attack_c_ready()
	{
	}
	void Yggdrasil_Chin::attack_c()
	{
	}
	void Yggdrasil_Chin::attack_c_finish()
	{
	}


	void Yggdrasil_Chin::groggy_start()
	{
		groggy_down();
	}
	void Yggdrasil_Chin::groggy_end()
	{
	}


	void Yggdrasil_Chin::intro()
	{
	}
	void Yggdrasil_Chin::die()
	{
	}


	void Yggdrasil_Chin::groggy_down()
	{
		//_pos.x = YggdrasilFace_pos.x + 0.f;
		//_pos.y = YggdrasilFace_pos.y - 65.f;
		if (_pos.y >= -150.f)
			_pos.y -= 40 * Time::DeltaTime();
		if (_pos.x >= 7.f)
			_pos.x -= 7 * Time::DeltaTime();
	}
	void Yggdrasil_Chin::groggy_up()
	{
	}



	void Yggdrasil_Chin::Lmove_up()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = mCenterpos.y - _pos.y - _maxdistance;
		_pos.y -= _chinspeed * static_cast<float>(Time::DeltaTime());

		if (fDist >= 5.0f)
			mDir *= -1;		

		tr->SetPosition(_pos);
	}

	void Yggdrasil_Chin::Lmove_down()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = mCenterpos.y - _pos.y - _maxdistance;
		_pos.y += _chinspeed * static_cast<float>(Time::DeltaTime());

		if (fDist <= -1.f)
			mDir *= -1;

		tr->SetPosition(_pos);
	}

}
