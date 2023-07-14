#pragma once
#include "JKEngine.h"


namespace jk
{
	class Entity
	{
	public:
		Entity();
		virtual	~Entity();

		void SetName(const std::wstring& name) { mName = name; }
		std::wstring& GetName() { return mName; }
		void SetID(UINT64 id) { mColliderID = id; }
		UINT64 GetID() { return mColliderID; }

	private:
		std::wstring mName;
		UINT64 mColliderID;
	};

}


