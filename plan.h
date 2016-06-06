#ifndef PLAN_H_
#define PLAN_H_

#include <string>

class plan
{
	int cod_plan;
	std::string lugar_plan;
	std::string nom_plan;
	std::string desc_plan;
	int num_part;

	public:

	plan( std::string lugar_plan, std::string nom_plan, std::string desc_plan, int num_part);

	~plan();
	plan(const plan &p);

	int getCod_plan() const ;
	std::string getLugar_plan() const ;
	std::string getNom_plan() const;
	std::string getDesc_plan() const;
	int getNum_part() const ;

	void setCod_plan(int cod_plan) ;
	void setLugar_plan(std::string lugar_plan) ;
	void setNom_plan(std::string nom_plan);
	void setDesc_plan(std::string desc_plan);
	void setNum_part(int num_part);

	virtual void printPlan();
};

#endif