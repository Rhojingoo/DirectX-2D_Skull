#pragma once
#include "jkGameObject.h"
#include "jkImage.h"

namespace jk
{
	class Tile : public GameObject
	{
	public:
		Tile();
		Tile(Vector2 pos);
		~Tile();

		void InitializeTile(std::shared_ptr<Image> atlas, int index);
		void SetIndex(int index);

		virtual void Update() override;
		virtual void Render() override;

		UINT Y() { return mY; }
		UINT X() { return mX; }
		UINT Index() { return mIndex; }


		void BindConstantBuffer(UINT X, UINT Y);

		/*virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);*/



	private:
		std::shared_ptr<Image> mAtlas;
		UINT mIndex;
		UINT mX;
		UINT mY;
	};

}
