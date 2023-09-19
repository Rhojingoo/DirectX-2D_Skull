#pragma once
#include "Include_Common.h"

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

		//enum class MonsterList
		//{
		//	Ice_wizard,
		//	Monster_Hammer,
		//	Monster_warrior,
		//	Monster_BigEnt,
		//	Monster_GreenTree,
		//	Monster_BlossomEnt,
		//	Monster_Goldwarrior,
		//	Monster_GoldHammer,
		//};
		//void Set_Monster_Type(MonsterList type);


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
		//static MonsterList monster_select;
		//MonsterList _monster;

		static Vector3 _Pos;
		GameObject* _Gobjs[1];
	};
}