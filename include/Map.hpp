//
// EPITECH PROJECT, 2018
// map.hpp
// File description:
// map
//

#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <iostream>
#include <map>
#include <memory>
#include <ctime>
#include <cstdlib>
#include <utility>

#define S_TO_WS(path) std::wstring(path.begin(), path.end()).c_str()

#include "irrlicht.h"
#include "Cube.hpp"
#include "Floor.hpp"

# define NBRBOMB 10000

class Map
{
public:
	Map(
		irr::scene::ISceneManager *manager,
		irr::video::IVideoDriver* driver,
		std::map<std::string, int> vParam
	);
	~Map();
	bool isValidPos(std::pair<int, int> pos);
	void createFloor();
	void generateBorder();
	void generateWidthMap();
	void generateHeightMap();
	void generateMap();
	Cube::TypeBox generateTypeBox();
	Cube::TypeBox generateTypeBoxRt(
		float rdm,
		float caseWSpeed,
		float caseWSRange,
		float caseWBoost
	);
	bool isInit() const;
	bool setCubeDeleted(int x, int y);
	bool isCubeNotEmpty(int x, int y, bool isToDestroy);
	int getHeight() const;
	int getWidth() const;
	int getNbrBomb() const;
	void addBonus();
	int getRange() const;
	int getSpeed() const;
	Cube::TypeBox getLastBonus() const;
private:
	int _prctCaseWithBoost;
	int _prctFill;
	int _height;
	int _width;
	int _speed;
	int _range;
	int _nbrbomb;
	bool _toInit;
	std::map<std::pair<int, int>, std::unique_ptr<Cube>> _map;
	irr::video::IVideoDriver *_driver;
	irr::scene::ISceneManager *_manager;
	Cube::TypeBox _lastBonus;
	int _speedBonus;
	int _rangeBonus;
	int _nbrbombBonus;
};

#endif