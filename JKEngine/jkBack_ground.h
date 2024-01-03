#pragma once
#include "BG.h"


namespace jk
{
	class Back_ground : public BG
	{
	public:
		Back_ground(const std::wstring& path);
		virtual ~Back_ground();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	};

}