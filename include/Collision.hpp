/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** COLLISION_HPP_
*/

#ifndef COLLISION_HPP_
	#define COLLISION_HPP_

#include <map>
#include <memory>

#include "Map.hpp"

class Collision
{
public:
	Collision(int mapWidth, int mapHeight);
	~Collision();
	bool checkCollision(
		int x, int y,
		std::shared_ptr<Map> Map);
	int getFarTen(int toFind);
private:
	int _mapWidth;
	int _mapHeight;
};

#endif /* !COLLISION_HPP_ */
