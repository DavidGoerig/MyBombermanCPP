/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** BOMBERMAN_CPP_
*/

#include "Bomberman.hpp"

/**
* \fn Bomberman::Bomberman(bool firstPlayer, bool ian int maxBomb)
* \param ia: is it ia or no
* \param firstPlayer: is it the first player
* \param maxBomb: nb max bomb to drop
* \brief construct the player
* with his parameters
* \return nothing
**/

Bomberman::Bomberman(bool firstPlayer, bool ia, int maxBomb)
{
	this->_run = true;
	this->_ia = ia;
	_alreadyPressed = false;
	_firstPlayer = firstPlayer;
	_listDepla = {
		irr::KEY_LEFT,
		irr::KEY_DOWN,
		irr::KEY_RIGHT,
		irr::KEY_UP
	};
	this->_multi = false;
	_maxBomb = maxBomb;
	_maxBombRet = maxBomb;
	_nbBomb = 0;
	_playerDead = "";
}

/**
* \fn void Bomberman::~Bomberman()
* \brief destructor
* \return nothing
**/

Bomberman::~Bomberman() {}

void Bomberman::setEnemy(std::shared_ptr<Bomberman> enemy)
{
	this->_enemy = enemy;
}

void Bomberman::setEnemy(std::shared_ptr<IA> ia)
{
	this->_iaEnnemy = ia;
}

/**
* \fn int Bomberman::initBomberman(irr::scene::ISceneManager *smgr,
* irr::video::IVideoDriver *Driver,
* std::shared_ptr<Graphical> Graphical)
* \param smgr: managing the scene
* \param Driver: handling vidéo
* \param Graphical: managing the graphics of character
* \brief Construction of the charcater bomberman
* \return int
**/

int Bomberman::initBomberman(
	irr::scene::ISceneManager *smgr,
	irr::video::IVideoDriver *Driver,
	std::shared_ptr<Graphical> Graphical)
{
	this->_x = 250;
	this->_z = 100;
	this->initKeyMove();
	this->_Graphical = Graphical;
	this->_bombermanMesh = smgr->getMesh("./Ressource/Character/pikachuhat.obj");
	if (!this->_bombermanMesh) {
		std::cout << "Error : Load Bomberman Mesh" << std::endl;
		return -1;
	}
	this->_bombermanNode = smgr->addAnimatedMeshSceneNode(
		this->_bombermanMesh, 0, -1, irr::core::vector3df(
			this->_x, 0, this->_z)
	);
	if (this->_bombermanNode) {
		this->_bombermanNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		this->_bombermanNode->setMD2Animation(irr::scene::EMAT_STAND);
		this->_bombermanNode->setMaterialTexture(
			0, Driver->getTexture("./Ressource/Character/yellow.png"));
		this->_bombermanNode->setScale(
			irr::core::vector3df(
				(irr::f32)0.05, (irr::f32)0.05, (irr::f32)0.05)
			);
	}
	this->_inv.push_back(std::shared_ptr<IItem>(new BombStandard(smgr, Driver, 1)));
	return 1;
}

/**
* \fn void Bomberman::realizeDeplacement()
* \brief realize the player deplacement withe keyboard inputs
* \return nothing
**/

void Bomberman::realizeDeplacement()
{
	std::map<std::pair<int, int>, int>::iterator itKMove = this->_keyMove.begin();

	for (; itKMove != this->_keyMove.end(); itKMove++) {
		if (this->_Graphical->getEvent().isKeyPressed(itKMove->second)) {
			this->_x += itKMove->first.first;
			this->_z += itKMove->first.second;
		}
	}
}

/**
* \fn void Bomberman::dropBomb()
* \brief droping bomb by players
* \return nothing
**/

void Bomberman::dropBomb()
{
	int toDrop = irr::KEY_SPACE;
	if (!this->_firstPlayer)
		toDrop = irr::KEY_TAB;
	if (this->_Graphical->getEvent().isKeyPressed(toDrop) &&
	this->_alreadyPressed == false &&
	this->_nbBomb < this->_maxBomb) {
		this->_nbBomb++;
		this->_alreadyPressed = true;
		this->_bombList.push_back(
			this->getItem()->isUsed(this->_x, this->_z));
		this->_bombPos.push_back(
			std::pair<int, int>(this->_x, this->_z));
		this->_bombTime.push_back(
			std::chrono::high_resolution_clock::now());
	} else if (!this->_Graphical->getEvent().isKeyPressed(toDrop)
	&& this->_alreadyPressed == true)
		this->_alreadyPressed = false;
}

