#include "LionWizard_Bullet.h"

namespace jk
{
	LionWizard_Bullet::LionWizard_Bullet()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	LionWizard_Bullet::~LionWizard_Bullet()
	{
	}
	void LionWizard_Bullet::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_collider->SetType(eColliderType::Circle);
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Bullet\\LionWizard_Bullet", this, 0,0.05);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Bullet\\LionWizard_Bullet", this, 1,0.05);

		at->PlayAnimation(L"BulletLionWizard_Bullet", true);

		GameObject::Initialize();
	}
	void LionWizard_Bullet::Update()
	{
		if (_effect_On == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"BulletLionWizard_Bullet", true);
			else
				at->PlayAnimation(L"BulletLionWizard_BulletR", true);
			_effect_On = false;
		}
		if (_animationswitch == true)
		{
			_attackatime += Time::DeltaTime();
			if (_attackatime > 5)
			{
				_animationswitch = false;
				_attackatime = 0;
				_rigidbody->ClearVelocity();
				_rigidbody->SetGround(true);
				this->SetState(eState::Paused);
			}
		}

		GameObject::Update();
	}
	void LionWizard_Bullet::LateUpdate()
	{
		_collider->SetSize(Vector2(0.35f, 0.35f));
		_collider->SetCenter(Vector2(5.f, 5.f));
		GameObject::LateUpdate();
	}
	void LionWizard_Bullet::Render()
	{
		GameObject::Render();
	}
	void LionWizard_Bullet::OnCollisionEnter(Collider2D* other)
	{
	}
	void LionWizard_Bullet::OnCollisionStay(Collider2D* other)
	{
	}
	void LionWizard_Bullet::OnCollisionExit(Collider2D* other)
	{
	}
	void LionWizard_Bullet::Compelete()
	{
		this->SetState(eState::Paused);
	}
}