#include "jkCameraScript.h"


namespace jk
{
	int CameraScript::camera = 0;
	Vector2 CameraScript::target_pos = Vector2::Zero;
	Vector2 CameraScript::mMove = Vector2::Zero;
	Vector2 CameraScript::mResolution = Vector2::Zero;
	Vector2 CameraScript::mLookPosition = Vector2::Zero;
	Vector2 CameraScript::mDistance = Vector2::Zero;
	GameObject* CameraScript::mTarget = nullptr;


	void CameraScript::Update()
	{
		//원래 있던것
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
		//if (Input::GetKey(eKeyCode::E))
		//{
		//	pos.x += 100.0f * (float)Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::Q))
		//{
		//	pos.x -= 100.0f * (float)Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//if (Input::GetKey(eKeyCode::UP))
		//{
		//	pos.y -= 100.0f * (float)Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::DOWN))
		//{
		//	pos.y += 100.0f * (float)Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
	}

	void CameraScript::Clear()
	{
		mResolution.x = static_cast<float>(application.GetWidth());
		mResolution.y = static_cast<float>(application.GetHeight());
		mLookPosition = (mResolution / 2.0f);
		mDistance = Vector2::Zero;
		mTarget = nullptr;
	}
}
