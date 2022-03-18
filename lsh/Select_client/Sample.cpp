#include "Sample.h"

LRESULT Sample::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(lParam))
		{
		case 200: // 입력버튼 200
		{
			char buffer[MAX_PATH] = { 0, };
			// 유니코드 때문에 A붙임
			SendMessageA(m_hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)buffer);
			TPacket tPacket(PACKET_CHAT_MSG);
			tPacket << 999 << "홍길동" << (short)50 << buffer;
			m_Net.SendMsg(m_Net.m_Sock, tPacket.m_uPacket);
		}break;
		}
	}break;
	}
	return m_Net.MsgProc(hWnd, msg, wParam, lParam);
}
/*
 Window Styles 정의

#define WS_OVERLAPPED       0x00000000L //디폴트 윈도우
#define WS_POPUP            0x80000000L  // 팝업 윈도우를 만든다. WS_CHILD와 함께 쓸수 없다.
#define WS_CHILD            0x40000000L  //차일드 윈도우를 만든다. WS_POPUP와 함께 쓸 수 없다.
#define WS_MINIMIZE         0x20000000L  //최초 최소화된 상태로 윈도우를 만든다.
#define WS_VISIBLE          0x10000000L  //윈도우를 만들자 마자 화면에 출력한다.
#define WS_DISABLED         0x08000000L  // 사용금지된 상태, 즉 입력을 받아들일 수 없는 상태로 만든다.
#define WS_CLIPSIBLINGS     0x04000000L //차일드끼리 상호 겹친 영역은 그리기 영역에서 제외된다.
#define WS_CLIPCHILDREN     0x02000000L //차일드가 위치한 영역은 그리기 영역에서 제외된다.
#define WS_MAXIMIZE         0x01000000L  // 최초 최대화된 ㅏㅇ태로 윈도우를 만든다.
#define WS_CAPTION          0x00C00000L  // WS_BORDER | WS_DLGFRAME   // 타이틀 바를 가진 윈도우를 만들며 WS_BORDER 스타일을 포함한다.
#define WS_BORDER           0x00800000L  // 단선으로 된 경계선을 만들며 크기 조정은 할 수 없다.
#define WS_DLGFRAME         0x00400000L // 두꺼운 경계선을 가지며 타이틀 바를 가질 수 없다.
#define WS_VSCROLL          0x00200000L  // 수직 스크롤 바를 가진 윈도우를 만든다.
#define WS_HSCROLL          0x00100000L  // 수평 스크롤 바를 가진 윈도우를 만든다.
#define WS_SYSMENU          0x00080000L // 시스템 메뉴를 가진 윈도우를 만든다.
#define WS_THICKFRAME       0x00040000L // 크기 조정 가능한 두꺼운 경계선을 가진다.
#define WS_GROUP            0x00020000L  // 라디오 버튼 등 그룹을 이루는 컨트롤의 그룹 지정에 사용된다.
#define WS_TABSTOP          0x00010000L // Tab키로 포커스를 이동할 수 있다.

#define WS_MINIMIZEBOX      0x00020000L // 최소화 버튼을 만든다.
#define WS_MAXIMIZEBOX      0x00010000L // 최대화 버튼을 만든다.
*/

/*
Edit Style 정의

#define ES_LEFT : EditBox에서 입력받을 위치를 왼쪽으로 지정함
#define ES_RIGHT : EditBox에서 입력받을 위치를 오른쪽으로 지정함
#define ES_CENTER : EditBox에서 입력받을 위치를 가운데로 지정함
#define ES_MULTILINE (ES_AUTOVSCROLL, ES_AUTOHSCROLL) : 여러줄을 사용받겠다는 것이며 라인이 넘어 갈때 표시 화면 이상으로 넘어 갔을경우 AUTOVSCROLL 이나 AUTOHSCROLL 과 같이 사용
#define ES_NUMBER : 숫자만 입력 가능하도록 하는 스타일
#define ES_WANTRETURN : EditBox에서 엔터키가 가능하도록 하는것
#define ES_PASSWORD : 암호 입력창에서 ****** 로 표시 되는것을 의미
*/

bool Sample::Init() // 초기화
{	
	// CreateWindow(문자열이면 윈도우 클래스명으로 정의해야함, 윈도우에 표시될 내용, 
	//	윈도우를 생성할때 지정하는 스타일, 윈도우 생성할 x좌표,  윈도우 생성할 y좌표, 윈도우의 너비, 윈도우의 높이, 
	//	생성될 이 윈도우를 가질 부모의 핸들, 메뉴핸들, 윈도우를 생성할 인스턴스 핸들, 사용하지않을경우 NULL);

	// 윈도우에 출력될 화면을 설정함
	DWORD style = WS_CHILD | WS_VISIBLE | ES_MULTILINE; // 차일드 윈도우,윈도우 만들자마자 화면에 출력, 여러줄을 사용 받겠다
	m_hEdit = CreateWindow(L"edit", NULL, style, 0, g_rtClient.bottom - 50, 300, 50, m_hWnd, (HMENU)100, m_hInstance, NULL);
	style = WS_CHILD | WS_VISIBLE;
	m_hButton = CreateWindow(L"button", L"전송", style, 310, g_rtClient.bottom - 50, 50, 50, m_hWnd, (HMENU)200, m_hInstance, NULL); // 전송버튼 200번
	m_hListBox = CreateWindow(L"listbox", NULL, style, 0, 0, 300, g_rtClient.bottom - 70, m_hWnd, (HMENU)300, m_hInstance, NULL);

	// 채팅창에 접속하면 바로 출력할 내용
	SendMessageA(m_hListBox, LB_ADDSTRING, 0, (LPARAM)"채팅시작");

	m_Net.InitNetwork();
	// ASyncselect를 사용하기 때문에 핸들이 필요함 다른데선 필요 x
	m_Net.Connect(g_hWnd, SOCK_STREAM, 10000, "192.168.0.117"); 

	return true;
}	
bool Sample::Frame() // 채팅창 지우고 뿌리고하는 작업이 필요함 ex 채팅이 10개이상이면 위에꺼 지워주는 작업필요
{
	if (m_Net.m_PlayerUser.m_packetPool.size() > 0)
	{
		list<TPacket>::iterator iter;
		// 채팅이 20개 이상이면 위에부터 지워주는 작업
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