#include "jkPlayerScript.h"
#include "jkCameraScript.h"
#include "jkTransform.h"
#include "jkGameObject.h"
#include "jkTime.h"
#include "jkInput.h"
#include "jkAnimator.h"

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
		//Animator* at = GetOwner()->GetComponent<Animator>();
		//at->CompleteEvent(L"Idle") = std::bind(&PlayerScript::Complete, this);

	}
	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();



		//if (Input::GetKey(eKeyCode::LEFT))
		//{
		//	pos.x -= 100.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::RIGHT))
		//{
		//	pos.x += 100.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y -= 100.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::UP))
		{
			pos.y += 100.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}
	void PlayerScript::Complete()
	{
		int a = 0;
	}
}
