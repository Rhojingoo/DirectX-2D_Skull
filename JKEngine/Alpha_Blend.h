#pragma once

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

		void Set_White_Transparent() { _State = Alpha_Blend_State::FadeIn_White_Transparent, _Time = 0, _Time2 = 0, _Colorcheck=0, _FadeCheck = false; };
		void Set_DeepWhite() { _State = Alpha_Blend_State::FadeIn_DeepWhite, _Time = 0, _Time2 = 3, _Colorcheck = 0, _FadeCheck = false; };
		void Set_Black_Transparent() { _State = Alpha_Blend_State::FadeIn_Black_Transparent, _Time = 1, _Time2 = 0, _Colorcheck = 1, _FadeCheck = false; };
		void Set_DeepBlack() { _State = Alpha_Blend_State::FadeIn_DeepBlack, _Time = 1, _Time2 = 3, _Colorcheck = 1, _FadeCheck = false; };

		void Set_FadeCheck(bool set) { _FadeCheck = set; }
		bool Get_FadeCheck() { return _FadeCheck; }

	private:
		Alpha_Blend_State _State = {};
		Transform* _tr = nullptr;

		float _Time = 0.f;
		float _Time2 = 0.f;
		float _Colorcheck = 0.f;
		static bool _FadeCheck;

		class Vector4 _FadeInStartColor = Vector4();
		class Vector4 _FadeInEndColor = Vector4();
		class Vector4 _FadeOutStartColor = Vector4();
		class Vector4 _FadeOutEndColor = Vector4();
		class Vector4 _CurrentColor = Vector4();
	};
}