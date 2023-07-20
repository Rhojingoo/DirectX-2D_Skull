#pragma once
#include "Include_Common.h"


namespace jk
{
	class Back_GR_1_1 : public BG
	{
	public:
		Back_GR_1_1();
		virtual ~Back_GR_1_1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


	};

}