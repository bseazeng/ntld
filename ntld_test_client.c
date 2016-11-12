/*socket tcp¿Í»§¶Ë*/
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
#include <errno.h>
#include "ntld.h"

#define SERVER_PORT 50001
#define BUF_SIZE 1024
#define SERVER_IP "127.0.0.1"
int main( void )
{  
	struct sockaddr_in serverAddr;
	char    sendbuf[BUF_SIZE] = {0};
	char    recvbuf[BUF_SIZE] = {0};
	int     iDataNum          = 0;
	int     clientSocket      = 0;
	if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket failed\n");
		return -1;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	if(connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		printf("connect failed[%d]\n",errno);
		return 1;
	}

	printf("connect with destination host...\n");

	ntld_message_struct  login_msg;
	INIT_LIST_HEAD(&login_msg.record_list);	
	int msg_len = setIntData(1,-1,&login_msg.record_list);
	msg_len    += setUIntData(2,(unsigned int)4294967295,&login_msg.record_list);
	msg_len    += setUCharData(3,'a',&login_msg.record_list);
	msg_len    += setCharData(4,'A',&login_msg.record_list);
	msg_len    += setStringData(5,"Hello World",&login_msg.record_list);
	msg_len    += setLongData(6,(long)4294967295,&login_msg.record_list);
	msg_len    += setLongLongData(7,(long long)9223372036854775805,&login_msg.record_list);
	
	setHead( (unsigned long long)200 ,msg_len+sizeof(ntld_message_head_struct), &login_msg.msg_head);
	printf("===========send start=========\n");
	printMsg(&login_msg);	
	printf("===========send end=========\n");
	int len = copyMsgToBuffer( &login_msg, sendbuf , BUF_SIZE);	
	send(clientSocket, sendbuf, len, 0);
	iDataNum = recv(clientSocket, recvbuf, BUF_SIZE, 0);
	
	ntld_message_struct tmp;
	copyBufferToMsg( recvbuf,len, &tmp);
	printf("===========recv start=========\n");	
	printMsg(&tmp);	
	printf("===========recv end=========\n");

	close(clientSocket);
	freeMsgData(&tmp.record_list);
	return 0;
}

