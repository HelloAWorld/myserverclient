#include "mysocket.h"
#include "stdio.h"
#include "errno.h"
#include "unistd.h"
#include "fcntl.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "sys/socket.h"
#include "sys/epoll.h"

CMySocket::CMySocket(CMySocketHandle * pHandle):
m_pSocketHandle(pHandle)
{
	m_readbuffer.InitBuffer(1024 * 10);
	m_sendbuffer.InitBuffer(1024 * 10);
}

CMySocket::CMySocket(int sockid, CMySocketHandle * pHandle):
m_socketid(sockid), m_pSocketHandle(pHandle)
{
}

int CMySocket::create_socket()
{
		
	m_socketid = socket(AF_INET, SOCK_STREAM, 0);
	return 0;
}

int CMySocket::bind(int port)
{
	struct sockaddr_in serveraddr;
	sizeof(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(port);
	::bind(m_socketid, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr));
	
	return 0;
}

int CMySocket::setsockopt()
{
	int opt = 1;
	::setsockopt(m_socketid, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	return 0;
}

int CMySocket::setnonblocking()
{
	fcntl(m_socketid, F_SETFL, fcntl(m_socketid, F_GETFD, 0)|O_NONBLOCK);
	return 0;
}


int CMySocket::get_socketid()
{
	return m_socketid;
}

void CMySocket::closesocket()
{
	close(m_socketid);
}

int CMySocket::readdata()
{
	char buf[1024] = {0};
	int nread = recv(m_socketid, buf, 1024, 0);
	if(nread <= 0)
	{
		return -1;
	}
	m_readbuffer.AddData(buf, 1024);
	m_pSocketHandle->handle_read(m_readbuffer, m_sendbuffer);
	return 0;
}	

int CMySocket::senddata(const char * pData, int iDataLen)
{
	int nsend = send(m_socketid, pData, iDataLen, 0);
	if(nsend < 0)
	{
		return -1;
	}
	if(nsend < iDataLen)
	{
		m_sendbuffer.AddData(pData + nsend, iDataLen - nsend);		
	}
	return 0;
}
