#include <iostream>
#include <stdio.h>
#include <string>
#include "plan.h"


	plan::plan(std::string lugar_plan, std::string nom_plan, std::string desc_plan, int num_part)
	{
		this->cod_plan = 0;
		this->nom_plan = nom_plan;
		this->lugar_plan = lugar_plan;
		this->desc_plan = desc_plan;
		this->num_part = num_part;
	}

	plan::plan(const plan &p)
	{
		this->cod_plan = p.cod_plan;
		this->nom_plan = p.nom_plan;
		this->lugar_plan = p.lugar_plan;
		this->desc_plan = p.desc_plan;
		this->num_part = p.num_part;
	}

	plan::~plan()
	{

	}

	int plan::getCod_plan() const
	{
		return this->cod_plan;
	}
	std::string plan::getLugar_plan() const 
	{
		return this->lugar_plan;
	}
	std::string plan::getNom_plan() const
	{
		return this->nom_plan;
	}
	std::string plan::getDesc_plan() const
	{
		return this->desc_plan;
	}
	int plan::getNum_part() const
	{
		return this->num_part;
	}

	void plan::setCod_plan(int cod_plan)
	{
		this->cod_plan = cod_plan;
	}
	void plan::setLugar_plan(std::string lugar_plan)
	{
		this->lugar_plan = lugar_plan;
	}
	void plan::setNom_plan(std::string nom_plan)
	{
		this->nom_plan = nom_plan;
	}
	void plan::setDesc_plan(std::string desc_plan)
	{
		this->desc_plan = desc_plan;
	}
	void plan::setNum_part(int num_part)
	{
		this->num_part = num_part;
	}

	void plan::printPlan()
	{
		std::cout << "Codigo:\t " << this->cod_plan << std::endl;
		std::cout << "Lugar:\t " << this->lugar_plan << std::endl;
		std::cout << "Nombre:\t " << this->nom_plan << std::endl;
		std::cout << "Descrip:\t " << this->desc_plan << std::endl;
		std::cout << "Partic:\t " << this->num_part << std::endl;
	}
