#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>

void count(char option[],char fname[])
{
	int handle;
	int ccnt=0,wcnt=0,lcnt=0;

	char ch;

	handle=open(fname,O_RDONLY);

	if(handle==-1)
	{
		printf("Unable to open File %s!!!\n",fname);
	}

	while(read(handle,&ch,1))
	{
		ccnt++;
		if(ch==' '||ch=='\t')
		{
			wcnt++;
		}
		else if(ch=='\n')
		{
			lcnt++;
			wcnt++;
		}

	}

	close(handle);

	if(strcmp(option,"C")==0)
	{
		printf("\n Total No, of character in file = %d\n",ccnt);
	}
	else if(strcmp(option,"W")==0)
	{
		printf("\n Total No, of Words in file = %d\n",wcnt);
	}
	else if(strcmp(option,"L")==0)
	{
		printf("\n Total No, of Lines in file = %d\n",lcnt);
	}
	else
	{
		printf("\nInvalid Option!!!\n");
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
			if(fork()==0)
			{
				execlp(tok1,tok1,NULL);
			}
			wait(0);
			break;
		case 2:
			if(fork()==0)
			{
				execlp(tok1,tok1,tok2,NULL);
			}
			wait(0);
			break;
		case 3:
			if(strcmp(tok1,"count")==0)
			{
				count(tok2,tok3);
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
				execlp(tok1,tok1,tok2,tok3,tok4,NULL);
			}
			break;
		}
	}
}