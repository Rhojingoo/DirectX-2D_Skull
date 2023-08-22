#include "jkRigidBody.h"
#include "jkTime.h"
#include "jkComponent.h"
#include "jkGameObject.h"

namespace jk
{
	RigidBody::RigidBody()
		: Component(eComponentType::RigidBody)
		, mMass(1.f)
		, mForce(Vector2::Zero)
		, mAccelation(Vector2::Zero)
		, mVelocity(Vector2::Zero)
	{
		mLimitedVelocity.x = 200.0f;
		mLimitedVelocity.y = 200.0f;
		mbGround = false;
		mGravity = Vector2(0.0f, -800.0f);
		mFriction = 100.0f;
	}
	RigidBody::~RigidBody()
	{
	}
	void RigidBody::Initialize()
	{
	}

	void RigidBody::Update()
	{

		// F = M * A
		// A = M / F
		mAccelation = mForce / mMass;

		// 속도에 가속도를 더해준다.
		mVelocity += mAccelation * Time::DeltaTime();

		if (_Setgravity == false)
		{
			if (mbGround)
			{
				// 땅위에 있을때
				Vector2 gravity = mGravity;
				gravity.Normalize();

				float dot = mVelocity.Dot(gravity);
				mVelocity -= gravity * dot;
			}
			else
			{
				mVelocity += mGravity * Time::DeltaTime();
			}
		}

		// 중력가속도 최대 속도 제한
		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = mVelocity.Dot(gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitedVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitedVelocity.y;
		}

		if (mLimitedVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitedVelocity.x;
		}

		if (_SetFriction == false)
		{// 마찰력 조건 ( 적용된 힘이 없고, 속도가 0이 아님)
			if (!(mVelocity == Vector2::Zero))
			{
				//속도에 반대방향으로 마찰력이 적용된다.
				Vector2 friction = -mVelocity;
				friction.Normalize();
				friction = friction * mFriction * mMass * Time::DeltaTime();

				//마찰력으로 인한 속도 감소는 현재 속도보다 큰 경우

				if (mVelocity.Length() < friction.Length())
				{
					mVelocity = Vector2::Zero;
				}
				else
				{
					mVelocity += friction;
				}
			}
		}

		// 속도에 맞게끔 물체를 이동시킨다.
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPositionXY();
		pos = pos + mVelocity * Time::DeltaTime();
		tr->SetPositionXY(pos);
		mForce = Vector2(Vector2::Zero);
	}

	void RigidBody::LateUpdate()
	{
	}

	void RigidBody::Render()
	{
	}

	void RigidBody::AddForce(Vector2 force)
	{
		mForce += force;
	}
}