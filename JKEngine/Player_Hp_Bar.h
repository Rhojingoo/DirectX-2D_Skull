#pragma once
#include "Include_Common.h"

namespace jk
{
	class Player_Hp_Bar : public GameObject
	{
	public:
		Player_Hp_Bar(const std::wstring& path);
		virtual ~Player_Hp_Bar();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		void BindConstantBuffer();
		void SetHitDamage(float set) { _Hit_Damage = set;}
		void Set_Max_Hp(float set) { _MaxHp = set; }
		void Set_Current_Hp(float set) { _CurrentHp = set; }

		//타입이다른 hp바
		void Set_Type(int set) { _Type = set; }
		void Set_Target(float set) { _target_point = set; }
		bool Get_Switch() { return _DageSwitch; }
		void Set_Switch(bool set) { _DageSwitch = set; }

		bool _HitOn = false;

	private:
		MeshRenderer* meshrenderer;
		Transform* tr;
		float	_MaxHp = 0.f;
		float	_CurrentHp = 0.f;
		float	_Hit_Damage = 0.f;
		float	_target_point = 0.f;
		int		_Type = 0;
		float	_Time;
		bool	_DageSwitch = false;
		Vector3 _Pos;
	};
}