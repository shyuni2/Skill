//#include <Windows.h>
//#include <iostream>
//
//using namespace std;
//
////동기 입출력 예시
//void main()
//{
//	setlocale(LC_ALL, "KOREAN"); // cout 유니코드로 출력 가능하게 함
//	// 파일쓰기
//	HANDLE hFileWrite = CreateFile(L"test.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // 파일 생성
//	if (hFileWrite != NULL) // 파일이 만들어졌으면 작업하자
//	{
//		WCHAR buffer[] = L"lsh";
//		DWORD dwLength = sizeof(buffer);
//		DWORD dwWritten; //얼만큼 썼다
//		BOOL ret = WriteFile(hFileWrite, buffer, dwLength, &dwWritten, NULL); // 반환값은 성공 실패를 따짐
//		// 마지막인자 lpOverlapped가 있어야 비동기 입출력, NULL쓰면 비동기 안하겠다라는 뜻
//		if (ret == TRUE)
//		{
//			// cout은 유니코드 출력못함, 기본적으로 멀티바이트 지원
//			// setlocale을 상단에서 사용해야됨, 기본적으로 영어이기때문에 필요하면 바꿔써라~
//			wcout << L"출력성공";
//		}
//	}
//	CloseHandle(hFileWrite);
//	// 파일 읽기
//	HANDLE hFileRead = CreateFile(L"test.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // 파일 생성
//	if (hFileRead != NULL) // 파일이 만들어졌으면 작업하자
//	{
//		WCHAR buffer[512] = { 0, };
//		DWORD dwLength = sizeof(buffer);
//		DWORD dwRead; //얼만큼 썼다
//		BOOL ret = ReadFile(hFileRead, buffer, dwLength, &dwRead, NULL); // 반환값은 성공 실패를 따짐
//		// 마지막인자 lpOverlapped가 있어야 비동기 입출력, NULL쓰면 비동기 안하겠다라는 뜻
//		if (ret == TRUE)
//		{
//			// cout은 유니코드 출력못함, 기본적으로 멀티바이트 지원
//			// setlocale을 상단에서 사용해야됨, 기본적으로 영어이기때문에 필요하면 바꿔써라~
//			wcout << buffer;
//		}
//	}
//	CloseHandle(hFileRead);
//}