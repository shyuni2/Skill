#include <Windows.h>
#include <iostream>

using namespace std;

// ���� ����� ���ÿ� (ū����ver.)

DWORD SectorsPerCluster;
DWORD BytesPerSector;
DWORD NumberOfFreeClusters;
DWORD TotalNumberOfClusters;

void main()
{
	WCHAR lpRootPathName[] = L"c:\\";
	GetDiskFreeSpace(lpRootPathName, &SectorsPerCluster, &BytesPerSector, &NumberOfFreeClusters, &TotalNumberOfClusters);

	setlocale(LC_ALL, "KOREAN"); // cout �����ڵ�� ��� �����ϰ� ��
	
	WCHAR* g_buffer = NULL;
	LARGE_INTEGER filesize;// ū�뷮 ������ ������
	OVERLAPPED g_ReadOV = { 0, };
	OVERLAPPED g_WriteOV = { 0, };

	HANDLE hFileReadAsync = CreateFile(L"Test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING, NULL); // ���ϻ���
	// CreateFile(������ �����ϰų� �� ���, ������ ���ų� ���� ����(�÷��� �ߺ�����), ������ �������, ���ȼӼ�, �ش���ġ�� ������ �����Ұ�� �ൿ, ������ ������ �Ӽ�,���Ͽ� ���� �Ӽ��� ����)
	// FILE_FLAG_NO_BUFFERING�� ������ CreateFile������� ReadFile,WriteFile���� sector������ 512byte �����谡 �Ǿ���Ѵ� �׷��� ������� �����߻�

	if (hFileReadAsync != INVALID_HANDLE_VALUE) // ������ ����������� �۾�����
	{
		GetFileSizeEx(hFileReadAsync, &filesize); // GetFileSize�� WORD���� 4.2GB�Ѿ �� ū�� GetFileSizeEx����
		DWORD dwSize = 0;
		if (filesize.QuadPart % BytesPerSector != 0)
		{
			dwSize = filesize.QuadPart / BytesPerSector;
			dwSize = (dwSize + 1) * BytesPerSector;
		}
		g_buffer = new WCHAR[filesize.QuadPart];
		DWORD dwRead;
		BOOL ret = ReadFile(hFileReadAsync, g_buffer, dwSize, &dwRead, &g_ReadOV);
		BOOL bPanding = FALSE; // ���
		if (ret == FALSE)
		{
			DWORD dwError = GetLastError();
			if (dwError == ERROR_IO_PENDING)
			{
				wcout << L"�ε� ��" << endl;
				bPanding = TRUE;
			}
			else
			{
				wcout << L"�ε� ����" << endl;
			}
		}
		else
		{
			wcout << L"�ε� �Ϸ�" << endl;
		}
		// �ε� ���� ���
		DWORD dwTrans = 0;
		BOOL bReturn;
		while (bPanding)
		{
			bReturn = GetOverlappedResult(hFileReadAsync, &g_ReadOV, &dwTrans, FALSE);
			if (bReturn == TRUE)
			{
				wcout << L"�ε� �Ϸ�" << endl;
				bPanding = FALSE;
			}
			else
			{
				DWORD dwError = GetLastError();
				if (dwError == ERROR_IO_INCOMPLETE)
				{
					wcout << L".";
				}
				else
				{
					wcout << L"�ε� ����" << endl;
				}
			}
			Sleep(1000); // 1�ʿ� �ѹ� �ε�ǰ�
		}
	}
	CloseHandle(hFileReadAsync);
	wcout << L"�������" << endl;

	HANDLE hFileWriteAsync = CreateFile(L"TestCopy.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_WRITE_THROUGH, NULL); // ���ϻ���
	// CreateFile(������ �����ϰų� �� ���, ������ ���ų� ���� ����(�÷��� �ߺ�����), ������ �������, ���ȼӼ�, �ش���ġ�� ������ �����Ұ�� �ൿ, ������ ������ �Ӽ�,���Ͽ� ���� �Ӽ��� ����)

	if (hFileWriteAsync != NULL) // ������ ����������� �۾�����
	{
		DWORD dwLength = filesize.QuadPart;
		DWORD dwWrite;
		BOOL ret = WriteFile(hFileWriteAsync, g_buffer, dwLength, &dwWrite, &g_WriteOV);
		BOOL bPanding = FALSE;
		if (ret == FALSE)
		{
			DWORD dwError = GetLastError();
			if (dwError == ERROR_IO_PENDING)
			{
				wcout << L"��� ��" << endl;
				bPanding = TRUE;
			}
			else
			{
				wcout << L"��� ����" << endl;
			}
		}
		else
		{
			wcout << L"��� �Ϸ�" << endl;
			bPanding = FALSE;
		}
		// �ε� ���� ���
		DWORD dwTrans = 0;
		BOOL bReturn;
		while (bPanding)
		{
			bReturn = GetOverlappedResult(hFileWriteAsync, &g_WriteOV, &dwTrans, FALSE);
			if (bReturn == TRUE)
			{
				wcout << L"��� �Ϸ�" << endl;
				bPanding = FALSE;
			}
			else
			{
				DWORD dwError = GetLastError();
				if (dwError == ERROR_IO_INCOMPLETE)
				{
					wcout << L".";
				}
				else
				{
					wcout << L"����";
					bPanding = FALSE;
				}
			}
			Sleep(1000);
		}
		CloseHandle(hFileWriteAsync);
	}
 }