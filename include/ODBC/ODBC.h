#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <string>
#include <tchar.h>
#include <sql.h>
#include <sqlext.h>
#include <vector>
#include<iomanip>

using namespace std;

struct ColumnInfo
{
	SQLUSMALLINT icol;
	SQLWCHAR ColName[20];
	SQLSMALLINT BufferLength;
	SQLSMALLINT	NameLengthPtr;
	SQLSMALLINT	pfSqlType;
	SQLULEN	ColumnSizePtr;
	SQLSMALLINT DecimalDigitsPtr;
	SQLSMALLINT	pfNullable;
};
struct TableInfo
{
	vector<ColumnInfo> ColumnList;
	SQLSMALLINT iNumcol;
	wstring TableName;
};
struct Field
{
	wstring tData;
	int iDataType;
};
struct Record
{
	vector<Field> record;
};

class ODBC
{
public:
	SQLHENV m_hEnv;//환경핸들
	SQLHDBC	m_hDbc;//연결핸들
	//명령당 핸들 하나씩 있는게 좋다
	SQLHSTMT m_hStmt;
	SQLHSTMT m_hAccountStmt;
	SQLHSTMT m_hFindAccountStmt;
public:
	SQLRETURN retcode;
	SWORD sReturn;
public:
	SQLWCHAR m_id[10] = L"NONE";
	SQLWCHAR m_pw[10] = L"NONE";
	SQLWCHAR m_ph[10] = L"NONE";
public:
	vector<Record> m_RealStringData;
public:
	void Error(SQLHSTMT stmt);
	void AllPrepare();
public:
	bool Init();
	bool Connect();
	bool Release();
public:
	bool ExecTableInfo(const TCHAR* TableName, const wstring sql);
	bool ExecSelect(const TCHAR* TableName, const wstring userid);
	bool ExecSelectAll(const TCHAR* TableName);
public: // 계정생성
	void PrepareAccountCreate();
	void ExecAccountCreate(const TCHAR* id, const TCHAR* pw);
public: // id/pw 찾기
	void PrepareFindAccount();
	void ExecFindAccount(int ph);
};

