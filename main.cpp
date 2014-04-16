#pragma comment (lib, "Kinect10.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "winmm.lib")

#include "./openGL/OGLMain.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT hMsg, WPARAM wParam, LPARAM lParam)
{
    if (hMsg == WM_CLOSE)
    {
        DestroyWindow(hWnd);
    }
    else if (hMsg == WM_DESTROY)
    {
        PostQuitMessage(EXIT_SUCCESS);
    }
    else if (hMsg == WM_KEYDOWN && wParam == VK_ESCAPE)
    {
        PostQuitMessage(EXIT_SUCCESS);
    }

    return(DefWindowProc(hWnd, hMsg, wParam, lParam));
}

int WINAPI WinMain(HINSTANCE hActualInst, HINSTANCE hPrevInst, LPSTR cmdLine, int cmdShow)
{
    WNDCLASSEX    wndCls;        memset(&wndCls, 0, sizeof(WNDCLASSEX));
    HWND        hWnd;        memset(&hWnd, 0, sizeof(HWND));
    MSG            hMsg;        memset(&hMsg, 0, sizeof(MSG));

    wndCls.cbSize = sizeof(WNDCLASSEX);
    wndCls.cbClsExtra = 0;
    wndCls.cbWndExtra = 0;

    wndCls.hInstance = hActualInst;
    wndCls.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndCls.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wndCls.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    wndCls.lpfnWndProc = WndProc;
    wndCls.lpszMenuName = NULL;
    wndCls.lpszClassName = L"D3D";

    wndCls.style = 0;
    wndCls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (RegisterClassEx(&wndCls) == 0)
    {
        MessageBox(NULL, L"Window Registration Failed", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return(EXIT_FAILURE);
    }

    hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"D3D", L"Kinect Movement Capture", WS_OVERLAPPEDWINDOW, 0, 0,
        GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        NULL, NULL, hActualInst, NULL);

    if (hWnd == NULL)
    {
        MessageBox(NULL, L"Window Creation Failed", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return(EXIT_FAILURE);
    }

    ShowWindow(hWnd, SW_SHOWMAXIMIZED);
    UpdateWindow(hWnd);

    OGLMain *oGL = new OGLMain(hWnd);
    oGL->initialize();

    while (hMsg.message != WM_QUIT)
    {
        if (PeekMessage(&hMsg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&hMsg);
            DispatchMessage(&hMsg);
        }
        else
        {
            oGL->update();
            oGL->render();
        }
    }

    delete(oGL);
    oGL = NULL;

    UnregisterClass(L"D3D", wndCls.hInstance);
    return(hMsg.wParam);
}
