#include "Archer_Arrow.h"

namespace jk
{
	Archer_Arrow::Archer_Arrow()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Archer_Arrow::~Archer_Arrow()
	{
	}
	void Archer_Arrow::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
		tr = this->GetComponent<Transform>();


		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Bullet\\Archer_Arrow", this);
		at->CreateAnimations(L"..\\Resources\\Texture\\MiniBoss\\Archer\\Bullet\\Archer_Arrow", this,1);

		//Bullet_Effect = new Kngiht_EnergyBall_Impact;
		//Bullet_Effect->Initialize();
		//Scene* scene = SceneManager::GetActiveScene();
		//scene->AddGameObject(eLayerType::Bullet, Bullet_Effect);
		//Transform* EffectTR = Bullet_Effect->GetComponent<Transform>();
		//EffectTR->SetPosition(tr->GetPosition());
		//Bullet_Effect->SetState(eState::Paused);

		at->PlayAnimation(L"BulletArcher_Arrow", true);
		GameObject::Initialize();
	}
	void Archer_Arrow::Update()
	{
		if (_bullet_animation == true)
		{
			if(_dir==1)
				at->PlayAnimation(L"BulletArcher_Arrow", true);
			if (_dir == -1)
				at->PlayAnimation(L"BulletArcher_ArrowR", true);
			_bullet_animation = false;
		}

		GameObject::Update();
	}
	void Archer_Arrow::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Archer_Arrow::Render()
	{
		GameObject::Render();
	}

	void Archer_Arrow::OnCollisionEnter(Collider2D* other)
	{
		//if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		//{
		//	_rigidbody->SetGround(true);
		//	_rigidbody->ClearVelocity();

		//	if (_EffectSwitch == true)
		//	{
		//		Transform* EffectTR = Bullet_Effect->GetComponent<Transform>();
		//		EffectTR->SetPosition(tr->GetPosition());
		//		Bullet_Effect->SetState(eState::Active);
		//		_EffectSwitch = false;
		//		this->SetState(eState::Paused);
		//	}
		//}
	}
	void Archer_Arrow::OnCollisionStay(Collider2D* other)
	{
	}
	void Archer_Arrow::OnCollisionExit(Collider2D* other)
	{
	}
	void Archer_Arrow::complete()
	{
	}
}