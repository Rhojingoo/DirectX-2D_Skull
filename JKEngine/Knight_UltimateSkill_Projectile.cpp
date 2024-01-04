#include "Knight_UltimateSkill_Projectile.h"
#include "Include_Common.h"
#include "MiniBoss_Bullet_Knight.h"

namespace jk
{
	Knight_UltimateSkill_Projectile::Knight_UltimateSkill_Projectile()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Knight_UltimateSkill_Projectile::~Knight_UltimateSkill_Projectile()
	{
	}
	void Knight_UltimateSkill_Projectile::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Bullet\\UltimateSkill_Projectile", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Knight_male\\Bullet\\UltimateSkill_Projectile", this, 1);


		at->PlayAnimation(L"BulletUltimateSkill_Projectile", true);

		GameObject::Initialize();
	}
	void Knight_UltimateSkill_Projectile::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"BulletUltimateSkill_Projectile", true);
			else
				at->PlayAnimation(L"BulletUltimateSkill_ProjectileR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Knight_UltimateSkill_Projectile::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Knight_UltimateSkill_Projectile::Render()
	{
		GameObject::Render();
	}
	void Knight_UltimateSkill_Projectile::OnCollisionEnter(Collider2D* other)
	{
	}
	void Knight_UltimateSkill_Projectile::OnCollisionStay(Collider2D* other)
	{
	}
	void Knight_UltimateSkill_Projectile::OnCollisionExit(Collider2D* other)
	{
	}
	void Knight_UltimateSkill_Projectile::Compelete()
	{
	}
}