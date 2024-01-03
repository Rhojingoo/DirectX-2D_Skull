#include "Dark_DimensionPierce_Attack.h"
#include "Include_Common.h"


namespace jk
{
	int Dark_DimensionPierce_Attack::mDir = 1;

	Dark_DimensionPierce_Attack::Dark_DimensionPierce_Attack()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Dark_DimensionPierce_Attack::~Dark_DimensionPierce_Attack()
	{
	}
	void Dark_DimensionPierce_Attack::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		tr = this->GetComponent<Transform>();
		at = AddComponent<Animator>();

		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_DimensionPierce_Attack", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_DimensionPierce_Attack", this, 1);
		at->CompleteEvent(L"EffectDark_DimensionPierce_Attack") = std::bind(&Dark_DimensionPierce_Attack::Compelete, this);
		at->CompleteEvent(L"EffectDark_DimensionPierce_AttackR") = std::bind(&Dark_DimensionPierce_Attack::Compelete, this);

		at->PlayAnimation(L"EffectDark_DimensionPierce_Attack", true);


		GameObject::Initialize();
	}
	void Dark_DimensionPierce_Attack::Update()
	{
		if (_SwitchOn == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"EffectDark_DimensionPierce_Attack", true);
			else
				at->PlayAnimation(L"EffectDark_DimensionPierce_AttackR", true);
			_SwitchOn = false;
		}
		GameObject::Update();
	}
	void Dark_DimensionPierce_Attack::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Dark_DimensionPierce_Attack::Render()
	{
		GameObject::Render();
	}
	void Dark_DimensionPierce_Attack::OnCollisionEnter(Collider2D* other)
	{
	}
	void Dark_DimensionPierce_Attack::OnCollisionStay(Collider2D* other)
	{
	}
	void Dark_DimensionPierce_Attack::OnCollisionExit(Collider2D* other)
	{
	}
	void Dark_DimensionPierce_Attack::Compelete()
	{
		_SwitchOff = true;
		this->SetState(eState::Paused);
	}
}