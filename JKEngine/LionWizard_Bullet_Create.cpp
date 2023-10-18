#include "LionWizard_Bullet_Create.h"

namespace jk
{
	LionWizard_Bullet_Create::LionWizard_Bullet_Create()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	LionWizard_Bullet_Create::~LionWizard_Bullet_Create()
	{
	}
	void LionWizard_Bullet_Create::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Bullet\\LionWizard_BulletReady", this, 0,0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Lion_wizard\\Bullet\\LionWizard_BulletReady", this, 1,0.05f);

		at->CompleteEvent(L"BulletLionWizard_BulletReady") = std::bind(&LionWizard_Bullet_Create::Compelete, this);
		at->CompleteEvent(L"BulletLionWizard_BulletReadyR") = std::bind(&LionWizard_Bullet_Create::Compelete, this);

		at->PlayAnimation(L"BulletLionWizard_BulletReady", false);

		GameObject::Initialize();
	}
	void LionWizard_Bullet_Create::Update()
	{
		if (_effect_On == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"BulletLionWizard_BulletReady", true);
			else
				at->PlayAnimation(L"BulletLionWizard_BulletReadyR", true);
			_effect_On = false;
		}
		GameObject::Update();
	}
	void LionWizard_Bullet_Create::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void LionWizard_Bullet_Create::Render()
	{
		GameObject::Render();
	}
	void LionWizard_Bullet_Create::OnCollisionEnter(Collider2D* other)
	{
	}
	void LionWizard_Bullet_Create::OnCollisionStay(Collider2D* other)
	{
	}
	void LionWizard_Bullet_Create::OnCollisionExit(Collider2D* other)
	{
	}
	void LionWizard_Bullet_Create::Compelete()
	{
		_endanimation = true;
		this->SetState(eState::Paused);
	}
}