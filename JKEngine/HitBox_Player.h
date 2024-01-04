#pragma once
#include "Attack_HitBox.h"


namespace jk
{
	class HitBox_Player : public Attack_HitBox
	{
	public:
		HitBox_Player();
		virtual ~HitBox_Player();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		int random(int a, int b);
		float GetDamage() { return _Damage; }

		void SetSize(Vector2 set) { _Size = set; }
		void SetCenter(Vector3 set) { _Center = set; }

		bool Geteffect() { return _attack; }
		bool Geteffect_Mid() { return _attack_Cri_Mid; }
		bool Geteffect_Hight() { return _attack_Cri_High; }

		void Seteffect(bool set) { _attack = set; }
		void Seteffect_Mid(bool set) {  _attack_Cri_Mid = set; }
		void Seteffect_Hight(bool set) {  _attack_Cri_High = set; }

	private:
		class Collider2D* _collider = nullptr;
		class AudioSource* as = nullptr;
		Transform* tr = nullptr;
		Vector3 _Pos = Vector3(0.f, 0.f, 0.f);
		int		_HitType = 0;
		float	_Damage = 0.f;
		Vector2 _Size = Vector2(150.f, 150.f);
		Vector3 _Center = Vector3(0.f, 0.f, -250.f);

		bool _attack = false;
		bool _attack_Cri_Mid = false;
		bool _attack_Cri_High = false;
	};
}