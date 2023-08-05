#pragma once
#include "Include_Common.h"

namespace jk
{
	class Yggdrasil_Hand_Right : public Yggdrasil
	{
	public:
		Yggdrasil_Hand_Right();
		virtual ~Yggdrasil_Hand_Right();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void idle();
		void attack_a();
		void attack_b();
		void attack_c();
		void intro();
		void die();

	public:
		static bool			_Attackswitch;
		static int			mDir;

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 _pos = Vector3(0.f, 0.f, 0.f);
		Vector3 _Savepointpos = Vector3(0.f, 0.f, 0.f);		// 본체좌표
		Vector3	_Yggdrasildistance = Vector3(0.f, 0.f, 0.f);	// 본체와의 거리 체크
		Vector3	_Playerdistance = Vector3(0.f, 0.f, 0.f);		// 플레이어와의 거리 체크
		Vector2 _velocity = Vector2(0.f, 0.f);

	private:
		float	_time = 0.f;							// 공격시 사용중
		bool	_Ground_check = false;					// 땅체크시에 쓰이고 있는 변수
	};
}