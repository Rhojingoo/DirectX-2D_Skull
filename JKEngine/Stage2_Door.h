#pragma once
#include "Door.h"

namespace jk
{
	class Stage2_Door : public Door
	{
	public:
		Stage2_Door();
		virtual ~Stage2_Door();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class Stage2Door_State
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

		void Set_Stage2_Door(int SET) { _Stage2_Door = SET; }
		void Set_Door_Allow(bool SET) { _Set_Door_Allow = SET; }
		void Set_NextStage(const std::wstring& path) { Path = path; }

	private:
		void basic_door();
		void get_skull_door();
		void mini_boss_door();
		void boss_door();


	private:
		Stage2Door_State _State = {};
		class Animator* at = nullptr;
		class Collider2D* _collider = nullptr;
		class Alpha_Blend* _Alpha = nullptr;
		Transform* tr = nullptr;
		int _Stage2_Door = 0;
		bool _Set_Door_Allow = false;

		float _time = 0.f;
		bool _Fadecheck = false;
		std::wstring Path = {};
	};
}