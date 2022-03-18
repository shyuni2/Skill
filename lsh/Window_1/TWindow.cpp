#include "TWindow.h"

// ������� �޼��� ��� ó��
// �ü��-> �޼��� ���� (����) : �޼��� ť ����-> WndProc ȣ��
// �ü��-> �޼��� ���� (����)-> WndProc ȣ�� , �޼����� ���� �ٸ�
// �������� ���� �޼��� ó�� �Լ� ��ƾ

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) // Ŭ���� ����� �ϰ������ static
{
    switch (msg)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0); // WM_QUIT 
    }break;
    }
    return DefWindowProc(hWnd, msg, wparam, lparam);
}

// 1. ������ Ŭ���� ���, �㰡(�ü��) 
BOOL TWindow::WinRegisterClass(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
    
    WNDCLASSW wc; // (WNDCLASSW ���Ƿ� �̵��ؼ� ���� �ؽ�Ʈ ������ �Ʒ��� �ִ°� �ʼ������) , �ݵ�� f12������ ���� Ȯ���ϱ�
    ZeroMemory(&wc, sizeof(WNDCLASSW)); // memset(&wc, 0, sizeof(WNDCLASSW));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc; // lp = ������ fn = �Լ� , LRESULT �Լ� �԰ݿ� �¾ƾ���
    wc.hInstance = hInstance; // �ü�� ��ȣ
    wc.lpszClassName = L"KGCA_Window"; // �ü�� �̸� ���
    if (RegisterClass(&wc) == false)
    {
        return FALSE;
    }
    return TRUE;
}

// 2. ������ ����
BOOL TWindow::SetWindow(const WCHAR* szTitle, int iClientWidth, int iClientHeight)
{
    RECT rt = { 0,0, iClientWidth , iClientHeight };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
   
    m_hWnd = CreateWindow
    (
        L"KGCA_Window", // ���� ������ �̸��� �ٸ��� �ȵ�
        szTitle,
        WS_OVERLAPPEDWINDOW,
        0, 0, // ��ġ
        rt.right - rt.left, // ũ��
        rt.bottom - rt.top,
        NULL,
        NULL,
        m_hInstance,
        NULL
    );
    if (m_hWnd == NULL)
    {
        return FALSE;
    }
    GetClientRect(m_hWnd, &m_rtClient);
    GetWindowRect(m_hWnd, &m_rtWindow);

    ShowWindow(m_hWnd, SW_SHOW);
    return TRUE;
}

// ������ ����ɶ�
bool TWindow::WinRun()
{
    MSG msg;
    // �޼��� ť�� �޼����� ������ ���
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            break;
        }
        TranslateMessage(&msg); // �޼��� ����
        DispatchMessage(&msg); // ������ ���ν���
    }
    return true;
}
