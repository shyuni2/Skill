#include "SWindow.h"

RECT g_rtClient;
HWND g_hWnd;
SWindow* g_pWindow = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    g_pWindow->MsgProc(hWnd, msg, wParam, lParam);
    switch (msg)
    {
    case WM_SIZE: // 윈도우 크기 메세지
    {
        UINT iWidth = LOWORD(lParam);
        UINT iHeight = HIWORD(lParam);
        g_pWindow->ResizeDevice(iWidth, iHeight);
    }break;
    case WM_DESTROY: // 윈도우 종료 메세지
    {
        PostQuitMessage(0);
    }break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

// -- 1. 윈도우 클래스 등록, 허가
BOOL SWindow::SetWinClass(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
    WNDCLASSW wc;
    ZeroMemory(&wc, sizeof(WNDCLASSW));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"Sample"; 
    wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
    if (RegisterClass(&wc) == false)
    {
        return FALSE;
    }
    return TRUE;
}
// -- 2. 윈도우 생성
BOOL SWindow::SetWindow(const WCHAR* szTitle, int iClientWidth, int iClientHeight)
{
    RECT rt = { 0,0, iClientWidth , iClientHeight };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
   

    m_hWnd = CreateWindow(L"Sample", szTitle, WS_OVERLAPPEDWINDOW, 0, 0, rt.right - rt.left, rt.bottom - rt.top, NULL, NULL, m_hInstance, NULL); // 클래스 등록할때랑 이름이 같아야함
    if (m_hWnd == NULL)
    {
        return FALSE;
    }
    g_hWnd = m_hWnd;
    GetClientRect(m_hWnd, &m_rtClient);
    GetWindowRect(m_hWnd, &m_rtWindow);
    g_rtClient = m_rtClient;

    ShowWindow(m_hWnd, SW_SHOW);
    return TRUE;
}
// -- 3. 윈도우 실행
bool SWindow::WinRun()
{
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))  // 메세지큐에 메세지가 없으면 블록
    {
        if (msg.message == WM_QUIT)
        {
            return false;
        }
        TranslateMessage(&msg);// 메세지 번역
        DispatchMessage(&msg);// 윈도우프로시져 호출
    }
    return true;
}


void SWindow::ResizeDevice(UINT iWidth, UINT iHeight)
{

}
LRESULT SWindow::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}


SWindow::SWindow()
{
    g_pWindow = this;
}
SWindow::~SWindow()
{

}
