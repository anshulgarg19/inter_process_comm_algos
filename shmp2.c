#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/ipc.h>

#define SHM_SIZE 1024

int main( void )
{
	key_t key;
	key = ftok("shmp1.c",'a');
	if( key == -1 )
	{
		perror("KEy ");
		exit(1);
	}
	int shmid;
	shmid = shmget( key, SHM_SIZE, 0666 );
	if( shmid == -1 )
	{
		perror("shmegt ");
		exit(2);
	}
	char* data,*t;
	data = shmat( shmid, (void*)0,0);
	if( data == (void*)-1)
	{
		perror("shmat ");
		exit(3);
	}
	char ch;
	t = data;

	while( 1 )
	{
		while(*t != '*' )
			putchar(*t++);	
	}
	putchar('\n');
	return 0;
}
