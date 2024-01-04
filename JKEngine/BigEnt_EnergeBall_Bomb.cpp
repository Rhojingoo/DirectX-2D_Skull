#include "BigEnt_EnergeBall_Bomb.h"
#include "Include_Common.h"


namespace jk
{
	BigEnt_EnergeBall_Bomb::BigEnt_EnergeBall_Bomb()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	BigEnt_EnergeBall_Bomb::~BigEnt_EnergeBall_Bomb()
	{
	}
	void BigEnt_EnergeBall_Bomb::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Bullet\\Energe_Ball_Bomb", this, 0, 0.075f);
		at->CompleteEvent(L"BulletEnerge_Ball_Bomb") = std::bind(&BigEnt_EnergeBall_Bomb::Compelete, this);

		at->PlayAnimation(L"BulletEnerge_Ball_Bomb", true);
		GameObject::Initialize();
	}
	void BigEnt_EnergeBall_Bomb::Update()
	{
		if (_effect_On == true)
		{
			at->PlayAnimation(L"BulletEnerge_Ball_Bomb", true); 
			_effect_On = false;
		}
		GameObject::Update();
	}
	void BigEnt_EnergeBall_Bomb::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void BigEnt_EnergeBall_Bomb::Render()
	{
		GameObject::Render();
	}
	void BigEnt_EnergeBall_Bomb::OnCollisionEnter(Collider2D* other)
	{
	}
	void BigEnt_EnergeBall_Bomb::OnCollisionStay(Collider2D* other)
	{
	}
	void BigEnt_EnergeBall_Bomb::OnCollisionExit(Collider2D* other)
	{
	}
	void BigEnt_EnergeBall_Bomb::Compelete()
	{
		this->SetState(eState::Paused);
	}
}