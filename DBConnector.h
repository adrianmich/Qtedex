#include <string>
#include "plan.h"
#include <vector>
#include "sqlite3.h"

class DBConnector
{

private:
  sqlite3 *db = NULL;

public:
	DBConnector(std::string dbFile); 

	~DBConnector();

	void showAllPlans() ;

	void deletePlan(int cod_plan);

	void updatePlan(int cod_plan);

	void createTablePlanAndPlanDet() ;

	std::vector<plan> recoveryPlan();

	std::vector<plan> recoverySpecific(int elec_cod_plan, int cod_plan, int elec_lugar_plan, std::string lugar_plan, int elec_nom_plan, std::string nom_plan);

	
	
	void insertNewPlan(plan p);
};