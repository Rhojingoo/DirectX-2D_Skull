#pragma once
#include "..\\Engine_SOURCE\\CommonInclude.h"
#include "..\\Engine_SOURCE\\JKEngine.h"
#include "..\\Engine_SOURCE\\jkGraphics.h"
#include "guiWidget.h"
#include "guiEditorObject.h"
#include "DebugOjbect.h"


namespace gui
{
	class Editor
	{
	public:
		static void Initialize();
		static void Run();

		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		static void DebugRender(const jk::graphics::DebugMesh& mesh);

	private:
		static std::vector<Widget*> mWidgets;
		static std::vector<EditorObject*> mEditorObjects;
		static std::vector<DebugOjbect*> mDebugOjbects;
	};
}
