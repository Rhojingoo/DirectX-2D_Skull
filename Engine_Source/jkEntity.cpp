#include "jkEntity.h"


namespace jk
{
	Entity::Entity()
		: mName(L"")
		, mColliderID((UINT64)this)
	{
	}

	Entity::~Entity()
	{
	}


}