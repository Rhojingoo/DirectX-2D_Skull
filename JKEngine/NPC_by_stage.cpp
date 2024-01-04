#include "NPC_by_stage.h"
#include "Include_Common.h"

namespace jk
{
	NPC_by_stage::NPC_by_stage()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	NPC_by_stage::~NPC_by_stage()
	{
	}
	void NPC_by_stage::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_tr = this->GetComponent<Transform>();

		at = AddComponent<Animator>();

		at->CreateAnimations(L"..\\Resources\\Texture\\Npc\\stage1", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Npc\\stage1", this, 1);

		//at->CreateAnimations(L"..\\Resources\\Texture\\Npc\\stage2", this, 0, 0.05);
		//at->CreateAnimations(L"..\\Resources\\Texture\\Npc\\stage2", this, 1, 0.05);

		at->PlayAnimation(L"Npcstage1", true);
		GameObject::Initialize();
	}
	void NPC_by_stage::Update()
	{
		if (_Set_Npc_Allow == true)
		{
			if (_Stage_Npc == 0)
			{
				at->PlayAnimation(L"Npcstage1", true);
				_state = NPC_State::Stage1_Npc;
			}
			if (_Stage_Npc == 1)
			{
				at->PlayAnimation(L"Npcstage1R", true);
				_state = NPC_State::Stage1_Npc;
			}

			if (_Stage_Npc == 2)
			{
				at->PlayAnimation(L"Npcstage2", true);
				_state = NPC_State::Stage2_Npc;
			}
			if (_Stage_Npc == 3)
			{
				at->PlayAnimation(L"Npcstage2Rr", true);
				_state = NPC_State::Stage2_Npc;
			}
			_Set_Npc_Allow = false;
		}


		switch (_state)
		{
		case jk::NPC_by_stage::NPC_State::Stage1_Npc:
			Stage1_Npc();
			break;

		case jk::NPC_by_stage::NPC_State::Stage2_Npc:
			Stage2_Npc();
			break;


		default:
			break;
		}
		GameObject::Update();
	}
	void NPC_by_stage::LateUpdate()
	{
		_collider->SetSize(Vector2(0.5f, 0.5f));
		_collider->SetCenter(Vector2(0.f, -0.1f));
		GameObject::LateUpdate();
	}
	void NPC_by_stage::Render()
	{
		GameObject::Render();
	}
	void NPC_by_stage::OnCollisionEnter(Collider2D* other)
	{
	}
	void NPC_by_stage::OnCollisionStay(Collider2D* other)
	{
		if (Tile_Ground* mGround = dynamic_cast<Tile_Ground*>(other->GetOwner()))
		{
				_rigidbody->SetGround(true);	
				_rigidbody->ClearVelocity();			
		}
		if (Ground_Map* mGround = dynamic_cast<Ground_Map*>(other->GetOwner()))
		{
				_rigidbody->SetGround(true);
				_rigidbody->ClearVelocity();		
		}
	}
	void NPC_by_stage::OnCollisionExit(Collider2D* other)
	{
	}
	void NPC_by_stage::Stage1_Npc()
	{
	}
	void NPC_by_stage::Stage2_Npc()
	{
	}
}