#include "jkEntity.h"


namespace jk
{
	Entity::Entity()
		: mName(L"")
		, mID((UINT64)this)
	{
	}

	Entity::~Entity()
	{
	}


}