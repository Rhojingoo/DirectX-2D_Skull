#include "Homing_Pierce_ShortHair.h"
#include "Include_Common.h"
#include "Hit_Critical_Middle.h"
#include "..\Engine_SOURCE\jkAudioSource.h"

namespace jk
{
	int Homing_Pierce_ShortHair::mDir = 1;

	Homing_Pierce_ShortHair::Homing_Pierce_ShortHair()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Homing_Pierce_ShortHair::~Homing_Pierce_ShortHair()
	{
	}
	void Homing_Pierce_ShortHair::Initialize()
	{
		_tr = this->GetComponent<Transform>();
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		as = AddComponent<AudioSource>();
		as->SetClipAndLoad(L"..\\Resources\\Sound\\Boss\\Leiana\\Leiana_DimensionPierce_Impact.wav", "Homing_Hit");//Ÿ�ݽ�


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Homing_pierce", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\Boss\\Layana_Sisters\\Bullet\\Homing_pierce", this, 1);

		{
			_Critical_Middle = new Hit_Critical_Middle;
			_Critical_Middle->Initialize();
			Scene* scene = SceneManager::GetInitializeScene();
			scene = SceneManager::GetInitializeScene();
			scene->AddGameObject(eLayerType::Effect, _Critical_Middle);
			_Critical_Middle->SetState(eState::Paused);
		}

		at->PlayAnimation(L"BulletHoming_pierce", true);
		GameObject::Initialize();
	}
	void Homing_Pierce_ShortHair::Update()
	{
		if (mDir == 1)
			at->PlayAnimation(L"BulletHoming_pierce", true);
		else
			at->PlayAnimation(L"BulletHoming_pierceR", true);

		GameObject::Update();
	}
	void Homing_Pierce_ShortHair::LateUpdate()
	{
		_collider->SetSize(Vector2(0.85f, 0.35f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Homing_Pierce_ShortHair::Render()
	{
		GameObject::Render();
	}
	void Homing_Pierce_ShortHair::OnCollisionEnter(Collider2D* other)
	{
		if (Tile_Ground* Bullet = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
			as->Play("Homing_Hit");
			Transform* hittr = Bullet->GetComponent<Transform>();
			Vector3 hitpos = hittr->GetPosition();
			if (mDir == 1)
			{
				Vector3 pos = _tr->GetPosition();
				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				Vector3 pos = _tr->GetPosition();
				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}

			this->SetState(eState::Paused);
		}

		if (Player* player = dynamic_cast<Player*>(other->GetOwner()))
		{
			as->Play("Homing_Hit");
			if (mDir == 1)
			{
				Vector3 pos = _tr->GetPosition();
				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			else
			{
				Vector3 pos = _tr->GetPosition();
				_Critical_Middle->_effect_animation = true;
				_Critical_Middle->SetDirection(-1);
				Transform* bulltr = _Critical_Middle->GetComponent<Transform>();
				bulltr->SetPosition(Vector3(pos.x, pos.y, pos.z - 1));
				_Critical_Middle->SetState(eState::Active);
			}
			this->SetState(eState::Paused);
		}
	}
	void Homing_Pierce_ShortHair::OnCollisionStay(Collider2D* other)
	{
	}
	void Homing_Pierce_ShortHair::OnCollisionExit(Collider2D* other)
	{
	}

}