/**
* \fn void Bomberman::moveBomberman(std::shared_ptr<Map> Map,
* std::shared_ptr<Collision> Collision)
* \param Map: represent the Map
* \param Collision: handling the collision
* \brief realise moving and moving the camera
* \return nothing
**/

void Bomberman::moveBomberman(
	std::shared_ptr<Map> Map,
	std::shared_ptr<Collision> Collision)
{
	int saveX = this->_x;
	int saveZ = this->_z;
	irr::core::vector3df camera = {0, 0, 30};

	this->dropBomb();
	this->timeToExplode(Map);
	this->realizeDeplacement();
	if (!Collision->checkCollision(this->_x, this->_z, Map))
		this->_bombermanNode->setPosition(
			irr::core::vector3df(this->_x, 0, this->_z));
	else {
		this->_x = saveX;
		this->_z = saveZ;
	}
	if (this->_multi) {
		camera.X = -150 + this->_x;
		camera.Y = 100;
		camera.Z = 50 + this->_z;
	}
	this->_Graphical->setCamera(
		(this->_x - camera.X),
		camera.Y,
		(this->_z - camera.Z)
	);
}

/**
* \fn void Bomberman::addBonus(std::shared_ptr<Map> Map)
* \param Map: represent the Map
* \brief adding all the bonuses
* \return nothing
**/

void Bomberman::addBonus(std::shared_ptr<Map> Map)
{
	_maxBomb = _maxBombRet + Map->getNbrBomb();
}

/**
* \fn void Bomberman::moveBomberman(std::shared_ptr<Map> Map)
* \param Map: represent the Map
* \brief handling the duration of the explodes of bomb
* \return nothing
**/

void Bomberman::timeToExplode(std::shared_ptr<Map> Map)
{
	this->_bombTimeIt = this->_bombTime.begin();
	std::chrono::duration<double, std::milli> elapsed;
	std::chrono::high_resolution_clock::time_point actualTime;

	while (this->_bombTimeIt != this->_bombTime.end() && !this->_bombList.empty()) {
		actualTime = std::chrono::high_resolution_clock::now();
		elapsed = actualTime - (*this->_bombTimeIt);
		if (elapsed.count() >= (3 * 1000)) {
			this->_nbBomb--;
			this->deleteBomb(Map);
		}
		if (this->_bombTime.empty())
			return;
		this->_bombTimeIt++;
	}
	addBonus(Map);
}

/**
* \fn void Bomberman::deleteBomb(std::shared_ptr<Map> Map)
* \param Map: represent the Map
* \brief deleting bomb when she explodes
* \return nothing
**/

void Bomberman::deleteBomb(std::shared_ptr<Map> Map)
{
	int f;
	int s;

	if (this->_bombList.empty())
		return;
	this->_actualIt = this->_bombList.begin();
	this->_bombPosIt = this->_bombPos.begin();
	this->_bombTimeIt = this->_bombTime.begin();
	f = (*this->_bombPosIt).first;
	s = (*this->_bombPosIt).second;
	(*this->_actualIt)->remove();
	this->invExplodeBomb(f, s, Map);
	_doSong.playShortSong("./Ressource/Bomb/bombe.ogg");
	this->_bombPos.erase(this->_bombPosIt);
	this->_bombList.erase(this->_actualIt);
	this->_bombTime.erase(this->_bombTimeIt);
}

/**
* \fn void Bomberman::invExplodeBomb(int f, int s, std::shared_ptr<Map> Map)
* \param Map: represent the Map
* \param f:  position first
* \param s: position second
* \brief getting the positions
* and see who died
* \return nothing
**/

