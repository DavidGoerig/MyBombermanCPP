/*
** EPITECH PROJECT, 2018
** BombStandard.cpp
** File description:
** Method for the standard bomb
*/

#include "BombStandard.hpp"

/**
* \fn BombStandard::BombStandard(ISceneManager *smgr, IVedeoDriver *driver, int range)
* \param ISceneManager *smgr: scene manager
* \param IVideoDriver *driver: driver
* \param int range: range
* \brief constructor (init standard bomb)
* \return nothing
**/

BombStandard::BombStandard(
	irr::scene::ISceneManager *smgr,
	irr::video::IVideoDriver *driver, int range)
{
	_scene = smgr;
	_driver = driver;
	_range = range;
	_itemName = "Bomb classic";
	_ID = 20;
	this->_bombSMesh = smgr->getMesh("./Ressource/Bomb/Bomb.obj");
	if (!this->_bombSMesh){
		std::cout << "Error : Load BombMMesh" << std::endl;
	}
	this->_playerDead = std::pair<int, int>(-1, -1);
	_speedBonus = 0;
	_rangeBonus = 0;
	_nbrBombBonus = 0;
}

/**
* \fn BombStandard::~BombStandard()
* \brief destructor
* \return nothing
**/

BombStandard::~BombStandard()
{
}

/**
* \fn IAnimatedMeshSceneNode *BombStandard::isUsed(float x, float y)
* \param float x: position on x
* \param float y: position on y
* \brief plant the bomb at (x, y) position.
* \return IAnimatedSceneNode *node
**/

irr::scene::IAnimatedMeshSceneNode* BombStandard::isUsed(float x, float z)
{
	irr::scene::IAnimatedMeshSceneNode* node;

	node = this->_scene->addAnimatedMeshSceneNode(this->_bombSMesh);
	if (node) {
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		node->setMD2Animation(irr::scene::EMAT_STAND);
		node->setMaterialTexture(
			0,
			this->_driver->getTexture(
				"./Ressource/Bomb/Texture/bomb.png"));
	}
	node->setPosition(irr::core::vector3df(x, 1, z));
	return node;
}

/**
* \fn BombStandard::getNbrBombBonus() const
* \brief get number of bombs bonus
* \return int _nbrBombBonus
**/

int BombStandard::getNbrBombBonus() const
{
	return this->_nbrBombBonus;
}

/**
* \fn BombStandard::getSpeedBonus() const
* \brief get speed bonus
* \return int _speedBonus
**/

int BombStandard::getSpeedBonus() const
{
	return this->_speedBonus;
}

/**
* \fn BombStandard::getRangeBonus() const
* \brief get range bonus
* \return int _rangeBonus
**/

int BombStandard::getRangeBonus() const
{
	return this->_rangeBonus;
}

/**
* \fn BombStandard::addBonus(Cube::TypeBox type)
* \param Cube::TypeBox type: bonus type
* \brief add bonus
* \return nothing
**/

void BombStandard::addBonus(Cube::TypeBox type)
{
	switch (type) {
		case Cube::SPEED:
			if (_speedBonus < 4)
				++_speedBonus;
		break;
		case Cube::BOMB:
			if (_nbrBombBonus < 3)
				++_nbrBombBonus;
		break;
		case Cube::RANGE:
			if (_rangeBonus < 3)
				++_rangeBonus;
		break;
	}
}

/**
* \fn std::string BombStandard::getItemName()
* \brief get item name
* \return std::string _itemName
**/

std::string BombStandard::getItemName() {return (this->_itemName);}

/**
* \fn int BombStandard::getID()
* \brief get ID
* \return int _ID
**/

int BombStandard::getId() {return this->_ID;}

/**
* \fn bool BombStandard::explodeBomb(int x, int y, std::shared_ptr<Map> Map, std::vector<std::pair<int, int>> playerPos)
* \param int x: position on x
* \param int y: position on y
* \param std::shared_ptr<Map> Map: map
* \param std::vector<std::pair<int, int>> playerPos: vector of player positions
* \brief Bomb explosion gestion (with bonus)
* \return true or false
**/

bool BombStandard::explodeBomb(
	int x, int y,
	std::shared_ptr<Map> Map,
	std::vector<std::pair<int, int>> playerPos)
{
	int range = this->_range;
	x = x + 5;
	y = y + 5;
	std::pair<int ,int> startPos(x - (range * 10), y - (range * 10));
	std::pair<int ,int> endPos(x + (range * 10), y + (range * 10));
	std::vector<std::pair<int, int>>::iterator itPlayerPos = playerPos.begin();
	while (startPos.first <= endPos.first) {
		if (Map->isCubeNotEmpty(startPos.first, y, true)) {
			Map->setCubeDeleted(std::abs(startPos.first), std::abs(y));
			addBonus(Map->getLastBonus());
		}
		for (itPlayerPos = playerPos.begin(); itPlayerPos != playerPos.end(); itPlayerPos++) {
			if (itPlayerPos->first >= startPos.first
			&& itPlayerPos->first <= (startPos.first + 10)
			&& itPlayerPos->second >= (y - 5)
			&& itPlayerPos->second <= (y + 5))
				this->_playerDead = *itPlayerPos;
		}
		startPos.first = startPos.first + 10;
	}
	while (startPos.second <= endPos.second) {
		if (Map->isCubeNotEmpty(x, startPos.second, true) == true) {
			Map->setCubeDeleted(std::abs(x), std::abs(startPos.second));
			addBonus(Map->getLastBonus());
		}
		for (itPlayerPos = playerPos.begin(); itPlayerPos != playerPos.end(); itPlayerPos++) {
			if (itPlayerPos->first >= (x - 5)
			&& itPlayerPos->first <= (x + 5)
			&& itPlayerPos->second >= startPos.second
			&& itPlayerPos->second <= (startPos.second + 10))
				this->_playerDead = *itPlayerPos;
		}
		startPos.second = startPos.second + 10;
	}
	return false;
}

/**
* \fn std::pair<int, int> BombStandard::getPlayerDead() const
* \brief get player dead
* \return std::pair<int, int> _playerDead
**/

std::pair<int, int> BombStandard::getPlayerDead() const
{
	return this->_playerDead;
}