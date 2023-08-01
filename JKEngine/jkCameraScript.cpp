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
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector2 _pos = mTarget->GetComponent<Transform>()->GetPositionXY();

		#pragma region apiī�޶�
		//mResolution.x = static_cast<float>(application.GetWidth());
		//mResolution.y = static_cast<float>(application.GetHeight());
		//mLookPosition = (mResolution / 2.0f);

		//ī�޶� �����ϼ� �ִ±��
		//if (Input::GetKey(eKeyCode::G))
		//	mLookPosition.x -= 100.0f * static_cast<float>(Time::DeltaTime());
		//if (Input::GetKey(eKeyCode::J))
		//	mLookPosition.x += 100.0f * static_cast<float>(Time::DeltaTime());
		//if (Input::GetKey(eKeyCode::Y))
		//	mLookPosition.y -= 100.0f * static_cast<float>(Time::DeltaTime());
		//if (Input::GetKey(eKeyCode::H))
		//	mLookPosition.y += 100.0f * static_cast<float>(Time::DeltaTime());


		//ĳ���͸� �߽����� �����̰� ����
		//if (camera == 0)
		//{
			//if (mTarget != nullptr)
			//{
			//	mLookPosition
			//		= mTarget->GetComponent<Transform>()->GetPositionXY();
			//	target_pos = mLookPosition;
			//}
			//mDistance.x = _pos.x - (mResolution.x / 2.0f);
			//mDistance.y = _pos.y - (mResolution.y / 2.0f);
			//tr->SetPositionXY(_pos);
		//}
#pragma endregion		

		//���� �ִ���
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
		//if (Input::GetKey(eKeyCode::LEFT))
		//{
		//	pos.x -= 250.0f * (float)Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::RIGHT))
		//{
		//	pos.x += 250.0f * (float)Time::DeltaTime();
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
