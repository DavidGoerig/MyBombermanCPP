/*
** EPITECH PROJECT, 2018
** Object.hpp
** File description:
** Interface Object
*/

#ifndef OBJECT_HPP_
	#define OBJECT_HPP_

#include <cstdio>
#include <iostream>
#include <memory>

#include "indieStudio.hpp"
#include "Map.hpp"

enum Item {
	BOMBS,
	BOMBM
};

class IItem
{
public:
	virtual ~IItem() = default;
	virtual irr::scene::IAnimatedMeshSceneNode* isUsed(float x, float z) = 0;
	virtual std::string getItemName() = 0;
	virtual int getId() = 0;
	virtual bool explodeBomb(
		int x, int y,
		std::shared_ptr<Map> Map,
		std::vector<std::pair<int, int>> playerPos) = 0;
	virtual std::pair<int, int> getPlayerDead() const = 0;

};

#endif /* !OBJECT_HPP_ */
