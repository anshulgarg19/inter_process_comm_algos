#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<string.h>
#include<sys/ipc.h>

#define SIZE 40
#define SEND_TYPE 1
#define RCV_TYPE 2

typedef struct msgBlock{
	long mtype;
	char text[SIZE];
}msgBlock;

int main( void )
{
	key_t key;
	int msgid;
	char inputStr[SIZE];

	key = ftok("msgqp1.c", 'a');
	if( key == -1 )
	{
		perror("Key ");
		exit(1);
	}

	msgid = msgget( key, IPC_CREAT | 0666 );
	if( msgid == -1 )
	{
		perror("msg get ");
		exit( 2 );
	}

	long mt;
	msgBlock mb;
	msgBlock mbRcv;
	printf("(Write exit to EXIT)\n");
	while( 1 )	
	{
		printf("Send msg content: ");
		if( fgets(inputStr,SIZE, stdin) == NULL )
			break;
		if(inputStr[0] == '\n')
			break;
		mb.mtype = SEND_TYPE;
		int len = strlen(inputStr);
		inputStr[ len -1 ] = '\0';
		if( strcmp(inputStr,"exit")==0)
			break;
		strcpy( mb.text, inputStr);
		if(msgsnd(msgid, &mb, len, 0)== -1)
			perror("msgsnd ");

		// receiving at 2
		if( msgrcv(msgid, &mbRcv, sizeof(mbRcv.text), RCV_TYPE,0) ==-1)
			perror("msgrcv p1 ");
		else
			printf("msg received: %s\n", mbRcv.text);
	}
	if( msgctl(msgid, IPC_RMID, NULL) == -1 )
		perror("msgctl ");
	return 0;
}
