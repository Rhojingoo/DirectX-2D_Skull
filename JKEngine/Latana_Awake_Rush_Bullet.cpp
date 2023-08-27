#include "Latana_Awake_Rush_Bullet.h"


namespace jk
{

	int	Latana_Awake_Rush_Bullet::mDir =1;
	bool Latana_Awake_Rush_Bullet::_effect_switch = false;
	bool Latana_Awake_Rush_Bullet::_bulletoff = false;
	Latana_Awake_Rush_Bullet::Latana_Awake_Rush_Bullet()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Latana_Awake_Rush_Bullet::~Latana_Awake_Rush_Bullet()
	{
	}
	void Latana_Awake_Rush_Bullet::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Dark_DimensionRush_Impact", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Dark_DimensionRush_Impact", this, 1);


		at->CompleteEvent(L"BulletDark_DimensionRush_Impact") = std::bind(&Latana_Awake_Rush_Bullet::Compelete_Pierce, this);
		at->CompleteEvent(L"BulletDark_DimensionRush_ImpactR") = std::bind(&Latana_Awake_Rush_Bullet::Compelete_Pierce, this);

		at->PlayAnimation(L"BulletDark_DimensionRush_Impact", true);
		GameObject::Initialize();
	}
	void Latana_Awake_Rush_Bullet::Update()
	{
		if (_effect_switch == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"BulletDark_DimensionRush_Impact", true);
			else
				at->PlayAnimation(L"BulletDark_DimensionRush_ImpactR", true);
			_effect_switch = false;
		}

		GameObject::Update();
	}
	void Latana_Awake_Rush_Bullet::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Latana_Awake_Rush_Bullet::Render()
	{
		GameObject::Render();
	}
	void Latana_Awake_Rush_Bullet::OnCollisionEnter(Collider2D* other)
	{
	}
	void Latana_Awake_Rush_Bullet::OnCollisionStay(Collider2D* other)
	{
	}
	void Latana_Awake_Rush_Bullet::OnCollisionExit(Collider2D* other)
	{
	}
	void Latana_Awake_Rush_Bullet::Compelete_Pierce()
	{
		_bulletoff = true;
		this->SetState(eState::Paused);
	}
}