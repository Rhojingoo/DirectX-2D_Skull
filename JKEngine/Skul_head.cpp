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
					_time += Time::DeltaTime();
					if (_time < 0.5)
					{
						if (mDir == 1)
							tr->AddRotationZ(5);
						else
							tr->AddRotationZ(-5);
					}
					else
					{
						_rigidbody->ClearVelocity();
						//if (_Head_Attack == true)
						//	_Head_Attack = false;
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

		if (Monster_Hammer* monster = dynamic_cast<Monster_Hammer*>(other->GetOwner()))
		{
			_Head_Attack = true;
		}
		
		if (Monster_warrior* monster = dynamic_cast<Monster_warrior*>(other->GetOwner()))
		{
			_Head_Attack = true;
		}

		if (Stone_wizard* monster = dynamic_cast<Stone_wizard*>(other->GetOwner()))
		{
			_Head_Attack = true;
		}

		if (Monster_GreenTree* monster = dynamic_cast<Monster_GreenTree*>(other->GetOwner()))
		{
			_Head_Attack = true;
		}

		if (Monster_BlossomEnt* monster = dynamic_cast<Monster_BlossomEnt*>(other->GetOwner()))
		{
			_Head_Attack = true;
		}

		if (Monster_BigEnt* monster = dynamic_cast<Monster_BigEnt*>(other->GetOwner()))
		{
			_Head_Attack = true;
		}

		if (Monster_Goldwarrior* monster = dynamic_cast<Monster_Goldwarrior*>(other->GetOwner()))
		{
			_Head_Attack = true;
		}

		if (Monster_GoldHammer* monster = dynamic_cast<Monster_GoldHammer*>(other->GetOwner()))
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
	}
}