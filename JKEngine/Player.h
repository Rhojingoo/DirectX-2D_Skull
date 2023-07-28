#pragma once
#include "Include_Common.h"

namespace jk
{	
	class Player : public GameObject
	{
	public:
		enum class PlayerList
		{
			basic_Skul,
			wolf_Skul,
			spere_Skul,
			head,
		};

		Player();
		virtual ~Player();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;		

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;
	
	public:
		virtual Vector3 GetPlayer_Pos() { return _Pos; }
		virtual void SetPlayer_Pos(Vector3 pos) { _Pos = pos; }
		static void SetPlay_List(PlayerList change, PlayerList current, bool ckeck, int direction) 
		{ player_select = change, player_check = current, _check_change = ckeck, mDir = direction; }
		static void Setskillcheck(bool check_head) {_skulhead_check = check_head;}

	private:
		static PlayerList player_select;
		static PlayerList player_check;
		static Vector3 _Pos; 
		GameObject* _Gobjs[4];
		static bool _check_change;
		static int mDir;
		static bool _skulhead_check;
	};
}