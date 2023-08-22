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

		// �ӵ��� ���ӵ��� �����ش�.
		mVelocity += mAccelation * Time::DeltaTime();

		if (_Setgravity == false)
		{
			if (mbGround)
			{
				// ������ ������
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

		// �߷°��ӵ� �ִ� �ӵ� ����
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
		{// ������ ���� ( ����� ���� ����, �ӵ��� 0�� �ƴ�)
			if (!(mVelocity == Vector2::Zero))
			{
				//�ӵ��� �ݴ�������� �������� ����ȴ�.
				Vector2 friction = -mVelocity;
				friction.Normalize();
				friction = friction * mFriction * mMass * Time::DeltaTime();

				//���������� ���� �ӵ� ���Ҵ� ���� �ӵ����� ū ���

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

		// �ӵ��� �°Բ� ��ü�� �̵���Ų��.
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