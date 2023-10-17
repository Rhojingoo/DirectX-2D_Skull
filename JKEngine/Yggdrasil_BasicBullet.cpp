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
		tr = this->GetComponent<Transform>();

		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Skul\\Hit\\Hit_Energy_Medium.wav", "Hit_Energy_Small");



		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Bullet\\Basic_Bullet", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Yggdrasil\\Bullet\\Energy_Bomb", this);


		
		BulletEffect = new Yggdrasil_basicBullet_Effect;
		BulletEffect->Initialize();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(eLayerType::Bullet, BulletEffect);
		Transform* EffectTR = BulletEffect->GetComponent<Transform>();
		EffectTR->SetPosition(tr->GetPosition());
		BulletEffect->SetState(eState::Paused);


		at->PlayAnimation(L"BulletBasic_Bullet", true);
		GameObject::Initialize();
	}
	void Yggdrasil_BasicBullet::Update()
	{
		if (_effect_switch == true)
			_EffectSwitch = true;
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
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			_rigidbody->SetGround(true);
			_rigidbody->ClearVelocity();

			if (_EffectSwitch == true)
			{
				Transform* EffectTR = BulletEffect->GetComponent<Transform>();
				EffectTR->SetPosition(tr->GetPosition().x, tr->GetPosition().y - 20, tr->GetPosition().z);
				BulletEffect->SetState(eState::Active);
				as->Play("Hit_Energy_Small");
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
				as->Play("Hit_Energy_Small");
				_EffectSwitch = false;
				_effect_switch = false;
			}
		}

		if (Player* mGround = dynamic_cast<Player*>(other->GetOwner()))
		{
			_rigidbody->SetGround(true);
			_rigidbody->ClearVelocity();

			if (_EffectSwitch == true)
			{
				Transform* EffectTR = BulletEffect->GetComponent<Transform>();
				EffectTR->SetPosition(tr->GetPosition().x, tr->GetPosition().y - 20, tr->GetPosition().z);
				BulletEffect->SetState(eState::Active);
				as->Play("Hit_Energy_Small");
				_EffectSwitch = false;
				_effect_switch = false;
			}
		}


	}
	void Yggdrasil_BasicBullet::OnCollisionStay(Collider2D* other)
	{
	}
	void Yggdrasil_BasicBullet::OnCollisionExit(Collider2D* other)
	{
	}
}