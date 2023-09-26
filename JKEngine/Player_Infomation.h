#pragma once
#include "Include_Common.h"

namespace jk
{
	class Player_Infomation : public GameObject
	{
	public:
		enum class PlayerList
		{
			basic_Skul,
			wolf_Skul,
			spere_Skul,
			sowrd_Skul,
			thief_Skul,
			head,
		};

		Player_Infomation();
		virtual ~Player_Infomation();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	public:	
		static void SetPlay_List(PlayerList set){Current_player = set;}
		static PlayerList GetPlay_List() { return	Current_player; }
		static PlayerList Current_player;

	public:
		static void Set_player_HP(PlayerList set) { Current_player = set; }
		static float Get_player_HP() { return Current_player_HP; }
		static float Current_player_HP;
	};
}