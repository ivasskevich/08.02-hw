#include <windows.h>
#include "resource.h"
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Cursor");
HICON hIcon;
HCURSOR hCursor1, hCursor2, hCursor3, hCursor4;
int windowWidth, windowHeight;

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG Msg;
    WNDCLASSEX wcl;
    wcl.cbSize = sizeof(wcl);
    wcl.style = CS_HREDRAW | CS_VREDRAW;
    wcl.lpfnWndProc = WindowProc;
    wcl.cbClsExtra = 0;
    wcl.cbWndExtra = 0;
    wcl.hInstance = hInst;
    wcl.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)); 
    wcl.hCursor = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR5));  
    wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wcl.lpszMenuName = NULL;
    wcl.lpszClassName = szClassWindow;
    wcl.hIconSm = NULL;
    if (!RegisterClassEx(&wcl))
        return 0;

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    windowWidth = screenWidth / 2;
    windowHeight = screenHeight / 2;

    HINSTANCE hInstance = GetModuleHandle(0);
    hCursor1 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
    hCursor2 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));
    hCursor3 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR3));
    hCursor4 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR4));

    hWnd = CreateWindowEx(0, szClassWindow, TEXT("Ints"), WS_OVERLAPPEDWINDOW,
        (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2, windowWidth, windowHeight, NULL, NULL, hInst, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&Msg, NULL, 0, 0))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_MOUSEMOVE:
    {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);

        int quadrant = 0;
        if (pt.x >= 0 && pt.x < windowWidth / 2) {
            if (pt.y >= 0 && pt.y < windowHeight / 2)
                quadrant = 0;
            else
                quadrant = 2;
        }
        else {
            if (pt.y >= 0 && pt.y < windowHeight / 2)
                quadrant = 1;
            else
                quadrant = 3;
        }

        switch (quadrant) {
        case 0:
            SetCursor(hCursor1);
            break;
        case 1:
            SetCursor(hCursor2);
            break;
        case 2:
            SetCursor(hCursor3);
            break;
        case 3:
            SetCursor(hCursor4);
            break;
        }
    }
    break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}