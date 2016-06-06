#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include "usuario.h"
#include <string.h>
#include <iostream>
#include <vector>
#include "plan.h"
#include "DBConnector.h"


#define MAX_LENGHT 20
#define MAX 3


void clear_if_needed(char *str)
{
    if (str[strlen(str) - 1] != '\n')
    {
        int c;
        while ( (c = getchar()) != EOF && c != '\n');
    }
}

void sacarListaEspecifica(int elec_cod_plan, int cod_plan, int elec_lugar_plan, std::string lugar_plan, int elec_nom_plan, std::string nom_plan, int elec_tipo_busc)
{
	DBConnector db("planes.sqlite");

	db.createTablePlanAndPlanDet();
	
	std::vector<plan> v;

	if (elec_tipo_busc==1)
	{
		v=db.recoverySpecific(elec_cod_plan, cod_plan, elec_lugar_plan, lugar_plan, elec_nom_plan, nom_plan);
	}

	else
	{
		std::vector<plan> aux;
		aux = db.recoveryPlan();
		if(elec_cod_plan==1)
		{
			
			for(unsigned int i=0;i<aux.size();i++)
			{
				
				plan p = v[i];
				if(p.getCod_plan()==cod_plan)
				{
					
					v.push_back(p);
				} 
			}
		}
		if(elec_lugar_plan==1)
		{
			for(unsigned int i=0;i<aux.size();i++)
			{
				std::string lugar = aux[i].getLugar_plan();
				std::size_t found = lugar.find(lugar_plan);
				if(found!=std::string::npos)
				{
					int key=1;

					for(unsigned int j=0;j<v.size();j++)
					{
						plan p1 = v[j];
						if(v[i].getCod_plan()==p1.getCod_plan())
						{
							key=0;
						} 
					}

					if(key==1)
					v.push_back(aux[i]);
				}
			}
		}




		if(elec_nom_plan==1)
		{
			for(unsigned int i=0;i<aux.size();i++)
			{
				plan p = aux[i];
				if(p.getNom_plan().find(nom_plan)!=std::string::npos)
				{
					int key=1;

					for(unsigned int j=0;j<v.size();j++)
					{
						plan p1 = v[j];
						if(p.getCod_plan()==p1.getCod_plan())
						{
							key=0;
						} 
					}

					if(key==1)
					v.push_back(p);
				} 
			}
		}
	}
	
	if(!v.empty())
	{
		
		for(unsigned int i=0;i<v.size();i++)
		{
			plan p = v[i];
			std::cout << "\t" << p.getCod_plan() << " | " << p.getNom_plan() << " | " << p.getLugar_plan() << " | " << p.getDesc_plan() << " | " << p.getNum_part() << std::endl;
		}

		int eleccion;
		do
		{
			std::cout << "Quieres apuntarte a un plan? (1=Si 0=No)" << std::endl;
			std::cout << "Eleccion: ";
			std::cin >> eleccion;                                    


			system("cls");
	    	if(!std::cin) // or if(cin.fail())
			{
			    std::cout << "User didn't input a number" << std::endl; 
			    std::cin.clear(); // reset failbit
			    std::cin.ignore();
			    eleccion=3;
			    // next, request user reinput
			}
			else
			{
				int door=0;
				int cod_apunt;

				switch(eleccion)
				{
					case 0:
						break;
					case 1:
						do
						{
							std::cout << "Inserte el codigo del plan al que quieres apuntarte: ";
							std::cin >> cod_apunt;

							system("cls");
					    	if(!std::cin) // or if(cin.fail())
							{
							    std::cout << "User didn't input a number" << std::endl; 
							    std::cin.clear(); // reset failbit
							    std::cin.ignore();
							    cod_apunt=0;
							    // next, request user reinput
							}
							else
							{

								for(unsigned i=0;i<v.size();i++)
								{
									plan p = v[i];
									if(p.getCod_plan()==cod_apunt)
									{
										db.updatePlan(cod_apunt);
										door=1;
										eleccion=0;
									} 
									else
									{
										std::cout << "Inserte un codigo correcto";
									}
								}
							}
						}while(door==0);
						break;
					default:
						std::cout << "Elija una de las opciones tecleando su correspondiente numero" << std::endl;
						break;
				}
			}
		}while(eleccion!=0);


	}
	else
	{
		std::cout << "No hay ningun plan que cumpla todos los parametros insertados" << std::endl;
	}
}

