#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <tchar.h>

SQLHENV g_hEnv = SQL_NULL_HENV; // ȯ��
SQLHDBC g_hDbc = SQL_NULL_HDBC; // ����
SQLHSTMT g_hStmt = SQL_NULL_HSTMT; // ���
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
	// ODBC ��� �ڴ� �Ҵ� SQLAllocHandle
	// ����ڵ��� �����ͼҽ��� ������ �� ���ϴ� �����͸� �׼����ϱ����� SQL����� �����ϸ� ����°� SQL���� �Ķ���������� ������
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &g_hEnv); //ȯ���ڵ� �Ҵ�
	retcode = SQLSetEnvAttr(g_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3_80, 0);// ȯ�� ����
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, g_hEnv, &g_hDbc); // ȯ�漼���ϰ� ����

	SQLSMALLINT cbCon;
	SQLTCHAR connStrbuf[1024] = { 0, };
	retcode = SQLDriverConnect(g_hDbc, GetDesktopWindow(), (SQLTCHAR*)L"Driver={SQL Server}", SQL_NTS, (SQLTCHAR*)connStrbuf, _countof(connStrbuf), &cbCon, SQL_DRIVER_PROMPT); // ��ȭ���ڰ� ������ ����
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt); // ���Ἴ���ϰ� ���

	SWORD sReturn = 0;
	SQLLEN cbRetParam = SQL_NTS;
	retcode = SQLBindParameter(g_hStmt, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sReturn, 0, &cbRetParam);

	SQLWCHAR id[10] = L"TestUser";
	retcode = SQLBindParameter(g_hStmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(id), 0, id, sizeof(id), NULL); //�����Ҷ� �Ķ���͸� �Ѱ������, ù��° ����ǥ �Ķ����
	SQLWCHAR pw[10] = L"111";
	retcode = SQLBindParameter(g_hStmt, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(pw), 0, pw, sizeof(pw), NULL);

	TCHAR callsp[] = L"{?=call NewUserAccount(?,?)}"; // �����Ѵ����� �� ���ν��� ȣ���ض�, �Ѿ�� ���ڰ� �ΰ��� ��ȯ���� �Ѱ���	
	retcode = SQLPrepare(g_hStmt, callsp, SQL_NTS); //���̷�Ʈ������ �Ź��ϸ� �Ź� üũ�ؼ� ���� �Ǵ��ؼ� �����ؼ� �����ϴµ� �������� �ѹ��� ��������, ������ ������ ����ϸ� �ӵ��� ����(�����Ҷ����� �����ϴ°� �ƴ϶� �̹� ������ �Ǿ��⶧����)
	

	 //SQLExecDirect(g_hStmt,callsp, SQL_NTS); //���̷�Ʈ����
	
	retcode = SQLExecute(g_hStmt);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) //���ϰ��� ������ �ƴϸ� �ȴ�
	{
		Error(g_hEnv, g_hDbc, g_hStmt);
		return;
	}
	while (SQLMoreResults(g_hStmt) != SQL_NO_DATA);
	SQLFreeStmt(g_hStmt, SQL_UNBIND);
	SQLCloseCursor;
	return;

}