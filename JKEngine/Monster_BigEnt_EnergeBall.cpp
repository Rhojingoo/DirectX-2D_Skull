#include "Monster_BigEnt_EnergeBall.h"


namespace jk
{
	Monster_BigEnt_EnergeBall::Monster_BigEnt_EnergeBall()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Monster_BigEnt_EnergeBall::~Monster_BigEnt_EnergeBall()
	{
	}
	void Monster_BigEnt_EnergeBall::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\GiganticEnt\\Bullet\\Energe_Ball", this);
		at->PlayAnimation(L"BulletEnerge_Ball", true);
		GameObject::Initialize();
	}
	void Monster_BigEnt_EnergeBall::Update()
	{
		if (_bullet_Life == true)
		{
			_attackatime += Time::DeltaTime();
			if (_attackatime >= 5)
			{
				this->SetState(eState::Paused);
				_attackatime = 0;
			}
		}
		GameObject::Update();
	}
	void Monster_BigEnt_EnergeBall::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Monster_BigEnt_EnergeBall::Render()
	{
		GameObject::Render();
	}
	void Monster_BigEnt_EnergeBall::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster_BigEnt_EnergeBall::OnCollisionStay(Collider2D* other)
	{
	}
	void Monster_BigEnt_EnergeBall::OnCollisionExit(Collider2D* other)
	{
	}
	void Monster_BigEnt_EnergeBall::complete()
	{
	}
}