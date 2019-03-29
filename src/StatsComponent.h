#pragma once
#include "Component.h"

class StatsComponent : public Component
{
private:
	int const STAT_CAP = 20;
	int const HP_POINT_INCREASE = 10;

	int const HP_BOOST_BONUS = 50;
	float const ATT_BOOST_BONUS = 0.5f;
	float const DEF_BOOST_BONUS = 0.5f;
	float const AGI_BOOST_BONUS = 0.5f;

	
	int const BASE_HP = 100;
	float const BASE_ATT = 1.f;
	float const BASE_DEF = 0.f;
	float const BASE_AGI = 1.f;

	int maxHP = BASE_HP;
	float attack = BASE_ATT;
	float defense = BASE_DEF;
	float agility = BASE_AGI;

	int points_HP = 0;
	int points_ATT = 0;
	int points_AGI = 0;


	bool boosted = false;
	enum Boosts {None, Green, YellowSunshine, GymCandy, ElectricIce, VelvetThunder};
	Boosts activeBoost = Boosts::None;
	Boosts currentBoost = Boosts::None;
public:
	StatsComponent() : Component("Stats") {};
	StatsComponent(int hp, float att, float def, float agi) : Component("Stats") {
		maxHP = hp; attack = att; defense = def; agility = agi; 
	}
	~StatsComponent() {};

	int getHealth() {
		if (boosted && (activeBoost == Boosts::Green || activeBoost == Boosts::VelvetThunder)) { return maxHP + HP_BOOST_BONUS; }
		else { return maxHP; }
	}
	void setHealth(int newMaxHealth) { maxHP = newMaxHealth; }

	float getAttack() {
		if (boosted && (activeBoost == Boosts::YellowSunshine || activeBoost == Boosts::VelvetThunder)) { return attack + ATT_BOOST_BONUS; }
		else { return attack; }
	}
	void setAttack(float newAttack) { attack = newAttack; }

	float getDefense() {
		if (boosted && (activeBoost == Boosts::GymCandy || activeBoost == Boosts::VelvetThunder)) { return defense + DEF_BOOST_BONUS; }
		else { return defense; }
	}
	void setDefense(float newDefense) { defense = newDefense; }

	float getAgility() {
		if (boosted && (activeBoost == Boosts::ElectricIce || activeBoost == Boosts::VelvetThunder)) { return agility + AGI_BOOST_BONUS; }
		else { return agility; }
	}
	void setAgility(float newAgility) { agility = newAgility; }





	/// <summary>

	/// </summary>
	/// <param name="time"></param>
	void resetActiveBoost() {
		boosted = false;
		activeBoost = Boosts::None;
	}
	/// <summary>

	/// </summary>
	/// <param name="time"></param>
	void setBoostActive() {
		boosted = true;
		activeBoost = currentBoost;
		if (activeBoost == Boosts::None)
		{
			boosted = false; //turn off boost, regardless of input
		}
	}
	/// <summary>
	/// Boosts
	/// 0 = turn off boost
	/// 1 = Green
	/// 2 = Yellow Sunshine
	/// 3 = Gym Candy
	/// 4 = Electric Ice
	/// 5 = Velvet Thunder
	/// </summary>
	/// <param name="boostType"></param>
	/// <param name="time"></param>
	void setBoost(int boostType) {
		switch (boostType)
		{
			boosted = false; //turn off boost, regardless of input
		case 0:
			currentBoost = Boosts::None;
			break;
		case 1:
			currentBoost = Boosts::Green;
			break;
		case 2:
			currentBoost = Boosts::YellowSunshine;
			break;
		case 3:
			currentBoost = Boosts::GymCandy;
			break;
		case 4:
			currentBoost = Boosts::ElectricIce;
			break;
		case 5:
			currentBoost = Boosts::VelvetThunder;
			break;
		default:
			break;
		}
	}
	/// <summary>
	/// Boosts
	/// 0 = turn off boost
	/// 1 = Green
	/// 2 = Yellow Sunshine
	/// 3 = Gym Candy
	/// 4 = Electric Ice
	/// 5 = Velvet Thunder
	/// </summary>
	/// <param name="time"></param>
	int getCurrentBoost() {
		if (currentBoost == Boosts::None)
		{
			return 0;
		}
		else if (currentBoost == Boosts::Green)
		{
			return 1;
		}
		else if (currentBoost == Boosts::YellowSunshine)
		{
			return 2;
		}
		else if (currentBoost == Boosts::GymCandy)
		{
			return 3;
		}
		else if (currentBoost == Boosts::ElectricIce)
		{
			return 4;
		}
		else if (currentBoost == Boosts::VelvetThunder)
		{
			return 5;
		}
	}
	/// <summary>
	/// Boosts
	/// 0 = turn off boost
	/// 1 = Green
	/// 2 = Yellow Sunshine
	/// 3 = Gym Candy
	/// 4 = Electric Ice
	/// 5 = Velvet Thunder
	/// </summary>
	/// <param name="time"></param>
	int getActiveBoost() {
		if (activeBoost == Boosts::None)
		{
			return 0;
		}
		else if (activeBoost == Boosts::Green)
		{
			return 1;
		}
		else if (activeBoost == Boosts::YellowSunshine)
		{
			return 2;
		}
		else if (activeBoost == Boosts::GymCandy)
		{
			return 3;
		}
		else if (activeBoost == Boosts::ElectricIce)
		{
			return 4;
		}
		else if (activeBoost == Boosts::VelvetThunder)
		{
			return 5;
		}
	}
	/// <summary>
	/// Call this when you want one of the 3 applicable stats to increase by 1 at random (up to a max of 20 each)
	/// </summary>
	void levelUp() {
		if (points_AGI == STAT_CAP && 
			points_ATT == STAT_CAP && 
			points_HP == STAT_CAP)
		{
			std::cout << "Max Level! No stat increases" << std::endl;
		}
		else
		{
			int r = rand() % 3;
			switch (r){
			case 0:
				if (points_HP != STAT_CAP) {
					points_HP++;
					setHealth(BASE_HP + (points_HP * HP_POINT_INCREASE));
				}
				else {
					levelUp();
				}
				break;
			case 1:
				if (points_ATT != STAT_CAP) {
					points_ATT++;
					setAttack(BASE_ATT + points_HP);
				}
				else {
					levelUp();
				}
				break;
			case 2:
				if (points_AGI != STAT_CAP) {
					points_AGI++;
					setAgility(BASE_AGI + points_AGI);
				}
				else {
					levelUp();
				}
				break;
			default:
				std::cout << "Error in Stats" << std::endl;
				break;
			}
		}
	}
	
};