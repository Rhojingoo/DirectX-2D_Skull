#pragma once
#include "Include_Common.h"

namespace jk
{
	class Player_Hp_Bar : public GameObject
	{
	public:
		Player_Hp_Bar();
		virtual ~Player_Hp_Bar();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		void BindConstantBuffer();
		void SetHitDamage(float set) { _Hit_Damage = set;}
		void Set_Max_Hp(float set) { _MaxHp = set; }
		void Set_Current_Hp(float set) { _CurrentHp = set; }

		bool _HitOn = false;

	private:
		MeshRenderer* meshrenderer;
		Transform* tr;	
		float ratio = 0.f;
		float _MaxHp = 0.f;
		float _CurrentHp = 0.f;
		float _Hit_Damage = 0.f;
		float _Time;
		Vector3 _Pos;
	};
}