#pragma once
#include "Include_Common.h"

namespace jk
{
	class Mini_Boss : public GameObject
	{
	public:
		Mini_Boss();
		virtual ~Mini_Boss();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		enum class MinibossList
		{
			knight,	
			archer,
			mage,
		};

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		static void SetPlayer(GameObject* set) { _player = set; }
		GameObject* Getplayer() { return _player; }
		static void SetPlayerPos(Vector3 set) { _playerpos = set; }
		static Vector3 GetPlayerPos() { return _playerpos; }
		static Vector3 _playerpos; //= Vector3(0.f, 0.f, 0.f);

	private : 
		static GameObject* _player;	
		static MinibossList miniboss_select;
		//static PlayerList player_check;
		MinibossList _mboss;
		int _minibosschoice = 0;

		static Vector3 _Pos;
		GameObject* _Gobjs[1];
		//static bool _check_change;
		//static int mDir;	


	};
}