//Created by Dale Sinnott, Connor Maguire
#include "CollisionManager.h"

bool CollisionManager::checkCollision(SDL_Rect &a, SDL_Rect &b)
{
	return checkIntersection(a, b);
}
bool CollisionManager::checkCollision(SDL_Point &a, SDL_Rect &b)
{
	return checkIntersection(a, b);
}
float CollisionManager::getHorizontalIntersectionDepth(SDL_Rect &a, SDL_Rect &b)
{
	float halfWidthA = a.w / 2;
	float halfWidthB = b.w / 2;

	float centerA = a.x + halfWidthA;
	float centerB = b.x + halfWidthB;

	float distanceX = centerA - centerB;
	float minDistanceX = halfWidthA + halfWidthB;

	if (std::abs(distanceX) >= minDistanceX)
	{
		return 0;
	}

	if (distanceX > 0) {
		return minDistanceX - distanceX;
	}
	else
	{
		return -minDistanceX - distanceX;
	}
}
float CollisionManager::getVerticalIntersectionDepth(SDL_Rect &a, SDL_Rect &b)
{
	float halfHeightA = a.h / 2;
	float HalfHeightB = b.h / 2;

	float centerA = a.y + halfHeightA;
	float centerB = b.y + HalfHeightB;

	float distanceY = centerA - centerB;
	float minDistanceY = halfHeightA + HalfHeightB;

	if (std::abs(distanceY) >= minDistanceY)
	{
		return 0;
	}

	if (distanceY > 0) {
		return minDistanceY - distanceY;
	}
	else
	{
		return -minDistanceY - distanceY;
	}
}

bool CollisionManager::checkIntersection(SDL_Rect &A, SDL_Rect &B)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	//Calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;
	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

bool CollisionManager::checkIntersection(SDL_Point &A, SDL_Rect &B)
{
	if (A.x >= B.x && A.x <= B.x + B.w && A.y >= B.y && A.y <= B.y + B.h)
		return true;
	return false;
}