void CrearPlan(std::string nomUsu)
{
	std::cout << nomUsu << ", necesitamos que rellenes unos campos para crear el plan." << std::endl;


	std::string lugar_plan;
	std::string nom_plan;
	std::string desc_plan;

	std::cin.ignore();
	std::cout <<"Nombre del plan: ";
	std::getline(std::cin,nom_plan);
	std::cout << std::endl;

	std::cin.ignore();
	std::cout <<"Lugar del plan: ";
	std::getline(std::cin,lugar_plan);
	std::cout << std::endl;

	std::cin.ignore();
	std::cout <<"Descripcion del plan: ";
	std::getline(std::cin,desc_plan);
	std::cout << std::endl;

	plan p(lugar_plan, nom_plan, desc_plan,0);
	DBConnector db("planes.sqlite");
	db.createTablePlanAndPlanDet();
	db.insertNewPlan(p);
}

void BorrarPlan(std::string nomUsu)
{
	std::cout << nomUsu << ", necesitamos que rellenes el codigo del plan a borrar." << std::endl;


	int eleccion;

	int key;
	
	do
	{
		std::cout << "Apunta el codigo del plan a borrar" << std::endl;
		std::cout << "Eleccion: ";
		std::cin >> eleccion;                                    


		system("cls");
    	if(!std::cin) // or if(cin.fail())
		{
		    std::cout << "User didn't input a number" << std::endl; 
		    std::cin.clear(); // reset failbit
		    std::cin.ignore();
		    eleccion=3;
		    // next, request user reinput
		}
		else
		{
			key =1;
		}
	}while(key!=1);


	DBConnector db("planes.sqlite");
	db.createTablePlanAndPlanDet();
	
	std::vector<plan> v;
	v=db.recoveryPlan();

	int door;

	for(unsigned int i = 0; i<v.size();i++)
	{
		if(v[i].getCod_plan()==eleccion)
			door=1;
	}

	if(door==1)
	{
		int elec;
	
		do
		{
			std::cout << "Quieres borrar el plan con codigo" << eleccion << " (1=Si 0=No)" << std::endl;
			std::cout << "Eleccion: ";
			std::cin >> elec;                                    


			system("cls");
	    	if(!std::cin) // or if(cin.fail())
			{
			    std::cout << "User didn't input a number" << std::endl; 
			    std::cin.clear(); // reset failbit
			    std::cin.ignore();
			    elec=3;
			    // next, request user reinput
			}
		}while((elec!=1) && (elec!=0));

		if(elec==1)
		db.deletePlan(eleccion);
	}
	else
	{
		std::cout << "No existe ningun plan con ese codigo" << std::endl; 
	}

}

