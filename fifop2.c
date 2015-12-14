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
	
	fd1 = open( FIFO_NAME1, O_WRONLY ); 
	//waiting for writers
	fd2 = open( FIFO_NAME2, O_RDONLY);
	//waiting for readers
	
	char buff[SIZE];
	char inputStr[SIZE];
	printf("(Write exit to EXIT)\n");
	while( 1 )
	{
		//writing to fifo1
		printf("p2: write - ");
		if(fgets( inputStr, SIZE, stdin ) == NULL )
			break;
		else
		{
			inputStr[strlen(inputStr)-1] = '\0';
			if( strcmp(inputStr,"exit")==0)
				break;
			num = write(fd1, inputStr, strlen(inputStr));
			if( num == -1 )
			{
				perror("write p1");		
			}
			else
				printf("p2: wrote - %s\n",inputStr);
		}		
		//reading from fifo1
		num = read( fd2, buff, SIZE);
		if( num == -1 )
		{
			perror("Reading fd2");
		}
		else if( num == 0 )
			break;
		else
		{
			buff[num] = '\0';
			printf("p2: read - %s\n",buff);
		}
	}	
	return 0;
}
