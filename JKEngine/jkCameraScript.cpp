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
		//	_Pos.z += 100.0f * (float)Time::DeltaTime();
		//	tr->SetPosition(_Pos);
		//}
		//else if (Input::GetKey(eKeyCode::S))
		//{
		//	_Pos.z -= 100.0f * (float)Time::DeltaTime();
		//	tr->SetPosition(_Pos);
		//}
		//if (Input::GetKey(eKeyCode::E))
		//{
		//	_Pos.x += 100.0f * (float)Time::DeltaTime();
		//	tr->SetPosition(_Pos);
		//}
		//else if (Input::GetKey(eKeyCode::Q))
		//{
		//	_Pos.x -= 100.0f * (float)Time::DeltaTime();
		//	tr->SetPosition(_Pos);
		//}
		//if (Input::GetKey(eKeyCode::UP))
		//{
		//	_Pos.y -= 100.0f * (float)Time::DeltaTime();
		//	tr->SetPosition(_Pos);
		//}
		//else if (Input::GetKey(eKeyCode::DOWN))
		//{
		//	_Pos.y += 100.0f * (float)Time::DeltaTime();
		//	tr->SetPosition(_Pos);
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
