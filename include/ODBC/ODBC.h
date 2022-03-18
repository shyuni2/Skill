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
	SQLHENV m_hEnv;//ȯ���ڵ�
	SQLHDBC	m_hDbc;//�����ڵ�
	//��ɴ� �ڵ� �ϳ��� �ִ°� ����
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
public: // ��������
	void PrepareAccountCreate();
	void ExecAccountCreate(const TCHAR* id, const TCHAR* pw);
public: // id/pw ã��
	void PrepareFindAccount();
	void ExecFindAccount(int ph);
};

