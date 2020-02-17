#ifndef __MY_SOCKET_HANDLE_H__
#define __MY_SOCKET_HANDLE_H__

#include "mycirclebuffer.h"

class CMySocketHandle
{
public:
	virtual ~CMySocketHandle() {};
	virtual int handle_read(CMyCircleBuffer & recvbuffer, CMyCircleBuffer & sendbuffer) = 0;
	virtual int handle_write(int iDataLen) = 0;
};

class CMySocketHandleImpl : public CMySocketHandle
{
public:
	int handle_read(CMyCircleBuffer & recvbuffer, CMyCircleBuffer & sendbuffer);
	int handle_write(int iDataLen);

};


#endif
