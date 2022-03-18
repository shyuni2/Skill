#include "odbc.h"

void main()
{
	setlocale(LC_ALL, "korean");
	Odbc odbc;
	odbc.Init();

	if (odbc.Connect())
	{
		odbc.ExecTableInfo(L"GAME");
	}

	odbc.Release();
}