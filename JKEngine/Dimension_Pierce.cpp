#include "Dimension_Pierce.h"


namespace jk
{
	 int Dimension_Pierce::mDir = 1;
	 bool Dimension_Pierce::_effect_switch = false;;
	Dimension_Pierce::Dimension_Pierce()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Dimension_Pierce::~Dimension_Pierce()
	{
	}
	void Dimension_Pierce::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Dimension_Pierce", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Dimension_Pierce", this, 1);

		at->PlayAnimation(L"BulletDimension_Pierce", false);
		GameObject::Initialize();
	}
	void Dimension_Pierce::Update()
	{
		if (_effect_switch == true)
		{
			if (mDir == 1)
				at->PlayAnimation(L"BulletDimension_Pierce", false);
			else
				at->PlayAnimation(L"BulletDimension_PierceR", false);
			_effect_switch = false;
		}
		

		GameObject::Update();
	}
	void Dimension_Pierce::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Dimension_Pierce::Render()
	{
		GameObject::Render();
	}
	void Dimension_Pierce::OnCollisionEnter(Collider2D* other)
	{
	}
	void Dimension_Pierce::OnCollisionStay(Collider2D* other)
	{
	}
	void Dimension_Pierce::OnCollisionExit(Collider2D* other)
	{
	}
}