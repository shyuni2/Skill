#pragma once
#include "Protocol.h"
#include <string>

using namespace std;

// ��Ŷ������ ������
// data << header << index << name << damage << message ; 
// data >> header >> index >> name >> damage >> message ; // ������ ó���ؾ���, �̷�������� �����͸� �ְ�ްڴ�
// �׷��� ���� <<, >> �� ���� ������ �����ε��� �������

class Packet
{
public:
	char* m_Offset; // ���� �����Ͱ� ���°�
	char* c_str() { return m_Offset; }
	UPACKET m_uPacket;
public:
	void PutData(const char* pData, int Size); // ������ �ְ�
	void GetData(const char* pData, int Size); // ������ �ޱ�
public: // ���������� ���������ϼ� ������ ���������� ���� ������ �����ε��� ���ش�
	Packet& operator << (int data);
	Packet& operator << (long data);
	Packet& operator << (short data);
	Packet& operator << (float data);
	Packet& operator << (byte data);
	Packet& operator << (char* data);
	Packet& operator << (DWORD data);
	Packet& operator << (string data);
public:
	Packet& operator >> (int data);
	Packet& operator >> (long data);
	Packet& operator >> (short data);
	Packet& operator >> (float data);
	Packet& operator >> (byte data);
	Packet& operator >> (char* data);
	Packet& operator >> (DWORD data);
	Packet& operator >> (string data);
public:
	Packet();
	Packet(WORD Type);
	Packet(const Packet& packet);
	~Packet();
};
