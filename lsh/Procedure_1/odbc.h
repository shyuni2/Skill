#pragma once
#include <Windows.h>
#include <iostream>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>
#include <vector>
#include <string>

using namespace std;

struct Column
{
	SQLSMALLINT Col;
	SQLWCHAR ColName[20];
	SQLSMALLINT BufferLength;
	SQLSMALLINT NameLengthPtr;
	SQLSMALLINT pfSqlType;
	SQLULEN ColumnSizePtr;
	SQLSMALLINT DecimalDigitsPtr;
	SQLSMALLINT pfNullable;
};
struct Table 
{
	vector<Column> ColumnList;
	SQLSMALLINT ColNum;
	wstring TableName;
};

struct Field
{
	wstring tData;
	int DataType;
};
struct Record
{
	vector<Field> record;
};

class Odbc
{
public:
	SQLWCHAR m_userName, m_userID, m_userPW, m_logintime, m_logouttime;
public:
	SQLWCHAR id[10] = L"NONE";
	SQLWCHAR pw[10] = L"NONE";
public:
	SQLHENV m_hEnv;
	SQLHDBC m_hDbc;
	SQLHSTMT m_hStmt;
	SQLHSTMT m_hStmtAccount; // 명령당 핸들 하나씩 만드는게 좋다
	SQLRETURN ret;
public:
	vector<Table> m_TableList;
	vector<Record> m_RealStringData;
public:
	bool Init();
	bool Connect(int iType, const TCHAR* dsn);
	void Check();
	bool Release();
public:
	bool ExecTableInfo(const TCHAR* TableName);
	bool ExecSelect(const TCHAR* sql);
public:
	void CreatePrepare();
	void ExecPrepare(const TCHAR* szid, const TCHAR* szps); // 추가
};

