//#include <Windows.h>
//#include <iostream>
//#define BlockSize (104857600) // 100�ް�
//#define MAX_WORKER_THREAD 3 //������ 3�� ����ڴ�
//
//WCHAR* g_buffer = NULL;
//LARGE_INTEGER filesize;
//OVERLAPPED g_ReadOV = { 0, }; // ������ ������ ����ü�� �׳� ���� �ȵ� ����ؼ� ���
//OVERLAPPED g_WriteOV = { 0, };
//
//DWORD g_dwCurrentRead; 
//DWORD g_dwCurrentWrite;
//// ������ ����ü�� ���� �־����
//OVERLAPPED g_ReadOVArray[100];
//OVERLAPPED g_WriteOVArray[100];
//
//HANDLE g_hFileRead;
//HANDLE g_hFileWrite;
//HANDLE g_hWorkThread[MAX_WORKER_THREAD];
//
//// �Ϸ���Ʈ ���� ��ü
//HANDLE g_hIOCP; 
//
//LARGE_INTEGER g_LargeRead;
//LARGE_INTEGER g_LargeWrite;
//
//HANDLE g_hKillEvent; // �� �̺�Ʈ�� �ߵ��ϸ� ������ ������
//
//bool DispatchRead(DWORD dwTransfer, OVERLAPPED* ov) // read �������ϱ� write �ض�
//{
//	g_LargeRead.QuadPart += dwTransfer; // ���� �� �������� �о��
//
//	++g_dwCurrentWrite;
//	g_WriteOVArray[g_dwCurrentWrite].Offset = g_LargeWrite.LowPart;
//	g_WriteOVArray[g_dwCurrentWrite].OffsetHigh = g_LargeWrite.HighPart;
//
//	DWORD dwWritten;
//	BOOL ret = WriteFile(g_hFileWrite, g_buffer, dwTransfer, &dwWritten, &g_WriteOVArray[g_dwCurrentWrite]);
//	if (ret == FALSE)
//	{
//		if (GetLastError() != ERROR_IO_PENDING) // ����� �ž� ����
//		{
//			return false;
//		}
//	}
//	return true;
//}
//bool DispatchWrite(DWORD dwTransfer, OVERLAPPED* ov) // write �������ϱ� read �ض�
//{
//	g_LargeWrite.QuadPart += dwTransfer; 
//
//	if (filesize.QuadPart <= g_LargeWrite.QuadPart) // ���� �����ŭ ������ ������
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
//		if (GetLastError() != ERROR_IO_PENDING) // ����� �ž� ����
//		{
//			return false;
//		}
//	}
//	return false; 
//}
//
//DWORD WINAPI WokerThread(LPVOID param)
//{
//	DWORD dwTransfer; // ��ŭ �о�����, �����
//	ULONG_PTR KeyValue; // �Ϸ� ��Ʈ��
//	OVERLAPPED* pOverlapped; // �񵿱� �۾��� ����������ü, ����������ü�� ������ offset ��밡��! ��𼭺��� ������ �о����� �˾ƾ� �ڿ������� �����ϱ�
//
//	while (1)
//	{
//		// �Ϸ� ť�� �����Ͱ� ������ �۾�����(����)
//		// �ϳ��� ������ �׳� ���
//		BOOL bReturn = ::GetQueuedCompletionStatus(g_hIOCP,&dwTransfer, &KeyValue, &pOverlapped, 1); // �Ϸ� ť g_hIOCP�� �����Ͱ� ������ üũ
//		if (bReturn == TRUE) // �۾�
//		{
//			if (KeyValue == 1000)
//			{
//				DispatchRead(dwTransfer, pOverlapped);
//			}
//			if (KeyValue == 2000)
//			{
//				if (DispatchWrite(dwTransfer, pOverlapped))
//				{
//					::SetEvent(g_hKillEvent); // �̺�Ʈ�� �־�� ����������
//					break;
//				}
//			}
//		}
//		else //����
//		{
//			//���������� ���´��� Ÿ�Ӿƿ����� �ɷȴ��� �������� Ȯ���ؾ���
//			if (GetLastError() != WAIT_TIMEOUT) // Ÿ�Ӿƿ� �ɸ��� ����
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
//	if (WaitForSingleObject(g_hKillEvent, 1) == WAIT_OBJECT_0) // g_hKillEvent �̺�Ʈ�� �ߵ��ϸ� ������ ������
//	{
//		return;
//	}
//
//	HANDLE hFileAsync = CreateFile(L"DXSDK_Jun10.exe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL); // ���ϻ���
//	if (hFileAsync == INVALID_HANDLE_VALUE)
//	{
//		return;
//	}
//	HANDLE hFileCopy = CreateFile(L"copy.exe", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL); // ���ϻ���
//	if (hFileCopy == INVALID_HANDLE_VALUE)
//	{
//		CloseHandle(hFileAsync);
//		return;
//	}
//
//	// �񵿱� ����� �۾� ��� ���� ť
//	// ���带 ��Ű�� �۾��� �Ϸ�Ǹ� �۾��� �����ϴ� ť�� �ְ� �ű⿡ �����Ұ���
//	// �����尡 �� ����ť�� ������ ������ �۾� ��������
//	g_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0); // �񵿱� ����� ��ü ����, ��ü�� �񵿱� �������� ����Ǵ� ť�� ����
//	// ���������� �ڵ��� IOCP��ü�� �������ش�, �۾��� �Ϸ� �Ǹ� ����� g_hIOCP�� �����
//	::CreateIoCompletionPort(g_hFileRead, g_hIOCP, 1000, 0); //g_hFileRead�� �Ϸ�Ǹ� 1000���̶�� ��ȣ�� �Ѱ���~ 1000���� �Ϸ���Ʈ�� ��, 1000�� �۾��� ��ȯ�Ǹ� ���尡 ������
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
//	// ������ ���
//	for (int iThread = 0; iThread < MAX_WORKER_THREAD; iThread++)
//	{
//		DWORD id;
//		CloseHandle(::CreateThread(0, 0, WokerThread, nullptr, 0, &id));
//	}
//	g_LargeRead.QuadPart = 0;
//	g_LargeWrite.QuadPart = 0;
//
//	// �񵿱� �ε� 
//	// 3���� �۾� �������� ������� ���, ���� �۾��� ��������! �׳� 3���� �����ٰ� ����
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