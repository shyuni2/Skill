#include "Packet.h"

// �Լ�
void Packet::PutData(const char* pData, int Size) // ������ �ְ�
{
	m_uPacket.ph.len += Size; // ���̴� �����ŭ ����
	memcpy(m_Offset, pData, Size); 
	m_Offset += Size; 
};
void Packet::GetData(const char* pData, int Size)// ������ �ޱ�
{
	memcpy(const_cast<char*>(pData), m_Offset, Size); // const�� �پ��ֱ⶧���� const_cast ĳ����
	m_Offset += Size;
};

// << �����ε�
Packet& Packet::operator<< (int data)
{
	PutData((char*)&data, sizeof(int));
	return *this;
}
Packet& Packet::operator<< (long data)
{
	PutData((char*)&data, sizeof(long));
	return *this;
}
Packet& Packet::operator<< (short data)
{
	PutData((char*)&data, sizeof(short));
	return *this;
}
Packet& Packet::operator<< (float data)
{
	PutData((char*)&data, sizeof(float));
	return *this;
}
Packet& Packet::operator<< (char* data) // �� ���������� �޸�Ǵµ� ���� ���������� ����ؾ��� ������ �ִ�
{
	PutData(data, strlen(data) + 1); // ���̿��� +1�ϴ����� : ���ڵڿ� �ΰ��� ���� ��ĭ �����
	return *this;
}
Packet& Packet::operator<< (string data)
{
	PutData(data.c_str(), data.size() + 1); // string���� const char*���� ��ȯ�Ҷ� ����ϴ� �Լ� c_str(), string���� ũ�⸦ ������ִ� �Լ� size()
	return *this;
}

// >> �����ε�
Packet& Packet::operator>> (int data)
{
	GetData((char*)&data, sizeof(int));
	return *this;
}
Packet& Packet::operator>> (long data)
{
	GetData((char*)&data, sizeof(long));
	return *this;
}
Packet& Packet::operator>> (short data)
{
	GetData((char*)&data, sizeof(short));
	return *this;
}
Packet& Packet::operator>> (float data)
{
	GetData((char*)&data, sizeof(float));
	return *this;
}
Packet& Packet::operator>> (char* data) // �� ���������� �޸�Ǵµ� ���� ���������� ����ؾ��� ������ �ִ�
{
	GetData(data, strlen(data) + 1); // ���̿��� +1�ϴ����� : ���ڵڿ� �ΰ��� ���� ��ĭ �����
	return *this;
}
Packet& Packet::operator>> (string data)
{
	GetData(data.c_str(), data.size() + 1); // string���� const char*���� ��ȯ�Ҷ� ����ϴ� �Լ� c_str(), string���� ũ�⸦ ������ִ� �Լ� size()
	return *this;
}

// ������
Packet::Packet()
{ 
	ZeroMemory(&m_uPacket, sizeof(UPACKET)); // �޸� �ʱ�ȭ 
	m_uPacket.ph.len = PACKET_HEADER_SIZE; 
	m_Offset = m_uPacket.msg; // m_Offset�� m_uPacket�� �޼����� ����
}
Packet::Packet(WORD Type)
{
	ZeroMemory(&m_uPacket, sizeof(UPACKET)); // �޸� �ʱ�ȭ 
	m_uPacket.ph.len = PACKET_HEADER_SIZE; 
	m_uPacket.ph.type = Type; 
	m_Offset = m_uPacket.msg; // m_Offset�� m_uPacket�� �޼����� ����
}
Packet::Packet(const Packet& packet)
{
	m_uPacket.ph = packet.m_uPacket.ph; 
	memcpy(m_uPacket.msg, packet.m_uPacket.msg, sizeof(char) * 4096);
	m_Offset = m_uPacket.msg; // m_Offset�� m_uPacket�� �޼����� ����
}
Packet::~Packet()
{

}