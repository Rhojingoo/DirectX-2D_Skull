#include "Monster_Tackle_Flash_Effect.h"
#include "Include_Common.h"


namespace jk
{
	Monster_Tackle_Flash_Effect::Monster_Tackle_Flash_Effect()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Monster_Tackle_Flash_Effect::~Monster_Tackle_Flash_Effect()
	{
	}
	void Monster_Tackle_Flash_Effect::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Public\\Effect\\Tackle_Flash", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Public\\Effect\\Tackle_Flash", this, 1);

		at->CompleteEvent(L"EffectTackle_Flash") = std::bind(&Monster_Tackle_Flash_Effect::Compelete, this);
		at->CompleteEvent(L"EffectTackle_FlashR") = std::bind(&Monster_Tackle_Flash_Effect::Compelete, this);

		at->PlayAnimation(L"EffectTackle_Flash", true);

		GameObject::Initialize();
	}
	void Monster_Tackle_Flash_Effect::Update()
	{
		if (_effect_animation == true)
		{
			if (_dir == 1)
				at->PlayAnimation(L"EffectTackle_Flash", true);
			else
				at->PlayAnimation(L"EffectTackle_FlashR", true);
			_effect_animation = false;
		}

		GameObject::Update();
	}
	void Monster_Tackle_Flash_Effect::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Monster_Tackle_Flash_Effect::Render()
	{
		GameObject::Render();
	}
	void Monster_Tackle_Flash_Effect::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster_Tackle_Flash_Effect::OnCollisionStay(Collider2D* other)
	{
	}
	void Monster_Tackle_Flash_Effect::OnCollisionExit(Collider2D* other)
	{
	}
	void Monster_Tackle_Flash_Effect::Compelete()
	{
	}
}