#pragma once
#include "Include_Common.h"

namespace jk
{
	class Knight_male : public Mini_Boss
	{
	public:
		Knight_male();
		virtual ~Knight_male();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		static int mDir;
		static bool _switch;
		float _time = 0.f;
		bool _attack = false;
		int _jump = 0;
		int _fallcheck = 0;
		bool _Ground_check = false;
		bool _Skulhead = false;
	};
}