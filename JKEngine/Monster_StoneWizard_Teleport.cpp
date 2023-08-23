#include "Monster_StoneWizard_Teleport.h"

namespace jk
{
	Monster_StoneWizard_Teleport::Monster_StoneWizard_Teleport()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bullet"));
	}
	Monster_StoneWizard_Teleport::~Monster_StoneWizard_Teleport()
	{
	}


	void Monster_StoneWizard_Teleport::Initialize()
	{
		_collider = AddComponent<Collider2D>();
		_rigidbody = AddComponent<RigidBody>();
		_rigidbody->SetMass(1.f);
		_rigidbody->SetGround(true);

		at = AddComponent<Animator>();
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Effect\\Telleport_In", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Effect\\Telleport_In", this, 1);

		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Effect\\Telleport_Out", this, 0);
		at->CreateAnimations(L"..\\Resources\\Texture\\Monster\\Stone_wizard\\Effect\\Telleport_Out", this, 1);

		at->CompleteEvent(L"EffectTelleport_In") = std::bind(&Monster_StoneWizard_Teleport::Compelete_Telleport_In, this);
		at->CompleteEvent(L"EffectTelleport_InR") = std::bind(&Monster_StoneWizard_Teleport::Compelete_Telleport_In, this);

		at->CompleteEvent(L"EffectTelleport_Out") = std::bind(&Monster_StoneWizard_Teleport::Compelete_Telleport_Out, this);
		at->CompleteEvent(L"EffectTelleport_OutR") = std::bind(&Monster_StoneWizard_Teleport::Compelete_Telleport_Out, this);

		at->PlayAnimation(L"EffectTelleport_Out", false);

		GameObject::Initialize();
	}
	void Monster_StoneWizard_Teleport::Update()
	{
		if (_effect_On == true)
		{
			if (Telleport_choive == Stone_wizard_Telleport::Teleport_In_Left)
				at->PlayAnimation(L"EffectTelleport_In", true);
			if (Telleport_choive == Stone_wizard_Telleport::Teleport_In_Right)
				at->PlayAnimation(L"EffectTelleport_InR", true);
			if (Telleport_choive == Stone_wizard_Telleport::Teleport_Out_Left)
				at->PlayAnimation(L"EffectTelleport_Out", true);
			if (Telleport_choive == Stone_wizard_Telleport::Teleport_Out_Right)
				at->PlayAnimation(L"EffectTelleport_OutR", true);
			_effect_On = false;
		}
		GameObject::Update();
	}
	void Monster_StoneWizard_Teleport::LateUpdate()
	{
		_collider->SetSize(Vector2(0.05f, 0.1f));
		_collider->SetCenter(Vector2(0.0f, -0.05f));
		GameObject::LateUpdate();
	}
	void Monster_StoneWizard_Teleport::Render()
	{
		GameObject::Render();
	}



	void Monster_StoneWizard_Teleport::OnCollisionEnter(Collider2D* other)
	{
	}
	void Monster_StoneWizard_Teleport::OnCollisionStay(Collider2D* other)
	{
	}
	void Monster_StoneWizard_Teleport::OnCollisionExit(Collider2D* other)
	{
	}


	void Monster_StoneWizard_Teleport::Compelete_Telleport_In()
	{
		_effect_On = false;
		this->SetState(eState::Paused);
	}
	void Monster_StoneWizard_Teleport::Compelete_Telleport_Out()
	{
		_effect_On = false;
		this->SetState(eState::Paused);
	}

}