#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>

void search(char option[],char pat[],char fname[])
{
	int handle,i=0,cnt=0;

	char ch,data[100],*ptr;

	handle=open(fname,O_RDONLY);

	if(handle==-1)
	{
		printf("Unable to open FIle %s !!!\n",fname);
		return;
	}

	if(strcmp(option,"F")==0)
	{
		i=0;
		while(read(handle,&ch,1))// on failure read() function returns 0
		{
			data[i]=ch;
			i++;
			if(ch=='\n')
			{
				data[i]='\0';
				if((strstr(data,pat))!=NULL)
				{
					printf("\n First occurance of pattern in line is given below \n");
					puts(data);
					break;
				}
				i=0;
			}
		}
	}
	else if (strcmp(option,"C")==0)
	{
		cnt=0;
		i=0;
		while(read(handle,&ch,1))
		{
			data[i]=ch;
			i++;
			if(ch=='\n')
			{
				data[i]='\0';
				ptr=data;
				while((ptr=strstr(ptr,pat))!=NULL)
				{
					cnt++;
					ptr++;
				}
				i=0;
			}
		}
		printf("\n No of occurances of '%s' = %d",pat,cnt);
	}
	else if(strcmp(option,"A")==0)
	{
		printf("\n Displaying All Occurances of %s \n",pat);
		i=0;
		while(read(handle,&ch,1)) // on failure read() function returns 0
		{
			data[i]=ch;
			i++;
			if(ch=='\n')
			{
				data[i]='\0';
				if((ptr=strstr(data,pat))!=NULL)
				{
					puts(data);
				}
				i=0;
			}
		}
	}
	else
	{
		printf("Invalid Option Selected !!\n");
	}
	close(handle);
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
			if(fork()==0)
			{
				execlp(tok1,tok1,tok2,NULL);
			}
			wait(0);
			break;
		case 4:
			if(strcmp(tok1,"search")==0)
			{	
				search(tok2,tok3,tok4);
			}
			else
			{
			if(fork()==0)
			{
				execlp(tok1,tok1,tok2,tok3,tok4,NULL);
			}
			wait(0);
			}
			break;

		}
	}
}
