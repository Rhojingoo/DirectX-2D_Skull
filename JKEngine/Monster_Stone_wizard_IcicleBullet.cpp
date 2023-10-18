#include "Monster_Stone_wizard_IcicleBullet.h"


namespace jk
{
	Monster_Stone_wizard_IcicleBullet::Monster_Stone_wizard_IcicleBullet()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Monster_Stone_wizard_IcicleBullet::~Monster_Stone_wizard_IcicleBullet()
	{
	}
	void Monster_Stone_wizard_IcicleBullet::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(false);
		tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Bullet\\Icicle", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Bullet\\Icicle", this, 1);

		at->PlayAnimation(L"BulletIcicle", true);
		GameObject::Initialize();
	}
	void Monster_Stone_wizard_IcicleBullet::Update()
	{
		if (_bullet_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"BulletIcicle", true);
			if (_dir == -1)
				at->PlayAnimation(L"BulletIcicleR", true);
			_bullet_animation = false;
		}

		if (_Life == true)
		{
			_attackatime += static_cast<float>(Time::DeltaTime());
			if (_attackatime > 3.5)
			{
				this->SetState(eState::Paused);
				_rigidbody->ClearVelocity();
				_attackatime = 0;
				_Life = false;
			}
		}

		GameObject::Update();
	}
	void Monster_Stone_wizard_IcicleBullet::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Monster_Stone_wizard_IcicleBullet::Render()
	{
		GameObject::Render();
	}
	void Monster_Stone_wizard_IcicleBullet::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster_Stone_wizard_IcicleBullet::OnCollisionStay(Collider2D* other)
	{
	}
	void Monster_Stone_wizard_IcicleBullet::OnCollisionExit(Collider2D* other)
	{
	}
	void Monster_Stone_wizard_IcicleBullet::complete()
	{
	}
}