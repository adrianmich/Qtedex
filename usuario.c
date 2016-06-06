#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGHT 20

void guardarUsuario(Usuario u)
{
	FILE * fp;
	fp=fopen("userinfo.txt","a");
	fprintf(fp,"%s\n", u.username);
	fprintf(fp,"%s\n", u.password);
	fclose(fp);
}

int checkFileExistance()
{
	FILE * entrada;
	int resultado = 0;

	if((entrada = fopen("userinfo.txt", "r"))==NULL)
	{
		resultado = 1;
		return resultado;
	}
	return resultado;
}

int comprobarUserPass(Usuario u1)
{
	FILE * fp;
	fp = fopen("userinfo.txt", "r");
	char str[MAX_LENGHT+2];
	int i=1;
	char name [MAX_LENGHT];
	char pass [MAX_LENGHT];
	int checker=1;
	int key=0;

	while(fgets(str,MAX_LENGHT+2,fp)!=NULL)
	{
		if(i%2!=0)
		{
			sscanf(str,"%s",name);
			if(strcmp(name,u1.username)==0)
			{
				key=1;
			}
		}
		if(key==1)
		{
			key=0;
			fgets(str,MAX_LENGHT+2,fp);
			sscanf(str,"%s",pass);
			if(strcmp(pass,u1.password)==0)
			{
				checker=0;
				return checker;
			}
		}
	}
	return checker;

}

int comprobarUsername(Usuario u1)
{
	FILE * fp;
	fp = fopen("userinfo.txt", "r");
	char str[MAX_LENGHT+2];
	int i=1;
	char name [MAX_LENGHT];
	int checker=1;

	while(fgets(str,MAX_LENGHT+2,fp)!=NULL)
	{
		if(i%2!=0)
		{
			sscanf(str,"%s",name);
			if(strcmp(name,u1.username)==0)
			{
				checker=0;
				return checker;
			}
		}
	}
	return checker;

}

void print(Usuario u)
{
	printf("Usuario:\t%s\n", u.username);
	printf("Password:\t%s\n", u.password);
}
