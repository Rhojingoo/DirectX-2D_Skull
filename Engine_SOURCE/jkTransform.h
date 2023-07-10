#pragma once
#include "jkComponent.h"

namespace jk
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindConstantBuffer();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetRotation(Vector3 rotation) 
		{
			const float pi = 3.141592f;
			float degree = pi / 180.f;
			mRotation = rotation * degree;
		}
		void SetScale(Vector3 scale) { mScale = scale; }

		void SetPosition(float x, float y, float z) { mPosition = Vector3(x, y, z); }
		void SetPositionX(const float posX) { mPosition.x = posX; }
		void SetPositionY(const float posY) { mPosition.y = posY; }
		void SetPositionZ(const float posZ) { mPosition.z = posZ; }

		void SetRotation(float x, float y, float z) { mRotation = Vector3(x, y, z); }
		void SetRotationX(const float rotX) { mRotation.x = rotX; }
		void SetRotationY(const float rotY) { mRotation.y = rotY; }
		void SetRotationZ(const float rotZ) { mRotation.z = rotZ; }

		void SetScale(float x, float y, float z) { mScale = Vector3(x, y, z); }
		void SetScaleX(const float scaleX) { mScale.x = scaleX; }
		void SetScaleY(const float scaleY) { mScale.y = scaleY; }
		void SetScaleZ(const float scaleZ) { mScale.z = scaleZ; }

		void AddPosition(const Vector3& position) { mPosition += position; }
		void AddPositionX(const float posX) { mPosition.x += posX; }
		void AddPositionY(const float posY) { mPosition.y += posY; }
		void AddPositionZ(const float posZ) { mPosition.z += posZ; }

		void AddRotation(const Vector3& rotation) { mRotation += rotation; }
		void AddRotationX(const float rotX) { mRotation.x += rotX; }
		void AddRotationY(const float rotY) { mRotation.y += rotY; }
		void AddRotationZ(const float rotZ) { mRotation.z += rotZ; }

		void AddScaleX(const float scaleX) { mScale.x += scaleX; }
		void AddScaleY(const float scaleY) { mScale.y += scaleY; }
		void AddScaleZ(const float scaleZ) { mScale.z += scaleZ; }


		Vector3 GetPosition() { return mPosition; }
		Vector3 GetRotation() { return mRotation; }
		Vector3 GetScale() { return mScale; }

		Vector3 Foward() { return mFoward; }
		Vector3 Right() { return mRight; }
		Vector3 Up() { return mUp; }

		void SetParent(Transform* transform) { mParent = transform; }
		Transform* GetParent() { return mParent; }

	private:
		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;


		Vector3 mUp;
		Vector3 mFoward;
		Vector3 mRight;

		Matrix mWorld;

		Transform* mParent;
	};
}
