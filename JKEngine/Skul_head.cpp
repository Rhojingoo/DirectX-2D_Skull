#include "Skul_head.h"

namespace jk
{
	bool Skul_head::_attack = false;
	int Skul_head::mDir = 1;
	Skul_head::Skul_head()
		: _state(Skul_Head_State::Move)
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Skill_face"));
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		
		//at = AddComponent<Animator>();
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_head", this);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Player\\Skul_head", this, 1);
		//at->PlayAnimation(L"PlayerSkul_head", false);

		tr = GetComponent<Transform>();
		pos = tr->GetPosition();
	}
	Skul_head::~Skul_head()
	{
	}
	void Skul_head::Initialize()
	{		

		GameObject::Initialize();
	}
	void Skul_head::Update()
	{
		//_velocity = _rigidbody->GetVelocity();

		switch (_state)
		{
		case jk::Skul_head::Skul_Head_State::Idle:idle();
			break;
		case jk::Skul_head::Skul_Head_State::Move:move();
			break;
		case jk::Skul_head::Skul_Head_State::Attack:attack();
			break;
		default:
			break;
		}

		//tr->SetPosition(pos);
		
		GameObject::Update();
	}
	void Skul_head::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Skul_head::Render()
	{
		GameObject::Render();
	}

	void Skul_head::idle()
	{
	}
	void Skul_head::move()
	{
		//_rigidbody->ClearVelocityY();
		//if (mDir == 1 && _velocity.x <= 220.0)
		//{			
		//	_state = Skul_Head_State::Idle;
		//	_rigidbody->SetGround(false);
		//	_rigidbody->ClearVelocityX();
		//	mDir = 1;			
		//}
		//else if (mDir == -1 && _velocity.x >= -220.0)
		//{			
		//	_state = Skul_Head_State::Idle;
		//	_rigidbody->SetGround(false);
		//	_rigidbody->ClearVelocityX();
		//	mDir = -1; 			
		//}
	}
	void Skul_head::attack()
	{
	}
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
			else
			{
				int a;
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