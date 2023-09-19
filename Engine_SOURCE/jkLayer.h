#pragma once
#include "jkGameObject.h"

namespace jk
{
	class Layer
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destory();

		void AddGameObject(GameObject* gameObj);
		void AddMonsterObject(GameObject* gameObj);
		void ReturnMonster(GameObject* monster);

		const std::vector<GameObject*> GetGameObjects()
		{
			return mGameObjects;
		}

	private:
		std::vector<GameObject*> mGameObjects;
		std::vector<GameObject*> mMonsterObjects;
	};
}
