#include "jkToolScene.h"
#include "jkApplication.h"
#include "jkImage.h"
#include "jkResources.h"
#include "jkTexture.h"
//#include "jkTile.h"
//#include "jkObject.h"
#include "jkInput.h"

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

    case WM_CREATE:
    {    
       
        //HMENU mMenubar = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_CLIENT));
        //SetMenu(hWnd, mMenubar);
       // ya::Image* tile = ya::Resources::Load<ya::Image>(L"TileAtlas", L"..\\Resources\\Tile.bmp");
       
        
        RECT rect = { 0, 0, 512, 384 };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

        // 윈도우 크기 변경및 출력 설정
        SetWindowPos(hWnd
            , nullptr, 1600, 0
            , rect.right - rect.left
            , rect.bottom - rect.top
            , 0);
        ShowWindow(hWnd, true);
    }


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

    
        std::shared_ptr<jk::Image> tile = jk::Resources::Load<jk::Image>( L"TileAtlas", L"..\\Resources\\Tile\\Tile.bmp");
        BitBlt(hdc, 0, 0, tile->GetWidth(), tile->GetHeight(), tile->GetHdc(), 0, 0, SRCCOPY);


        //HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        //HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

        //Ellipse(hdc, 0, 0, 100, 100);
        ////RoundRect(hdc, 200, 200, 300, 300, 500, 500);
        //(HPEN)SelectObject(hdc, oldPen);
        //DeleteObject(redPen);


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