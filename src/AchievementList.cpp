#include "AchievementList.h"

void AchievementList::setAchievement(std::shared_ptr<std::vector<bool>> ac, SDL_Renderer* renderer)
{
	Notify(ac,renderer);
}