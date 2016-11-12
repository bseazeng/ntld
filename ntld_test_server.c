#include "ntld.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_PORT 50001
#define BUF_SIZE 1024

int main()
{	
    #if 1    
    struct list_head test_xml_file;
    loadFile("database/test.xml" &test_xml_file);
    #else
    
	struct sockaddr_in server_addr;
	struct sockaddr_in clientAddr;
	int     addr_len          = sizeof(clientAddr);
	int     client            = 0;	
	int     serverSocket     = 0;
	
	pid_t   child_pid         = 0;

	if((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket failed");
		return 1;
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(serverSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("connect");
		return 1;
	}

	if(listen(serverSocket, 5) < 0) 
	{
		perror("listen");
		return 1;
	}

	while(1)
	{
		printf("Listening on port: %d\n", SERVER_PORT);
		client = accept(serverSocket, (struct sockaddr*)&clientAddr, (socklen_t*)&addr_len);
		if(client < 0)
		{
			perror("accept");
			continue;
		}
		if( -1 ==(child_pid = fork()))
		{
			printf("fork error\n");
			continue;
		}
		printf("\nrecv client data...n");
		printf("IP: %s\n", inet_ntoa(clientAddr.sin_addr));
		printf("Port:%d\n", htons(clientAddr.sin_port));
		if(0 == child_pid )
		{	
			close(serverSocket);
			char    buffer[BUF_SIZE]  = {0};
			char    sendbuf[BUF_SIZE] = {0};
			int     iDataNum          =0 ;
			while(1)
			{
				
				memset(buffer,0,BUF_SIZE);
				memset(sendbuf,0,BUF_SIZE);
				iDataNum = recv(client, buffer, BUF_SIZE, 0);
				if(iDataNum < 0)
				{
					perror("recv");
					continue;
				}
				ntld_message_struct tmp;
				copyBufferToMsg( buffer,iDataNum, &tmp);
				printMsg(&tmp);
				send(client, buffer, iDataNum, 0);
				#if 1
				break;
				#endif
			}
			exit(0);
		}
		
	}
  #endif
  return 0;
}

