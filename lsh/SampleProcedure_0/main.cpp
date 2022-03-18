#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <tchar.h>

SQLHENV g_hEnv = SQL_NULL_HENV; // 환경
SQLHDBC g_hDbc = SQL_NULL_HDBC; // 연결
SQLHSTMT g_hStmt = SQL_NULL_HSTMT; // 명령
SQLRETURN retcode;

void Error(SQLHENV env, SQLHDBC dbc, SQLHSTMT stmt)
{
	SQLTCHAR buffer[SQL_MAX_MESSAGE_LENGTH + 1];
	SQLTCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];
	SQLINTEGER sqlcode;
	SQLSMALLINT length;
	while (SQLError(env, dbc, stmt, sqlstate, &sqlcode, buffer, SQL_MAX_MESSAGE_LENGTH + 1, &length) == SQL_SUCCESS)
	{
		printf("%s", buffer);
	}
}

void main()
{
	// ODBC 명령 핸달 할당 SQLAllocHandle
	// 명령핸들은 데이터소스에 연결한 후 원하는 데이터를 액세스하기위한 SQL명령을 저장하며 결과셋과 SQL문의 파라미터정보를 가진다
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &g_hEnv); //환경핸들 할당
	retcode = SQLSetEnvAttr(g_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3_80, 0);// 환경 세팅
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, g_hEnv, &g_hDbc); // 환경세팅하고 연결

	SQLSMALLINT cbCon;
	SQLTCHAR connStrbuf[1024] = { 0, };
	retcode = SQLDriverConnect(g_hDbc, GetDesktopWindow(), (SQLTCHAR*)L"Driver={SQL Server}", SQL_NTS, (SQLTCHAR*)connStrbuf, _countof(connStrbuf), &cbCon, SQL_DRIVER_PROMPT); // 대화상자가 열리고 접속
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt); // 연결세팅하고 명령

	SWORD sReturn = 0;
	SQLLEN cbRetParam = SQL_NTS;
	retcode = SQLBindParameter(g_hStmt, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sReturn, 0, &cbRetParam);

	SQLWCHAR id[10] = L"TestUser";
	retcode = SQLBindParameter(g_hStmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(id), 0, id, sizeof(id), NULL); //실행할때 파라미터를 넘겨줘야함, 첫번째 물음표 파라미터
	SQLWCHAR pw[10] = L"111";
	retcode = SQLBindParameter(g_hStmt, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(pw), 0, pw, sizeof(pw), NULL);

	TCHAR callsp[] = L"{?=call NewUserAccount(?,?)}"; // 접속한다음에 이 프로시저 호출해라, 넘어가는 인자가 두개고 반환값이 한개다	
	retcode = SQLPrepare(g_hStmt, callsp, SQL_NTS); //다이렉트쿼리를 매번하면 매번 체크해서 오류 판단해서 검증해서 실행하는데 프리페어는 한번만 검증해줌, 검증된 프리페어를 사용하면 속도가 빠름(실행할때마다 검증하는게 아니라 이미 검증이 되었기때문에)
	

	 //SQLExecDirect(g_hStmt,callsp, SQL_NTS); //다이렉트쿼리
	
	retcode = SQLExecute(g_hStmt);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) //리턴값이 음수가 아니면 된다
	{
		Error(g_hEnv, g_hDbc, g_hStmt);
		return;
	}
	while (SQLMoreResults(g_hStmt) != SQL_NO_DATA);
	SQLFreeStmt(g_hStmt, SQL_UNBIND);
	SQLCloseCursor;
	return;

}