/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** COLLISION_CPP_
*/

#include "Collision.hpp"

/**
* \fn Collision::Collision(int mapWidth, int mapHeight)
* \param mapWidth: width of the map
* \param mapHeight: height of the map
* \brief constructor (set the map size)
* \return nothing
**/

Collision::Collision(int mapWidth, int mapHeight)
{
	_mapWidth = mapWidth;
	_mapHeight = mapHeight;
}

/**
* \fn Collision::~Collision()
* \brief destructor
* \return nothing
**/

Collision::~Collision() {}

/**
* \fn Collision::getFarTen(int toFind)
* \param int toFind: number to round
* \brief round to ten
* \return i or 0
**/

int Collision::getFarTen(int toFind)
{
	int i = 0;

	while (i < toFind) {
		i += 10;
	}
	return ((i) > 0) ? (i) : 0;
}

/**
* \fn bool Collision::checkCollision(int x, int y, std::shared_ptr<Map> Map)
* \param x: position on x
* \param y: position on y
* \param std::shared_ptr<Map> Map: Map
* \brief search for an empty cube or not
* \return true or false
**/

bool Collision::checkCollision(int x, int y, std::shared_ptr<Map> Map)
{
	bool left = Map->isCubeNotEmpty(x, y, false);
	bool right = Map->isCubeNotEmpty(x + 7, y, false);
	bool top = Map->isCubeNotEmpty(x, y + 7, false);
	bool bottom = Map->isCubeNotEmpty(x + 7, y + 7, false);

	if (left || right || top || bottom)
		return true;
	return false;
}