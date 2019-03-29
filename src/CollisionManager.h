////////////////////////////////////////////////////////////
//
// Created by Dale Sinnott
//
////////////////////////////////////////////////////////////
#ifndef _CollisionManager_H_
#define _CollisionManager_H_
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>
#include "SDL.h"
class CollisionManager
{
public:
	CollisionManager() {};
	/*bool checkCollision(sf::Vector2f &point, sf::FloatRect &box);
	bool checkCollision(sf::Vector2f &point, sf::IntRect &box);
	bool checkCollision(sf::RectangleShape &point, sf::IntRect &box);
	bool checkCollision(sf::IntRect &a, sf::IntRect &b);
	bool checkCollision(sf::RectangleShape &a, sf::RectangleShape &b);
	bool checkCollision(sf::RectangleShape &a, sf::FloatRect &b);*/

	bool checkCollision(SDL_Rect &a, SDL_Rect &b);
	bool checkCollision(SDL_Point &a, SDL_Rect &b);

	float getHorizontalIntersectionDepth(SDL_Rect &a, SDL_Rect &b);
	float getVerticalIntersectionDepth(SDL_Rect &a, SDL_Rect &b);
private:

	bool checkIntersection(SDL_Rect &A, SDL_Rect &B);
	bool checkIntersection(SDL_Point &A, SDL_Rect &B);
	//float getHorizontalIntersectionDepth(sf::FloatRect &a, sf::FloatRect &b);
	//float getVerticalIntersectionDepth(sf::FloatRect &a, sf::FloatRect &b);
	//sf::FloatRect asFloatRect(sf::IntRect& rect);
	//sf::IntRect asIntRect(sf::FloatRect &rect);
	//sf::FloatRect asFloatRect(sf::RectangleShape &rect);

};
#endif;