#pragma once
#include "Include_Common.h"


namespace jk
{
	class Alpha_Blend : public GameObject
	{
	public:
		Alpha_Blend();
		virtual ~Alpha_Blend();

		virtual void Initialize()	override;
		virtual void Update()		override;
		virtual void LateUpdate()	override;
		virtual void Render()		override;

		void BindConstantBuffer();

		enum class Alpha_Blend_State
		{
			FadeIn_White_Transparent = 0,
			FadeIn_DeepWhite,
			FadeIn_Black_Transparent,
			FadeIn_DeepBlack,	
			FadeOut,
			End,
		};	

		void FadeIn_White_Transparent();
		void FadeIn_DeepWhite();
		void FadeIn_Black_Transparent();
		void FadeIn_DeepBlack();
		void FadeOut();	

		void Set_White_Transparent() { _State = Alpha_Blend_State::FadeIn_White_Transparent, mTime = 0, _Time = 0, _FadeCheck = false; };
		void Set_DeepWhite() { _State = Alpha_Blend_State::FadeIn_DeepWhite, mTime = 0, _Time = 3, _FadeCheck = false; };
		void Set_Black_Transparent() { _State = Alpha_Blend_State::FadeIn_Black_Transparent, mTime = 1, _Time = 0, _FadeCheck = false; };
		void Set_DeepBlack() { _State = Alpha_Blend_State::FadeIn_DeepBlack, mTime = 1, _Time = 3, _FadeCheck = false; };

		void Set_FadeCheck(bool set) { _FadeCheck = set; }
		bool Get_FadeCheck() { return _FadeCheck; }

	private:
		Alpha_Blend_State _State = {};
		Transform* _tr = nullptr;

		float mTime = 0.f;
		float _Time = 0.f;
		static bool _FadeCheck;

		Vector4 mFadeInStartColor = Vector4();
		Vector4 mFadeInEndColor = Vector4();
		Vector4 mFadeOutStartColor = Vector4();
		Vector4 mFadeOutEndColor = Vector4();
		Vector4 mCurrentColor = Vector4();
	};
}