#include "Odbc.h"

// �ʱ⼳��
bool Odbc::Init()
{
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv) != SQL_SUCCESS) 
	{
		return false;
	}
	if (SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION,
		(SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
		return false;
	}
	if (SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc) != SQL_SUCCESS)
	{
		return false;
	}

	return true;
}
// ����üũ
void Odbc::Check()
{
	SQLTCHAR SQLState[SQL_SQLSTATE_SIZE + 1];
	SQLTCHAR errorBuffer[SQL_MAX_MESSAGE_LENGTH + 1];
	SQLINTEGER SQLCode;
	SQLSMALLINT length;
	SQLError(m_hEnv, m_hDbc, m_hStmt, SQLState, &SQLCode, errorBuffer, sizeof(errorBuffer), &length);

	cout << errorBuffer << SQLState;
	//MessageBox(NULL, errorBuffer, SQLState, MB_OK);
}
// ����
bool Odbc::Connect(int iType, const TCHAR* dsn)
{
	SQLTCHAR OutCon[255];
	SQLSMALLINT cbOutCon;
	TCHAR InCon[256] = { 0, };
	int Size = sizeof(OutCon);
	SQLSMALLINT cbOutLen;
	//SQLRETURN ret;

	//ret = SQLConnect(m_hDbc, (SQLWCHAR*)L"GAME", SQL_NTS, (SQLWCHAR*)L"sa", SQL_NTS, (SQLWCHAR*)L"lshlove0723!", SQL_NTS); 

	//if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) // ���Ӽ����� �Ǿ���� �̰������� ���������ִ� üũ�Լ��� �Ἥ ���� �������� Ȯ��
	//{
	//	Check();
	//	return false;
	//}
	//if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt) != SQL_SUCCESS) // ���������� ����ڵ� �Ҵ�
	//{
	//	return false;
	//}
	switch (iType)
	{
	case 0:
	{
		_stprintf(InCon, _T("%s"), _T("Driver={SQL Server};Server=directx.kr;Address=192.168.0.87,1433;Network=dbmssocn;Database=GAME;Uid=sa;Pwd=lshlove0723!;"));
		ret = SQLDriverConnect(m_hDbc, NULL, InCon, _countof(InCon), OutCon, _countof(OutCon), &cbOutLen, SQL_DRIVER_NOPROMPT);
	}break;

	// SQL Server ��ȭ���� ����
	case 4:
	{
		HWND hWnd = GetDesktopWindow();
		SQLSMALLINT len;
		ret = SQLDriverConnect(m_hDbc, hWnd, (SQLWCHAR*)L"Driver={SQL Server}", SQL_NTS, (SQLWCHAR*)InCon, _countof(InCon), &len, SQL_DRIVER_PROMPT);
	}break;
	}

	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		Check();
		return false;
	}

	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt) != SQL_SUCCESS)
	{
		return false;
	}

	return true;
}
// �Ҵ�, ���� ����
bool Odbc::Release()
{
	SQLCloseCursor(m_hStmt);
	SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	SQLDisconnect(m_hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);

	return true;
}


