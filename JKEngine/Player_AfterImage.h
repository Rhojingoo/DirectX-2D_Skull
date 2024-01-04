#pragma once
#include "jkGameObject.h"


namespace jk
{
	class Player_AfterImage :  public GameObject
	{
	public:
		Player_AfterImage();
		virtual ~Player_AfterImage();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void BindConstantBuffer();
		void Set_Owner(Player* set) { mOwner = set; }
		void Set_AfterImage_Switch(bool set) { _AfterImage = set; }

		enum class AfterImage_State
		{
			Skul_Basic = 0,
			Skul_NoHead,
			Skul_Wolf,
			Skul_Spear,
			Finish_Image,
			End,
		};	

		void Skul_Basic();
		void Skul_NoHead();
		void Skul_Wolf();
		void Skul_Spear();
		void Finish_Image();


		void Set_Basic_Dash(int Dir, Vector3 position) { _State = AfterImage_State::Skul_Basic, _Dir = Dir, _Pos = position; };
		void Set_Nohead_Dash(int Dir, Vector3 position) { _State = AfterImage_State::Skul_NoHead, _Dir = Dir, _Pos = position; }
		void Set_Wolf_Dash(int Dir, Vector3 position) { _State = AfterImage_State::Skul_Wolf, _Dir = Dir, _Pos = position; }
		void Set_Spear_Dash(int Dir, Vector3 position) { _State = AfterImage_State::Skul_Spear, _Dir = Dir, _Pos = position; }

		bool _AfterImage = false;

	private:
		class Player* mOwner = nullptr;
		Transform* PlayerTr = nullptr;
		AfterImage_State _State = {};
		int _Dir = 1;
		Vector3 _Pos = Vector3();


		bool _AfterImage_Late = false;
		bool _AfterImage_Render = false;
		float mTime = 1.f;
		float _Time = 0.f;

		float timeSinceLastImage = 0.0f;  // 마지막 잔상 생성 후 경과 시간
		const float delayBetweenImages = 0.3f;


	
	private://첨에 오브젝트로 진행하려할때의 변수들
		std::shared_ptr<Material> mMaterial;
		class Animator* mAnimator;
		class Animator* at = nullptr;
		class Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		static bool _FadeCheck;
	};
}