#include "Odbc.h"

// 초기설정
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
// 오류체크
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
// 연결
bool Odbc::Connect(int iType, const TCHAR* dsn)
{
	SQLTCHAR OutCon[255];
	SQLSMALLINT cbOutCon;
	TCHAR InCon[256] = { 0, };
	int Size = sizeof(OutCon);
	SQLSMALLINT cbOutLen;
	//SQLRETURN ret;

	//ret = SQLConnect(m_hDbc, (SQLWCHAR*)L"GAME", SQL_NTS, (SQLWCHAR*)L"sa", SQL_NTS, (SQLWCHAR*)L"lshlove0723!", SQL_NTS); 

	//if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) // 접속성공이 되어야함 이과정에서 오류날수있다 체크함수를 써서 무슨 오류인지 확인
	//{
	//	Check();
	//	return false;
	//}
	//if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt) != SQL_SUCCESS) // 접속했으니 명령핸들 할당
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

	// SQL Server 대화상자 버전
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
// 할당, 연결 해제
bool Odbc::Release()
{
	SQLCloseCursor(m_hStmt);
	SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	SQLDisconnect(m_hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);

	return true;
}


// 테이블 정보
bool Odbc::ExecTableInfo(const TCHAR* TableName)
{
	Table table;
	table.TableName = TableName;
	wstring sql = L"select * from ";
	sql += TableName;
	// 명령을 실행하는 함수 
	// SQLExecDirect(명령핸들, 실행한 SQL문, SQL문의 문자열 길이)
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
		// 컬럼에 대한 세부적인 설명을 얻는 함수 
		// SQLDescribeCol(명령핸들, 마커순서, 열이름 포인터, *name의 길이, *name에 반환 가능한 총 바이트수, 열의 SQL 데이터 타입 포인터, DB에 대한 열크기의 포인터, DB에 대한 열의 십진숫자의 개수 포인터, 열이 null이 허용 되는지를 보여주는 값의 포인터)
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

			// SQLBindCol(명령핸들, 열을 식별하는 번호, 두번째 인자에 적용되는 데이터유형 타입, 열 데이터를 저장할 버퍼를 가리키는 포인터, 열 데이터를 저장하는데 사용할수있는 버퍼의 크기)
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
	//SQLFetch 함수는 바인딩된 변수에 컬럼값을 대입해주고 다음 로우셋으로 이동한다 SQL_NO_DATA를 리턴할 때까지 반복적으로 호출하면 모든 레코드를 읽을 수가 있다
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
// 테이블정보 선택
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

// 추가
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
