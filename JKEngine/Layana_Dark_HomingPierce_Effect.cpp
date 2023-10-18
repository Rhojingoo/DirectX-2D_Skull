#include "Layana_Dark_HomingPierce_Effect.h"

namespace jk
{
	Layana_Dark_HomingPierce_Effect::Layana_Dark_HomingPierce_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Layana_Dark_HomingPierce_Effect::~Layana_Dark_HomingPierce_Effect()
	{
	}
	void Layana_Dark_HomingPierce_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		//미사일 생성
	
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Effect\\Dark_HomingPierce_Effect_Sign", this,0, 0.1f,Vector2(0.35f,0.f));

		at->PlayAnimation(L"EffectDark_HomingPierce_Effect_Sign", false);
		GameObject::Initialize();
	}
	void Layana_Dark_HomingPierce_Effect::Update()
	{
		if (_effect_switch == true)
		{
			//this->SetState(eState::Paused);
			_effect_switch = false;
		}

		GameObject::Update();
	}
	void Layana_Dark_HomingPierce_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Layana_Dark_HomingPierce_Effect::Render()
	{
		GameObject::Render();
	}
	void Layana_Dark_HomingPierce_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_Dark_HomingPierce_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Layana_Dark_HomingPierce_Effect::OnCollisionExit(Collider2D* other)
	{
	}

}