#include "Odbc.h"

// 초기설정
bool Odbc::Init()
{
	// 환경핸들
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv) != SQL_SUCCESS)
	{
		return false;
	}
	// 환경세팅
	if (SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
		return false;
	}
	// 접속핸들
	if (SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc) != SQL_SUCCESS)
	{
		return false;
	}

	return true;
}
// 오류체크
void Odbc::Check()
{
	SQLTCHAR szSQLState[SQL_SQLSTATE_SIZE + 1];
	SQLTCHAR errorBuffer[SQL_MAX_MESSAGE_LENGTH + 1];
	SQLINTEGER SQLCode;
	SQLSMALLINT length;
	SQLError(m_hEnv, m_hDbc, m_hStmt, szSQLState, &SQLCode, errorBuffer, sizeof(errorBuffer), &length);
	MessageBox(NULL, errorBuffer, szSQLState, MB_OK);
}
// 연결
bool Odbc::Connect(int Type, const TCHAR* dsn)
{
	SQLTCHAR OutCon[255];
	SQLSMALLINT cbOutCon;
	TCHAR InCon[256] = { 0, };
	int Size = sizeof(OutCon);
	SQLSMALLINT cbOutLen;
	SQLRETURN ret;

	switch (Type)
	{
	case 0:
	{
		_stprintf(InCon, _T("Dsn=%s"), dsn);
		ret = SQLConnect(m_hDbc, (SQLTCHAR*)dsn, SQL_NTS, (SQLTCHAR*)L"sa", SQL_NTS, (SQLTCHAR*)L"lshlove0723!", SQL_NTS);
	}break;

	case 1:
	{

	}break;

	case 2:
	{

	}break;

	case 3:
	{

	}break;
	}

	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) // 접속성공이 되어야함 이과정에서 오류날수있다 체크함수를 써서 무슨 오류인지 확인하자
	{
		Check();
		return false;
	}
	// 명령핸들
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt) != SQL_SUCCESS)
	{
		return false;
	}
	return true;
}
// 해제
bool Odbc::Release()
{
	SQLCloseCursor(m_hStmt);
	SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	SQLDisconnect(m_hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);

	return true;
}

