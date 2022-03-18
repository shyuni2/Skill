#include "TNetUser.h"

int TNetUser::DispatchRead(char* szRecvBuffer, int iRecvByte)
{
	// 데이터가 짤려서 들어올수있기 때문에 어디가 시작인지 모르니까 시작위치를 바꿔서 더 받아줌
	if (m_iWritePos + iRecvByte >= 2048)
	{
		if (m_iReadPos > 0)
		{
			memmove(&m_szRecvBuffer[0], &m_szRecvBuffer[m_iPacketPos], m_iReadPos);
		}
		m_iReadPos = 0;
		m_iWritePos = m_iReadPos; // 잘린 짜투리가 부족할때 더 받음
	}
	// 얼만큼 데이터가 들어왔는지 확인할수있기 때문에 받은 양 만큼 넣어주고
	memcpy(&m_szRecvBuffer[m_iWritePos], szRecvBuffer, iRecvByte);
	m_iWritePos += iRecvByte; // 버퍼의 이전에 저장된 위치
	m_iReadPos += iRecvByte; // 패킷 시작 위치로부터 받은 바이트

	if (m_iReadPos >= PACKET_HEADER_SIZE) 
	{
		// 패킷 해석가능
		UPACKET* pPacket = (UPACKET*)&m_szRecvBuffer[m_iPacketPos]; // 모든데이터가 문자열에 있으니 포인터사용, 처음엔 0번주소가 패킷
		// 적어도 한개의 패킷은 도착했다
		if (pPacket->ph.len <= m_iReadPos)
		{
			do {
				TPacket tPacket(pPacket->ph.type); // UPacket, TPacket 상관없음
				memcpy(&tPacket, &m_szRecvBuffer[m_iPacketPos], pPacket->ph.len); // 하나의 패킷 완성
				m_packetPool.push_back(tPacket); // 완성된 패킷 푸시

				// 잔여량이 있으면 또 받을수있음
				// 다음패킷 처리
				m_iPacketPos += pPacket->ph.len;
				m_iReadPos -= pPacket->ph.len;
				if (m_iReadPos < PACKET_HEADER_SIZE)
				{
					break;
				}
				pPacket = (UPACKET*)&m_szRecvBuffer[m_iPacketPos];
			} while (pPacket->ph.len <= m_iReadPos);
		}
	}
	return 1;
}

void TNetUser::set(SOCKET sock, SOCKADDR_IN addr)
{
	m_bConnect = true; // 연결 성공
	ZeroMemory(m_szRecvBuffer, sizeof(char) * 2048);
	m_iPacketPos = 0;
	m_iWritePos = 0; // 현재 저장위치
	m_iReadPos = 0;

	m_Sock = sock;
	m_Addr = addr;
	m_csName = inet_ntoa(addr.sin_addr);
	m_iPort = ntohs(addr.sin_port);
}