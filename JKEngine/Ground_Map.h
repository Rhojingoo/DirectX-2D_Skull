#pragma once
#include "Include_Common.h"
#include "Alpha_Blend.h"

namespace jk
{
	class Ground_Map : public BG
	{
	public:
		Ground_Map();
		virtual ~Ground_Map();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void Set_StageTurn(bool set) { _StageTurn = set; }
		bool Get_Turnon() { return _turnon; }

		Collider2D* _collider = nullptr;
		Alpha_Blend* _Alpha = nullptr;
		bool _SkullOn = false;
		bool _StageTurn = false;
		bool _turnon = false;	
	};

}