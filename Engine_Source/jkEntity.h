#pragma once
#include "JKEngine.h"


namespace jk
{
	class Entity
	{
	public:
		Entity();
		virtual	~Entity();

		void SetNmae(const std::wstring& name) { mName = name; }
		std::wstring& GetName() { return mName; }
		void SetID(UINT64 id) { mID = id; }
		UINT64 GetID() { return mID; }


	private:
		std::wstring mName;
		UINT64 mID;
	};

}