void MenuPlanes(std::string nomUsu)
{
	int elec_busc;
	do
	{
		std::cout << nomUsu << ", deseas ver todos los planes o una busqueda especifica?." << std::endl;   
		std::cout << "(1=Todos 0=Especifica): ";
		std::cin >> elec_busc;

		system("cls");
		if(!std::cin) // or if(cin.fail())
		{
		    std::cout << "User didn't input a number" << std::endl; 
		    std::cin.clear(); // reset failbit
		    std::cin.ignore();
		    elec_busc=2;
		    // next, request user reinput
		}
		else
		{
			if(elec_busc==0)
			{
				int elec_cod_plan;
				int cod_plan;
				int elec_lugar_plan;
				std::string lugar_plan;
				int elec_nom_plan;
				std::string nom_plan;
				do
				{	
					std::cout << nomUsu << ", necesitamos unos parametros de busqueda." << std::endl << "Pulsa 1 en aquellos parametros que quieras rellenar" << std::endl;   
					std::cout << "Codigo del plan (1=Si 0=No): ";
					std::cin >> elec_cod_plan;

			    	system("cls");
			    	if(!std::cin) // or if(cin.fail())
					{
					    std::cout << "User didn't input a number" << std::endl; 
					    std::cin.clear(); // reset failbit
					    std::cin.ignore();
					    elec_cod_plan=3;
					    // next, request user reinput
					}
					else
					{
						if(elec_cod_plan==1)
						{	
							int door1=0;
							do
							{
								std::cout << "Inserte el codigo del plan: ";
								std::cin >> cod_plan;

								if(!std::cin) // or if(cin.fail())
								{
								    std::cout << "User didn't input a number" << std::endl; 
								    std::cin.clear(); // reset failbit
								    std::cin.ignore();
								    cod_plan=0;
								    // next, request user reinput
								}
								else
								{
									door1=1;
								}
							}while(door1!=1);

						}


						if((elec_cod_plan==0) || (elec_cod_plan==1))
					    {
					    	do
							{	
								std::cout << "Lugar del plan (1=Si 0=No): ";
								std::cin >> elec_lugar_plan;

								system("cls");
						    	if(!std::cin) // or if(cin.fail())
								{
								    std::cout << "User didn't input a number" << std::endl; 
								    std::cin.clear(); // reset failbit
								    std::cin.ignore();
								    elec_lugar_plan=3;
								    // next, request user reinput
								}
								else
								{
									if(elec_lugar_plan==1)
									{
										int door2=0;
										do
										{
											std::cin.ignore();
											std::cout <<"Lugar del plan: ";
											std::getline(std::cin,lugar_plan);

											if(!std::cin) // or if(cin.fail())
											{
											    std::cout << "User didn't input a number" << std::endl; 
											    std::cin.clear(); // reset failbit
											    std::cin.ignore();
											    lugar_plan="";
											    // next, request user reinput
											}
											else
											{
												door2=1;
											}
										}while(door2!=1);
									}

									if((elec_lugar_plan==0) || (elec_lugar_plan==1))
								    {
								    	do
										{	
											std::cout << "Nombre del plan (1=Si 0=No): ";
											std::cin >> elec_nom_plan;

									    	if(!std::cin) // or if(cin.fail())
											{
											    std::cout << "User didn't input a number" << std::endl; 
											    std::cin.clear(); // reset failbit
											    std::cin.ignore();
											    elec_nom_plan=3;
											    // next, request user reinput
											}
											else
											{

												if(elec_nom_plan==1)
												{
													int door3=0;
													do
													{
														std::cin.ignore();
														std::cout <<"Inserte el nombre del plan: ";
														std::getline(std::cin,nom_plan);

														if(!std::cin) // or if(cin.fail())
														{
														    std::cout << "User didn't input a number" << std::endl; 
														    std::cin.clear(); // reset failbit
														    std::cin.ignore();
														    nom_plan="";
														    // next, request user reinput
														}
														else
														{
															door3=1;
														}
													}while(door3!=1);
												}

												if((elec_nom_plan!=0) && (elec_nom_plan!=1))
											    {
											    	std::cout << "Elija una de las opciones tecleando su correspondiente numero" << std::endl;
											    }
											}
										}while((elec_nom_plan!=0) && (elec_nom_plan!=1) );
								    }
								    else
								    {
								    	std::cout << "Elija una de las opciones tecleando su correspondiente numero" << std::endl;
								    }
								}

							}while((elec_lugar_plan!=0) && (elec_lugar_plan!=1) );
					    }
					    else
					    {
					    	std::cout << "Elija una de las opciones tecleando su correspondiente numero" << std::endl;
					    }
					}
				}while((elec_cod_plan!=0) && (elec_cod_plan!=1));

				std::cout << "Parametros de busqueda:" << std::endl << std::endl;

				if(elec_cod_plan==1)
				{
					std::cout << "Codigo del plan: " << cod_plan << std::endl;  
				}

				if(elec_lugar_plan==1)
				{
					std::cout << "Lugar del plan: " << lugar_plan << std::endl;  
				}

				if(elec_nom_plan==1)
				{
					std::cout << "Nombre del plan: " << nom_plan << std::endl;  
				}

				if((elec_cod_plan==0) && (elec_lugar_plan==0) && (elec_nom_plan==0))
				{
					std::cout << "No ha seleccionado ningun parametro" << std::endl; 
				}
				else
				{	
					int elec_tipo_busc;
					do
					{	
						std::cout << "Tipo de busqueda (1=Extricta 0=Permisiva): ";
						std::cin >> elec_tipo_busc;

				    	if(!std::cin) // or if(cin.fail())
						{
						    std::cout << "User didn't input a number" << std::endl; 
						    std::cin.clear(); // reset failbit
						    std::cin.ignore();
						    elec_tipo_busc=2;
						    // next, request user reinput
						}
						else
						{

						}
					}while((elec_tipo_busc!=0) && (elec_tipo_busc!=1));

					
					sacarListaEspecifica(elec_cod_plan, cod_plan, elec_lugar_plan, lugar_plan, elec_nom_plan, nom_plan, elec_tipo_busc);
				}
			}
			else
			{
				DBConnector db("planes.sqlite");
				db.createTablePlanAndPlanDet();
				db.showAllPlans();
			}
		}
	}while((elec_busc!=0) && (elec_busc!=1));

}

