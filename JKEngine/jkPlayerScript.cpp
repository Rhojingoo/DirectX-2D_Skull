#include "jkPlayerScript.h"
#include "jkCameraScript.h"
#include "jkTransform.h"
#include "jkGameObject.h"
#include "jkTime.h"
#include "jkInput.h"
#include "jkAnimator.h"
#include "..\\Engine_SOURCE\\jkCamera.h"
#include "Include_Common.h"

namespace jk
{
	PlayerScript::PlayerScript()
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
		//if (GetOwner()->GetComponent<RigidBody>())
		//	_Rig = GetOwner()->GetComponent<RigidBody>();
		//_Rig->SetMass(1.0f);
		//Animator* at = GetOwner()->GetComponent<Animator>();
		//at->CompleteEvent(L"Idle") = std::bind(&PlayerScript::Complete, this);

	}
	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		

		if (Input::GetKey(eKeyCode::LEFT))
		{
			//_Rig->AddForce(Vector2(-1000.f, 0.f));
				//-= 100.0f * static_cast<float>(Time::DeltaTime());
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			//_Pos.x += 100.0f * static_cast<float>(Time::DeltaTime());
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y -= 100.0f * static_cast<float>(Time::DeltaTime());
			//tr->SetPosition(_Pos);
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			pos.y += 100.0f * static_cast<float>(Time::DeltaTime());
			//tr->SetPosition(_Pos);
		}

		//if (Input::GetKey(eKeyCode::Z))
		//{
		//	_Pos.x += 1000.0f * static_cast<float>(Time::DeltaTime());
		//	//tr->SetPosition(_Pos);
		//}


		//tr->SetPosition(_Pos);
	}
	void PlayerScript::Complete()
	{
		int a = 0;
	}
}
