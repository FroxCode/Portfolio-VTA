#include "Subject.h"


void Subject::Attach(Achievement* achieve)
{
	achievements.push_back(achieve);
}



void Subject::Detach(Achievement* achieve)
{
	//achievements.erase(std::remove(achievements.begin(), achievements.end(), achieve), achievements.end());
}
void Subject::Notify(std::shared_ptr<std::vector<bool>> ac, SDL_Renderer* renderer)
{
	for (int i = 0; i < ac->size(); i++)
	{
		if (ac->at(i))
		{
			achievements[i]->Update(true,renderer);
		}
	}
}