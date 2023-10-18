#include "Layana_Ground_Thunder.h"


namespace jk
{
	int	Layana_Ground_Thunder::mDir = 1;
	bool Layana_Ground_Thunder::_effect_switch = false;
	bool Layana_Ground_Thunder::_bulletoff = false;

	Layana_Ground_Thunder::Layana_Ground_Thunder()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Layana_Ground_Thunder::~Layana_Ground_Thunder()
	{
	}
	void Layana_Ground_Thunder::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_DarkMeteorGround_Thunder.wav", "Leiana_DarkMeteorGround_Thunder");


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Dark_Ground_Thunder", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Dark_Ground_Thunder", this, 1);


		at->CompleteEvent(L"BulletDark_Ground_Thunder") = std::bind(&Layana_Ground_Thunder::Compelete_Pierce, this);
		at->CompleteEvent(L"BulletDark_Ground_ThunderR") = std::bind(&Layana_Ground_Thunder::Compelete_Pierce, this);

		at->PlayAnimation(L"BulletDark_Ground_Thunder", true);
		GameObject::Initialize();
	}
	void Layana_Ground_Thunder::Update()
	{
		if (_effect_switch == true)
		{
			//if (mDir == 1)
			//	at->PlayAnimation(L"BulletDark_Ground_Thunder", true);
			//else
			//	at->PlayAnimation(L"BulletDark_Ground_ThunderR", true);

			as->Play("Leiana_DarkMeteorGround_Thunder");
			_effect_switch = false;
		}

		GameObject::Update();
	}
	void Layana_Ground_Thunder::LateUpdate()
	{
		_collider->SetSize(Vector2(0.25f, 0.95f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Layana_Ground_Thunder::Render()
	{
		GameObject::Render();
	}
	void Layana_Ground_Thunder::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_Ground_Thunder::OnCollisionStay(Collider2D* other)
	{
	}
	void Layana_Ground_Thunder::OnCollisionExit(Collider2D* other)
	{
	}
	void Layana_Ground_Thunder::Compelete_Pierce()
	{
		_bulletoff = true;
		this->SetState(eState::Paused);
	}
}