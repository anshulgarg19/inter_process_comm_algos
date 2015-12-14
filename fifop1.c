#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

#define FIFO_NAME1 "./fifoFile1"
#define FIFO_NAME2 "./fifoFile2"

#define SIZE 30

int main( void )
{
	int fd1,fd2,num;
	mkfifo( FIFO_NAME1, 0666 );
	mkfifo( FIFO_NAME2, 0666 );
	
	fd1 = open( FIFO_NAME1, O_RDONLY ); 
	//waiting for writers
	fd2 = open( FIFO_NAME2, O_WRONLY);
	//waiting for readers
	
	char buff[SIZE];
	char inputStr[SIZE];
	printf("(Write exit to EXIT)\n");
	while( 1 )
	{
		//reading from fifo1
		num = read( fd1, buff, SIZE);
		if( num == -1 )
		{
			perror("Reading fd1");
		}
		else if( num == 0 )
			break;
		else
		{
			buff[num] = '\0';
			printf("p1: read - %s\n",buff);
		}
		//writing to fifo2
		printf("p1: write - ");
		if(fgets(inputStr, SIZE, stdin) == NULL )
			break;
		else
		{
			inputStr[strlen(inputStr)-1] = '\0';
			if( strcmp(inputStr,"exit") == 0 )
				break;
			num = write(fd2, inputStr, strlen(inputStr));
			if( num == -1 )
			{
				perror("write p1");		
			}
			else
				printf("p1: wrote - %s\n",inputStr);
		}		
	}	
	return 0;
}
