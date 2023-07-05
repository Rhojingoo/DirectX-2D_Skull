#pragma once
#include "jkGameObject.h"
//#include "jkImage.h"

namespace jk
{
	class Tile : public GameObject
	{
	public:
		Tile();
		Tile(Vector2 pos);
		~Tile();

		//void InitializeTile(Image* atlas, int index);
		void SetIndex(int index);

		virtual void Update() override;
		virtual void Render() override;

	private:
		//Image* mAtlas;
		int mIndex;
		int mX;
		int mY;
	};
}