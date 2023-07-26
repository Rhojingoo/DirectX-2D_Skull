#pragma once
#include "Include_Common.h"
#include "..\\Engine_SOURCE\\jkGameObject.h"

namespace jk
{
	class Tile : public BG
	{
	public:
		Tile();
		~Tile();

		void Initialize()override;
		virtual void Update() override;
		virtual void Render() override;


	private:

	};

}
