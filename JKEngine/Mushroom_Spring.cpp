#include "Mushroom_Spring.h"
#include "Include_Common.h"
#include "Spring_Effect.h"

namespace jk
{
	Mushroom_Spring::Mushroom_Spring()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Mushroom_Spring::~Mushroom_Spring()
	{
	}
	void Mushroom_Spring::Initialize()
	{
		tr = this->GetComponent<Transform>();
		_collider = AddComponent<Collider2D>();
		//_collider->SetType(eColliderType::Circle);
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);
	
		{
			smokeef = new Spring_Effect();
			smokeef->Initialize();
			Scene* scene = SceneManager::GetActiveScene();
			scene = SceneManager::GetActiveScene();
			scene->AddGameObject(eLayerType::Effect, smokeef);
			Transform* smoke_tr = smokeef->GetComponent<Transform>();
			smokeef->SetState(eState::Paused);
		}

		at = AddComponent<Animator>(); 
		at->CreateAnimations(L"..\\Resources\\Texture\\Spring\\Stage1", this, 0);
		at->PlayAnimation(L"SpringStage1", true);

		GameObject::Initialize();
	}
	void Mushroom_Spring::Update()
	{
		_pos = tr->GetPosition();
		Transform* smoke_tr = smokeef->GetComponent<Transform>();
		smoke_tr->SetPosition(Vector3(_pos.x, _pos.y+20, _pos.z - 1));

		GameObject::Update();
	}
	void Mushroom_Spring::LateUpdate()
	{
		_collider->SetSize(Vector2(0.85f, 0.55f));
		_collider->SetCenter(Vector2(0.f, -0.1f));
		GameObject::LateUpdate();
	}
	void Mushroom_Spring::Render()
	{
		GameObject::Render();
	}
	void Mushroom_Spring::OnCollisionEnter(Collider2D* other)
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
				smokeef->SetState(eState::Active);
				smokeef->_effect_On = true;
			}
		}
	}
	void Mushroom_Spring::OnCollisionStay(Collider2D* other)
	{
	}
	void Mushroom_Spring::OnCollisionExit(Collider2D* other)
	{
	}
	void Mushroom_Spring::Compelete()
	{	
	}
}