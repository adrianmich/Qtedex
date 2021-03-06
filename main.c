#include <stdio.h>
#include <stdlib.h>
#include "usuario.h"
#include <string.h>

#define MAX_LENGHT 20
#define NOM_ARCHIVO_USER  "user.txt"
#define NOM_ARCHIVO_PASS  "pass.txt"


void sobreNosotros(void)
{
	int key;
	do
	{
		system("cls");
		printf("\nEn EPA developers llevamos trabajando en aplicaciones para dispositivos moviles con intencion de mejorar y hacer mas facil las vidas de nuestros usuarios. Nuestros fundadores son Elena Perez de Iriarte, Paula Urteaga y Adrian Michelena. Nuestra andadura como grupo de desarrolladores comenzo con esta aplicacion de la cual estamos muy orgullosos.\n");
		printf("\nSalir (1=Si/0=No): ");
		scanf( "%d", &key);
	}while(key!=1);
}

void infoApp(void)
{
	int key;
		do
		{
			system("cls");
			printf("\nQtedex (Version 2.3.2) \n");
			printf("\nDesarrollado por EPA developers");
			printf("\n\nRequisitos recomendados:");
			printf("\n\tMemoria Ram:\t\t500 Mbytes");
			printf("\n\tEspacio en disco:\t25 Mbytes");
			printf("\n\tCalidad minima:\t\t1080px720p");
			printf("\n\nSalir (1=Si/0=No): ");
			scanf( "%d", &key);
		}while(key!=1);
}

void clear_if_needed(char *str)
{
    if (str[strlen(str) - 1] != '\n')
    {
        int c;
        while ( (c = getchar()) != EOF && c != '\n');
    }
}

void registro(void)
{
	char * username;
	char * password;
	char str[MAX_LENGHT];
	char savename[MAX_LENGHT];
	char savepass[MAX_LENGHT];

	if (fgets (str, MAX_LENGHT, stdin) != NULL)
	{
		system("cls");
		printf("\nUsuario: ");
		fgets(str,MAX_LENGHT,stdin);
		clear_if_needed(str);
		sscanf(str, "%s", savename);

		username = (char*)malloc ( strlen((savename) +1) * sizeof(char) );
		strcpy(username, savename);

		printf("Contrasena: ");
		fgets(str,MAX_LENGHT,stdin);
		clear_if_needed(str);
		sscanf(str, "%s",savepass);

		password = (char*)malloc ( strlen((savepass) +1) * sizeof(char) );
		strcpy(password, savepass);

		Usuario u = { username, password };

		if(checkFileExistance()==0)
		{
			int cmp = comprobarUsername(u);

			if(cmp==1)
			{
				guardarUsuario(u);
			}
			else
			{
				system("cls");
				printf("\nEl usuario ya existe");
				printf("Pulse una tecla para continuar: ");
				char cad; 
				cad = (char)getch();
			}
		}
		else
		{
			guardarUsuario(u);
		}

		free(password);
		free(username);
	}
}

void iniciarSesion(void)
{
	char str[MAX_LENGHT];
	char savename[MAX_LENGHT];
	char savepass[MAX_LENGHT];
	char * username;
	char * password;

	if (fgets (str, MAX_LENGHT, stdin) != NULL)
	{
		system("cls");
		printf("\nUsuario: ");
		fgets(str,MAX_LENGHT,stdin);
		clear_if_needed(str);
		sscanf(str, "%s", savename);

		username = (char*)malloc ( strlen((savename) +1) * sizeof(char) );
		strcpy(username, savename);

		printf("Contrasena: ");
		fgets(str,MAX_LENGHT,stdin);
		clear_if_needed(str);
		sscanf(str, "%s",savepass);

		password = (char*)malloc ( strlen((savepass) +1) * sizeof(char) );
		strcpy(password, savepass);

		Usuario u = { username, password };

		if(checkFileExistance()==0)
		{
			int check = comprobarUserPass(u);

			if(check==0)
			{
				system("cls");
				printf("\nHas iniciado sesion\n");
				printf("Pulse una tecla para continuar: ");
				char cad; 
				cad = (char)getch(); 
			}
			else
			{
				system("cls");
				printf("\nUsuario o contrasena erroneos");
				printf("Pulse una tecla para continuar: ");
				char cad; 
				cad = (char)getch(); 
			}
		}
		else
		{
			system("cls");
			printf("\nNo existen usuarios");
			printf("Pulse una tecla para continuar: ");
			char cad; 
			cad = (char)getch(); 
		}



		free(password);
		free(username);
	}
}

void menuAcceso(void)
{
	int eleccion;

	do
	{
		system("cls");
		printf("\n1.Iniciar sesion\n");
		printf("2.Registrarse\n");
		printf("3.Volver.\n");
		printf("\nEleccion: ");

		scanf( "%d", &eleccion );

		switch(eleccion)
		{
			case 1:
				iniciarSesion();
				eleccion = 3;
				break;
			case 2:
				registro();
				eleccion = 3;
				break;
			case 3:
				break;
			default:
				printf("\nElija una de las opciones tecleando su correspondiente numero \n");
				break;
		}
	}while(eleccion!=3);
}

int main()
{
	int entrar;
	int opcion;

	setvbuf(stdout, 0, _IONBF, 0);

	system("cls");
	printf("\nBienvenido a la aplicacion QTedex realizada por EPA Developers.\n");
	printf("Una vez que la pruebes tu mundo no sera igual.\n");

    printf("\nEntrar (1=Si/0=No): ");

    scanf( "%d", &entrar);

    if(entrar==1)
    {
        do
        {
            system("cls");
            printf("\n1.Acceder\n");
            printf("2.Sobre Nosotros\n");
            printf("3.Informacion de la aplicacion\n");
            printf("4.Cerrar\n");
            printf("\nEleccion: ");

            scanf( "%d", &opcion );

            switch(opcion)
            {
				case 1:
					menuAcceso();
					break;
				case 2:
					sobreNosotros();
					break;
				case 3:
					infoApp();
					break;
				case 4: break;
				default:
					printf("\nElija una de las opciones tecleando su correspondiente numero \n");
					break;
            }
        }while(opcion!=4);
    }
    return 0;
}
