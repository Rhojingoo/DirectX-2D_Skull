#pragma once
#include "Effect.h"

namespace jk
{
	class Yggdrasil_BoddyDead_Effect : public Effect
	{
	public:
		Yggdrasil_BoddyDead_Effect();
		virtual ~Yggdrasil_BoddyDead_Effect();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


		enum class Alpha_Effect_State
		{
			AlphaEffect_Start = 0,
			AlphaEffect_End,
			End,
		};

		void Set_AlphaEffect_Start() { _State = Alpha_Effect_State::AlphaEffect_Start, mTime = 0, _Time = 1; };

		void BindConstantBuffer();
		void Compelete();

	private:
		Alpha_Effect_State _State = Alpha_Effect_State::AlphaEffect_End;
		class Animator* at = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;

	private:
		void AlphaEffect_Start();
		void AlphaEffect_End();

		float mTime = 0.f;
		float _Time = 1.f;
	};
}