void menuUsuario(std::string nomUsu)
{
	int eleccion;

	do
	{	
		std::cout << "Bienvenido " << nomUsu << ", Que deseas realizar?:" << std::endl << std::endl;   
		
		std::cout << "1.Ver Planes" << std::endl;
		std::cout << "2.Crear Plan" << std::endl;
		std::cout << "3.Cerrar Sesion." << std::endl;
		std::cout << "Eleccion: ";
		
		std::cin >> eleccion;
		system("cls");
		if(!std::cin) // or if(cin.fail())
		{
		    std::cout << "User didn't input a number" << std::endl; 
		    std::cin.clear(); // reset failbit
		    std::cin.ignore();
		    eleccion=0;
		    // next, request user reinput
		}
		else
		{
			switch(eleccion)
			{
				case 1:
					MenuPlanes(nomUsu);
					break;
				case 2:
					CrearPlan(nomUsu);
					break;
				case 3:
					break;
				default:
					std::cout << "Elija una de las opciones tecleando su correspondiente numero" << std::endl;
					break;
			}
		}	
	}while(eleccion!=3);
}

void menuAdmin()
{
	int eleccion;

	do
	{	
		std::cout << "Bienvenido " << "admin" << ", Que deseas realizar?:" << std::endl << std::endl;   
		
		std::cout << "1.Ver Planes" << std::endl;
		std::cout << "2.Crear Plan" << std::endl;
		std::cout << "3.Borrar Plan" << std::endl;
		std::cout << "4.Cerrar Sesion." << std::endl;
		std::cout << "Eleccion: ";
		
		std::cin >> eleccion;
		system("cls");
		if(!std::cin) // or if(cin.fail())
		{
		    std::cout << "User didn't input a number" << std::endl; 
		    std::cin.clear(); // reset failbit
		    std::cin.ignore();
		    eleccion=0;
		    // next, request user reinput
		}
		else
		{
			switch(eleccion)
			{
				case 1:
					MenuPlanes("admin");
					break;
				case 2:
					CrearPlan("admin");
				case 3:
					BorrarPlan("admin");
					break;
				case 4:
					break;
				default:
					std::cout << "Elija una de las opciones tecleando su correspondiente numero" << std::endl;
					break;
			}
		}	
	}while(eleccion!=4);
}