void Bomberman::invExplodeBomb(int f, int s, std::shared_ptr<Map> Map)
{
	std::vector<std::shared_ptr<IItem>>::iterator invIt;
	int xEnemy = (this->_iaEnnemy) ? static_cast<int>(this->_iaEnnemy->getX()) : static_cast<int>(this->_enemy->getX());
	int zEnemy = (this->_iaEnnemy) ? static_cast<int>(this->_iaEnnemy->getZ()) : static_cast<int>(this->_enemy->getZ());

	this->_playerPos.clear();
	std::pair<int, int> posPlayer = std::pair<int, int>(
		static_cast<int>(this->_x),
		static_cast<int>(this->_z)
	);
	std::pair<int, int> posEnemy = std::pair<int, int>(
		xEnemy,
		zEnemy
	);
	this->_playerPos.push_back(posPlayer);
	this->_playerPos.push_back(posEnemy);
	invIt = this->_inv.begin();
	(*invIt)->explodeBomb(f, s, Map, this->_playerPos);
	if ((*invIt)->getPlayerDead() == posPlayer)
		this->_playerDead = (this->_iaEnnemy) ? "YOU" : "PLAYER 1";
	if ((*invIt)->getPlayerDead() == posEnemy)
		this->_playerDead = (this->_iaEnnemy) ? "IA" : "PLAYER 2";
}

/**
* \fn bool Bomberman::isRunning()
* \brief check if bomberman is running
* \return true or false
**/

bool Bomberman::isRunning() const
{
	return this->_run;
}

/**
* \fn void Bomberman::setItem()
* \brief set an item
* \return nothing
**/

void Bomberman::setItem(Item nItem)
{
	if (nItem == Item::BOMBS) {
		_inv.push_back(std::shared_ptr<IItem>(
			new BombStandard(this->_scene, this->_driver, 1))
		);
	}
}

/**
* \fn std::shared_ptr<IItem> Bomberman::getItem()
* \brief get an item
* \return std::shared_ptr<IItem> _inv[0]
**/

std::shared_ptr<IItem> Bomberman::getItem()
{
	return this->_inv[0];
}

/**
* \fn void Bomberman::findSpawn(std::shared_ptr<Map> Map, std::shared_ptr<Collision> Collision)
* \param Map: represent the Map
* \param Collision: handling collision
* \brief searching the good spawn
* \return nothing
**/

void Bomberman::findSpawn(std::shared_ptr<Map> Map, std::shared_ptr<Collision> Collision)
{
	int mapX = (Map->getHeight() * 10);
	int mapY = (Map->getWidth() * 10);

	std::srand(std::time(nullptr));
	int xChar = (std::rand() % mapX);
	int yChar = (std::rand() % mapY);

	while (Collision->checkCollision(xChar, yChar, Map)) {
		xChar = (std::rand() % mapX);
		yChar = (std::rand() % mapY);
	}
	if (!this->_firstPlayer) {
		xChar = (std::rand() % mapX);
		yChar = (std::rand() % mapY);
		while (Collision->checkCollision(xChar, yChar, Map)) {
			xChar = (std::rand() % mapX);
			yChar = (std::rand() % mapY);
		}
	}
	this->_x = xChar;
	this->_z = yChar;
}

/**
* \fn float Bomberman::getZ()
* \brief get z
* \return float _z
**/

float Bomberman::getZ() const
{
	return this->_z;
}

/**
* \fn float Bomberman::getX()
* \brief get x
* \return float _x
**/

float Bomberman::getX() const
{
	return this->_x;
}

/**
* \fn void Bomberman::setKeyMove(int key, int x, int y)
* \param key: key nbr
* \param x: x index
* \param y: y index
* \brief set key moves
* \return nothing
**/

void Bomberman::setKeyMove(int key, int x, int z)
{
	this->_keyMove[std::pair<int, int>(x, z)] = key;
}

/**
* \fn void Bomberman::initKeyMove()
* \brief initialision of commands
* for player1 and player2
* \return nothing
**/

void Bomberman::initKeyMove()
{
	if (this->_firstPlayer) {
		this->setKeyMove(irr::KEY_LEFT, -2, 0);
		this->setKeyMove(irr::KEY_RIGHT, 2, 0);
		this->setKeyMove(irr::KEY_UP, 0, 2);
		this->setKeyMove(irr::KEY_DOWN, 0, -2);
	} else {
		this->setKeyMove(irr::KEY_KEY_Q, -2, 0);
		this->setKeyMove(irr::KEY_KEY_D, 2, 0);
		this->setKeyMove(irr::KEY_KEY_Z, 0, 2);
		this->setKeyMove(irr::KEY_KEY_S, 0, -2);
	}
}

/**
* \fn void Bomberman::setMulti()
* \brief set multiplayer
* \return nothing
**/

void Bomberman::setMulti()
{
	this->_multi = true;
}

/**
* \fn std::string Bomberman::getPlayerDead()
* \brief get player dead
**/

std::string Bomberman::getPlayerDead() const
{
	return this->_playerDead;
}
