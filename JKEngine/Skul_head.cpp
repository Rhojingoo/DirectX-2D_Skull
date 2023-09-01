#include "Skul_head.h"

namespace jk
{

	Skul_head::Skul_head()		
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Basic_Skul"));
	}
	Skul_head::~Skul_head()
	{
	}
	void Skul_head::Initialize()
	{		
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_head", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_head", this, 1);
		at->PlayAnimation(L"PlayerSkul_head", true);

		tr = GetComponent<Transform>();
		pos = tr->GetPosition();

		GameObject::Initialize();
	}
	void Skul_head::Update()
	{
		pos = tr->GetPosition();
		float CurrentPos = pos.x - _Before_Attack_Pos.x;

		if (SetHead == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"PlayerSkul_head", true);	
			else			
				at->PlayAnimation(L"PlayerSkul_headR", true);			
			
			Head_Life = true;
			SetHead = false;
		}
		else
		{		
			if (mDir == 1)
				tr->AddRotationZ(15);
			else
				tr->AddRotationZ(-15);

			if (CurrentPos >= 550)
			{
				_rigidbody->ClearVelocity();	
				_rigidbody->SetFriction(false);
				_rigidbody->SetGravity(false);
				_rigidbody->SetGround(false);
				tr->SetRotationZ(tr->GetRotationZ());				
			}			
			if (CurrentPos <= -550)
			{
				_rigidbody->ClearVelocity();
				_rigidbody->SetFriction(false);
				_rigidbody->SetGravity(false);
				_rigidbody->SetGround(false);
				tr->SetRotationZ(tr->GetRotationZ());				
			}
			Head_Life = false;
		}
		
		GameObject::Update();
	}
	void Skul_head::LateUpdate()
	{
		_collider->SetSize(Vector2(0.1f, 0.5f));
		_collider->SetCenter(Vector2(0.0f, -2.5f));
		GameObject::LateUpdate();
	}
	void Skul_head::Render()
	{
		GameObject::Render();
	}

	//void Skul_head::idle()
	//{
	//}
	//void Skul_head::move()
	//{
	//	//_rigidbody->ClearVelocityY();
	//	//if (mDir == 1 && _velocity.x <= 220.0)
	//	//{			
	//	//	_state = Skul_Head_State::Idle;
	//	//	_rigidbody->SetGround(false);
	//	//	_rigidbody->ClearVelocityX();
	//	//	mDir = 1;			
	//	//}
	//	//else if (mDir == -1 && _velocity.x >= -220.0)
	//	//{			
	//	//	_state = Skul_Head_State::Idle;
	//	//	_rigidbody->SetGround(false);
	//	//	_rigidbody->ClearVelocityX();
	//	//	mDir = -1; 			
	//	//}
	//}
	//void Skul_head::attack()
	//{
	//}

	void Skul_head::OnCollisionEnter(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_attack = false;
				_rigidbody->SetGround(true);
				_rigidbody->ClearVelocity();
				_Ground_check = true;
			}
		}
	}
	void Skul_head::OnCollisionStay(Collider2D* other)
	{
	}
	void Skul_head::OnCollisionExit(Collider2D* other)
	{
	}
}