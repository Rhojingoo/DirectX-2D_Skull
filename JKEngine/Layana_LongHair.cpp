#include "Layana_LongHair.h"


namespace jk
{
	Layana_LongHair::Layana_LongHair()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Layana_LongHair::~Layana_LongHair()
	{
	}


	void Layana_LongHair::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);


		tr = GetComponent<Transform>();
		_pos = Vector3(0.f, 0.f, -200.f);		
		_LongHairCreatepos = _pos;
		tr->SetPosition(_pos);
		
		
		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Awaken", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\AwakenJump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\AwakenReady", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\BackGround_Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\BackGround_Move", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\BackStep", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Die", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Intro_Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Intro_Fall", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Intro_Landing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross00_Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross01_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross02_Landing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross03_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross04_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground01_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground02_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground03_Landing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground04_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical00_Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical01_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical02_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical03_Landing", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical04_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Rush_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Rush_Ready", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushA", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushB", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushC", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_A_Bullet", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_A_Bullet_End", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_B_RisingPierce", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_C_DimensionPierce", this);
		
		
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Awaken", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\AwakenJump", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\AwakenReady", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\BackGround_Idle", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\BackGround_Move", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\BackStep", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Dash", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Die", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Idle", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Intro_Dash", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Intro_Fall", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Intro_Landing", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross00_Jump", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross01_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross02_Landing", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross03_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Cross04_Attack", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground01_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground02_Attack", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground03_Landing", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Ground04_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical00_Jump", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical01_Ready", this,1);	
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical03_Landing", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Meteor_Vertical04_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Rush_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Rush_Ready", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushA", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushB", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\RushC", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_A_Bullet", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_A_Bullet_End", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_B_RisingPierce", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Long_hair\\Skill_C_DimensionPierce", this,1);
	
		//bind 부분
		at->CompleteEvent(L"Long_hairRush_Ready") = std::bind(&Layana_LongHair::Complete_RushReady, this);
		at->CompleteEvent(L"Long_hairRushA") = std::bind(&Layana_LongHair::Complete_Rush, this);
		at->CompleteEvent(L"Long_hairRushB") = std::bind(&Layana_LongHair::Complete_Rush, this);
		at->CompleteEvent(L"Long_hairRushC") = std::bind(&Layana_LongHair::Complete_Rush, this);
		at->CompleteEvent(L"Long_hairRush_End") = std::bind(&Layana_LongHair::Complete_RushReady, this);
		at->CompleteEvent(L"Long_hairMeteor_Cross01_Ready") = std::bind(&Layana_LongHair::Complete_CrossJump, this);
		at->CompleteEvent(L"Long_hairMeteor_Cross03_End") = std::bind(&Layana_LongHair::Complete_CrossEnd, this);
		at->CompleteEvent(L"Long_hairMeteor_Ground01_Ready") = std::bind(&Layana_LongHair::Complete_GroundLanding, this);
		at->CompleteEvent(L"Long_hairMeteor_Ground04_End") = std::bind(&Layana_LongHair::CompleteGroundEnd, this);

		
		at->CompleteEvent(L"Long_hairRush_ReadyR") = std::bind(&Layana_LongHair::Complete_RushReady, this);
		at->CompleteEvent(L"Long_hairRushAR") = std::bind(&Layana_LongHair::Complete_Rush, this);
		at->CompleteEvent(L"Long_hairRushBR") = std::bind(&Layana_LongHair::Complete_Rush, this);
		at->CompleteEvent(L"Long_hairRushCR") = std::bind(&Layana_LongHair::Complete_Rush, this);
		at->CompleteEvent(L"Long_hairRush_EndR") = std::bind(&Layana_LongHair::Complete_RushReady, this);
		at->CompleteEvent(L"Long_hairMeteor_Cross01_ReadyR") = std::bind(&Layana_LongHair::Complete_CrossJump, this);
		at->CompleteEvent(L"Long_hairMeteor_Cross03_EndR") = std::bind(&Layana_LongHair::Complete_CrossEnd, this);
		at->CompleteEvent(L"Long_hairMeteor_Ground01_ReadyR") = std::bind(&Layana_LongHair::Complete_GroundLanding, this);
		at->CompleteEvent(L"Long_hairMeteor_Ground04_EndR") = std::bind(&Layana_LongHair::CompleteGroundEnd, this);

		
		at->PlayAnimation(L"Long_hairIdle", true);

		GameObject::Initialize();
	}
	void Layana_LongHair::Update()
	{
		_Playerpos = Player::GetPlayer_Pos();
		_velocity = _rigidbody->GetVelocity();
		_Playerdistance.x = _Playerpos.x - _pos.x;
		_Playerdistance.y = _Playerpos.y - _pos.y;
		if (_Playerdistance.x >= 0)
			mDir = 1;
		else
			mDir = -1;
		_pos = tr->GetPosition();

		switch (_state)
		{
		case jk::Layana_Sisters::Layana_Sisters_State::Idle:
			Layana_LongHair::idle();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Rush_Ready:
			Layana_LongHair::Rushready();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::RushA:
			Layana_LongHair::Rush_A();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::RushB:
			Layana_Sisters::Rush_B();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::RushC:
			Layana_LongHair::Rush_C();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Rush_End:
			Layana_LongHair::Rush_End();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Dash:
			Layana_LongHair::Dash();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::FlyDash:
			Layana_LongHair::FlyDash();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::LandingDash:
			LandingDash();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Ready:
			Layana_LongHair::CrossReady();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Jump:
			Layana_LongHair::CrossJump();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Attack:
			CrossAttack();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_Landing:
			Layana_LongHair::CrossLanding();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Cross_End:
			Layana_LongHair::CrossEnd();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_Ready:
			Layana_LongHair::GroundReady();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_Attack:
			Layana_LongHair::GroundAttack();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_Landing:
			Layana_LongHair::GroundLanding();
			break;

		case jk::Layana_Sisters::Layana_Sisters_State::Meteor_Ground_End:
			Layana_LongHair::GroundEnd();
			break;

		default:
			break;
		}

		tr->SetPosition(_pos);
		GameObject::Update();
	}
	void Layana_LongHair::LateUpdate()
	{
		_collider->SetSize(Vector2(0.1f, 0.55f));
		_collider->SetCenter(Vector2(0.0f, -20.5f));
		GameObject::LateUpdate();
	}
	void Layana_LongHair::Render()
	{
		GameObject::Render();
	}


	void Layana_LongHair::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_LongHair::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();
				_rigidbody->ClearVelocity();
			}
			else
			{
				if (_state == Layana_Sisters_State::Meteor_Cross_Landing)
				{						
					if (mDir == 1)
						at->PlayAnimation(L"Long_hairMeteor_Cross02_Landing", true);
					else
						at->PlayAnimation(L"Long_hairMeteor_Cross02_LandingR", true);			
					tr->SetRotationZ(0.f);
					_CrossMeteorLanding = true;
				}
				if (_state == Layana_Sisters_State::LandingDash)
				{					
					if (mDir == 1)
						at->PlayAnimation(L"Long_hairMeteor_Ground01_Ready", true);
					else
						at->PlayAnimation(L"Long_hairMeteor_Ground01_ReadyR", true);		
					_GroundMeteorLanding = true;
				}
			}
		}
	}
	void Layana_LongHair::OnCollisionExit(Collider2D* other)
	{
	}	

	
	void Layana_LongHair::idle()
	{
		_time += Time::DeltaTime();
		//_SelectAttack = random(0, 2);
		_SelectAttack = 2;

		if (_time >= 5.0)
		{
			if(_SelectAttack == 3)
				Rush_Combo();
			if (_SelectAttack == 1)
				Meteor_Cross_Combo();
			if (_SelectAttack == 2)
			{
				_GroundMeteorSwitch = true; // 이동이 되었을때 공격하는 모션 온
				_state = Layana_Sisters_State::FlyDash;			
				if (mDir == -1)
					at->PlayAnimation(L"Long_hairDash", true);
				else
					at->PlayAnimation(L"Long_hairDashR", true);					
			}			
		}
	}
	void Layana_LongHair::Rushready()
	{		
	}
	void Layana_LongHair::Rush_A()
	{
	}
	void Layana_LongHair::Rush_B()
	{
	}
	void Layana_LongHair::Rush_C()
	{
	}
	void Layana_LongHair::Rush_End()
	{
		_RushSwitch = false;
	}
	void Layana_LongHair::Dash()
	{
		if (!(_Playerdistance.x <= 30 && _Playerdistance.x >= -30))
		{
			if (mDir == 1)
				_pos.x += 250.f * Time::DeltaTime();			
			else
				_pos.x -= 250.f * Time::DeltaTime();			
		}
		else
		{
			if (_RushSwitch == true)
			{
				_state = Layana_Sisters_State::Rush_Ready;
				if (mDir == 1)
					at->PlayAnimation(L"Long_hairRush_Ready", true);
				else
					at->PlayAnimation(L"Long_hairRush_ReadyR", true);
			}		
			if (_CrossMeteorSwitch == true)
			{
				_state = Layana_Sisters_State::Meteor_Cross_Jump;
				if (mDir == 1)
				{
					at->PlayAnimation(L"Long_hairMeteor_Cross00_JumpR", false);
					_rigidbody->SetVelocity(Vector2(250.f, 450.f));
					_rigidbody->SetGround(false);					
				}
				else
				{
					at->PlayAnimation(L"Long_hairMeteor_Cross00_Jump", false);
					_rigidbody->SetVelocity(Vector2(-250.f, 450.f));
					_rigidbody->SetGround(false);					
				}
			}
		}		
	}

	

	void Layana_LongHair::CrossJump()
	{
	
		if (_velocity.y <= -0.1f)
		{
			_rigidbody->ClearVelocity();
			_rigidbody->SetGround(true);

			if (mDir == 1)
				at->PlayAnimation(L"Long_hairMeteor_Cross01_Ready", true);			
			else
				at->PlayAnimation(L"Long_hairMeteor_Cross01_ReadyR", true);
			_state = Layana_Sisters_State::Meteor_Cross_Ready;
			_Ground_check = false;
		}
	}
	void Layana_LongHair::CrossReady()
	{	
	}
	void Layana_LongHair::CrossAttack()
	{
		int a = 0;
		Vector2 attackpoint = Vector2(_Playerpos.x, _Playerpos.y);
		Vector2 attackrotation_PLAYER = Vector2(_Playerpos.x, _Playerpos.y);
		Vector2 rotation = Vector2(_pos.x, _pos.y);
		attackrotation_PLAYER.Normalize();
		rotation.Normalize();

		//if(mDir ==1)
		//	tr->SetRotation(Vector3(0.f, 0.f, 45));
		//else
		//	tr->SetRotation(Vector3(0.f, 0.f, 135));

		float dotProduct = attackrotation_PLAYER.Dot(rotation);
		dotProduct = std::clamp(dotProduct, -1.0f, 1.0f);
		float angle = std::acos(dotProduct);
		float angleInDegrees = angle * (180.0f / XM_PI);
		//tr->SetRotation(Vector3(0.f,0.f, angleInDegrees));
		if (mDir == 1)
			tr->AddRotationZ(45);
		else
			tr->AddRotationZ(-45);		
		
		_rigidbody->SetGround(false);
		_rigidbody->SetVelocity(Vector2(attackrotation_PLAYER.x * -300.f, attackrotation_PLAYER.y * 200));
		_state = Layana_Sisters_State::Meteor_Cross_Landing;
		
	}
	void Layana_LongHair::CrossLanding()
	{
		if (_CrossMeteorLanding == true)
			Complete_CrossLanding();
	}
	void Layana_LongHair::CrossEnd()
	{
	}



	void Layana_LongHair::GroundReady()
	{
	}
	void Layana_LongHair::GroundAttack()
	{
		if (_GroundMeteorAttack_Right == true)
		{
			if (_pos.x >= _LongHairCreatepos.x + 312)
			{
				_rigidbody->ClearVelocity();
				_GroundMeteorAttack_Right = false;
				_state = Layana_Sisters_State::Meteor_Ground_End;
				if(mDir == 1)
					at->PlayAnimation(L"Long_hairMeteor_Ground04_End", true);					
				else
					at->PlayAnimation(L"Long_hairMeteor_Ground04_EndR", true);
			}
		}
		if (_GroundMeteorAttack_Left == true)
		{
			if (_pos.x <= _LongHairCreatepos.x - 312)
			{
				_rigidbody->ClearVelocity();
				_GroundMeteorAttack_Left = false;
				_state = Layana_Sisters_State::Meteor_Ground_End;
				if (mDir == 1)
					at->PlayAnimation(L"Long_hairMeteor_Ground04_End", true);
				else
					at->PlayAnimation(L"Long_hairMeteor_Ground04_EndR", true);
			}
		}			
	}
	void Layana_LongHair::GroundLanding()
	{
	}
	void Layana_LongHair::GroundEnd()
	{
	}
	void Layana_LongHair::FlyDash()
	{
		if (_GroundMeteorSwitch == true)
		{
			GroundAttackpos_Right;
			if (mDir == -1)
			{
				if (_pos.x < _LongHairCreatepos.x + 700)
					_pos.x += 750.f * Time::DeltaTime();
				if (_pos.y < _LongHairCreatepos.y + 150)
					_pos.y += 150.f * Time::DeltaTime();
			}
			else
			{
				if (_pos.x > _LongHairCreatepos.x - 700)
					_pos.x -= 750.f * Time::DeltaTime();
				if (_pos.y < _LongHairCreatepos.y + 150)
					_pos.y += 150.f * Time::DeltaTime();
			}
			if (_pos.y >= _LongHairCreatepos.y + 150.f)
			{
				_state = Layana_Sisters_State::LandingDash;
				_Ground_check = false;
				_rigidbody->SetGround(false);
				if (mDir == -1)
				{
					_rigidbody->SetVelocity(Vector2(-650.f, -150.f));
					at->PlayAnimation(L"Long_hairDashR", true);
				}
				else
				{
					_rigidbody->SetVelocity(Vector2(650.f, -150.f));
					at->PlayAnimation(L"Long_hairDash", true);
				}
			}
		}

	}
	void Layana_LongHair::LandingDash()
	{
		_Attacktime += Time::DeltaTime();
		if (_GroundMeteorLanding == true)
		{
			if (_Attacktime >= 1.f)
			{
				_state = Layana_Sisters_State::Meteor_Ground_Attack;

				if (mDir == 1)
				{
					at->PlayAnimation(L"Long_hairMeteor_Ground02_Attack", true);
					_rigidbody->SetVelocity(Vector2(700.f, 0.f));
					_GroundMeteorAttack_Right = true;
				}
				else
				{
					at->PlayAnimation(L"Long_hairMeteor_Ground02_AttackR", true);
					_rigidbody->SetVelocity(Vector2(-700.f, 0.f));
					_GroundMeteorAttack_Left = true;
				}
				_Attacktime = 0;
			}
		}
	}



	void Layana_LongHair::Rush_Combo()
	{
		_RushSwitch = true;
		_Rushnumber = 0;
		if (_Playerdistance.x <= 30 && _Playerdistance.x >= -30)
		{
			_state = Layana_Sisters_State::Rush_Ready;
			if (mDir == 1)
				at->PlayAnimation(L"Long_hairRush_Ready", true);
			else
				at->PlayAnimation(L"Long_hairRush_ReadyR", true);
		}
		else
		{
			_state = Layana_Sisters_State::Dash;
			if (mDir == 1)
				at->PlayAnimation(L"Long_hairDash", true);
			else
				at->PlayAnimation(L"Long_hairDashR", true);
		}
		
	
	}
	void Layana_LongHair::Complete_Rush()
	{
		
		if (_Rushnumber >= 3)
		{
			_state = Layana_Sisters_State::Rush_End;
			if (mDir == 1)
				at->PlayAnimation(L"Long_hairRush_End", true);
			else
				at->PlayAnimation(L"Long_hairRush_EndR", true);
		}
		else
		{		
			_state = Layana_Sisters_State::Rush_Ready;
			if (mDir == 1)
				at->PlayAnimation(L"Long_hairRush_Ready", true);
			else
				at->PlayAnimation(L"Long_hairRush_ReadyR", true);
		}
	}
	void Layana_LongHair::Complete_RushReady()
	{		
		if (_Rushnumber == 0)
		{
			_state = Layana_Sisters_State::RushA;
			if (mDir == 1)
				at->PlayAnimation(L"Long_hairRushA", true);
			else
				at->PlayAnimation(L"Long_hairRushAR", true);
		}
		if (_Rushnumber == 1)
		{
			_state = Layana_Sisters_State::RushB;
			if (mDir == 1)
				at->PlayAnimation(L"Long_hairRushB", true);
			else
				at->PlayAnimation(L"Long_hairRushBR", true);
		}
		if (_Rushnumber == 2)
		{
			_state = Layana_Sisters_State::RushC;
			if (mDir == 1)
				at->PlayAnimation(L"Long_hairRushC", true);
			else
				at->PlayAnimation(L"Long_hairRushCR", true);
		}
		if (_Rushnumber >= 3)
		{
			_state = Layana_Sisters_State::Idle;
			if (mDir == 1)
				at->PlayAnimation(L"Long_hairIdle", true);
			else
				at->PlayAnimation(L"Long_hairIdleR", true);			
			_time = 0;
		}
		_Rushnumber++;
	}


	void Layana_LongHair::Meteor_Cross_Combo()
	{
		_CrossMeteorSwitch = true;
		if (_Playerdistance.x <= 30 && _Playerdistance.x >= -30)
		{
			_state = Layana_Sisters_State::Meteor_Cross_Jump;
			if (mDir == 1)
			{
				at->PlayAnimation(L"Long_hairMeteor_Cross00_JumpR", false);
				_rigidbody->SetVelocity(Vector2(250.f, 300.f));
				_rigidbody->SetGround(false);
			}
			else
			{
				at->PlayAnimation(L"Long_hairMeteor_Cross00_Jump", false);
				_rigidbody->SetVelocity(Vector2(-250.f, 300.f));
				_rigidbody->SetGround(false);
			}
		}
		else
		{
			_state = Layana_Sisters_State::Dash;
			if (mDir == 1)
				at->PlayAnimation(L"Long_hairDash", true);
			else
				at->PlayAnimation(L"Long_hairDashR", true);
		}
	}
	void Layana_LongHair::Complete_CrossJump()
	{
		_state = Layana_Sisters_State::Meteor_Cross_Attack;
		if(mDir == 1)
		at->PlayAnimation(L"Long_hairMeteor_Cross04_AttackR", false);		
		else
		at->PlayAnimation(L"Long_hairMeteor_Cross04_Attack", false);
	}
	void Layana_LongHair::Complete_CrossLanding()
	{
		if (mDir)
			at->PlayAnimation(L"Long_hairMeteor_Cross03_End", true);
		else
			at->PlayAnimation(L"Long_hairMeteor_Cross03_EndR", true);
		_state = Layana_Sisters_State::Meteor_Cross_End;		
	}
	void Layana_LongHair::Complete_CrossEnd()
	{
		if (mDir)
			at->PlayAnimation(L"Long_hairIdle", true);
		else
			at->PlayAnimation(L"Long_hairIdleR", true);
		_state = Layana_Sisters_State::Idle;
		_time = 0;
		_CrossMeteorSwitch = false;
		_CrossMeteorLanding = false;
	}

	void Layana_LongHair::Complete_GroundLanding()
	{		
	}
	void Layana_LongHair::CompleteGroundEnd()
	{
		if (mDir==1)
			at->PlayAnimation(L"Long_hairIdle", true);
		else
			at->PlayAnimation(L"Long_hairIdleR", true);
		_state = Layana_Sisters_State::Idle;
		_time = 0;

		_GroundMeteorSwitch = false;
		_GroundMeteorLanding = false;
		_GroundMeteorAttack_Right = false;
		_GroundMeteorAttack_Left = false;
	}


	void Layana_LongHair::die()
	{
	}
}