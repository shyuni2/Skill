#pragma once
#include <Windows.h>
#include <iostream>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>
#include <vector>

using namespace std;

struct ColumnInfo
{
	SQLSMALLINT col;
	SQLWCHAR szColName[20];
	SQLSMALLINT BufferLength;
	SQLSMALLINT NameLengthPtr;
	SQLSMALLINT pfSqlType;
	SQLULEN ColumnSizePtr;
	SQLSMALLINT DecimalDigitsPtr;
	SQLSMALLINT pfNullable;
};
struct TableInfo
{
	vector<ColumnInfo> ColumnList;
	SQLSMALLINT Numcol;
	wstring szTableName;
};

struct Field
{
	wstring szData;
	int DataType;
};
struct Record
{
	vector<Field> record;
};

class Odbc
{
public:
	SQLHENV m_hEnv;
	SQLHDBC m_hDbc;
	SQLHSTMT m_hStmt;
public:
	vector<TableInfo> m_TableList;
	vector<Record> m_RealStringData;
public:
	bool Init();
	bool Connect(int Type, const TCHAR* dsn);
	void Check();
	bool Release();	
public:
	bool Exec(const TCHAR* sql);
	bool ExecSelect(const TCHAR* sql, int iTableIndex = 0);
	bool ExecInsert(const TCHAR* sql, int iTableIndex = 0);
	bool ExecUpdate(const TCHAR* sql, int iTableIndex = 0);
	bool ExecDelete(const TCHAR* sql, int iTableIndex = 0);
	bool ExecTableInfo(const TCHAR* szTableName);
};

