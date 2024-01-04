#pragma once
#include "jkGameObject.h"

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
			cleric,
		};

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		static void SetPlayer(GameObject* set) { _player = set; }
		GameObject* Getplayer() { return _player; }
		static void SetPlayerPos(Vector3 set) { _playerpos = set; }
		static Vector3 GetPlayerPos() { return _playerpos; }
		static Vector3 _playerpos; 
		int random(int a, int b);

		static Vector3 Left_Ground;
		static Vector3 Right_Ground;
		bool _Die = false;


	private : 
		static GameObject* _player;	
		static MinibossList miniboss_select;
		MinibossList _mboss;
		int _minibosschoice = 0;
		static Vector3 _Pos;
	};
}