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


		Vector3 GetPosition() const { return mPosition; }
		float GetPositionX() const { return mPosition.x; }
		float GetPositionY() const { return mPosition.y; }
		float GetPositionZ() const { return mPosition.z; }
		Vector2 GetPositionXY() const { return Vector2(mPosition); }

		Vector3 GetRotation() const { return mRotation; }
		float GetRotationX() const { return mRotation.x; }
		float GetRotationY() const { return mRotation.y; }
		float GetRotationZ() const { return mRotation.z; }
		Vector2 GetRotationXY() const { return Vector2(mRotation); }

		Vector3 GetScale() const { return mScale; }
		float GetScaleX() const { return mScale.x; }
		float GetScaleY() const { return mScale.y; }
		float GetScaleZ() const { return mScale.z; }
		Vector2 GetScaleXY() const { return Vector2(mScale); }



		void SetPosition(float x, float y, float z) { mPosition = Vector3(x, y, z); }
		void SetPositionX(const float posX) { mPosition.x = posX; }
		void SetPositionY(const float posY) { mPosition.y = posY; }
		void SetPositionZ(const float posZ) { mPosition.z = posZ; }
		void SetPositionXY(const Vector2& position) { mPosition.x = position.x; mPosition.y = position.y; }


		void SetRotation(float x, float y, float z) { mRotation = Vector3(x, y, z); }
		void SetRotationX(const float rotX) { mRotation.x = rotX; }
		void SetRotationY(const float rotY) { mRotation.y = rotY; }
		void SetRotationZ(const float rotZ) { mRotation.z = rotZ; }
		void SetRotationXY(const Vector2& rotation) { mRotation.x = rotation.x; mRotation.y = rotation.y; }


		void SetScale(float x, float y, float z) { mScale = Vector3(x, y, z); }
		void SetScaleX(const float scaleX) { mScale.x = scaleX; }
		void SetScaleY(const float scaleY) { mScale.y = scaleY; }
		void SetScaleZ(const float scaleZ) { mScale.z = scaleZ; }
		void SetScaleXY(const Vector2& scale) { mScale.x = scale.x; mScale.y = scale.y; }




		void AddPosition(const Vector3& position) { mPosition += position; }
		void AddPositionX(const float posX) { mPosition.x += posX; }
		void AddPositionY(const float posY) { mPosition.y += posY; }
		void AddPositionZ(const float posZ) { mPosition.z += posZ; }
		void AddPositionXY(const Vector2& position) { mPosition.x += position.x; mPosition.y += position.y; }


		void AddRotation(const Vector3& rotation) { mRotation += rotation; }
		void AddRotationX(const float rotX) { mRotation.x += rotX; }
		void AddRotationY(const float rotY) { mRotation.y += rotY; }
		void AddRotationZ(const float rotZ) { mRotation.z += rotZ; }

		void AddScale(const Vector3& scale) { mScale += scale; }
		void AddScaleX(const float scaleX) { mScale.x += scaleX; }
		void AddScaleY(const float scaleY) { mScale.y += scaleY; }
		void AddScaleZ(const float scaleZ) { mScale.z += scaleZ; }



		const Matrix& GetWorldMatrix() const { return mWorld; }

		Vector3 GetPosition() { return mPosition; }
		Vector3 GetRotation() { return mRotation; }
		Vector3 GetScale() { return mScale; }

		Vector3 Foward() { return mFoward; }
		Vector3 Right() { return mRight; }
		Vector3 Up() { return mUp; }

		void SetParent(Transform* transform) { mParent = transform; }
		Transform* GetParent() { return mParent; }
		Matrix& GetMatrix() { return mWorld; }

	private:
		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;


		Vector3 mUp;
		Vector3 mFoward;
		Vector3 mRight;
		Vector3 mRelativeForward;
		Vector3 mRelativeRight;
		Vector3 mRelativeUp;

		Matrix mWorld;

		Transform* mParent;

		bool mInheritParentScale;
		Vector3 mWorldPosition;
		Vector3 mWorldRotation;
		Vector3 mWorldScale;

	};
}
