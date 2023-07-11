#pragma once
#include "CommonInclude.h"
#include "JKEngine.h"
#include "guiWidget.h"
#include "guiEditorObject.h"
#include "DebugOjbect.h"
#include "jkGraphics.h"

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
