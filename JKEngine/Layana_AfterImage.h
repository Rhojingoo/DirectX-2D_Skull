#pragma once
#include "..\Engine_SOURCE\jkGameObject.h"



namespace jk
{

	class Layana_AfterImage : public GameObject
	{
	public:
		Layana_AfterImage();
		virtual ~Layana_AfterImage();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void BindConstantBuffer();
		void Set_Owner(Layana_Sisters* set) { mOwner = set; }
		void Set_AfterImage_Switch(bool set) { _AfterImage = set; }
		
		
		enum class LayanaAfterImage_State
		{
			MeterorCross = 0,
			Finish_Image,
			End,
		};

		void Set_Basic_Dash(int Dir, Vector3 position) { _State = LayanaAfterImage_State::MeterorCross, _Dir = Dir, _Pos = position; };

		bool _AfterImage = false;
		void MeterorCross();
		void Finish_Image();

	private:
		class Layana_Sisters* mOwner = nullptr;
		Transform* PlayerTr = nullptr;
		LayanaAfterImage_State _State = {};
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