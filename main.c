#include <stdio.h>
#include "save.h"
#include <stdlib.h>
#include <string.h>
typedef int bool;
#define true 1
#define false 0





int main()
{
	int entrar;
	int opcion;

	setvbuf(stdout, 0, _IONBF, 0);

	printf("Bienvenido a la aplicacion QTedex realizada por EPA Developers.\n");
	printf("Una vez que la pruebes tu mundo no sera igual.\n");

    printf("\nEntrar (1=Si/0=No): ");

    scanf( "%d", &entrar);

    if(entrar==1)
    {
        do
        {
            system("cls");
            printf("1.Acceder\n");
            printf("2.Sobre Nosotros\n");
            printf("3.Informacion de la aplicacion\n");
            printf("4.Cerrar\n");
            printf("\n   Eleccion: ");

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
					printf("\n Elija una de las opciones tecleando su correspondiente numero \n");
					break;
            }
        }while(opcion!=4);
    }
    return 0;
}

void menuAcceso()
{
	int eleccion;

	do
	{
		system("cls");
		printf("1.Iniciar sesion\n");
		printf("2.Registrarse\n");
		printf("3.Volver.\n");
		printf("\n   Eleccion: ");

		scanf( "%d", &eleccion );

		switch(eleccion)
		{
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				printf("\n Elija una de las opciones tecleando su correspondiente numero \n");
				break;
		}
	}while(eleccion!=3);
}

void sobreNosotros()
{
	int key;
	do
	{
		system("cls");
		printf("En EPA developers llevamos trabajando en aplicaciones para dispositivos moviles con intencion de mejorar y hacer mas facil las vidas de nuestros usuarios. Nuestros fundadores son Elena Perez de Iriarte, Paula Urteaga y Adrian Michelena. Nuestra andadura como grupo de desarrolladores comenzo con esta aplicacion de la cual estamos muy orgullosos.\n");
		printf("\nSalir (1=Si/0=No): ");
		scanf( "%d", &key);
	}while(key!=1);
}

void infoApp()
{
	int key;
		do
		{
			system("cls");
			printf("En EPA developers llevamos trabajando en aplicaciones para dispositivos moviles con intencion de mejorar y hacer mas facil las vidas de nuestros usuarios. Nuestros fundadores son Elena Perez de Iriarte, Paula Urteaga y Adrian Michelena. Nuestra andadura como grupo de desarrolladores comenzo con esta aplicacion de la cual estamos muy orgullosos.\n");
			printf("\nSalir (1=Si/0=No): ");
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
