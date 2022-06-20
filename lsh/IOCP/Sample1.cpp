//#include <Windows.h>
//#include <iostream>
//#define BlockSize (104857600) // 100메가
//#define MAX_WORKER_THREAD 3 //스레드 3개 만들겠다
//
//WCHAR* g_buffer = NULL;
//LARGE_INTEGER filesize;
//OVERLAPPED g_ReadOV = { 0, }; // 이제는 오버랩 구조체를 그냥 쓰면 안됨 상속해서 사용
//OVERLAPPED g_WriteOV = { 0, };
//
//DWORD g_dwCurrentRead; 
//DWORD g_dwCurrentWrite;
//// 오버랩 구조체는 따로 있어야함
//OVERLAPPED g_ReadOVArray[100];
//OVERLAPPED g_WriteOVArray[100];
//
//HANDLE g_hFileRead;
//HANDLE g_hFileWrite;
//HANDLE g_hWorkThread[MAX_WORKER_THREAD];
//
//// 완료포트 관리 객체
//HANDLE g_hIOCP; 
//
//LARGE_INTEGER g_LargeRead;
//LARGE_INTEGER g_LargeWrite;
//
//HANDLE g_hKillEvent; // 이 이벤트가 발동하면 스레드 끝내기
//
//bool DispatchRead(DWORD dwTransfer, OVERLAPPED* ov) // read 끝났으니까 write 해라
//{
//	g_LargeRead.QuadPart += dwTransfer; // 읽은 양 다음부터 읽어라
//
//	++g_dwCurrentWrite;
//	g_WriteOVArray[g_dwCurrentWrite].Offset = g_LargeWrite.LowPart;
//	g_WriteOVArray[g_dwCurrentWrite].OffsetHigh = g_LargeWrite.HighPart;
//
//	DWORD dwWritten;
//	BOOL ret = WriteFile(g_hFileWrite, g_buffer, dwTransfer, &dwWritten, &g_WriteOVArray[g_dwCurrentWrite]);
//	if (ret == FALSE)
//	{
//		if (GetLastError() != ERROR_IO_PENDING) // 펜딩이 돼야 정상
//		{
//			return false;
//		}
//	}
//	return true;
//}
//bool DispatchWrite(DWORD dwTransfer, OVERLAPPED* ov) // write 끝났으니까 read 해라
//{
//	g_LargeWrite.QuadPart += dwTransfer; 
//
//	if (filesize.QuadPart <= g_LargeWrite.QuadPart) // 파일 사이즈만큼 썼으면 끝난거
//	{
//		return true;
//	}
//
//	++g_dwCurrentRead;
//	g_ReadOVArray[g_dwCurrentRead].Offset = g_LargeRead.LowPart;
//	g_ReadOVArray[g_dwCurrentRead].OffsetHigh = g_LargeRead.HighPart;
//
//	DWORD dwRead;
//	BOOL ret = ReadFile(g_hFileRead, g_buffer, dwTransfer, &dwRead, &g_ReadOVArray[g_dwCurrentRead]);
//	if (ret == FALSE)
//	{
//		if (GetLastError() != ERROR_IO_PENDING) // 펜딩이 돼야 정상
//		{
//			return false;
//		}
//	}
//	return false; 
//}
//
//DWORD WINAPI WokerThread(LPVOID param)
//{
//	DWORD dwTransfer; // 얼만큼 읽었는지, 썼는지
//	ULONG_PTR KeyValue; // 완료 포트값
//	OVERLAPPED* pOverlapped; // 비동기 작업한 오버랩구조체, 오버랩구조체가 있으니 offset 사용가능! 어디서부터 어디까지 읽었는지 알아야 뒤에서부터 읽으니까
//
//	while (1)
//	{
//		// 완료 큐에 데이터가 있으면 작업시작(리턴)
//		// 하나도 없으면 그냥 대기
//		BOOL bReturn = ::GetQueuedCompletionStatus(g_hIOCP,&dwTransfer, &KeyValue, &pOverlapped, 1); // 완료 큐 g_hIOCP에 데이터가 들어갔는지 체크
//		if (bReturn == TRUE) // 작업
//		{
//			if (KeyValue == 1000)
//			{
//				DispatchRead(dwTransfer, pOverlapped);
//			}
//			if (KeyValue == 2000)
//			{
//				if (DispatchWrite(dwTransfer, pOverlapped))
//				{
//					::SetEvent(g_hKillEvent); // 이벤트가 있어야 끝낼수있음
//					break;
//				}
//			}
//		}
//		else //오류
//		{
//			//정상적으로 끝냈는지 타임아웃으로 걸렸는지 오류인지 확인해야함
//			if (GetLastError() != WAIT_TIMEOUT) // 타임아웃 걸리면 정상
//			{
//				::SetEvent(g_hKillEvent);
//				break;
//			}
//		}
//	}
//	return 1;
//}
//
//void main()
//{
//	setlocale(LC_ALL, "KOREAN");
//	g_hKillEvent = ::CreateEvent(0, TRUE, FALSE, 0);
//	if (WaitForSingleObject(g_hKillEvent, 1) == WAIT_OBJECT_0) // g_hKillEvent 이벤트가 발동하면 스레드 끝내기
//	{
//		return;
//	}
//
//	HANDLE hFileAsync = CreateFile(L"DXSDK_Jun10.exe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL); // 파일생성
//	if (hFileAsync == INVALID_HANDLE_VALUE)
//	{
//		return;
//	}
//	HANDLE hFileCopy = CreateFile(L"copy.exe", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL); // 파일생성
//	if (hFileCopy == INVALID_HANDLE_VALUE)
//	{
//		CloseHandle(hFileAsync);
//		return;
//	}
//
//	// 비동기 입출력 작업 결과 저장 큐
//	// 리드를 시키고 작업이 완료되면 작업을 저장하는 큐가 있고 거기에 저장할거임
//	// 스레드가 그 저장큐에 있으면 뭔가가 작업 끝난거임
//	g_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0); // 비동기 입출력 객체 만듬, 객체가 비동기 저장결과가 저장되는 큐를 만듬
//	// 파일포인터 핸들을 IOCP객체에 연결해준다, 작업이 완료 되면 결과가 g_hIOCP에 저장됨
//	::CreateIoCompletionPort(g_hFileRead, g_hIOCP, 1000, 0); //g_hFileRead가 완료되면 1000번이라는 번호를 넘겨줘~ 1000번이 완료포트가 됨, 1000번 작업이 반환되면 리드가 끝났다
//	::CreateIoCompletionPort(g_hFileWrite, g_hIOCP, 2000, 0); // 
//
//	GetFileSizeEx(hFileAsync, &filesize);
//
//	DWORD dwRead;
//	DWORD dwWritten;
//	DWORD dwTotalWrite = 0;
//
//	g_buffer = new WCHAR[BlockSize];
//
//	// 스레드 사용
//	for (int iThread = 0; iThread < MAX_WORKER_THREAD; iThread++)
//	{
//		DWORD id;
//		CloseHandle(::CreateThread(0, 0, WokerThread, nullptr, 0, &id));
//	}
//	g_LargeRead.QuadPart = 0;
//	g_LargeWrite.QuadPart = 0;
//
//	// 비동기 로드 
//	// 3번의 작업 끝났을때 말해줘야 몇번, 무슨 작업이 끝난지모름! 그냥 3번이 끝났다고만 말함
//	BOOL ret = ReadFile(g_hFileRead, g_buffer, BlockSize, &dwRead, &g_ReadOVArray[g_dwCurrentRead++]);
//	WaitForMultipleObjects(MAX_WORKER_THREAD, g_hWorkThread, TRUE, INFINITE);
//	for (int iThread = 0; iThread < MAX_WORKER_THREAD; iThread++)
//	{
//		CloseHandle(g_hWorkThread[iThread]);
//	}
//	CloseHandle(g_hKillEvent);
//	CloseHandle(g_hIOCP);
//	CloseHandle(g_hFileRead);
//	CloseHandle(g_hFileWrite);
//
//	return;
//}