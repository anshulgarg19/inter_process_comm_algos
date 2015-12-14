#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

#define SIZE 30

int main( void )
{
	int pfd1[2],pfd2[2];
	char buff[SIZE];
	char inputStr[SIZE-1];
	int retVal;
	int rbytes;

	pipe( pfd1 );
	pipe( pfd2 );
	
	retVal = fork();
	if( retVal == 0 )
	{
		while(1)
		{	
			printf("Child: Enter data to send to parent:\n");
			if( gets(inputStr) == NULL )
			{
				break;
			}
			write( pfd1[1], inputStr, strlen(inputStr));
			rbytes = read( pfd2[0], buff, SIZE);
			printf("Child: Data received from parent is:%s\n\n",buff);
		}
	}
	else
	{
		while( 1 )
		{
			rbytes = read( pfd1[0], buff,SIZE);
			printf("Parent: Data received from child is: %s\n\n",buff);
			printf("Parent: Enter data to send to child:\n");
			if( gets(inputStr) == NULL )
				break;
			write( pfd2[1], inputStr, strlen(inputStr));
		}			
	}
	return 0;
}
