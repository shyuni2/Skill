//#include <Windows.h>
//#include <iostream>
//
//using namespace std;
//
////���� ����� ����
//void main()
//{
//	setlocale(LC_ALL, "KOREAN"); // cout �����ڵ�� ��� �����ϰ� ��
//	// ���Ͼ���
//	HANDLE hFileWrite = CreateFile(L"test.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // ���� ����
//	if (hFileWrite != NULL) // ������ ����������� �۾�����
//	{
//		WCHAR buffer[] = L"lsh";
//		DWORD dwLength = sizeof(buffer);
//		DWORD dwWritten; //��ŭ ���
//		BOOL ret = WriteFile(hFileWrite, buffer, dwLength, &dwWritten, NULL); // ��ȯ���� ���� ���и� ����
//		// ���������� lpOverlapped�� �־�� �񵿱� �����, NULL���� �񵿱� ���ϰڴٶ�� ��
//		if (ret == TRUE)
//		{
//			// cout�� �����ڵ� ��¸���, �⺻������ ��Ƽ����Ʈ ����
//			// setlocale�� ��ܿ��� ����ؾߵ�, �⺻������ �����̱⶧���� �ʿ��ϸ� �ٲ���~
//			wcout << L"��¼���";
//		}
//	}
//	CloseHandle(hFileWrite);
//	// ���� �б�
//	HANDLE hFileRead = CreateFile(L"test.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // ���� ����
//	if (hFileRead != NULL) // ������ ����������� �۾�����
//	{
//		WCHAR buffer[512] = { 0, };
//		DWORD dwLength = sizeof(buffer);
//		DWORD dwRead; //��ŭ ���
//		BOOL ret = ReadFile(hFileRead, buffer, dwLength, &dwRead, NULL); // ��ȯ���� ���� ���и� ����
//		// ���������� lpOverlapped�� �־�� �񵿱� �����, NULL���� �񵿱� ���ϰڴٶ�� ��
//		if (ret == TRUE)
//		{
//			// cout�� �����ڵ� ��¸���, �⺻������ ��Ƽ����Ʈ ����
//			// setlocale�� ��ܿ��� ����ؾߵ�, �⺻������ �����̱⶧���� �ʿ��ϸ� �ٲ���~
//			wcout << buffer;
//		}
//	}
//	CloseHandle(hFileRead);
//}