void registro()
{
	char * username;
	char * password;
	char str[MAX_LENGHT];
	char savename[MAX_LENGHT];
	char savepass[MAX_LENGHT];

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

	printf("\n1");

	if(checkFileExistance()==0)
	{
		int cmp = comprobarUsername(u);
		printf("\n2");

		if(cmp==1)
		{
			guardarUsuario(u);
			system("cls");
			printf("\nSe ha creado el usuario");

		}
		else
		{
			system("cls");
			printf("\nEl usuario ya existe");
			printf("Pulse una tecla para continuar: ");
		}
	}
	else
	{
		guardarUsuario(u);
	}

	free(password);
	free(username);
}

void iniciarSesion()
{
	char str[MAX_LENGHT];
	char savename[MAX_LENGHT];
	char savepass[MAX_LENGHT];
	char * username;
	char * password;

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

	system("cls");

	if(checkFileExistance()==0)
	{
		int check = comprobarUserPass(u);

		if(check==0)
		{
			std::string str(username);
			menuUsuario(str);
		}
		else
		{
			if(strcmp(u.username, "admin")==0)
				if(strcmp(u.password, "admin")==0)
					menuAdmin();
			printf("\nUsuario o contrasena erroneos");
		 
		}
	}
	else
	{
		printf("\nNo existen usuarios");
		
	}

	free(password);
	free(username);
}

void menuAcceso()
{
	int eleccion;
    char str[MAX];

	do
	{
		printf("\n1.Iniciar sesion\n");
		printf("2.Registrarse\n");
		printf("3.Volver.\n");
		printf("\nEleccion: ");

		fgets(str,MAX,stdin);
    	clear_if_needed(str);
    	sscanf(str,"%d",&eleccion);

    	system("cls");

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

void sobreNosotros()
{
	int salir;
	char str[MAX];
	do
	{
		printf("\nEn EPA developers llevamos trabajando en aplicaciones para dispositivos moviles con intencion de mejorar y hacer mas facil las vidas de nuestros usuarios. Nuestros fundadores son Elena Perez de Iriarte, Paula Urteaga y Adrian Michelena. Nuestra andadura como grupo de desarrolladores comenzo con esta aplicacion de la cual estamos muy orgullosos.\n");
		printf("\nSalir (1=Si/0=No): ");
		fgets(str,MAX,stdin);
	    clear_if_needed(str);
	    sscanf(str,"%d",&salir);
	    system("cls");
		if((salir!=0) & (salir!=1))
	    {
	    	printf("\nElija una de las opciones tecleando su correspondiente numero \n");
	    }
	}while(salir!=1);
}

void infoApp()
{
	int salir;
	char str[MAX];
	do
	{
		printf("\nQtedex (Version 2.3.2) \n");
		printf("\nDesarrollado por EPA developers");
		printf("\n\nRequisitos recomendados:");
		printf("\n\tMemoria Ram:\t\t500 Mbytes");
		printf("\n\tEspacio en disco:\t25 Mbytes");
		printf("\n\tCalidad minima:\t\t1080px720p");
		printf("\n\nSalir (1=Si/0=No): ");
		fgets(str,MAX,stdin);
	    clear_if_needed(str);
	    sscanf(str,"%d",&salir);
	    system("cls");
	    if((salir!=0) & (salir!=1))
	    {
	    	printf("\nElija una de las opciones tecleando su correspondiente numero \n");
	    }
	    
	}while(salir!=1);
}

int main()
{
	system("cls");
	int opcion;
	char str[MAX];

    do
    {
        printf("\n1.Acceder\n");
        printf("2.Sobre Nosotros\n");
        printf("3.Informacion de la aplicacion\n");
        printf("4.Cerrar\n");
        printf("\nEleccion: ");

        fgets(str,MAX,stdin);
		clear_if_needed(str);
		sscanf(str,"%d",&opcion);

		system("cls");

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

    return 0;
}
