#pragma once
#include "Include_Common.h"

namespace jk
{
	class Monster_StoneWizard_Teleport : public Effect
	{
	public:
		Monster_StoneWizard_Teleport();
		virtual ~Monster_StoneWizard_Teleport();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		enum class Stone_wizard_Telleport
		{
			Teleport_In_Left,
			Teleport_In_Right,
			Teleport_Out_Left,
			Teleport_Out_Right,
		};

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void Compelete_Telleport_In();
		void Compelete_Telleport_Out();

		bool _effect_On = false;
		Stone_wizard_Telleport Telleport_choive = {};

	private:
		Animator* at = nullptr;
		RigidBody* _rigidbody = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		float _attackatime = 0.f;
	};
}