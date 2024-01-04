#pragma once
#include "jkGameObject.h"

namespace jk
{
	class Sofa_Spring : public GameObject
	{
	public:
		Sofa_Spring();
		virtual ~Sofa_Spring();

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
		class Spring_Effect* smokeef = nullptr;
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 _pos = Vector3();
		float _attackatime = 0.f;
		int _dir = 1;
	};
}