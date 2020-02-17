#include "myserver.h"
#include "stdio.h"
#include "errno.h"
#include "unistd.h"
#include "fcntl.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "sys/socket.h"
#include "sys/epoll.h"
#include "string.h"

CMyServer::CMyServer():
m_serversocket(new CMySocketHandleImpl())
{
}

int CMyServer::create_server(int port)
{
	m_serversocket.create_socket();
	m_serversocket.bind(port);
	m_serversocket.setnonblocking();
	listen(m_serversocket.get_socketid(), 100);

	return 0;
}

int CMyServer::epoll_bind()
{
	m_ep_fd = epoll_create(10000);
	epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = m_serversocket.get_socketid();
	epoll_ctl(m_ep_fd,EPOLL_CTL_ADD,m_serversocket.get_socketid(),&ev);
}

int CMyServer::start_loop()
{
	struct epoll_event events[10000];
	struct epoll_event ev;
	int curfds = 1;
	int nfds = epoll_wait(m_ep_fd, events, curfds, -1);
	for(int i = 0; i < nfds; i++)
	{
		if(events[i].data.fd == m_serversocket.get_socketid())
		{
			struct sockaddr_in clienaddr;
			socklen_t socklen = sizeof(struct sockaddr_in);
			int connfd = accept(m_serversocket.get_socketid(),(struct sockaddr *)&clienaddr, &socklen);
			printf("accept from %s %d\r\n", inet_ntoa(clienaddr.sin_addr), clienaddr.sin_port);
			
			CMySocket *pmysocket = new CMySocket(connfd, new CMySocketHandleImpl());
			pmysocket->setnonblocking();
			m_mapClients.insert(std::make_pair(connfd, pmysocket));
			ev.events = EPOLLIN | EPOLLET;
			ev.data.fd = connfd;
			epoll_ctl(m_ep_fd, EPOLL_CTL_ADD, connfd, &ev);
		}
		else
		{
			int ret = handle(events[i].data.fd);
			if(ret < 0)
			{
				epoll_ctl(m_ep_fd, EPOLL_CTL_DEL, events[i].data.fd,&ev);
			}
		}
	}
	return 0;
}

int CMyServer::handle(int fd)
{
	int nread;
	char buf[1024]= {0};
	std::map<int, CMySocket *>::iterator it;
	it = m_mapClients.find(fd);
	if(it != m_mapClients.end())
	{
		int ret =it->second->readdata();	
		if(ret < 0)
		{
			it->second->closesocket();
			delete it->second;
			m_mapClients.erase(fd);
		}
	}
	return 0;
}

int CMyServer::end_loop()
{
	return 0;
}
