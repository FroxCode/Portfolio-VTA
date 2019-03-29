#pragma once

#include "Subject.h"


class AchievementList : public Subject
{
public:
	void setAchievement(std::shared_ptr<std::vector<bool>> ac, SDL_Renderer* renderer);


};

