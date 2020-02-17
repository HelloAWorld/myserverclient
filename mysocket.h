#ifndef __MY_SOCKET_H__
#define __MY_SOCKET_H__

#include "mycirclebuffer.h"
#include "mysockethandle.h"

class CMySocket
{
public:
	CMySocket(CMySocketHandle  * pHandle);
	CMySocket(int sockid, CMySocketHandle * pHandle);
	int create_socket();
	int bind(int port);
	int setsockopt();
	int setnonblocking();	
	int get_socketid();
	void closesocket();
	
	int readdata();
	int senddata(const char * pData, int iDataLen);
private:
	int m_socketid;
	CMySocketHandle * m_pSocketHandle;
	CMyCircleBuffer m_readbuffer;
	CMyCircleBuffer m_sendbuffer;
};

#endif
