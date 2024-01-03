#pragma once
#include "Bullet.h"

namespace jk
{
	class Latana_Awake_Rush_Bullet : public Bullet
	{
	public:
		Latana_Awake_Rush_Bullet();
		virtual ~Latana_Awake_Rush_Bullet();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


		static void SetPos(Vector3 set) { _pos = set; }
		static Vector3 GetPos() { return _pos; }
		static void SetDirection(int set) { mDir = set; }
		static int	mDir;
		static bool _effect_switch;
		static bool _bulletoff;

		void Compelete_Pierce();


	private:
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

	private:
		static Vector3 _pos;
		float _attackatime = 0.f;
	};
}