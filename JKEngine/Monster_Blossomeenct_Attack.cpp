#include "Monster_Blossomeenct_Attack.h"

namespace jk
{
	Monster_Blossomeenct_Attack::Monster_Blossomeenct_Attack()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Monster_Blossomeenct_Attack::~Monster_Blossomeenct_Attack()
	{
	}
	void Monster_Blossomeenct_Attack::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Bullet\\BlossomEnt_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\BlossomEnt\\Bullet\\BlossomEnt_Attack", this,1);

		at->CompleteEvent(L"BulletBlossomEnt_Attack") = std::bind(&Monster_Blossomeenct_Attack::complete, this);
		at->CompleteEvent(L"BulletBlossomEnt_AttackR") = std::bind(&Monster_Blossomeenct_Attack::complete, this);

		at->PlayAnimation(L"BulletBlossomEnt_Attack", true);
		GameObject::Initialize();
	}
	void Monster_Blossomeenct_Attack::Update()
	{
		if (_bullet_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"BulletBlossomEnt_Attack", true);
			else
				at->PlayAnimation(L"BulletBlossomEnt_AttackR", true);
			_bullet_animation = false;
		}

		GameObject::Update();
	}
	void Monster_Blossomeenct_Attack::LateUpdate()
	{
		_collider->SetSize(Vector2(0.85f, 0.85f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Monster_Blossomeenct_Attack::Render()
	{
		GameObject::Render();
	}
	void Monster_Blossomeenct_Attack::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster_Blossomeenct_Attack::OnCollisionStay(Collider2D* other)
	{
	}
	void Monster_Blossomeenct_Attack::OnCollisionExit(Collider2D* other)
	{
	}
	void Monster_Blossomeenct_Attack::complete()
	{
		_bullet_Life = false;
		this->SetState(eState::Paused); 
	}
}