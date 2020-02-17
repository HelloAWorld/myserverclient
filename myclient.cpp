#include "myclient.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "stdio.h"
#include "errno.h"
#include "unistd.h"
#include "fcntl.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "sys/socket.h"
#include "sys/epoll.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"

int CMyClient::create_socket()
{
	m_clientsocket.create_socket();
	return 0;
}

int CMyClient::connect(const std::string & strServerIp, int serverport)
{
	struct sockaddr_in seraddr;
	
	memset(&seraddr, 0, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(serverport);
	inet_pton(AF_INET, strServerIp.c_str(), &seraddr.sin_addr);

	::connect(m_clientsocket.get_socketid(), (struct sockaddr*)&seraddr, sizeof(seraddr));
	
	handle();
}

int CMyClient::handle()
{
	char sendline[1024], recvline[1024];

	int n = 0;
	for(;;)
	{
		printf("I say:");
		fgets(sendline, 1024, stdin);
		n = write(m_clientsocket.get_socketid(), sendline, strlen(sendline));
		n = read(m_clientsocket.get_socketid(), recvline, 1024);
		write(STDOUT_FILENO, recvline, n);
	}
	return 0;
}
