//
// EPITECH PROJECT, 2018
// Map.cpp
// File description:
// Map
//

#include "Map.hpp"

/**
 * \fn Map::Map(irr::scene::ISceneManager *manager,
 * irr::video::IVideoDriver* driver,
 * std::map<std::string, int> vParam)
 * \param manager: the manager of the scene
 * \param driver: for handling video
 * \param vParam: the parameters of the map
 * \brief build and initialise
 * all value the class map need to draw it
 * \return nothing
 **/

Map::Map(irr::scene::ISceneManager *manager,
	irr::video::IVideoDriver* driver,
	std::map<std::string, int> vParam)
{
	_prctCaseWithBoost = vParam["BOOST"];
	_prctFill = vParam["FILL"];
	_height = vParam["HEIGHT"];
	_width = vParam["WIDTH"];
	_speed = vParam["SPEED"];
	_range = vParam["RANGE"];
	_nbrbomb = vParam["NBOMB"];
	_manager = manager;
	_driver = driver;
	_toInit = false;

	_speedBonus = 0;
	_rangeBonus = 0;
	_nbrbombBonus = 0;
	_lastBonus = Cube::NOBOX;
}

Map::~Map() {}

/**
 * \fn bool Map::isValidPos(std::pair<int, int> pos)
 * \param pos: positions to check
 * \brief check if the position is valid or no
 * \return true or false
 **/

bool	Map::isValidPos(std::pair<int, int> pos)
{
	if (pos.first == 1 &&
	(pos.second == 1 || pos.second == _height -1))
		return false;
	if (pos.first == (_width - 1) &&
	(pos.second == 1 || pos.second == _height - 1))
		return false;
	if (pos.first == 2 &&
	(pos.second == 1 || pos.second == _height -1))
		return false;
	if (pos.first == (_width - 2) &&
	(pos.second == 1 || pos.second == _height - 1))
		return false;
	if (pos.first == 1 &&
	(pos.second == 2 || pos.second == _height - 2))
		return false;
	if (pos.first == (_width - 1) &&
	(pos.second == 2 || pos.second == _height - 2))
		return false;
	return true;
}

/**
 * \fn void Map::generateWidthMap()
 * \brief generating the width map with border Cube.
 * \return nothing
 **/

void Map::generateWidthMap()
{
	for (int x = 0; x <= _width; x++) {
		std::pair<int, int> posf(x, _height);
		std::pair<int, int> poss(x, 0);
		poss.first = x;
		poss.second = 0;
		_map.insert(std::make_pair(
			posf, std::unique_ptr<Cube>(new Cube(
				x, _height, _manager,
				_driver, false, Cube::BORDER)
			)
		));
		_map.insert(std::make_pair(
			poss, std::unique_ptr<Cube>(new Cube(
				x, 0, _manager,
				_driver, false, Cube::BORDER)
			)
		));
	}
}

/**
 * \fn void Map::generateHeighthMap()
 * \brief generating the height map with border Cube.
 * \return nothing
 **/

void Map::generateHeightMap()
{
	for (int y = 0; y <= _height; y++) {
		std::pair<int, int> posf;
		std::pair<int, int> poss;

		posf.first = 0;
		posf.second = y;
		poss.first = _width;
		poss.second = y;
		_map.insert(std::make_pair(
			posf, std::unique_ptr<Cube>(new Cube(
				0, y, _manager, _driver, false, Cube::BORDER)
			)
		));
		_map.insert(std::make_pair(
			poss, std::unique_ptr<Cube>(new Cube(
				_width, y, _manager,
				_driver, false, Cube::BORDER)
			)
		));
	}
}

/**
 * \fn Map::createFloor()
 * \brief call to Floor constructor who create the floor
 * \return nothing
 **/

void Map::createFloor()
{
	Floor floor(_height, _width, _manager, _driver);
}

/**
 * \fn int Map::getNbrBomb()
 * \brief get the bomb number
 * \return int _nbrbomb
 **/

int Map::getNbrBomb() const
{
	return _nbrbomb;
}

/**
 * \fn Map::generateBorder()
 * \brief generating all the border by calling
 * generateWidthMap() and generatWidthMap().
 * \return nothing
 **/

void	Map::generateBorder()
{
	int origPos[2] = {0, 0};
	int picLen[4] = {0, 0, 1200, 800};
	irr::video::ITexture *toDisplay =
	this->_driver->getTexture("./Ressource/disp.png");

	this->createFloor();
	this->generateWidthMap();
	this->generateHeightMap();
	if (!toDisplay) {
		std::cout << "Fail at Texture" << std::endl;
		return;
	}
	this->_driver->draw2DImage(
		toDisplay, irr::core::position2d<irr::s32>(origPos[0], origPos[1]),
		irr::core::rect<irr::s32>(picLen[0], picLen[1], picLen[2], picLen[3]),
		0, irr::video::SColor(255, 255, 255, 255), true
	);
}

/**
 * \fn Cube::TypeBox Map::generateTypeBoxRt(float rdm,
 * float caseWSpeed, float caseWSRange, float caseWBoost)
 * \param rdm: random
 * \param caseWSpeed: case box of speed
 * \param caseWSRange: case box of range
 * \param caseWBoost: case box boost
 * \brief generating the type of box we need
 * \return a Cube::TypeBox
 **/

