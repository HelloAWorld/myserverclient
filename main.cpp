#ifdef __MY_SERVER__
#include "myserver.h"
#else
#include "myclient.h"
#endif
#include "mycirclebuffer.h"

void test_mycirclebuffer();
void start_server();
void start_client();

int main()
{
	test_mycirclebuffer();
	
	#ifdef __MY_SERVER__
	start_server();
	#else
	start_client();
	#endif
	return 0;
}

#ifdef __MY_SERVER__
void start_server()
{
	CMyServer server;
	server.create_server(8080);
	server.epoll_bind();
	for(;;)
	{
		server.start_loop();
	}
}
#else
void start_client()
{
	CMyClient client;
	client.create_socket();
	client.connect("127.0.0.1",8080);
}

void test_mycirclebuffer()
{
	CMyCircleBuffer circlebuffer;
	circlebuffer.InitBuffer(32);
	circlebuffer.AddData("111111111122222222223333333333",30);
	char buffer[10];
	circlebuffer.GetData(buffer,10);
	circlebuffer.AddData("5555555555",10);
	circlebuffer.GetData(buffer, 10);
	circlebuffer.AddData("6666666666", 10);	
}

#endif
