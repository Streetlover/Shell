#include<stdio.h> // for input output
#include<stdlib.h> // for exit
#include<string.h> // for String
#include<unistd.h>
#include<string.h> // for string
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<ctype.h>
#include<dirent.h> // for directories

DIR *path=NULL;
struct dirent *dir;
char folderPath[20]="./Users/";

// validate if user in its own account then he cant use create or login cmd

void printDirectory()
{

	printf("The ls in Directory is:- \n");

	path=opendir(folderPath);

	if(path)
	{
		while((dir=readdir(path))!=NULL)
		{
			printf("%s\n",dir->d_name);
		}
	}
	// printf("executed\n");
}

int create()
{
	FILE *fp=NULL;
	
	fp=fopen("./Admin/Login.txt","a+");

	if(fp==NULL)
	{
		printf("Unable to open file!!!\n");
		return 0;
	}

	char uname[100],pwd[20];
	char line[80];
	printf("Enter the UserName:- ");
	// fgets(uname,sizeof(uname),stdin);
	scanf("%s", uname);
	getchar();

	while(fgets(line,sizeof(line),fp))
	{
		if(strstr(line,uname)!=NULL)
		{
			printf("User Already Exists!!!\n");
			return 0;
		}
	}

	printf("Enter the Password:- ");
	// fgets(pwd,sizeof(pwd),stdin);
	scanf("%s", pwd);
	getchar();
	
	fputs(uname,fp);
	fputs(" :- ",fp);
	fputs(pwd,fp);
	fputs("\n",fp);

	char here[20]="./Users/";
	strcat(here,uname);

	mkdir(here,0777);

	fclose(fp);
	return 1;

}


char* login()
{
	FILE *fp;
	int flag=-1;

	fp=fopen("./Admin/Login.txt","r");

	if(fp==NULL)
	{
		printf("Unable to open a File !!!\n");
		return NULL;
	}
	// char folderPath[20]="./Users/";
	static char uname[20];
	char pwd[20],line[80];	
	printf("UserName:- ");
	// fgets(uname,sizeof(uname),stdin);
	scanf("%s", uname);
	getchar();
	while(fgets(line,sizeof(line),fp))
	{
		if(strstr(line,uname)!=NULL)
		{
			flag=1;
			break;
		}

	}

	if(flag>=0)
	{
			printf("Password:- ");
			// fgets(pwd,sizeof(pwd),stdin);
			scanf("%s", pwd);
			getchar();
			if(strstr(line,pwd)!=NULL)
			{

//----------------------------------------------------
	// The code for accessing the specific directory
				strcat(folderPath,uname);
				printf("\nFolder Path : %s\n", folderPath);

				path=opendir(folderPath);
				//printf("\nPath : %s\n", path);

				if(path)
				{
					while((dir=readdir(path))!=NULL)
					{
						printf("%s\n",dir->d_name);
					}

				}

				printDirectory();

//----------------------------------------------------
				printf("\n%s Login Succesfully !!\n",uname);
				return uname;
			}
			else
			{
				printf("\nincorrect Password!!\n");
				return NULL;
			}
	}
	else
	{
		printf("\n %s Not exists Please Create Accrount (use Create cmd)!!\n",uname);
		return NULL;
	}

}

int main()
{
	char cmd[40],*uname=NULL;
	char tok1[10],tok2[10],tok3[10],tok4[10];
	int n,flag=0;

	system("clear");
	while(1)
	{
		// if(uname!=NULL)
		if(path!=NULL)
		{
			printf("\n%s SHELL $] ",uname);
		}
		else
		{
			printf("\nMYSHELL $] ");
		}
		fgets(cmd,40,stdin);

		n=sscanf(cmd,"%s%s%s%s",tok1,tok2,tok3,tok4);


// 	strToLower(str)
//=====================================================
		for(int i=0;tok1[i]!='\0';i++)
		{	
			tok1[i]=tolower((unsigned char)tok1[i]);
		}
//======================================================
		switch(n)
		{
		case 1:
			
			if(strcmp(tok1,"login")==0)
			{
				uname=login();

			}
			else if(strcmp(tok1,"create")==0)
			{
				flag=create();
				if(flag==1)
				{
					printf("\nUser Created Succesfully!!\n");
				}
			}
			else if(strcmp(tok1,"exit")==0 || strcmp(tok1,"0")==0)
			{
				if(fork()==0)
				{
					execlp(tok1,tok1,NULL);
				}

					closedir(path); //closing directory
					wait(0);
					return 0;
			}
			else if(strcmp(tok1,"logout")==0)
			{
				// uname=NULL;
				memset(folderPath, 0, sizeof(folderPath));
				strcpy(folderPath,"./Users/");
				path=NULL; 		
			}
			else if(!(strcmp(tok1,"ls")) && path!=NULL)
			{
				// printf("You are in gs\n");
				printDirectory();
				// printf("You are after in gs\n");
			}
			else
			{
				if(fork()==0)
				{
					execlp(tok1,tok1,NULL);
				}
				wait(0);
	
			}
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
				execlp(tok1,tok1,tok2,tok3,NULL);
			}
			wait(0);
			break;
		case 4:
			if(fork()==0)
			{
				execlp(tok1,tok1,tok2,NULL);
			}
			wait(0);
			break;
		}
	}
}