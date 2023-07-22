#pragma once
#include "Include_Common.h"

namespace jk
{
	class Decil_chair : public BG
	{
	public:	
		Decil_chair();
		virtual ~Decil_chair();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;			
	};
}