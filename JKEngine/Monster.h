#pragma once
#include "..\\Engine_SOURCE\\jkGameObject.h"

namespace jk
{
	class Monster : public GameObject
	{
	public:
		Monster();
		virtual ~Monster();

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
		static Vector3 _playerGRpos;
		static bool _player_groundcheck;
		bool _Die = false;


	private:
		static GameObject* _player;
		static Vector3 _Pos;
		GameObject* _Gobjs[1];
	};
}