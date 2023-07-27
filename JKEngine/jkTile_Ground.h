
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
	};

}