#pragma once
#include "Include_Common.h"


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
	};

}