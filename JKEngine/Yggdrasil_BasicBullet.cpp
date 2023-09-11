#include "Yggdrasil_BasicBullet.h"

namespace jk
{
	Vector3 Yggdrasil_BasicBullet::_pos = Vector3(0.f,0.f,0.f);

	Yggdrasil_BasicBullet::Yggdrasil_BasicBullet()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_BasicBullet::~Yggdrasil_BasicBullet()
	{
	}
	void Yggdrasil_BasicBullet::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_collider->SetType(eColliderType::Circle);
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		//_pos = Vector3(GetPos().x - 150.f, GetPos().y - 100, -205.f);
		//tr = GetComponent<Transform>();
		//tr->SetPosition(Vector3(_pos));

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Bullet\\Basic_Bullet", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Bullet\\Energy_Bomb", this);


		at->PlayAnimation(L"BulletBasic_Bullet", true);
		GameObject::Initialize();
	}
	void Yggdrasil_BasicBullet::Update()
	{
		GameObject::Update();
	}
	void Yggdrasil_BasicBullet::LateUpdate()
	{
		_collider->SetSize(Vector2(0.5f, 0.5f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_BasicBullet::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_BasicBullet::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrasil_BasicBullet::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_BasicBullet::OnCollisionExit(Collider2D* other)
	{
	}
}