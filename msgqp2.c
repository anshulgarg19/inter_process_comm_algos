#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

#define SIZE 40
#define RCV_TYPE 1
#define SEND_TYPE 2

typedef struct msgBlock{
	long mtype;
	char text[SIZE];
}msgBlock;

int main( void )
{
	key_t key;
	key = ftok("msgqp1.c", 'a');
	if( key == -1 )
	{
		perror("Key ");
		exit(1);
	}
	int msgid;
	msgid = msgget( key, 0666);
	if( msgid == -1 )
	{
		perror("msgget ");
		exit(2);
	}
	
	msgBlock mb;
	msgBlock mbSend;

	printf("(Write exit to EXIT)\n");
	char inputStr[SIZE];
	while( 1 )
	{
		if( msgrcv( msgid, &mb, sizeof(mb.text),RCV_TYPE,0) == -1 )
		{
			perror("msgrcv p2 ");
			exit(1);
		}
		printf("msg fetched: %s \n",mb.text);
		printf("send msg: ");
		if( fgets(inputStr, SIZE, stdin) == NULL )
			break;
		if(inputStr[0] == '\n')
			break;

		int len = strlen(inputStr);
		inputStr[len-1] = '\0';
		if( strcmp(inputStr,"exit") == 0 )
			break;
		mbSend.mtype = SEND_TYPE;
		strcpy( mbSend.text, inputStr);
		if( msgsnd(msgid, &mbSend, len,0) == -1)
			perror("msgsend p2 ");
	}
	if( msgctl(msgid, IPC_RMID, NULL) == -1 )
		perror("msgctl ");
	return 0;
}
