#pragma once
#include "Include_Common.h"

namespace jk
{
	class Boss : public GameObject
	{
	public:
		Boss();
		virtual ~Boss();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		static void SetPlayer(GameObject* set) { _player = set; }
		GameObject* Getplayer() { return _player; }
		static void SetPlayerPos(Vector3 set) { _playerpos = set; }
		static Vector3 GetPlayerPos() { return _playerpos; }
		static Vector3 _playerpos;

	private:
		static GameObject* _player;
		static Vector3 _Pos;
	};
}