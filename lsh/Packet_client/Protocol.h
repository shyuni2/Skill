#pragma once
#include <Windows.h>

#pragma pack(push,1) // ���� 1����Ʈ ��ŷ�� ��, �� ó���� �Ǿ���� ������ �ȵ� pack~pop���̰� 1����Ʈ����
// ������ ������ ��� ����ü�� 1����Ʈ ��ŷ�� �� 
// ����ü�� �̿��ϴ��� �ݵ�� ����Ʈ������ ����� �Ǿ����, ����ü ũ�Ⱑ �޶����� ���ڿ� �����ϴµ� �ɰ��� �������� 

typedef struct
{
	WORD len; // ����
	WORD type; // Ÿ��
}PACKET_HEADER;

typedef struct // ��� 1>
{
	PACKET_HEADER ph; // ��Ŷ����� �ݵ�� �����ؾ���
	char msg[4096]; // �ջ������� �迭ũ��ȿ� ������ ������ ����, ��Ŷ�� ������ ������ �����س��� ���
}UPACKET, * P_UPACKET;

// �� ��Ģ�� �ȵ����� ����� �ȵ�, ������ � �޼����� �� UPACKET�� �̿�����

struct ChatMsg // ��� 2> // ���� �޼��� ó���� �� 
{
	long index;
	char name[20]; // ȫ�浿 , �����ͺ��̽��� �̸��� �����Ʈ�� �����ߴ����� ���� �޶���
	short damage;
	char message[2048]; // �ȳ��ϼ���! ���� �޼����� ��´�
};

#pragma pack(pop) // �ؿ��� ����ü ũ��ε�

#define PACKET_CHAT_MSG 1000
#define PACKET_HEADER_SIZE 4