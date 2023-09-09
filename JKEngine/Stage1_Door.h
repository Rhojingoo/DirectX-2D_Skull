#pragma once
#include "Include_Common.h"
#include "Door.h"

namespace jk
{
	class Stage1_Door : public Door
	{
	public:
		Stage1_Door();
		virtual ~Stage1_Door();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;
		
		enum class Stage1Door_State
		{
			Open_Basic_Door,
			Open_GetSkull_Door,
			Open_MiniBoss_Door,
			Open_Boss_Door,

			Close_Basic_Door,
			Close_GetSkull_Door,
			Close_MiniBoss_Door,
			Close_Boss_Door,

			Deactivate_Door_First,
			Deactivate_Door_Second,
		};

		void Set_Stage1_Door(int SET) { _Stage1_Door = SET; }
		void Set_Door_Allow(bool SET) { _Set_Door_Allow = SET; }

	private:
		void basic_door();
		void get_skull_door();
		void mini_boss_door();
		void boss_door();


	private:
		Stage1Door_State _State = {};
		Animator* at = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		int _Stage1_Door = 0;
		bool _Set_Door_Allow = false;
	};
}