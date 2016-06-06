#include "sqlite3.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include "plan.h"
#include "DBConnector.h"
#include <sstream>



	DBConnector::DBConnector(std::string dbFile)
	{
		//int result = sqlite3_open("test.sqlite", &db);
		int result = sqlite3_open(dbFile.c_str(), &db);
		if (result != SQLITE_OK) 
		{
		  std::cout << "Error opening database" << std::endl;

		}
	}

	DBConnector::~DBConnector() 
	{
		int result = sqlite3_close(db);
		if (result != SQLITE_OK) 
		{
		  std::cout << "Error closing database" << std::endl;
		  std::cout << sqlite3_errmsg(db) << std::endl;
		}
	}

	void DBConnector::showAllPlans()
	{
	    sqlite3_stmt *stmt;

	    char sql[] = "select cod_plan, lugar_plan, nom_plan, desc_plan, num_part from planes";
		
		sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

	    int cod_plan;
	    char lugar_plan[30];
	    char nom_plan[30];
	    char desc_plan[100];
	    int num_part;

	    int result;

	    do {
	      result = sqlite3_step(stmt);
	      if (result == SQLITE_ROW) 
	      {
	      	cod_plan = sqlite3_column_int(stmt, 0);
	        strcpy(lugar_plan, (char *) sqlite3_column_text(stmt, 1));
	      	strcpy(nom_plan, (char *) sqlite3_column_text(stmt, 2));
	        strcpy(desc_plan, (char *) sqlite3_column_text(stmt, 3));
	        num_part = sqlite3_column_int(stmt, 4);
	      	std::cout << "Cod_plan: " << cod_plan << "\tLugar_plan: " << lugar_plan << "\tNom_plan: " << nom_plan << "\tDesc_plan: " << desc_plan << "\tNum_part: " << num_part << std::endl;
	      }
	    } while (result == SQLITE_ROW);
		
		sqlite3_finalize(stmt);
  	}

  	void DBConnector::deletePlan(int cod_plan) 
	{
		sqlite3_stmt *stmt;

		char sql[] = "delete from planes where cod_plan = ?";
		sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
		sqlite3_bind_int(stmt, 1, cod_plan);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	

		char sql1[] = "delete from planesDet where cod_plan = ?";
		sqlite3_prepare_v2(db, sql1, strlen(sql1) + 1, &stmt, NULL) ;
		sqlite3_bind_int(stmt, 1, cod_plan);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);		
	}

	void DBConnector::createTablePlanAndPlanDet() 
	{
		sqlite3_stmt *stmt;

		char sql[] = "create table if not exists planes (cod_plan integer primary key autoincrement, lugar_plan text not null, nom_plan text not null, desc_plan text, num_part int)";
		sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
		
		char sql1[] = "create table if not exists planesDet (cod_plan integer primary key autoincrement, participantes text)";
		sqlite3_prepare_v2(db, sql1, -1, &stmt, NULL) ;
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}

	void DBConnector::updatePlan(int cod_plan)
	{
		sqlite3_stmt *stmt;

		char sql[] = "select num_part from planes where cod_plan = ?";
		sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
		sqlite3_bind_int(stmt, 1, cod_plan);
		sqlite3_step(stmt);
		int i = sqlite3_column_int(stmt, 0);
		sqlite3_finalize(stmt);

		char sql1[] = "update planes set num_part = ? where cod_plan = ?";
		sqlite3_prepare_v2(db, sql1, strlen(sql1) + 1, &stmt, NULL) ;
		sqlite3_bind_int(stmt, 1, ++i);
		sqlite3_bind_int(stmt, 2, cod_plan);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}

	std::vector<plan> DBConnector::recoveryPlan()
	{
		sqlite3_stmt *stmt;

		char sql[] = "select cod_plan, lugar_plan, nom_plan, desc_plan, num_part from planes";

		sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

		std::vector<plan> v;

		int cod_plan;
		char lugar_plan[30];
		char nom_plan[30];
		char desc_plan[100];
		int num_part;

		int result;

		do {
		  result = sqlite3_step(stmt);
		  if (result == SQLITE_ROW) 
		  {
		    cod_plan = sqlite3_column_int(stmt, 0);
		    strcpy(lugar_plan, (char *) sqlite3_column_text(stmt, 1));
		    strcpy(nom_plan, (char *) sqlite3_column_text(stmt, 2));
		    strcpy(desc_plan, (char *) sqlite3_column_text(stmt, 3));
		    num_part = sqlite3_column_int(stmt, 4);

		    plan p =  plan(std::string(lugar_plan), std::string(nom_plan), std::string(desc_plan), num_part);
		    p.setCod_plan(cod_plan);

		    v.push_back(p);
		    
		  }
		} while (result == SQLITE_ROW);

		sqlite3_finalize(stmt);

		return v;
	}

	std::vector<plan> DBConnector::recoverySpecific(int elec_cod_plan, int cod_plan, int elec_lugar_plan, std::string lugar_plan, int elec_nom_plan, std::string nom_plan)
	{
		sqlite3_stmt *stmt;

		char sql[] = "select cod_plan, lugar_plan, nom_plan, desc_plan, num_part from planes where";

		if(elec_cod_plan==1)
		{
			strncat(sql," cod_plan = ?", 13);
		}

		if(elec_lugar_plan==1)
		{
			if(elec_cod_plan==1)
			{
				strncat(sql," and",4);
			}
			strncat(sql," lugar_plan = ?",15 );
		}

		if(elec_nom_plan==1)
		{
			if((elec_cod_plan==1) || (elec_lugar_plan==1))
			{
				strncat(sql," and",4);
			}
			strncat(sql," nom_plan = ?",15);
		}

		sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

		int pos_lugar_plan=1;
		int pos_nom_plan=1;

		if(elec_cod_plan==1)
		{
			sqlite3_bind_int(stmt, 1, cod_plan);
			pos_lugar_plan=2;
			pos_nom_plan=2;
		}

		if(elec_lugar_plan==1)
		{
			
			if(elec_cod_plan==1)
			{
				pos_nom_plan=3;
			}
			else
			{
				pos_nom_plan=2;
			}
			sqlite3_bind_text(stmt, pos_lugar_plan, lugar_plan.c_str(), lugar_plan.length(), SQLITE_STATIC);
		}
		
		if(elec_nom_plan==1)
		{
			sqlite3_bind_text(stmt, pos_nom_plan, nom_plan.c_str(), nom_plan.length(), SQLITE_STATIC);
		}

		std::vector<plan> v;

		int cod_plan_c;
		char lugar_plan_c[30];
		char nom_plan_c[30];
		char desc_plan_c[100];
		int num_part_c;
		int result;

		do 
		{
		  result = sqlite3_step(stmt);
		  if (result == SQLITE_ROW) 
		  {
		    cod_plan_c = sqlite3_column_int(stmt, 0);
		    strcpy(lugar_plan_c, (char *) sqlite3_column_text(stmt, 1));
		    strcpy(nom_plan_c, (char *) sqlite3_column_text(stmt, 2));
		    strcpy(desc_plan_c, (char *) sqlite3_column_text(stmt, 3));
		    num_part_c = sqlite3_column_int(stmt, 4);

		    plan p =  plan(std::string(lugar_plan_c), std::string(nom_plan_c), std::string(desc_plan_c), num_part_c);
		    p.setCod_plan(cod_plan_c);

		    v.push_back(p);
		  }
		} while (result == SQLITE_ROW);

		result = sqlite3_finalize(stmt);

		return v;
	}

	void DBConnector::insertNewPlan(plan p) 
	{
		sqlite3_stmt *stmt;

		char sql[] = "insert into planes (lugar_plan, nom_plan, desc_plan, num_part) values (?, ?, ?, ?)";
		sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
		sqlite3_bind_text(stmt, 1, p.getLugar_plan().c_str(), p.getLugar_plan().length(), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, p.getNom_plan().c_str(), p.getNom_plan().length(), SQLITE_STATIC);	
		sqlite3_bind_text(stmt, 3, p.getDesc_plan().c_str(), p.getDesc_plan().length(), SQLITE_STATIC);
		sqlite3_bind_int(stmt, 4, p.getNum_part());
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
		

		char sql1[] = "insert into planesDet (participantes) values (NULL)";
		sqlite3_prepare_v2(db, sql1, strlen(sql1) + 1, &stmt, NULL) ;
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}




	/*void DBConnector::updatePlan(int cod_plan, std::string participante)
	{
		sqlite3_stmt *stmt;

		char sql2[] = "select participantes from planesDet where cod_plan = ?";
		int result=sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt, NULL);
		if (result != SQLITE_OK) 
	    {
	      std::cout << "Error preparing statement (SELECT)" << std::endl;      
	      std::cout << sqlite3_errmsg(db) << std::endl;
	    }

		result=sqlite3_bind_int(stmt, 1, cod_plan);
		if (result != SQLITE_OK) 
	    {
	      std::cout << "Error binding statement (SELECT)" << std::endl;      
	      std::cout << sqlite3_errmsg(db) << std::endl;
	    }	

		result=sqlite3_step(stmt);
		if (result != SQLITE_OK) 
	    {
	      std::cout << "Error steping statement (SELECT)"<< result << std::endl;      
	      std::cout << sqlite3_errmsg(db) << std::endl;
	    }
	    if (result == SQLITE_ROW) 
		{
      		strcpy(c, (char *) sqlite3_column_text(stmt, 0));		    
		}

    	result=sqlite3_finalize(stmt);
    	if (result != SQLITE_OK) 
	    {
	      std::cout << "Error steping statement (SELECT)" << std::endl;      
	      std::cout << sqlite3_errmsg(db) << std::endl;
	    }


    	std::string parti(c);
  		std::stringstream ss(parti);
	    std::string item;
	    std::vector<std::string>  elems;
	    char delim = ',';

	    while (std::getline(ss, item, delim)) 
	    {
	        elems.push_back(item);
	    }
	    
	    int repetido;

	    for(unsigned int i=0;i<elems.size();i++)
	  	{
	    	if(elems[i].compare(participante))
	    	{
	    		repetido=1;
	    	}
		}

		if(repetido!=1)
		{
			elems.push_back(participante);
			
			std::stringstream sss;
		    for(size_t i = 0; i < elems.size(); ++i)
		    {
		      if(i != 0)
		        sss << ",";
		      sss << elems[i];
		    }
		    std::string ssss = sss.str();
		    std::cout << ssss;

			char sql[] = "update planesDet set participantes = ? where cod_plan = ?";
			sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
			sqlite3_bind_text(stmt, 1, ssss.c_str(), ssss.length(), SQLITE_STATIC);
			sqlite3_bind_int(stmt, 2, cod_plan);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);


			char sql1[] = "update planes set num_part = ? where cod_plan = ?";
			sqlite3_prepare_v2(db, sql1, strlen(sql1) + 1, &stmt, NULL) ;
			sqlite3_bind_int(stmt, 1, elems.size());
			sqlite3_bind_int(stmt, 2, cod_plan);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		}
		else
		{
			std::cout << "Ya estabas apuntado a este plan" << std::endl;
		}
	}*/

