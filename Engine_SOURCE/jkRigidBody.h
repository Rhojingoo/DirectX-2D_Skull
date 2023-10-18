#pragma once
#include "jkComponent.h"

using namespace jk::math;
namespace jk
{
	class RigidBody : public Component
	{
	public:
		RigidBody();
		virtual ~RigidBody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void AddForce(Vector2 force);
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool isGround) { mbGround = isGround; }
		bool GetGround() { return mbGround; }
		bool IsGround() { return mbGround; }
		Vector2 GetVelocity() { return mVelocity; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		void ClearVelocityX() { mVelocity.x = 0.f; }
		void ClearVelocityY() { mVelocity.y = 0.f; }
		void ClearVelocity() { mVelocity = Vector2(0.f,0.f); }
		void SetFriction(float fl) { mFriction = fl; }
		void SetGravity(bool set) { _Setgravity = set; }
		void SetFriction(bool set) { _SetFriction = set; }

	/*	void OnFriction(bool isOn) { mbOnFriction = isOn; }
		void OnHorizonAccelMove(bool isOn) { mbHorizonAccelMove = isOn; }*/

		eMoveDir GetMoveDir() { return mMoveDir; }

	private:
		// ���� �������� �̿��� �̵�
		float mMass;
		Vector2 mForce;
		Vector2 mAccelation;
		Vector2 mVelocity;
		Vector2 mLimitedVelocity;

		Vector2 mGravity;
		float mFriction;
		bool mbGround;
		bool _Setgravity = false;;
		bool _SetFriction = false;;
		// �߷� �̿��� ����

		eMoveDir mMoveDir = {};
	};
}