// ���̺� ����
bool Odbc::ExecTableInfo(const TCHAR* TableName)
{
	Table table;
	table.TableName = TableName;
	wstring sql = L"select * from ";
	sql += TableName;
	// ����� �����ϴ� �Լ� 
	// SQLExecDirect(����ڵ�, ������ SQL��, SQL���� ���ڿ� ����)
	ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)sql.c_str(), SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		Check();
		return false;
	}

	SQLNumResultCols(m_hStmt, &table.ColNum);
	for (int Col = 1; Col <= table.ColNum; Col++)
	{
		Column column;
		column.Col = Col;
		int size = _countof(column.ColName);
		// �÷��� ���� �������� ������ ��� �Լ� 
		// SQLDescribeCol(����ڵ�, ��Ŀ����, ���̸� ������, *name�� ����, *name�� ��ȯ ������ �� ����Ʈ��, ���� SQL ������ Ÿ�� ������, DB�� ���� ��ũ���� ������, DB�� ���� ���� ���������� ���� ������, ���� null�� ��� �Ǵ����� �����ִ� ���� ������)
		SQLDescribeCol(m_hStmt, Col, column.ColName, size, &column.NameLengthPtr, &column.pfSqlType, &column.ColumnSizePtr, &column.DecimalDigitsPtr, &column.pfNullable);
		table.ColumnList.push_back(column);
	}

	SQLLEN temp;
	TCHAR tData[100][21] = { 0, };
	int iData[100];
	Record recordData;
	for (int Bind = 0; Bind < table.ColumnList.size(); Bind++)
	{
		switch (table.ColumnList[Bind].pfSqlType)
		{
		case SQL_TYPE_TIMESTAMP:
		{
			Field data;
			data.DataType = SQL_UNICODE;

			// SQLBindCol(����ڵ�, ���� �ĺ��ϴ� ��ȣ, �ι�° ���ڿ� ����Ǵ� ���������� Ÿ��, �� �����͸� ������ ���۸� ����Ű�� ������, �� �����͸� �����ϴµ� ����Ҽ��ִ� ������ ũ��)
			ret = SQLBindCol(m_hStmt, Bind + 1, SQL_TYPE_TIMESTAMP, &tData[Bind], 0, &temp);
			if (ret != SQL_SUCCESS)
			{
				Check();
				return false;
			}
			recordData.record.push_back(data);
		}break;

		case SQL_WCHAR:

		case SQL_WVARCHAR:
		{
			Field data;
			data.DataType = SQL_UNICODE;
			ret = SQLBindCol(m_hStmt, Bind + 1, SQL_UNICODE, tData[Bind], sizeof(tData[Bind]), &temp);
			if (ret != SQL_SUCCESS)
			{
				Check();
				return false;
			}
			recordData.record.push_back(data);
		}break;

		case SQL_INTEGER:
		{
			Field data;
			data.DataType = SQL_INTEGER;
			ret = SQLBindCol(m_hStmt, Bind + 1, SQL_INTEGER, &iData[Bind], 0, &temp);
			if (ret != SQL_SUCCESS)
			{
				Check();
				return false;
			}
			recordData.record.push_back(data);
		}break;

		case SQL_BIT:
		{
			Field data;
			data.DataType = SQL_C_ULONG;
			ret = SQLBindCol(m_hStmt, Bind + 1, SQL_C_ULONG, &iData[Bind], 0, &temp);
			if (ret != SQL_SUCCESS)
			{
				Check();
				return false;
			}
			recordData.record.push_back(data);
		};
		}
	}
	//SQLFetch �Լ��� ���ε��� ������ �÷����� �������ְ� ���� �ο������ �̵��Ѵ� SQL_NO_DATA�� ������ ������ �ݺ������� ȣ���ϸ� ��� ���ڵ带 ���� ���� �ִ�
	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		for (int Col = 0; Col < table.ColumnList.size(); Col++)
		{
			recordData.record[Col].DataType = recordData.record[Col].DataType;
			if (recordData.record[Col].DataType == SQL_UNICODE)
			{
				recordData.record[Col].tData = tData[Col];
			}
			else
			{
				recordData.record[Col].tData = to_wstring(iData[Col]);
			}
		}
		m_RealStringData.push_back(recordData);
	}
	SQLCloseCursor(m_hStmt);
	m_TableList.push_back(table);
	return true;
}
// ���̺����� ����
bool Odbc::ExecSelect(const TCHAR* sql)
{
	SQLLEN userName, userID, userPW, logintime, logouttime;

	ret = SQLBindCol(m_hStmt, 1, SQL_UNICODE, &m_userName, 0, &userName);
	ret = SQLBindCol(m_hStmt, 2, SQL_UNICODE, &m_userID, sizeof(m_userID), &userID);
	ret = SQLBindCol(m_hStmt, 3, SQL_UNICODE, &m_userPW, sizeof(m_userPW), &userPW);
	ret = SQLBindCol(m_hStmt, 4, SQL_UNICODE, &m_logintime, sizeof(m_logintime), &logintime);
	ret = SQLBindCol(m_hStmt, 5, SQL_UNICODE, &m_logouttime, sizeof(m_logouttime), &logouttime);

	return true;
}

// �߰�
void Odbc::CreatePrepare() 
{
	ret = SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmtAccount);
	SWORD sReturn = 0;
	SQLLEN cbRetParam = SQL_NTS;
	ret = SQLBindParameter(m_hStmtAccount, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sReturn, 0, &cbRetParam);
	ret = SQLBindParameter(m_hStmtAccount, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(id), 0, id, sizeof(id), NULL);
	ret = SQLBindParameter(m_hStmtAccount, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(pw), 0, pw, sizeof(pw), NULL);

	TCHAR callsp[] = L"{?=call AccountCreate(?,?)}"; 
	ret = SQLPrepare(m_hStmtAccount, callsp, SQL_NTS);
}
void Odbc::ExecPrepare(const TCHAR* szid, const TCHAR* szps)
{
	memcpy(id, szid, sizeof(id));
	memcpy(pw, szps, sizeof(pw));
	ret = SQLExecute(m_hStmtAccount);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		Check();
		return;
	}
	while (SQLMoreResults(m_hStmtAccount) != SQL_NO_DATA);
	SQLFreeStmt(m_hStmtAccount, SQL_CLOSE);
	SQLCloseCursor(m_hStmtAccount);
}
