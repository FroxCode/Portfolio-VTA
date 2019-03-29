#pragma once
#include "Component.h"
#include<iostream>
#include<fstream>
#include<string>
#include<limits>
#include "StatsComponent.h"

class ExperienceComponent : public Component
{
private:
	unsigned int maxExp = 0;
	unsigned int currentExp = 0;
	unsigned int level = 0;
	unsigned int totalExp = 0;

	std::vector<unsigned int> expTable;

public:
	ExperienceComponent() : currentExp(0), Component("Experience") {}
	~ExperienceComponent() {};

	//int getExp() { return currentExp; }
	//int getMaxExp() { return maxExp; }
	int getLevel() { return level; }

	unsigned int getExp() { return currentExp; }
	unsigned int getMaxExp() { return maxExp; }
	void setExp(unsigned int exp) { currentExp = exp; }
	
	void incExperience(unsigned int experience) {this->currentExp += experience;}
	void setNextLevelCap() { this->maxExp = expTable.at(level); }
	void incLevel() { this->level++;}
	void setLevel(int starLevel) { this->level = starLevel; }
	void loadExpTable() {
		//Open file and input into the array 
		std::ifstream file;
		file.open("data/expTable.txt");
		if (file.is_open())
		{
			std::cout << "File Opened" << std::endl;
			unsigned int temp = 0;
			while (!file.eof())
			{
				file >> temp;
				expTable.push_back(temp);
			}
		}

	}
};