#include "jkToolScript.h"


namespace jk
{
	ToolScript::ToolScript()
		:mIndex(-1)
	{
	}
	ToolScript::~ToolScript()
	{
	}
	void ToolScript::Initialize()
	{
	}
	void ToolScript::Update()
	{
		mIndex = TilePalatte::GetIndex();

		if (mIndex < 0)
			return;

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 cursorPos = tr->GetPosition();

			TilePalatte::CreateTile(mIndex, Vector2(cursorPos.x, cursorPos.y));
		}
	}
	void ToolScript::LateUpdate()
	{
	}
	void ToolScript::Render()
	{
	}
}
