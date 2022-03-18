#define _CRT_SECURE_NO_WARNINGS

#include <WIndows.h>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>
#include <iostream>
#include <string>

using namespace std;

// g는 전역변수 h는 핸들
SQLHENV g_hEnv;// 환경핸들
SQLHDBC g_hDbc; // 접속핸들
SQLHSTMT g_hStmt; // 명령핸들

void main()
{
	// 환경핸들
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &g_hEnv) != SQL_SUCCESS)
	{
		return;
	}
	// 환경세팅
	if (SQLSetEnvAttr(g_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
		return;
	}

	// 접속핸들
	if (SQLAllocHandle(SQL_HANDLE_DBC, g_hEnv, &g_hDbc) != SQL_SUCCESS)
	{
		return;
	}
	// 경로를 가져와서
	SQLWCHAR dir[MAX_PATH] = { 0, };
	GetCurrentDirectory(MAX_PATH, dir);
	wstring dbpath = dir;
	dbpath += L"cigarette.accdb";
	// 어떻게 접속하냐면
	TCHAR InCon[256] = { 0, };
	_stprintf(InCon, _T("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=%s;"), dbpath.c_str()); // 여기서 *는 모든을 뜻함, 띄어쓰기 중요함, 옆 accdb파일에 접근하겠다
	SQLSMALLINT cbOutLen;
	SQLRETURN ret = SQLDriverConnect(g_hDbc, NULL, InCon, _countof(InCon), NULL, 0, &cbOutLen, SQL_DRIVER_NOPROMPT); // InCon으로 접속
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) // 접속성공이 되어야함
	{
		return;
	}
	// 이과정에서 오류날수있음, 별도의 체크함수를 써서 무슨 오류인지 확인하자

	// 명령핸들
	if (SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt) != SQL_SUCCESS)
	{
		return;
	}

	TCHAR Name[21];
	SQLLEN IName,IPrice, IKorean;
	int Price;
	BOOL Korean;

	// 결과
	ret = SQLBindCol(g_hStmt, 1, SQL_UNICODE, Name, sizeof(Name), &IName); // 유니코드로 첫번째 필드가 네임으로 바인딩
	ret = SQLBindCol(g_hStmt, 2, SQL_C_ULONG, &Price, 0, &IPrice);
	ret = SQLBindCol(g_hStmt, 3, SQL_C_ULONG, &Korean, 0, &IKorean);

	TCHAR sql[MAX_PATH] = L"select * from tblCigar"; // 여기에 명령, 명령하면 리턴값이 나옴 tblCigar라는 테이블에서 이름 줘~
	ret = SQLExecDirect(g_hStmt, (SQLTCHAR*)&sql, SQL_NTS); // 리턴값에 뭐 들어있는지 찾으면된다

	// 조회
	while (SQLFetch(g_hStmt) != SQL_NO_DATA) // 명령을내리면 데이터가 패킷으로 전달된다라고 생각하면 됨, 그 패킷을 받아서 출력한다
	{
		wcout << Name << Price << Korean;
	}

	// 작업이 끝났으면 할당해준걸 해제해줘야함, 해제할때는 역순으로
	SQLFreeHandle(SQL_HANDLE_STMT, g_hStmt);
	SQLDisconnect(g_hDbc); // 연결해제
	SQLFreeHandle(SQL_HANDLE_DBC, g_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
}