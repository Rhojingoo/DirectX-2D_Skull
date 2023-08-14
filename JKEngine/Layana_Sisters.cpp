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
	Vector3 Layana_Sisters::GroundAttackpos_Right = Vector3(0.f, 0.f, 0.f);
	Vector3 Layana_Sisters::GroundAttackpos_Left = Vector3(0.f, 0.f, 0.f);

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

		case jk::Layana_Sisters::Layana_Sisters_State::FlyDash:
			FlyDash();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::LandingDash:
			LandingDash();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::BackStep:
			BackStep();
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




		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_Ready:
			GroundReady();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_Attack:
			GroundAttack();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_Landing:
			GroundLanding();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_End:
			GroundEnd();
			break;



		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_Jump:
			Vertical_Jump();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_Ready:
			Vertical_Ready();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_Attack:
			Vertical_Attack();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_Landing:
			Vertical_Landing();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Vertical_End:
			Vertical_End();
			break;




		case jk::Layana_Sisters::Layana_Sisters_State::Skill_A_Bullet_Ready:
			Skill_A_Ready();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Skill_A_Bullet:
			Skill_A();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Skill_A_Bullet_End:
			Skill_A_End();
			break;




		case jk::Layana_Sisters::Layana_Sisters_State::Skill_B_RisingPierce:
			Skill_B();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Skill_B_RisingPierce_End:
			Skill_B_End();
			break;
			



		case jk::Layana_Sisters::Layana_Sisters_State::Skill_C_DimensionPierce:
			Skill_C();
			break;





		case jk::Layana_Sisters::Layana_Sisters_State::BackGround_Idle:

			break;

		case jk::Layana_Sisters::Layana_Sisters_State::BackGround_Move:

			break;





		case jk::Layana_Sisters::Layana_Sisters_State::Intro_Dash:
			Intro_Dash();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Intro_Fall:
			Intro_Landing();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Intro_Landing:
			Intro_Fall();
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
	void Layana_Sisters::FlyDash()
	{
	}
	void Layana_Sisters::LandingDash()
	{
	}
	void Layana_Sisters::BackStep()
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
	void Layana_Sisters::GroundReady()
	{
	}
	void Layana_Sisters::GroundAttack()
	{
	}
	void Layana_Sisters::GroundLanding()
	{
	}
	void Layana_Sisters::GroundEnd()
	{
	}
	void Layana_Sisters::Vertical_Jump()
	{
	}
	void Layana_Sisters::Vertical_Ready()
	{
	}
	void Layana_Sisters::Vertical_Attack()
	{
	}
	void Layana_Sisters::Vertical_Landing()
	{
	}
	void Layana_Sisters::Vertical_End()
	{
	}
	void Layana_Sisters::Skill_A_Ready()
	{
	}
	void Layana_Sisters::Skill_A()
	{
	}
	void Layana_Sisters::Skill_A_End()
	{
	}
	void Layana_Sisters::Skill_B()
	{
	}
	void Layana_Sisters::Skill_B_End()
	{
	}
	void Layana_Sisters::Skill_C()
	{
	}
	void Layana_Sisters::Intro_Dash()
	{
	}
	void Layana_Sisters::Intro_Landing()
	{
	}
	void Layana_Sisters::Intro_Fall()
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