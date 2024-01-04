#include "Yggdrasil_Energy_Bomb.h"
#include "Include_Common.h"
#include "Yggdrasil_EnergyBullet_Effect.h"
#include "..\Engine_SOURCE\jkAudioSource.h"

namespace jk
{
	Yggdrasil_Energy_Bomb::Yggdrasil_Energy_Bomb()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Yggdrasil_Energy_Bomb::~Yggdrasil_Energy_Bomb()
	{
	}
	void Yggdrasil_Energy_Bomb::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_collider->SetType(eColliderType::Circle);
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();

		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Hit\\Hit_Energy_Large.wav", "Hit_Energy_Large");



		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Bullet\\Energy_Bomb", this);


		BulletEffect = new Yggdrasil_EnergyBullet_Effect;
		BulletEffect->Initialize();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(eLayerType::Bullet, BulletEffect);
		Transform* EffectTR = BulletEffect->GetComponent<Transform>();
		EffectTR->SetPosition(tr->GetPosition());
		BulletEffect->SetState(eState::Paused);

		at->PlayAnimation(L"BulletEnergy_Bomb", true);
		GameObject::Initialize();
	}
	void Yggdrasil_Energy_Bomb::Update()
	{
		if (_effect_switch == true)
			_EffectSwitch = true;
		GameObject::Update();
	}
	void Yggdrasil_Energy_Bomb::LateUpdate()
	{
		_collider->SetSize(Vector2(0.75f, 0.75f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Yggdrasil_Energy_Bomb::Render()
	{
		GameObject::Render();
	}
	void Yggdrasil_Energy_Bomb::OnCollisionEnter(Collider2D* other)
	{

	}
	void Yggdrasil_Energy_Bomb::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			_rigidbody->SetGround(true);
			_rigidbody->ClearVelocity();

			if (_EffectSwitch == true)
			{
				Transform* EffectTR = BulletEffect->GetComponent<Transform>();
				EffectTR->SetPosition(tr->GetPosition().x, tr->GetPosition().y-20, tr->GetPosition().z);
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
				EffectTR->SetPosition(tr->GetPosition().x, tr->GetPosition().y - 20, tr->GetPosition().z);
				BulletEffect->SetState(eState::Active);
				as->Play("Hit_Energy_Large");
				_EffectSwitch = false;
				_effect_switch = false;
			}
		}

	}
	void Yggdrasil_Energy_Bomb::OnCollisionExit(Collider2D* other)
	{
	}
}