#ifndef	__MY_SERVER_H__
#define __MY_SERVER_H__

#include "sys/epoll.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "mysocket.h"
#include <map>

class CMyServer
{
public:
	CMyServer();
	int create_server(int port);
	int epoll_bind();
	int start_loop();
	int handle(int fd);
	int end_loop();
private:
	int m_ep_fd;
	CMySocket m_serversocket;
	std::map<int, CMySocket *> m_mapClients;
};

#endif
