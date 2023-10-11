#pragma once
#include "Include_Common.h"
#include "Spring_Effect.h"


namespace jk
{
	class Mushroom_Spring : public GameObject
	{
	public:
		Mushroom_Spring();
		virtual ~Mushroom_Spring();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetDirection(int set) { _dir = set; }
		void Compelete();


	private:
		Spring_Effect* smokeef = nullptr;
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 _pos = Vector3();
		float _attackatime = 0.f;
		int _dir = 1;
	};
}