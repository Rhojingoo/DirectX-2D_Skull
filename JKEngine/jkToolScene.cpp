#include "jkToolScene.h"


namespace jk
{
    ToolScene::ToolScene()
    {
    }
    ToolScene::~ToolScene()
    {
    }
    void ToolScene::Initialize()
    {
    }
    void ToolScene::Update()
    {
        Scene::Update();
    }
    void ToolScene::LateUpdate()
    {
        Scene::LateUpdate();
    }
    void ToolScene::Render()
    {
        Scene::Render();
    }
}


LRESULT CALLBACK ToolWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        switch (wmId)
        {

            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}