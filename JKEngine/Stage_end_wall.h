#pragma once
#include "Door.h"

namespace jk
{
	class Stage_end_wall : public Door
	{
	public:
		Stage_end_wall();
		virtual ~Stage_end_wall();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class End_Wall_State
		{
			Stage1_EnD_Wall,
			Stage2_EnD_Wall,
		};

		void Set_Wall_Stage(int SET) { _Stage_Wall = SET; }
		void Set_Wall_Allow(bool SET) { _Set_Wall_Allow = SET; }

	private:
		void Stage1_End_Wall();
		void Stage2_End_Wall();


	private:
		End_Wall_State _State = {};
		class Animator* at = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		int _Stage_Wall = 0;
		bool _Set_Wall_Allow = false;
	};
}