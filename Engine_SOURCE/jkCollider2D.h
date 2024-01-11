#pragma once
#include "jkComponent.h"
#include "jkTransform.h"


namespace jk
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void OnCollisionEnter(Collider2D* other);
		void OnCollisionStay(Collider2D* other);
		void OnCollisionExit(Collider2D* other);

		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 size) { mCenter = size; }
		UINT GetColliderID() { return mColliderID; }
		Vector3 GetPosition() {	return mPosition; }
		void SetPosition(Vector3 Set) {  mPosition = Set; }
		void SetColorcheck(int Set) {_Colcheck = Set;}
		Vector2 GetSize() { return mSize; }
		Vector2 GetCenter() { return mCenter; }
		Vector3 GetScale() { return _Scale; }
		Vector2	GetScaleXY() { return Vector2(_Scale); }

	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		Transform* mTransform;

		Vector3 mPosition;
		Vector3 _Scale;
		Vector2 mSize;
		Vector2 mCenter;
		static int _ColSwitch;
		int _Colcheck;
		bool _Collider_attack = false;
	};
}
