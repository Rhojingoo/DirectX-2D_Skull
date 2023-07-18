#include "jkCameraScript.h"


namespace jk
{
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();


		//if (Input::GetKey(eKeyCode::W))
		//{
		//	pos.z += 100.0f * (float)Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::S))
		//{
		//	pos.z -= 100.0f * (float)Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 100.0f * (float)Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 100.0f * (float)Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::Q))
		{
			pos.y -= 100.0f * (float)Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::E))
		{
			pos.y += 100.0f * (float)Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}
}
