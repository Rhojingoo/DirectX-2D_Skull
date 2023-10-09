
#pragma once
#include "Include_Common.h"


namespace jk
{
	class Tile_Ground : public BG
	{
	public:
		Tile_Ground();
		virtual ~Tile_Ground();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void CreateAnimation() {};

		void Set_StageTurn(bool set) { _StageTurn = set; }
		bool Get_Turnon() { return _turnon; }

		bool _SkullOn = false;
		bool _StageTurn = false;
		bool _turnon = false;

	private:
		Collider2D* _collider = nullptr;
		Transform* tr = nullptr;
		Vector3 pos = Vector3(0.f, 0.f, 0.f);

	

	};

}