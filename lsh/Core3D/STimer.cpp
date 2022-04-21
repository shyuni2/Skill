#include "STimer.h"

float g_fSecPerFrame = 0.0f;
float g_fGameTimer = 0.0f;

bool STimer::Init()
{
    m_fSecondPerFrame = 0.0f;
    m_fTimer = 0.0f;
    m_dwBeforeTime = timeGetTime();
    return false;
}
bool STimer::Frame()
{
    DWORD dwCurrentTime = timeGetTime(); // ����ð� ����
    DWORD dwElapseTime = dwCurrentTime - m_dwBeforeTime; // ����ð� = ����ð� - �� �ð�
    m_fSecondPerFrame = min(0.1f, dwElapseTime / 1000.0f);
    
    m_fTimer += m_fSecondPerFrame;

    g_fSecPerFrame = m_fSecondPerFrame;
    g_fGameTimer = m_fTimer;

    m_fFPSTimer += m_fSecondPerFrame;
    if (m_fFPSTimer >= 1.0f)
    {
        m_iFPS = m_iFPSCounter;
        m_iFPSCounter = 0;
        m_fFPSTimer -= 1.0f;
    }
    m_iFPSCounter++;

    m_dwBeforeTime = dwCurrentTime;
    return false;
}

bool STimer::Render()
{
    return false;
}

bool STimer::Release()
{
    return false;
}
