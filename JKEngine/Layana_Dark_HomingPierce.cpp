#include "Layana_Dark_HomingPierce.h"


namespace jk
{
	Layana_Dark_HomingPierce::Layana_Dark_HomingPierce()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Layana_Dark_HomingPierce::~Layana_Dark_HomingPierce()
	{
	}
	void Layana_Dark_HomingPierce::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		//미사일 생성
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Dark_HomingPierce_Begin", this,0, 0.03f);
		at->CompleteEvent(L"BulletDark_HomingPierce_Begin") = std::bind(&Layana_Dark_HomingPierce::Compelete_Begin, this);

		
		// 생성후 발사까지 진행 애니메이션
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Dark_HomingPierce", this,0, 0.03f);


		//발사후 애니메이션
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Dark_HomingPierce_End", this,0,0.03f);
		at->CompleteEvent(L"BulletDark_HomingPierce_End") = std::bind(&Layana_Dark_HomingPierce::Compelete_Pierce, this);

		at->PlayAnimation(L"BulletDark_HomingPierce_Begin", true);
		GameObject::Initialize();
	}
	void Layana_Dark_HomingPierce::Update()
	{

		if (_effect_switch == true)
		{
			at->PlayAnimation(L"BulletDark_HomingPierce_Begin", true);
			_effect_switch = false;
		}

		if (_bulletoff == true)
		{
			at->PlayAnimation(L"BulletDark_HomingPierce_End", true);			
			_bulletoff = false;
		}


		GameObject::Update();
	}
	void Layana_Dark_HomingPierce::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Layana_Dark_HomingPierce::Render()
	{
		GameObject::Render();
	}
	void Layana_Dark_HomingPierce::OnCollisionEnter(Collider2D* other)
	{
	}
	void Layana_Dark_HomingPierce::OnCollisionStay(Collider2D* other)
	{
	}
	void Layana_Dark_HomingPierce::OnCollisionExit(Collider2D* other)
	{
	}
	void Layana_Dark_HomingPierce::Compelete_Begin()
	{
		at->PlayAnimation(L"BulletDark_HomingPierce", true);
	}
	void Layana_Dark_HomingPierce::Compelete_Pierce()
	{
		_effect_switch = false;
		this->SetState(eState::Paused);
	}
}