Cube::TypeBox Map::generateTypeBoxRt(
	float rdm,
	float caseWSpeed,
	float caseWSRange,
	float caseWBoost)
{
	float caseWSmtg = 10000.0 * (0.90 * ((float)_prctFill / 100));

	if (rdm < caseWSpeed)
		return Cube::SPEED;
	else if (rdm > caseWSpeed && rdm <= caseWSpeed + caseWSRange)
		return Cube::RANGE;
	else if (rdm > caseWSpeed + caseWSRange && rdm <= caseWBoost)
		return Cube::BOMB;
	else if (rdm > caseWBoost && rdm < caseWSmtg)
		return Cube::NORMAL;
	else
		return Cube::NOBOX;
}

/**
 * \fn Cube::TypeBox Map::generateTypeBox()
 * \brief generating the type of box we need and call to generateTypeBoxRt()
 * \return a Cube::TypeBox
 **/

Cube::TypeBox Map::generateTypeBox()
{
	float caseWSmtg = 10000.0 * (0.90 * ((float)_prctFill / 100));
	float caseWBoost = caseWSmtg * ((float)_prctCaseWithBoost / 100);
	float totalBoost = _speed + _range + _nbrbomb;
	float caseWSpeed;
	float caseWSRange;
	float caseWSBomb;
	float rdm;

	rdm = (float)((std::rand() + 1) % 10000);
	if (totalBoost == 0) {
		if (rdm < caseWSmtg)
			return Cube::NORMAL;
		else
			return Cube::NOBOX;
	}
	caseWSpeed = caseWBoost * (_speed / totalBoost);
	caseWSRange = caseWBoost * (_range / totalBoost);
	caseWSBomb = caseWBoost * (_nbrbomb / totalBoost);
	return this->generateTypeBoxRt(rdm, caseWSpeed, caseWSRange, caseWBoost);
}

/**
 * \fn Map::generateMap()
 * \brief generate the map and the boxes with calling generatingTypeBox()
 * \return nothing
 **/

void	Map::generateMap()
{
	std::pair<int, int> pos;

	std::srand(std::time(nullptr));
	for (int y = 1; y < _height - 1; y++) {
		for (int x = 1; x < _width; x++) {
			Cube::TypeBox type = generateTypeBox();
			pos.first = x;
			pos.second = y;
			if (isValidPos(pos) == true && type != Cube::NOBOX)
				_map.insert(std::make_pair(
					pos, std::unique_ptr<Cube>(
						new Cube(x, y, _manager,
						_driver, true, type)
					)
				));
		}
	}
	this->_toInit = true;
}

/**
 * \fn bool Map::isInit()
 * \brief know if the map is initialized
 * \return true or false
 **/

bool Map::isInit() const
{
	return this->_toInit;
}

/**
 * \fn void Map::addBonus()
 * \brief add the bonus
 * \return nothing
 **/

void Map::addBonus()
{
	switch (_lastBonus) {
		case Cube::SPEED:
			if (_speed < 4)
				++_speed;
		break;
		case Cube::BOMB:
			if (_nbrbomb < 3)
				++_nbrbomb;
		break;
		case Cube::RANGE:
			if (_range < 3)
				++_range;
		break;
	}
}

/**
 * \fn Cube::TypeBox Map::getLastBonus()
 * \brief get the last bonus
 * \return Cube::TypeBox _lastBonus
 **/

Cube::TypeBox Map::getLastBonus() const
{
	return _lastBonus;
}

/**
 * \fn Map::setCubeDeleted(int x, int y)
 * \param x: position x of the Cube
 * \param y: position y of the Cube
 * \brief this function set if a cube is possible to delete
 * \return true or false
 **/

bool Map::setCubeDeleted(int x, int y)
{
	int mapX = 0;
	int mapY = 0;
	std::map<
		std::pair<int, int>, std::unique_ptr<Cube>
	>::iterator itMap = this->_map.begin();

	_lastBonus = Cube::NOBOX;
	for (; itMap != this->_map.end(); itMap++) {
		mapX = itMap->second->getposx() * 10;
		mapY = itMap->second->getposy() * 10;
		if ((x >= mapX)
		&& (x <= (mapX + 10))
		&& (y >= mapY)
		&& (y <= (mapY + 10))) {
			_lastBonus = itMap->second->getCubeType();
			this->addBonus();
			itMap->second->setDestruct();
			return true;
		}
	}
	return false;
}

/**
 * \fn Map::isCubeNotEmpty(int x, int y, bool isToDestroy)
 * \param x: the position x of cube
 * \param y: position y of the Cube
 * \param isToDestroy: give if is it to destroy a cube or no
 * \brief this function check if is it ok to destroy a cube
 * \return true or false
 **/

bool Map::isCubeNotEmpty(int x, int y, bool isToDestroy)
{
	int mapX = 0;
	int mapY = 0;
	std::map<
		std::pair<int, int>, std::unique_ptr<Cube>
	>::iterator itMap = this->_map.begin();
	for (; itMap != this->_map.end(); itMap++) {
		mapX = itMap->second->getposx() * 10;
		mapY = itMap->second->getposy() * 10;
		if ((x >= mapX)
		&& (x <= (mapX + 10))
		&& (y >= mapY)
		&& (y <= (mapY + 10))
		&& (!itMap->second->isDestruct())
		) {
			if (isToDestroy
			&& !itMap->second->isDestructable())
				return false;
			return true;
		}
	}
	return false;
}

/**
 * \fn Map::getHeight() const
 * \brief get the height of map
 * \return int _height
 **/

int Map::getHeight() const
{
	return this->_height;
}

/**
 * \fn Map::getWidth() const
 * \brief get the width of map
 * \return int _width
 **/

int Map::getWidth() const
{
	return this->_width;
}