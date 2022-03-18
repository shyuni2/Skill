#define _CRT_SECURE_NO_WARNINGS

#include <WIndows.h>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>
#include <iostream>
#include <string>

using namespace std;

// g�� �������� h�� �ڵ�
SQLHENV g_hEnv;// ȯ���ڵ�
SQLHDBC g_hDbc; // �����ڵ�
SQLHSTMT g_hStmt; // ����ڵ�

void main()
{
	// ȯ���ڵ�
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &g_hEnv) != SQL_SUCCESS)
	{
		return;
	}
	// ȯ�漼��
	if (SQLSetEnvAttr(g_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
		return;
	}

	// �����ڵ�
	if (SQLAllocHandle(SQL_HANDLE_DBC, g_hEnv, &g_hDbc) != SQL_SUCCESS)
	{
		return;
	}
	// ��θ� �����ͼ�
	SQLWCHAR dir[MAX_PATH] = { 0, };
	GetCurrentDirectory(MAX_PATH, dir);
	wstring dbpath = dir;
	dbpath += L"cigarette.accdb";
	// ��� �����ϳĸ�
	TCHAR InCon[256] = { 0, };
	_stprintf(InCon, _T("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=%s;"), dbpath.c_str()); // ���⼭ *�� ����� ����, ���� �߿���, �� accdb���Ͽ� �����ϰڴ�
	SQLSMALLINT cbOutLen;
	SQLRETURN ret = SQLDriverConnect(g_hDbc, NULL, InCon, _countof(InCon), NULL, 0, &cbOutLen, SQL_DRIVER_NOPROMPT); // InCon���� ����
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) // ���Ӽ����� �Ǿ����
	{
		return;
	}
	// �̰������� ������������, ������ üũ�Լ��� �Ἥ ���� �������� Ȯ������

	// ����ڵ�
	if (SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt) != SQL_SUCCESS)
	{
		return;
	}

	TCHAR Name[21];
	SQLLEN IName,IPrice, IKorean;
	int Price;
	BOOL Korean;

	// ���
	ret = SQLBindCol(g_hStmt, 1, SQL_UNICODE, Name, sizeof(Name), &IName); // �����ڵ�� ù��° �ʵ尡 �������� ���ε�
	ret = SQLBindCol(g_hStmt, 2, SQL_C_ULONG, &Price, 0, &IPrice);
	ret = SQLBindCol(g_hStmt, 3, SQL_C_ULONG, &Korean, 0, &IKorean);

	TCHAR sql[MAX_PATH] = L"select * from tblCigar"; // ���⿡ ���, ����ϸ� ���ϰ��� ���� tblCigar��� ���̺��� �̸� ��~
	ret = SQLExecDirect(g_hStmt, (SQLTCHAR*)&sql, SQL_NTS); // ���ϰ��� �� ����ִ��� ã����ȴ�

	// ��ȸ
	while (SQLFetch(g_hStmt) != SQL_NO_DATA) // ����������� �����Ͱ� ��Ŷ���� ���޵ȴٶ�� �����ϸ� ��, �� ��Ŷ�� �޾Ƽ� ����Ѵ�
	{
		wcout << Name << Price << Korean;
	}

	// �۾��� �������� �Ҵ����ذ� �����������, �����Ҷ��� ��������
	SQLFreeHandle(SQL_HANDLE_STMT, g_hStmt);
	SQLDisconnect(g_hDbc); // ��������
	SQLFreeHandle(SQL_HANDLE_DBC, g_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
}