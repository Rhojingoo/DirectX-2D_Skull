#pragma once
#include "Include_Common.h"

namespace jk
{
	class Layana_HpFrame : public GameObject
	{
	public:
		Layana_HpFrame();
		virtual ~Layana_HpFrame();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		enum class Layana_HP_State
		{
			First_Phase,
			Second_Phase,
		};

		void First_Phase();
		void Second_Phase();
		void Set_Animation(bool set) { _SetAnimation = set; }
		void ChoicetHp_bar(int set) { _SellectHp_bar = set; }
	private:
		Layana_HP_State _State = {};
		Animator* at = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		bool _SetAnimation = false;
		int _SellectHp_bar = 0;
	};
}