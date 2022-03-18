#include "TWindow.h"

// 윈도우는 메세지 기반 처리
// 운영체제-> 메세지 전달 (통지) : 메세지 큐 저장-> WndProc 호출
// 운영체제-> 메세지 전달 (통지)-> WndProc 호출 , 메세지에 따라 다름
// 윈도우의 각종 메세지 처리 함수 루틴

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) // 클래스 멤버로 하고싶으면 static
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

BOOL TWindow::WinRegisterClass(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
    // 1, 윈도우 클래스 등록, 허가(운영체제) 
    WNDCLASSW wc; // (WNDCLASSW 정의로 이동해서 하위 텍스트 가져옴 아래에 있는건 필수적요소) , 반드시 f12눌러서 정의 확인하기
    ZeroMemory(&wc, sizeof(WNDCLASSW)); // memset(&wc, 0, sizeof(WNDCLASSW));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc; // lp = 포인터 fn = 함수 , LRESULT 함수 규격에 맞아야함
    wc.hInstance = hInstance; // 운영체제 번호
    wc.lpszClassName = L"KGCA_Window"; // 운영체제 이름 등록
    if (RegisterClass(&wc) == false)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL TWindow::SetWindow(const WCHAR* szTitle,int iClientWidth,int iClientHeight)
{
    RECT rt = { 0,0, iClientWidth , iClientHeight };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
    // 2, 윈도우 생성
    m_hWnd = CreateWindow(
        L"KGCA_Window", // 위에 윈도우 이름과 다르면 안됨
        szTitle,
        WS_OVERLAPPEDWINDOW,
        0, 0, // 위치
        rt.right - rt.left, // 크기
        rt.bottom - rt.top,
        NULL,
        NULL,
        m_hInstance,
        NULL);
    if (m_hWnd == NULL)
    {
        return FALSE;
    }
    GetClientRect(m_hWnd, &m_rtClient);
    GetWindowRect(m_hWnd, &m_rtWindow);

    ShowWindow(m_hWnd, SW_SHOW);
    return TRUE;
}

bool TWindow::WinRun()
{
    MSG msg;

    // 기본 메세지 루프입니다
    //while (GetMessage(&msg, nullptr, 0, 0))
    //{
    //    TranslateMessage(&msg);
    //    DispatchMessage(&msg); // WndProc(윈도우 프로시져) 호출 
    //}

    //return 1;

    while (1)
    {
        // 메세지 큐에 메세지가 없으면 블록
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&msg); // 메세지 번역
            DispatchMessage(&msg); // 윈도우 프로시져
        }
        else
        {
            // 게임로직 호출
            static int count = 0;
            count++;
        }
    }
    return false;
}
