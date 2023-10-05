#pragma once
#include "Include_Common.h"

namespace jk
{
	class AdventureUI : public GameObject
	{
	public:
		AdventureUI();
		virtual ~AdventureUI();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		enum class AdventureUI_State
		{
			ArcherUI,
			Archer_DeadUI,

			ClericUI,
			Cleric_DeadUI,

			HeroUI,
			Hero_DeadUI,

			MageUI,
			Mage_DeadUI,
		};

		void ArcherUI();
		void ClericUI();
		void HeroUI();
		void MageUI();
		void Dead();

		void Set_UISelect(int SET) { _UISelect = SET; }
		void Set_animation(bool SET) { _animation = SET; }

	private:
		Animator* at = nullptr;
		Collider2D* _collider = nullptr;
		bool _animation = false;
		AdventureUI_State _State = {};
		int _UISelect = 0;
	};
}