#ifndef __MY_CLIENT_H__
#define __MY_CLIENT_H__

#include <string>

#include "mysocket.h"
class CMyClient
{
public:
	int create_socket();
	int connect(const std::string& strServerIp, int serverport);
	int handle();
private:
	CMySocket m_clientsocket;
};

#endif
