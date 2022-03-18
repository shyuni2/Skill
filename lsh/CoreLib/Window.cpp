#include "Window.h"

RECT g_rtClient;
HWND g_hWnd;
Window* g_pWindow = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    g_pWindow->MsgProc(hWnd, msg, wParam, lParam);
    switch (msg)
    {
    case WM_SIZE:
    {
        UINT iWidth = LOWORD(lParam);
        UINT iHeight = HIWORD(lParam);
        g_pWindow->ResizeDevice(iWidth, iHeight);
    }break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}
void Window::ResizeDevice(UINT iWidth, UINT iHeight)
{
}
LRESULT Window::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}
BOOL Window::SetWinClass(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
    // 1. ������ Ŭ���� ��� & �㰡
    WNDCLASSW wc;
    ZeroMemory(&wc, sizeof(WNDCLASSW));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"lsh";
    wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
    if (RegisterClass(&wc) == false)
    {
        return FALSE;
    }

    return TRUE;
}

BOOL Window::SetWindow(const WCHAR* szTitle, int iClientWidth, int iClientHeight)
{
    RECT rt = { 0,0, iClientWidth , iClientHeight };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
    // 2. ������ ����
    m_hWnd = CreateWindow(L"lsh", szTitle, WS_OVERLAPPEDWINDOW, 0, 0, 1920, 1080, NULL, NULL, m_hInstance, NULL);
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

bool Window::WinRun()
{
    MSG msg;
    // �޼���ť�� �޼����� ������ ���
    while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            return false;
        }
        TranslateMessage(&msg);// �޼��� ����
        DispatchMessage(&msg);// ���������ν��� ȣ��
    }
    return true;
}

Window::Window()
{
    g_pWindow = this;
}
Window::~Window()
{

}
