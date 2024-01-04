#include "Yggdrsil_Energy_Corps.h"
#include "Include_Common.h"
#include "Yggdrasil_EnergyBullet_Effect.h"
#include "..\Engine_SOURCE\jkAudioSource.h"

namespace jk
{
	Yggdrsil_Energy_Corps::Yggdrsil_Energy_Corps()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrsil_Energy_Corps::~Yggdrsil_Energy_Corps()
	{
	}
	void Yggdrsil_Energy_Corps::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_collider->SetType(eColliderType::Circle);
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);


		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Hit\\Hit_Energy_Large.wav", "Hit_Energy_Large");


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Bullet\\Energy_Corps", this);
		tr = this->GetComponent<Transform>();


		BulletEffect = new Yggdrasil_EnergyBullet_Effect;
		BulletEffect->Initialize();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(eLayerType::Bullet, BulletEffect);
		Transform* EffectTR = BulletEffect->GetComponent<Transform>();
		EffectTR->SetPosition(tr->GetPosition());
		BulletEffect->SetState(eState::Paused);



		at->PlayAnimation(L"BulletEnergy_Corps", true);
		GameObject::Initialize();
	}
	void Yggdrsil_Energy_Corps::Update()
	{
		if (_effect_switch == true)
			_EffectSwitch = true;
		GameObject::Update();
	}
	void Yggdrsil_Energy_Corps::LateUpdate()
	{
		_collider->SetSize(Vector2(0.75f, 0.75f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrsil_Energy_Corps::Render()
	{
		GameObject::Render();
	}
	void Yggdrsil_Energy_Corps::OnCollisionEnter(Collider2D* other)
	{
	}
	void Yggdrsil_Energy_Corps::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			_rigidbody->SetGround(true);
			_rigidbody->ClearVelocity();

			if (_EffectSwitch == true)
			{				
				Transform* EffectTR = BulletEffect->GetComponent<Transform>();
				EffectTR->SetPosition(tr->GetPosition());
				BulletEffect->SetState(eState::Active);
				as->Play("Hit_Energy_Large");
				_EffectSwitch = false;	
				_effect_switch = false;
			}
		}

		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
			_rigidbody->SetGround(true);
			_rigidbody->ClearVelocity();

			if (_EffectSwitch == true)
			{
				Transform* EffectTR = BulletEffect->GetComponent<Transform>();
				EffectTR->SetPosition(tr->GetPosition());
				BulletEffect->SetState(eState::Active);
				as->Play("Hit_Energy_Large");
				_EffectSwitch = false;
				_effect_switch = false;
			}
		}

	}
	void Yggdrsil_Energy_Corps::OnCollisionExit(Collider2D* other)
	{
	}
}