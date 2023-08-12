#pragma once
#include "Include_Common.h"
#include "Layana_Sisters.h"

namespace jk
{
	class Layana_ShortHair : public Layana_Sisters
	{
	public:
		Layana_ShortHair();
		virtual ~Layana_ShortHair();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void idle();
		void die();

		static void SetPlayerPos(Vector3 set) { _playerpos = set; }
		static Vector3 GetPlayerPos() { return _playerpos; }
		static void SetPos(Vector3 set) { _pos = set; }
		static Vector3 GetPos() { return _pos; }
		static void SetRotation(Vector3 set) { _Rotation = set; }
		static Vector3 GetRotations() { return _Rotation; }
		Vector3	_Playerdistance = Vector3(0.f, 0.f, 0.f);
		static int	mDir;
		static float _time;


	private:
		GameObject* _Gobjs[5];
		static Vector3 _pos;
		static Vector3 _Rotation;
		float _attackatime = 0.f;
		int test = 0;

	};
}