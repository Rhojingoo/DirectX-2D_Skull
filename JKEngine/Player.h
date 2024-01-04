#pragma once
#include "..\\Engine_SOURCE\\jkGameObject.h"
#include "Face_UI.h"
#include "Player_Hp_Bar.h"


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
			sowrd_Skul,
			thief_Skul,
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
		static Vector3 GetPlayer_Pos() { return _Pos; }
		virtual void SetPlayer_Pos(Vector3 pos) { _Pos = pos; }
		static void SetPlay_List(PlayerList change, PlayerList current, bool ckeck, int direction)
		{player_select = change, player_check = current, _check_change = ckeck, mDir = direction;}
		virtual PlayerList GetPlay_List() { return player_select;}
		static void Setskillcheck(bool check_head) {_skulhead_check = check_head;}
		static bool Get_Ground_On() { return _Ground_On; }
		static Vector3 GetPlayer_GRPos() { return _Player_GRpos; }


		static void SettingPlay_List(PlayerList set) { Current_player = set; }
		static PlayerList GetCurrentPlay_List(){return	Current_player;}
		static int GetDirection() { return	mDir; }
		void SetSwitch(bool set = false) { _Switch = set; }


		static Player_Hp_Bar* Get_HP_Bar() {	return Player_Hp;}
		static Player_Hp_Bar* Get_DamageHP_Bar() { return Player_Hp_Damage; }
		void Set_HP_Bar(Player_Hp_Bar* SET) { Player_Hp = SET; }
		void Set_DamageHP_Bar(Player_Hp_Bar* SET) { Player_Hp_Damage = SET; }


		
		Transform* PlayerTR = nullptr;
		static PlayerList player_select;
		static PlayerList player_check;
		static PlayerList Current_player;
		static Vector3 _Pos; 
		static Vector3 _Player_GRpos;
		static bool _Ground_On;
		static bool firstGroundcheck;	
		bool _Switch = false;


	public:
		static bool _skul_act;
		static bool _wolf_act;
		static bool _spear_act;

	private:
		GameObject* _Gobjs[5];
		static bool _check_change;
		static int mDir;
		static bool _skulhead_check;
	


	private:
		class Face_UI* Basic_Face = nullptr;
		class Face_UI* Wolf_Face = nullptr;
		class Face_UI* Spear_Face = nullptr;

	public:
		static Player_Hp_Bar* Player_Hp;
		static Player_Hp_Bar* Player_Hp_Damage;
		static float _Max_Player_Hp;
		static float _Curren_Player_Hp;
	};
}