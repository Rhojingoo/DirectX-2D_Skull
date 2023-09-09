#pragma once
#include "Include_Common.h"
#include "Door.h"

namespace jk
{
	class Stage_end_table : public Door
	{
	public:
		Stage_end_table();
		virtual ~Stage_end_table();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class End_Table_State
		{
			Stage1_EnD_Table,
			Stage2_EnD_Table,
			Stage1_EnD_Choice_Table,
			Stage2_EnD_Choice_Table,

		};

		void Set_End_Table(int SET) { _Stage_Table = SET; }
		void Set_Table_Allow(bool SET) { _Set_Table_Allow = SET; }

	private:
		void EnD_Table();
		void EnD_Choice_Table();



	private:
		End_Table_State _State = {};
		Animator* at = nullptr;
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		int _Stage_Table = 0;
		bool _Set_Table_Allow = false;
	};
}