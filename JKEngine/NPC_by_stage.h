#pragma once
#include "Item_OBJ.h"

namespace jk
{
	class NPC_by_stage : public Item_OBJ
	{
	public:
		NPC_by_stage();
		virtual ~NPC_by_stage();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class NPC_State
		{
			Stage1_Npc,
			Stage2_Npc,
		};

		void Set_End_Table(int SET) { _Stage_Npc = SET; }
		void Set_Table_Allow(bool SET) { _Set_Npc_Allow = SET; }

	private:
		void Stage1_Npc();
		void Stage2_Npc();

	private:
		NPC_State _state = {};
		class Animator* at = nullptr;
		class RigidBody* _rigidbody = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* _tr = nullptr;
		int _Stage_Npc = 0;
		bool _Set_Npc_Allow = false;
	};
}