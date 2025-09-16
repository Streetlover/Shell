#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>

void typeline(char option[],char fname[])
{
	int handle,n,lcnt;
	char ch;

	handle=open(fname,O_RDONLY);

	if(handle==-1)
	{
		printf("\n Unable to open File %s !!!",fname);
		return;
	}

	if(strcmp(option,"a")==0)
	{
		// Displaying All contents of file

		printf("\n Contents of FIle = %s\n",fname);
		while(read(handle,&ch,1)) // on failure read() function returns 0
		{
			printf("%c",ch);
		}
		close(handle);
	}
	else
	{
		n=atoi(option);

		
			lcnt=0;
			if(n>0)
			{
				printf("Displaying First %d lines of file \n",n);
				while(read(handle,&ch,1))
				{
					printf("%c",ch);
					if(ch=='\n')
					{
						lcnt++;
					}

					if(lcnt==n)
					{
						break;
					}
				}
				close(handle);
			}
			else
			{
				n=-n;
				printf("Displaying Last %d lines of file \n",n);
				while(read(handle,&ch,1))
				{
					if(ch=='\n')
					{
						lcnt++;
					}
				}

				n=lcnt-n;
				lcnt=0;
				lseek(handle,0,SEEK_SET);

				while(read(handle,&ch,1))
				{
					if(ch=='\n')
					{
						lcnt++;
					}
					if(lcnt==n)
					{
						break;
					}
				}

				while(read(handle,&ch,1))
				{
					printf("%c",ch);
				}
				close(handle);
			}
		
	}
}


int main()
{
	char cmd[40];
	char tok1[10],tok2[10],tok3[10],tok4[10];
	int n;

	while(1)
	{
		printf("\nMYSHELL $] ");

		fgets(cmd,40,stdin);

		n=sscanf(cmd,"%s%s%s%s",tok1,tok2,tok3,tok4);

		switch(n)
		{
		case 1:

			if(strcmp(tok1,"Exit"))
			{
				if(fork()==0)
				{
					execlp(tok1,tok1,NULL);
				}
			}
			wait(0);
			return 0;
			break;
		case 2:
			if(fork()==0)
			{
				execlp(tok1,tok1,tok2,NULL);
			}
			wait(0);
			break;
		case 3:	
			if(strcmp(tok1,"list")==0)
			{	
				typeline(tok2,tok3);
			}
			else
			{
			if(fork()==0)
			{
				execlp(tok1,tok1,tok2,tok3,NULL);
			}
			wait(0);
			}
			break;
		case 4:
			if(fork()==0)
			{
				execlp(tok1,tok1,tok2,tok3,tok3,NULL);
			}
			wait(0);
			break;

		}
	}
}
