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
			_Head_Rotation = true;
			_Head_Attack = false;
		}
		else
		{	
			if (_Head_Rotation == true)
			{
				if (mDir == 1)
					tr->AddRotationZ(15);
				else
					tr->AddRotationZ(-15);

				if (_Head_Attack == false)
				{
					if (CurrentPos >= 550)
					{
						_Head_Rotation = false;
						_rigidbody->ClearVelocity();
						_rigidbody->SetFriction(false);
						_rigidbody->SetGravity(false);
						_rigidbody->SetGround(false);
						tr->SetRotationZ(tr->GetRotationZ());
						_Head_Boom = true;
					}
					if (CurrentPos <= -550)
					{
						_Head_Rotation = false;
						_rigidbody->ClearVelocity();
						_rigidbody->SetFriction(false);
						_rigidbody->SetGravity(false);
						_rigidbody->SetGround(false);
						tr->SetRotationZ(tr->GetRotationZ());
						_Head_Boom = true;
					}
				}
				else
				{
					_Head_Rotation = false;
					_rigidbody->ClearVelocity();
					_rigidbody->SetFriction(false);
					_rigidbody->SetGravity(false);
					_rigidbody->SetGround(false);
					tr->SetRotationZ(tr->GetRotationZ());
					_Head_Boom = true;		
					//_Head_Attack = false;
				}
			}
			else
			{
				if (_Head_Boom == true)
				{
					if (mDir == 1)
						tr->AddRotationZ(5);
					else
						tr->AddRotationZ(-5);
					_rigidbody->SetVelocity(Vector2(0.f, 150.f));
					_Head_Boom = false;

				}
				else
				{
					if(_Ground_check == false)
					{
						if (mDir == 1)
							tr->AddRotationZ(5);
						else
							tr->AddRotationZ(-5);
					}
					else
					{
						_rigidbody->ClearVelocity();
					}
				}
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
				_Head_Attack = false;
			}
		}

		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			if (_Ground_check == false)
			{
				_attack = false;
				_rigidbody->SetGround(true);
				_rigidbody->ClearVelocity();
				_Ground_check = true;
				_Head_Attack = false;
			}
		}

		if (Skul_Basic* player = dynamic_cast<Skul_Basic*>(other->GetOwner()))
		{
			_time = 0;
			_Head_Attack = false;
		}
		if (Monster* monster = dynamic_cast<Monster*>(other->GetOwner()))
		{
			_Head_Attack = true;
		}		

		if (Mini_Boss* monster = dynamic_cast<Mini_Boss*>(other->GetOwner()))
		{
			_Head_Attack = true;
		}
	}
	void Skul_head::OnCollisionStay(Collider2D* other)
	{
	}
	void Skul_head::OnCollisionExit(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			_Ground_check = false;
		}

		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			_Ground_check = false;
		}
	}
}