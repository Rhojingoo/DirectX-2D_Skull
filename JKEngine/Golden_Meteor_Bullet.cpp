#include "Golden_Meteor_Bullet.h"
#include "Include_Common.h"

namespace jk
{
	Golden_Meteor_Bullet::Golden_Meteor_Bullet()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Golden_Meteor_Bullet::~Golden_Meteor_Bullet()
	{
	}
	void Golden_Meteor_Bullet::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Golden_Meteor_Effect", this, 0, 0.05f);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Golden_Meteor_Effect", this, 1, 0.05f);

		at->PlayAnimation(L"BulletGolden_Meteor_Effect", true);
		GameObject::Initialize();
	}
	void Golden_Meteor_Bullet::Update()
	{
		if (_effect_switch == true)
		{			
			at->PlayAnimation(L"BulletGolden_Meteor_Effect", true);
			_effect_switch = false;
		}

		GameObject::Update();
	}
	void Golden_Meteor_Bullet::LateUpdate()
	{
		_collider->SetSize(Vector2(0.65f, 0.35f));
		_collider->SetCenter(Vector2(0.0f, -25.5f));
		GameObject::LateUpdate();
	}
	void Golden_Meteor_Bullet::Render()
	{
		GameObject::Render();
	}
	void Golden_Meteor_Bullet::OnCollisionEnter(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			this->SetState(eState::Paused);
		}
	}
	void Golden_Meteor_Bullet::OnCollisionStay(Collider2D* other)
	{
	}
	void Golden_Meteor_Bullet::OnCollisionExit(Collider2D* other)
	{
	}
}