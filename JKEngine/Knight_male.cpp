#include "Knight_male.h"


namespace jk
{
	int Knight_male::mDir = 1;
	bool Knight_male::_switch = false;
	GameObject* Knight_male::oWner = nullptr;

	Knight_male::Knight_male()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Knight_male"));
	}
	Knight_male::~Knight_male()
	{
	}
	void Knight_male::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		//_playerpos = oWner->GetComponent<Transform>()->GetPosition();

		//Skul_Head = new Skul_head();
		//Skul_Head->Initialize();
		//Scene* scene = SceneManager::GetActiveScene();
		//scene->AddGameObject(eLayerType::Item, Skul_Head);
		//Transform* tr_head = Skul_Head->GetComponent<Transform>();
		//tr_head->SetPosition(Vector3(pos.x, pos.y, -250.f));
		//Skul_Head->GetComponent<Transform>()->SetScale(Vector3(15.f, 13.f, 0.f));
		//Skul_Head->SetState(eState::Paused);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_A", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_B", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_C", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_D", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_E", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\BackDash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Dash", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Die", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\EnergeBall", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Explosion_Loop", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Glorggy", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Hit", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Idle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Intro", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Jump", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Potion", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Stinger", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Stinger_Ready", this);

		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_A", this,1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_B", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_C", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_D", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Attack_E", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\BackDash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Dash", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Die", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\EnergeBall", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Explosion_Loop", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Glorggy", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Hit", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Idle", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Intro", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Jump", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Potion", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Stinger", this, 1);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Stinger_Ready", this, 1);


		at->PlayAnimation(L"Knight_maleAttack_A", true);
		GameObject::Initialize();
	}
	void Knight_male::Update()
	{
		GameObject::Update();
	}
	void Knight_male::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Knight_male::Render()
	{
		GameObject::Render();
	}
	void Knight_male::OnCollisionEnter(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{

			if (_Ground_check == false)
			{
				_fallcheck = 0;	_jump = 0;
				_rigidbody->SetGround(true);
				_Ground_check = true;
				_Ground_check = _rigidbody->GetGround();
				
				//if (_State == Skul_Basic_State::JumpAttack || _State == Skul_Basic_State::Fall || _State == Skul_Basic_State::Falling)
				//{
				//	_State = Skul_Basic_State::Idle;
				//	if (mDir == 1)
				//		at->PlayAnimation(L"Skul_BasicIdle", true);
				//	else
				//		at->PlayAnimation(L"Skul_BasicIdleR", true);
				//}
			}
			else
			{
				//if (Input::GetKeyDown(eKeyCode::Z))
				//{
				//	_State = Skul_Basic_State::Dash;
				//	if (mDir == 1)
				//	{
				//		at->PlayAnimation(L"Skul_BasicDash", true);
				//		if (_Skulhead == true)
				//			at->PlayAnimation(L"NoHeadDash", true);
				//		_rigidbody->SetVelocity(Vector2(250.f, 0.f));
				//		mDir = 1;
				//	}
				//	if (mDir == -1)
				//	{
				//		at->PlayAnimation(L"Skul_BasicDashR", true);
				//		if (_Skulhead == true)
				//			at->PlayAnimation(L"NoHeadDashR", true);
				//		_rigidbody->SetVelocity(Vector2(-250.f, 0.f));
				//		mDir = -1;
				//	}
				//}
			}
		}
	}
	void Knight_male::OnCollisionStay(Collider2D* other)
	{
	}
	void Knight_male::OnCollisionExit(Collider2D* other)
	{
	}
}