#pragma once
#include "Include_Common.h"
#include "Effect.h"

namespace jk
{
	class Dimension_Pierce_BulletEffect : public Effect
	{
	public:
		Dimension_Pierce_BulletEffect();
		virtual ~Dimension_Pierce_BulletEffect();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		static void SetDirection(int set) { mDir = set; }
		static int	mDir;
		static bool	_SwitchOn;
		static bool	_SwitchOff;

		void Compelete_Pierce();

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
	};
}