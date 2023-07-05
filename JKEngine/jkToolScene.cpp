#include "jkToolScene.h"
#include <jkApplication.h>


extern jk::Application application;

namespace jk
{
    ToolScene::ToolScene()
    {
    }
    ToolScene::~ToolScene()
    {
    }
    void ToolScene::Initialize(HWND hWnd)
    {
        
        //jk::Image* tile = jk::Resources::Find<ya::Image>(L"TileAtlas");
        //Tile* test = object::Instantiate<Tile>(eLayerType::Tile);
        //test->InitializeTile(tile, 0);

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
        //HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
        //HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

        //int maxRow = application.GetHeight() / TILE_SIZE_Y + 1;
        //for (size_t y = 0; y < maxRow; y++)
        //{
        //    MoveToEx(hdc, 0, TILE_SIZE_Y * y, NULL);
        //    LineTo(hdc, application.GetWidth(), TILE_SIZE_Y * y);
        //}
        //int maxColumn = application.GetWidth() / TILE_SIZE_X + 1;
        //for (size_t x = 0; x < maxColumn; x++)
        //{
        //    MoveToEx(hdc, TILE_SIZE_X * x, 0, NULL);
        //    LineTo(hdc, TILE_SIZE_X * x, application.GetHeight());
        //}
        //(HPEN)SelectObject(hdc, oldPen);
        //DeleteObject(redPen);

        Scene::Render();
    }
}


LRESULT CALLBACK ToolWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    //case WM_CREATE:
    //{
    //    //512 384
    //    //HMENU mMenubar = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_CLIENT));
    //    //SetMenu(hWnd, mMenubar);
    //    //ya::Image* tile = ya::Resources::Load<ya::Image>(L"TileAtlas", L"..\\Resources\\Tile.bmp");
    //    RECT rect = { 0, 0, tile->GetWidth(), tile->GetHeight() };
    //    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

    //    // 윈도우 크기 변경및 출력 설정
    //    SetWindowPos(hWnd
    //        , nullptr, 1600, 0
    //        , rect.right - rect.left
    //        , rect.bottom - rect.top
    //        , 0);
    //    ShowWindow(hWnd, true);
    //}
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