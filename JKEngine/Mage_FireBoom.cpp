#include "Mage_FireBoom.h"


namespace jk
{
	Mage_FireBoom::Mage_FireBoom()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}

	Mage_FireBoom::~Mage_FireBoom()
	{
	}

	void Mage_FireBoom::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_collider->SetType(eColliderType::Circle);
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();


		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\Hit_Flame_Short.wav", "Hit_Flame_Short");
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Adventurer\\Mage\\Arson_Explosion.wav", "Arson_Explosion");


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Bullet\\Fire_Boom", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Mage\\Bullet\\Fire_Boom", this, 1);
		at->CompleteEvent(L"BulletFire_Boom") = std::bind(&Mage_FireBoom::complete, this);

		at->PlayAnimation(L"BulletFire_Boom", true);
		GameObject::Initialize();
	}

	void Mage_FireBoom::Update()
	{
		if (_bullet_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"BulletFire_Boom", true);
			if (_dir == -1)
				at->PlayAnimation(L"BulletFire_BoomR", true);
			_bullet_animation = false;
		}
		GameObject::Update();
	}

	void Mage_FireBoom::LateUpdate()
	{
		_collider->SetSize(Vector2(0.5f, 0.5f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}

	void Mage_FireBoom::Render()
	{
		GameObject::Render();
	}

	void Mage_FireBoom::OnCollisionEnter(Collider2D* other)
	{
		if (Player* mGround = dynamic_cast<Player*>(other->GetOwner()))
		{
			as->Play("Hit_Flame_Short");
		}

	}

	void Mage_FireBoom::OnCollisionStay(Collider2D* other)
	{
	}

	void Mage_FireBoom::OnCollisionExit(Collider2D* other)
	{
	}

	void Mage_FireBoom::complete()
	{
		this->SetState(eState::Paused);
	}
}