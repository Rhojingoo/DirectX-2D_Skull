#include "Sofa_Spring.h"
#include "Include_Common.h"
#include "Spring_Effect.h"


namespace jk
{
	Sofa_Spring::Sofa_Spring()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Sofa_Spring::~Sofa_Spring()
	{
	}
	void Sofa_Spring::Initialize()
	{
		tr = this->GetComponent<Transform>();
		_collider = AddComponent<Collider2D>();
		//_collider->SetType(eColliderType::Circle);
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

			Scene* scene = SceneManager::GetInitializeScene();
		{
			smokeef = new Spring_Effect();
			smokeef->Initialize();
			scene->AddGameObject(eLayerType::Effect, smokeef);
			Transform* smoke_tr = smokeef->GetComponent<Transform>();
			smokeef->SetState(eState::Paused);
		}

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Spring\\Stage2\\idle", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Spring\\Stage2\\jump", this, 0);
		at->CompleteEvent(L"Stage2jump") = std::bind(&Sofa_Spring::Compelete, this);
		at->PlayAnimation(L"Stage2idle", true);

		GameObject::Initialize();
	}
	void Sofa_Spring::Update()
	{
		_pos = tr->GetPosition();
		Transform* smoke_tr = smokeef->GetComponent<Transform>();
		smoke_tr->SetPosition(Vector3(_pos.x, _pos.y + 20, _pos.z - 1));

		GameObject::Update();
	}
	void Sofa_Spring::LateUpdate()
	{
		_collider->SetSize(Vector2(0.85f, 0.55f));
		_collider->SetCenter(Vector2(0.f, -0.1f));
		GameObject::LateUpdate();
	}
	void Sofa_Spring::Render()
	{
		GameObject::Render();
	}
	void Sofa_Spring::OnCollisionEnter(Collider2D* other)
	{
		if (Player* player = dynamic_cast<Player*>(other->GetOwner()))
		{
			Transform* Player_TR = other->GetOwner()->GetComponent<Transform>();
			Collider2D* Player_Col = other->GetOwner()->GetComponent<Collider2D>();
			Vector3 Player_pos = Player_TR->GetPosition();
			float Skul_halfsize = Player_Col->GetScale().y / 2;
			float skul_footpos = Player_pos.y - Skul_halfsize;

			float Gr_Size = _collider->GetScale().y / 2;
			float Gr_Top_pos = _pos.y + Gr_Size;

			if (skul_footpos > Gr_Top_pos)
			{
				at->PlayAnimation(L"Stage2jump", true);
				smokeef->SetState(eState::Active);
				smokeef->_effect_On = true;
			}
		}
	}
	void Sofa_Spring::OnCollisionStay(Collider2D* other)
	{
	}
	void Sofa_Spring::OnCollisionExit(Collider2D* other)
	{
	}
	void Sofa_Spring::Compelete()
	{
		at->PlayAnimation(L"Stage2idle", true);
	}
}