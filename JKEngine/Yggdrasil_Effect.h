#pragma once
#include "Include_Common.h"

namespace jk
{
	class Yggdrasil_Effect : public Effect
	{
	public:
		Yggdrasil_Effect();
		virtual ~Yggdrasil_Effect();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		//enum class Yggdrasil_State
		//{
		//	Idle,
		//	Die,
		//};
		//void idle();
		//void die();
		//static Yggdrasil_State _state;


		static void SetPos(Vector3 set) { _pos = set; }
		static Vector3 GetPos() { return _pos; }
		static bool _effect_switch;
		int	mDir = 1;

	private:	
		static Vector3 _pos;
		float _attackatime = 0.f;
	};
}