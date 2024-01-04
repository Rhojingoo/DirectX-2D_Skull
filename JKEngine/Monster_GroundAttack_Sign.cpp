#include "Monster_GroundAttack_Sign.h"
#include "Include_Common.h"

namespace jk
{
	Monster_GroundAttack_Sign::Monster_GroundAttack_Sign()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Monster_GroundAttack_Sign::~Monster_GroundAttack_Sign()
	{
	}
	void Monster_GroundAttack_Sign::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Public\\Effect\\GroundAttack_Sign", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Public\\Effect\\GroundAttack_Sign", this, 1);

		at->CompleteEvent(L"EffectGroundAttack_Sign") = std::bind(&Monster_GroundAttack_Sign::Compelete, this);
		at->CompleteEvent(L"EffectGroundAttack_SignR") = std::bind(&Monster_GroundAttack_Sign::Compelete, this);

		at->PlayAnimation(L"EffectGroundAttack_Sign", true);

		GameObject::Initialize();
	}
	void Monster_GroundAttack_Sign::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectGroundAttack_Sign", true);
			else
				at->PlayAnimation(L"EffectGroundAttack_SignR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Monster_GroundAttack_Sign::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Monster_GroundAttack_Sign::Render()
	{
		GameObject::Render();
	}
	void Monster_GroundAttack_Sign::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster_GroundAttack_Sign::OnCollisionStay(Collider2D* other)
	{
	}
	void Monster_GroundAttack_Sign::OnCollisionExit(Collider2D* other)
	{
	}
	void Monster_GroundAttack_Sign::Compelete()
	{
		_effect_end = false;
		this->SetState(eState::Paused);
	}
}