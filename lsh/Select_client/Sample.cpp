#include "Sample.h"

LRESULT Sample::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(lParam))
		{
		case 200: // �Է¹�ư 200
		{
			char buffer[MAX_PATH] = { 0, };
			// �����ڵ� ������ A����
			SendMessageA(m_hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)buffer);
			TPacket tPacket(PACKET_CHAT_MSG);
			tPacket << 999 << "ȫ�浿" << (short)50 << buffer;
			m_Net.SendMsg(m_Net.m_Sock, tPacket.m_uPacket);
		}break;
		}
	}break;
	}
	return m_Net.MsgProc(hWnd, msg, wParam, lParam);
}
/*
 Window Styles ����

#define WS_OVERLAPPED       0x00000000L //����Ʈ ������
#define WS_POPUP            0x80000000L  // �˾� �����츦 �����. WS_CHILD�� �Բ� ���� ����.
#define WS_CHILD            0x40000000L  //���ϵ� �����츦 �����. WS_POPUP�� �Բ� �� �� ����.
#define WS_MINIMIZE         0x20000000L  //���� �ּ�ȭ�� ���·� �����츦 �����.
#define WS_VISIBLE          0x10000000L  //�����츦 ������ ���� ȭ�鿡 ����Ѵ�.
#define WS_DISABLED         0x08000000L  // �������� ����, �� �Է��� �޾Ƶ��� �� ���� ���·� �����.
#define WS_CLIPSIBLINGS     0x04000000L //���ϵ峢�� ��ȣ ��ģ ������ �׸��� �������� ���ܵȴ�.
#define WS_CLIPCHILDREN     0x02000000L //���ϵ尡 ��ġ�� ������ �׸��� �������� ���ܵȴ�.
#define WS_MAXIMIZE         0x01000000L  // ���� �ִ�ȭ�� �����·� �����츦 �����.
#define WS_CAPTION          0x00C00000L  // WS_BORDER | WS_DLGFRAME   // Ÿ��Ʋ �ٸ� ���� �����츦 ����� WS_BORDER ��Ÿ���� �����Ѵ�.
#define WS_BORDER           0x00800000L  // �ܼ����� �� ��輱�� ����� ũ�� ������ �� �� ����.
#define WS_DLGFRAME         0x00400000L // �β��� ��輱�� ������ Ÿ��Ʋ �ٸ� ���� �� ����.
#define WS_VSCROLL          0x00200000L  // ���� ��ũ�� �ٸ� ���� �����츦 �����.
#define WS_HSCROLL          0x00100000L  // ���� ��ũ�� �ٸ� ���� �����츦 �����.
#define WS_SYSMENU          0x00080000L // �ý��� �޴��� ���� �����츦 �����.
#define WS_THICKFRAME       0x00040000L // ũ�� ���� ������ �β��� ��輱�� ������.
#define WS_GROUP            0x00020000L  // ���� ��ư �� �׷��� �̷�� ��Ʈ���� �׷� ������ ���ȴ�.
#define WS_TABSTOP          0x00010000L // TabŰ�� ��Ŀ���� �̵��� �� �ִ�.

#define WS_MINIMIZEBOX      0x00020000L // �ּ�ȭ ��ư�� �����.
#define WS_MAXIMIZEBOX      0x00010000L // �ִ�ȭ ��ư�� �����.
*/

/*
Edit Style ����

#define ES_LEFT : EditBox���� �Է¹��� ��ġ�� �������� ������
#define ES_RIGHT : EditBox���� �Է¹��� ��ġ�� ���������� ������
#define ES_CENTER : EditBox���� �Է¹��� ��ġ�� ����� ������
#define ES_MULTILINE (ES_AUTOVSCROLL, ES_AUTOHSCROLL) : �������� ���ްڴٴ� ���̸� ������ �Ѿ� ���� ǥ�� ȭ�� �̻����� �Ѿ� ������� AUTOVSCROLL �̳� AUTOHSCROLL �� ���� ���
#define ES_NUMBER : ���ڸ� �Է� �����ϵ��� �ϴ� ��Ÿ��
#define ES_WANTRETURN : EditBox���� ����Ű�� �����ϵ��� �ϴ°�
#define ES_PASSWORD : ��ȣ �Է�â���� ****** �� ǥ�� �Ǵ°��� �ǹ�
*/

bool Sample::Init() // �ʱ�ȭ
{	
	// CreateWindow(���ڿ��̸� ������ Ŭ���������� �����ؾ���, �����쿡 ǥ�õ� ����, 
	//	�����츦 �����Ҷ� �����ϴ� ��Ÿ��, ������ ������ x��ǥ,  ������ ������ y��ǥ, �������� �ʺ�, �������� ����, 
	//	������ �� �����츦 ���� �θ��� �ڵ�, �޴��ڵ�, �����츦 ������ �ν��Ͻ� �ڵ�, �������������� NULL);

	// �����쿡 ��µ� ȭ���� ������
	DWORD style = WS_CHILD | WS_VISIBLE | ES_MULTILINE; // ���ϵ� ������,������ �����ڸ��� ȭ�鿡 ���, �������� ��� �ްڴ�
	m_hEdit = CreateWindow(L"edit", NULL, style, 0, g_rtClient.bottom - 50, 300, 50, m_hWnd, (HMENU)100, m_hInstance, NULL);
	style = WS_CHILD | WS_VISIBLE;
	m_hButton = CreateWindow(L"button", L"����", style, 310, g_rtClient.bottom - 50, 50, 50, m_hWnd, (HMENU)200, m_hInstance, NULL); // ���۹�ư 200��
	m_hListBox = CreateWindow(L"listbox", NULL, style, 0, 0, 300, g_rtClient.bottom - 70, m_hWnd, (HMENU)300, m_hInstance, NULL);

	// ä��â�� �����ϸ� �ٷ� ����� ����
	SendMessageA(m_hListBox, LB_ADDSTRING, 0, (LPARAM)"ä�ý���");

	m_Net.InitNetwork();
	// ASyncselect�� ����ϱ� ������ �ڵ��� �ʿ��� �ٸ����� �ʿ� x
	m_Net.Connect(g_hWnd, SOCK_STREAM, 10000, "192.168.0.117"); 

	return true;
}	
bool Sample::Frame() // ä��â ����� �Ѹ����ϴ� �۾��� �ʿ��� ex ä���� 10���̻��̸� ������ �����ִ� �۾��ʿ�
{
	if (m_Net.m_PlayerUser.m_packetPool.size() > 0)
	{
		list<TPacket>::iterator iter;
		// ä���� 20�� �̻��̸� �������� �����ִ� �۾�
		if (m_Net.m_PlayerUser.m_packetPool.size() > 20)
		{
			//m_Net.m_PlayerUser.m_packetPool.pop_front();
		}
		for (iter = m_Net.m_PlayerUser.m_packetPool.begin(); iter != m_Net.m_PlayerUser.m_packetPool.end(); )
		{
			TChatMsg recvdata;
			ZeroMemory(&recvdata, sizeof(recvdata));
			(*iter) >> recvdata.index >> recvdata.name >> recvdata.damage >> recvdata.message;
			SendMessageA(m_hListBox, LB_ADDSTRING, 0, (LPARAM)recvdata.message);
			iter = m_Net.m_PlayerUser.m_packetPool.erase(iter);
		}
	}
	return true;
}	
bool Sample::Render()
{	
	return true;
}	
bool Sample::Release()
{
	m_Net.CloseNetwork();
	return true;
}

Sample::Sample()
{

}
Sample::~Sample()
{

}
RUN();