#include "Layana_Sisters.h"
#include <iostream>
#include <random>

namespace jk
{
	Layana_Sisters::Layana_Sisters_State Layana_Sisters::_state = Layana_Sisters_State();
	Vector3 Layana_Sisters::_pos = Vector3(0.f,0.f,0.f);
	Vector3 Layana_Sisters::_Rotation = Vector3(0.f, 0.f, 0.f);
	int	Layana_Sisters::mDir = 1;
	float Layana_Sisters::_time = 0.f;

	Layana_Sisters::Layana_Sisters()
	{
	}
	Layana_Sisters::~Layana_Sisters()
	{
	}

	void Layana_Sisters::Initialize()
	{
		_Gobjs[0] = new Layana_LongHair;
		_Gobjs[0]->Initialize();

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(eLayerType::Boss, _Gobjs[0]);

		GameObject::Initialize();
	}
	void Layana_Sisters::Update()
	{
		switch (_state)
		{
		case jk::Layana_Sisters::Layana_Sisters_State::Idle:
			idle();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Rush_Ready:
			Rushready();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::RushA:
			Rush_A();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::RushB:
			Rush_B();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::RushC:
			Rush_C();
			break;		

		case jk::Layana_Sisters::Layana_Sisters_State::Rush_End:
			Rush_End();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Dash:
			Dash();
			break;



		case jk::Layana_Sisters::Layana_Sisters_State::BackGround_Idle:
	
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::BackGround_Move:
		
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::BackStep:
	
			break;


		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Ready:
			CrossReady();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Jump:
			CrossJump();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Attack:
			CrossAttack();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Landing:
			CrossLanding();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_End:
			CrossEnd();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground01_Ready:
		
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground02_Attack:

			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground03_Landing:
		
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground04_End:
		
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical00_Jump:
		
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical01_Ready:
		
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical02_Attack:
		
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical03_Landing:
	
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical04_End:
		
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Skill_A_Bullet:
			
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Skill_A_Bullet_End:
			
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Skill_B_RisingPierce:
			
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Skill_C_DimensionPierce:
			
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Intro_Dash:
			
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Intro_Fall:
			
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Intro_Landing:
			
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Awaken:
			
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::AwakenJump:
			
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::AwakenReady:
			
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Die:
			
			break;

		default:
			break;
		}

		GameObject::Update();
	}
	void Layana_Sisters::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Layana_Sisters::Render()
	{
		GameObject::Render();
	}

	void Layana_Sisters::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_Sisters::OnCollisionStay(Collider2D* other)
	{
	}
	void Layana_Sisters::OnCollisionExit(Collider2D* other)
	{
	}


	void Layana_Sisters::idle()
	{
	}
	void Layana_Sisters::Rushready()
	{
	}
	void Layana_Sisters::Rush_A()
	{
	}
	void Layana_Sisters::Rush_B()
	{
	}
	void Layana_Sisters::Rush_C()
	{
	}
	void Layana_Sisters::Rush_End()
	{
	}
	void Layana_Sisters::Dash()
	{
	}
	void Layana_Sisters::CrossJump()
	{
	}
	void Layana_Sisters::CrossReady()
	{
	}
	void Layana_Sisters::CrossAttack()
	{
	}
	void Layana_Sisters::CrossLanding()
	{
	}
	void Layana_Sisters::CrossEnd()
	{
	}
	void Layana_Sisters::die()
	{
	}

	int Layana_Sisters::random(int a, int b)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(a, b);
		int abc = distribution(gen);
		return abc;
	}

}