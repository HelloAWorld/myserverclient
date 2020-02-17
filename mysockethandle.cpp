#include "mysockethandle.h"
#include "mymsgheader.h"

int CMySocketHandleImpl::handle_read(CMyCircleBuffer & recvbuffer, CMyCircleBuffer & sendbuffer)
{
	CMyMsgHeader msg;
	
	if(buffer.GetDataLen() > sizeof(int))
	{
		int msglen = 0;
		memcpy(msglen, recvbuffer.GetData(), sizeof(int));
		if(msglen <= recvbuffer.GetDataLength())
		{
			int ret = msg.parse(recvbuffer.GetData(), msglen);
			recvbuffer.SetPosition(msglen);
			printf("recv msglen:%d msgtype:%d msgdata:%s\r\n", msg.GetMsgLen(), msg.GetMsgType(), msg.GetMsgData());
			
		}
	}
	return 0;
}

int CMySocketHandleImpl::handle_write(int iDataLen)
{
	return 0;
}
