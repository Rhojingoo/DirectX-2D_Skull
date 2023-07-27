
#pragma once
#include "Include_Common.h"


namespace jk
{
	class Tile_background : public BG
	{
	public:
		Tile_background();
		virtual ~Tile_background();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}