bool Odbc::Exec(const TCHAR* sql)
{
	return true;
}
// 조회
bool Odbc::ExecSelect(const TCHAR* sql, int iTableIndex = 0)
{
	SQLLEN IName, IPrice, IKorean;
	TCHAR Name[21];
	int Price;
	BOOL Korean;

	SQLRETURN ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)sql, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		Check();
		return false;
	}
	SQLLEN len;
	SQLSMALLINT NumCols;

	SQLRowCount(m_hStmt, &len);
	SQLNumResultCols(m_hStmt, &NumCols);

	SQLCloseCursor(m_hStmt);
	return true;
}
// 추가
bool Odbc::ExecInsert(const TCHAR* sql, int iTableIndex = 0)
{
	TCHAR sql3[MAX_PATH] = { 0, }; 
	wsprintf(sql3, L"insert into tblCigar (szData,price, korean) values ('%s',%d,%d)", L"디스플러스", 4100, 1);
	SQLRETURN ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)&sql3, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		Check();
		return false;
	}
	SQLLEN len;
	SQLSMALLINT Cols;

	SQLRowCount(m_hStmt, &len);
	SQLNumResultCols(m_hStmt, &Cols);

	SQLCloseCursor(m_hStmt);
	return true;
}
// 수정
bool Odbc::ExecUpdate(const TCHAR* sql, int iTableIndex = 0)
{
	TCHAR sql4[MAX_PATH] = { 0, };
	wsprintf(sql4, L"update tblCigar set szData='%s' where szData='%s'", L"코로나", L"88 Light");
	SQLRETURN ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)&sql4, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		Check();
		return false;
	}
	SQLLEN len;
	SQLSMALLINT Cols;

	SQLRowCount(m_hStmt, &len);
	SQLNumResultCols(m_hStmt, &Cols);

	SQLCloseCursor(m_hStmt);
	return true;
}
// 삭제
bool Odbc::ExecDelete(const TCHAR* sql, int iTableIndex = 0)
{
	TCHAR sql3[MAX_PATH] = { 0, };
	wsprintf(sql3, L"delete from tblCigar where szData='%s'", L"xxxx");
	SQLRETURN ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)&sql3, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		Check();
		return false;
	}
	SQLLEN len;
	SQLSMALLINT Cols;
	SQLRowCount(m_hStmt, &len);
	SQLNumResultCols(m_hStmt, &Cols);

	SQLCloseCursor(m_hStmt);
	return true;
}
// 테이블 정보
bool Odbc::ExecTableInfo(const TCHAR* szTableName)
{
	TableInfo table;
	table.szTableName = szTableName;
	wstring sql = L"select * from ";
	sql += szTableName;
	SQLRETURN ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)sql.c_str(), SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		Check();
		return false;
	}

	SQLSMALLINT iNumCols;
	SQLNumResultCols(m_hStmt, &table.Numcol);
	for (int iCols = 1; iCols <= table.Numcol; iCols++)
	{
		ColumnInfo column;
		column.col = iCols;
		int iSize = _countof(column.szColName);
		SQLDescribeCol(m_hStmt, iCols, column.szColName, iSize, &column.NameLengthPtr, &column.pfSqlType, &column.ColumnSizePtr, &column.DecimalDigitsPtr, &column.pfNullable);
		table.ColumnList.push_back(column);
	}

	SQLLEN lTemp;
	TCHAR szData[100][21] = { 0, };
	int   iData[100];
	Record rData;
	for (int iBind = 0; iBind < table.ColumnList.size(); iBind++)
	{
		switch (table.ColumnList[iBind].pfSqlType)
		{
		case SQL_TYPE_TIMESTAMP:
		{
			Field data;
			data.DataType = SQL_UNICODE;
			ret = SQLBindCol(m_hStmt, iBind + 1, SQL_TYPE_TIMESTAMP, &szData[iBind], 0, &lTemp);
			if (ret != SQL_SUCCESS)
			{
				Check();
				return false;
			}
			rData.record.push_back(data);
		}break;
		case SQL_WCHAR:
		case SQL_WVARCHAR: 
		{
			Field data;
			data.DataType = SQL_UNICODE;
			ret = SQLBindCol(m_hStmt, iBind + 1, SQL_UNICODE, szData[iBind], sizeof(szData[iBind]), &lTemp);
			if (ret != SQL_SUCCESS)
			{
				Check();
				return false;
			}
			rData.record.push_back(data);
		}break;
		case SQL_INTEGER: 
		{
			Field data;
			data.DataType = SQL_INTEGER;
			ret = SQLBindCol(m_hStmt, iBind + 1, SQL_INTEGER, &iData[iBind], 0, &lTemp);
			if (ret != SQL_SUCCESS)
			{
				Check();
				return false;
			}
			rData.record.push_back(data);
		}break;
		case -7: 
		{
			Field data;
			data.DataType = SQL_C_ULONG;
			ret = SQLBindCol(m_hStmt, iBind + 1, SQL_C_ULONG, &iData[iBind], 0, &lTemp);
			if (ret != SQL_SUCCESS)
			{
				Check();
				return false;
			}
			rData.record.push_back(data);
		};
		}
	}

	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		for (int iCol = 0; iCol < table.ColumnList.size(); iCol++)
		{
			rData.record[iCol].DataType = rData.record[iCol].DataType;
			if (rData.record[iCol].DataType == SQL_UNICODE)
			{
				rData.record[iCol].szData = szData[iCol];
			}
			else
			{
				rData.record[iCol].szData = to_wstring(iData[iCol]);
			}
		}
		m_RealStringData.push_back(rData);
	}
	SQLCloseCursor(m_hStmt);
	m_TableList.push_back(table);
	return true;
}




