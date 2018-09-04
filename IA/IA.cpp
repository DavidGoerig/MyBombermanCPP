/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** IA_CPP_
*/

#include "IA.hpp"

/**
* \fn IA::IA( irr::scene::ISceneManager *smgr, irr::video:IVideoDriver
* *Driver, std::shared_ptr<Grapgical> Graphical)
* \param smgr: managing the scene
* \param Driver: handling vidéo
* \param Graphical: managing the graphics of character
* \brief Construction of the IA and the character IA
* \return nothing
**/

IA::IA(
	irr::scene::ISceneManager *smgr,
	irr::video::IVideoDriver *Driver,
	std::shared_ptr<Graphical> Graphical
	)
{
	this->_x = 10;
	this->_z = 10;
	this->_Graphical = Graphical;
	_lastDir = LAST;
	_isBomb = false;
	this->_iaMesh = smgr->getMesh("./Ressource/Character/pikachuhat.obj");
	if (!this->_iaMesh) {
		std::cout << "Error : Load Bomberman Mesh" << std::endl;
		return;
	}
	this->_iaNode = smgr->addAnimatedMeshSceneNode(
		this->_iaMesh, 0, -1, irr::core::vector3df(
			this->_x, 0, this->_z)
	);
	if (this->_iaNode) {
		this->_iaNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		this->_iaNode->setMD2Animation(irr::scene::EMAT_STAND);
		this->_iaNode->setMaterialTexture(
			0, Driver->getTexture("./Ressource/Character/yellow.png"));
		this->_iaNode->setScale(
			irr::core::vector3df(
				(irr::f32)0.05, (irr::f32)0.05, (irr::f32)0.05)
			);
	}
	this->_inv.push_back(std::shared_ptr<IItem>(new BombStandard(smgr, Driver, 1)));
	this->_playerDead = "";
}

/**
* \fn IA::~IA()
* \brief destructor of IA
* \return nothing
**/

IA::~IA() {}

/**
* \fn void IA::setPPose(float a, float b)
* \param a: position player
* \param b: position player
* \brief setting the position of IA
* \return nothing
**/

void IA::setPPos(float a, float b)
{
	_ppos.first = a;
	_ppos.second = b;
}

/**
* \fn IaDir IA::checkIfContinue(std::shared<Map> Map,
* std::shared_ptr<Collision> Collision)
* \param Map: map that contain the map
* \param Collision: handle the collision of character
* \brief helping the ia to be more smart and
* running in a single direction
* \return IaDir
**/

IA::IaDir IA::checkIfContinue(
	std::shared_ptr<Map> Map,
	std::shared_ptr<Collision> Collision)
{
	std::pair<int, int> pos;

	if (_lastDir == LAST || rand() % 10 == 1)
		return LAST;
	switch (_lastDir) {
		case LEFT:
		pos.first = _x - 1;
		pos.second = _z;
		break;
		case RIGHT:
		pos.first = _x + 1;
		pos.second = _z;
		break;
		case UP:
		pos.first = _x;
		pos.second = _z + 1;
		break;
		case DOWN:
		pos.first = _x;
		pos.second = _z - 1;
		break;
		default:
		return LAST;
		break;
	}
	if (!Collision->checkCollision(pos.first, pos.second, Map))
			return _lastDir;
	return LAST;
};

/**
* \fn IaDir IA::checkIfNotLast(std::shared_ptr<Map> Map,
* std::shared_ptr<Collision> Collision)
* \param Map: map that contain the map
* \param Collision: handle the collision of character
* \brief check if not last
* \return IaDir
**/

IA::IaDir IA::checkIfNotLast(
	std::shared_ptr<Map> Map,
	std::shared_ptr<Collision> Collision)
{
	std::pair<int, int> pos;

	if (_lastDir == RIGHT || _lastDir == LEFT) {
		pos.first = _x;
		pos.second = _z + 1;
		if (!Collision->checkCollision(pos.first, pos.second, Map) && pos != _last)
			return UP;
		pos.first = _x;
		pos.second = _z - 1;
		if (!Collision->checkCollision(pos.first, pos.second, Map) && pos != _last)
			return DOWN;
	}
	if (_lastDir == RIGHT || _lastDir == LEFT) {
		pos.first = _x + 1;
		pos.second = _z;
		if (!Collision->checkCollision(pos.first, pos.second, Map) && pos != _last)
			return RIGHT;
		pos.first = _x - 1;
		pos.second = _z;
		if (!Collision->checkCollision(pos.first, pos.second, Map) && pos != _last)
			return LEFT;
	}
}

/**
* \fn std::pair<int, int> IA::getIaNewPos(srd::shared_ptr<Map> Map,
* std::shared_ptr<Collision> Collision)
* \param Map: map that contain the map
* \param Collision: handle the collision of character
* \brief Getting a new good position for Ia
* \return std::pair<int, int> position
**/

std::pair<int, int> IA::getIaNewPos(
	std::shared_ptr<Map> Map,
	std::shared_ptr<Collision> Collision)
{
	std::pair<int, int> pos;
	IaDir move;

	if ((move = checkIfContinue(Map, Collision)) == LAST)
		move = static_cast<IaDir>(rand() % LAST);
	switch (move) {
		case LEFT:
		pos.first = _x - 1;
		pos.second = _z;
		break;
		case RIGHT:
		pos.first = _x + 1;
		pos.second = _z;
		break;
		case UP:
		pos.first = _x;
		pos.second = _z + 1;
		break;
		case DOWN:
		pos.first = _x;
		pos.second = _z - 1;
		break;
		default:
		pos.first = _x;
		pos.second = _z - 1;
		break;
	}
	_lastDir = move;
	return pos;
}

/**
* std::shared_ptr<Collision> Collision, std::pair<int, int> pos)
* \param Map: map that contain the map
* \param Collision: handle the collision of character
* \param pos: positions of IA in the map
* \brief find a position out of bomb range
* \return true or false
**/

bool IA::findPosNoSmash(
	std::shared_ptr<Map> Map,
	std::shared_ptr<Collision> Collision,
	std::pair<int, int> pos)
{
	if (this->_bombPos.empty())
		return false;
	for (std::vector<std::pair<int, int>>::iterator i = _bombPos.begin();
	i != _bombPos.end();++i){
		if (_x != (*i).first && _z != (*i).second) {
			if (pos.first == (*i).first || pos.second == (*i).second)
			return true;
		}
		if (pos.first == (*i).first && pos.second == (*i).second)
			return true;
	}
	return false;
}

/**
* \fn void IA::moveIA(srd::shared_ptr<Map> Map,
* std::shared_ptr<Collision> Collision)
* \param Map: map that contain the map
* \param Collision: handle the collision of character
* \brief move the IA int the better direction
* \return nothing
**/

void IA::moveIA(
	std::shared_ptr<Map> Map,
	std::shared_ptr<Collision> Collision)
{
	std::pair<int, int> pos;
	std::pair<int, int> posIfB;

	this->dropBomb(Map, Collision);
	this->timeToExplode(Map);
	pos = getIaNewPos(Map, Collision);
	if (!this->_bombPos.empty()) {
		if((posIfB = BetterPosAround(Map, Collision)).first == -42 && posIfB.second == -42) {
			if (findPosNoSmash(Map, Collision, pos) == true)
				return ;
			}
		else
			pos = posIfB;
	}
	if (!Collision->checkCollision(pos.first, pos.second, Map)) {
		this->_iaNode->setPosition(
		irr::core::vector3df(pos.first, 0, pos.second));
		_last.first = _x;
		_last.second = _z;
		_x = pos.first;
		_z = pos.second;
	}
}

/**
* \fn bool IA::wallAround(srd::shared_ptr<Map> Map,
* std::shared_ptr<Collision> Collision)
* \param Map: Map that contain the map
* \param Collision: handle the collision of the character
* \brief checking if there is wall around IA
* \return true or false
**/

bool IA::wallAround(
	std::shared_ptr<Map> Map,
	std::shared_ptr<Collision> Collision)
{
	if (Collision->checkCollision(_x - 1, _z, Map)) {
		return true;
	}
	if (Collision->checkCollision(_x + 1, _z, Map)) {
		return true;
	}
	if (Collision->checkCollision(_x, _z - 1, Map)) {
		return true;
	}
	if (Collision->checkCollision(_x, _z + 1, Map)) {
		return true;
	}
	return false;
}

/**
* \fn float IA::calcBombDirst(float _x, float _s)
* \param _x: position z
* \param _z: position x
* \brief calcul the distance between bomb and position
* \return float
**/

float IA::calcBombDirst(float _x, float _z)
{
	if (this->_bombPos.empty())
		return 0;
	for (std::vector<std::pair<int, int>>::iterator i = _bombPos.begin();
	i != _bombPos.end();++i){
		return (std::abs(std::abs(_x) - std::abs((*i).first)) +
	std::abs(std::abs(_z) - std::abs((*i).second)));
	}
	return 0;
}

/**
* \fn std::pair<int, int> IA::BetterPosAround(std::shared_ptr<Map> Map,
* std::shared_ptr<Collision> Collision)
* \param Map: a map that contain map
* \param Collision: handle the collision
* \brief check the collision and the position and know what's the best pos for IA
* \return std::pair<int, int> position
**/

std::pair<int, int> IA::BetterPosAround(
	std::shared_ptr<Map> Map,
	std::shared_ptr<Collision> Collision)
{
	std::pair<int, int> pos(-42, -42);
	float newDist;
	float oldDist = calcBombDirst(_x, _z);

	if (!Collision->checkCollision(_x - 1, _z, Map)) {
		if ((newDist = calcBombDirst(_x - 1, _z)) > oldDist) {
			pos.first = _x - 1;
			pos.second = _z;
			return pos;
		}
	}
	if (!Collision->checkCollision(_x + 1, _z, Map)) {
		if ((newDist = calcBombDirst(_x + 1, _z)) > oldDist) {
			pos.first = _x + 1;
			pos.second = _z;
			return pos;
		}
	}
	if (!Collision->checkCollision(_x, _z - 1, Map)) {
		if ((newDist = calcBombDirst(_x, _z - 1)) > oldDist) {
			pos.first = _x;
			pos.second = _z -1;
			return pos;
		}
	}
	if (!Collision->checkCollision(_x, _z + 1, Map)) {
		if ((newDist = calcBombDirst(_x, _z + 1)) > oldDist) {
			pos.first = _x;
			pos.second = _z + 1;
			return pos;
		}
	}
	return pos;
}

/**
* \fn bool IA::nearPlayer()
* \brief see where is the player
* \return true or false
**/

bool IA::nearPlayer()
{
	if (std::abs(std::abs(_x) - std::abs(_ppos.first)) +
	std::abs(std::abs(_z) - std::abs(_ppos.second)) < 10) {
		return true;
	}
	return false;
}

/**
* \fn void IA::dropBomb(std::shared_ptr<Map> Map,
* std::shared_ptr<Collision> Collision)
* \param Map: a map that contain map
* \param Collision: handle the collision
* \brief drop a bomb
* \return nothing
**/

void IA::dropBomb(
	std::shared_ptr<Map> Map,
	std::shared_ptr<Collision> Collision)
{
	if (this->_isBomb == false && (wallAround(Map, Collision) || nearPlayer())) {
		this->_isBomb = true;
		std::shared_ptr<IItem> myItem = getItem();
		if (myItem == nullptr)
			return;
		this->_bombList.push_back(myItem->isUsed(this->_x, this->_z));
		this->_bombPos.push_back(
			std::pair<int, int>(this->_x, this->_z));
		this->_bombTime.push_back(
			std::chrono::high_resolution_clock::now());
	};
}

/**
* \fn void IA::deleteBomb(std::shared_ptr<Map> Map)
* \param Map: a map that contain map
* \brief delete the bomb after explosion
* \return nothing
**/

void IA::deleteBomb(std::shared_ptr<Map> Map)
{
	int f;
	int s;

	if (this->_bombList.empty()
	|| this->_bombPos.empty()
	|| this->_bombTime.empty())
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
* \fn std::shared_ptr<IItem> IA::getItem()
* \brief get the items
* \return std::shared_ptr<IITem>
**/

std::shared_ptr<IItem> IA::getItem()
{
	if (!this->_inv.empty())
		return this->_inv[0];
	return nullptr;
}

/**
* \fn void IA::timeToExplode(std::shared_ptr<Map> Map)
* \param Map: map type that contain the map
* \brief timer before explosion
* \return nothing
**/

void IA::timeToExplode(std::shared_ptr<Map> Map)
{
	this->_bombTimeIt = this->_bombTime.begin();
	std::chrono::duration<double, std::milli> elapsed;
	std::chrono::high_resolution_clock::time_point actualTime;

	while (this->_bombTimeIt != this->_bombTime.end() && !this->_bombList.empty()) {
		actualTime = std::chrono::high_resolution_clock::now();
		elapsed = actualTime - (*this->_bombTimeIt);
		if (elapsed.count() >= (3 * 1000)) {
			this->_isBomb = false;
			this->deleteBomb(Map);
		}
		if (this->_bombTime.empty())
			return;
		this->_bombTimeIt++;
	}
}

/**
* \fn void IA::invExplodeBomb(int f, int s, std::shared_ptr<Map> Map)
* \param Map: map type that contain the map
* \param f: first pos
* \param s: second pos
* \brief get the positions and see who died
* \return nothing
**/

void IA::invExplodeBomb(int f, int s, std::shared_ptr<Map> Map)
{
	std::vector<std::shared_ptr<IItem>>::iterator invIt;

	this->_playerPos.clear();
	std::pair<int, int> posPlayer = std::pair<int, int>(
		static_cast<int>(this->_x),
		static_cast<int>(this->_z)
	);
	this->_playerPos.push_back(posPlayer);
	this->_playerPos.push_back(_ppos);
	if (this->_inv.empty())
		return;
	invIt = this->_inv.begin();
	(*invIt)->explodeBomb(f, s, Map, this->_playerPos);
	if ((*invIt)->getPlayerDead() == posPlayer)
		this->_playerDead = "IA";
	if ((*invIt)->getPlayerDead() == _ppos)
		this->_playerDead = "YOU";
}

/**
* \fn void IA::findSpawn(srd::shared_ptr<Map> Map,
* std::shared_ptr<Collision> Collision)
* \param Map: map that contain the map
* \param Collision: handle the collision of the character
* \brief searching for the good spawn
* \return nothing
**/

void IA::findSpawn(std::shared_ptr<Map> Map, std::shared_ptr<Collision> Collision)
{
	int mapX = (Map->getHeight() * 10);
	int mapY = (Map->getWidth() * 10);
	int xChar = (std::rand() % mapX);
	int yChar = (std::rand() % mapY);

	while (Collision->checkCollision(xChar, yChar, Map)) {
		xChar = (std::rand() % mapX);
		yChar = (std::rand() % mapY);
	}
	this->_x = xChar;
	this->_z = yChar;
}

/**
* \fn float IA::getZ() const
* \brief get Z position
* \return float _z
**/

float IA::getZ() const
{
	return this->_z;
}

/**
* \fn float IA::getX() const
* \brief get Z position
* \return float _x
**/

float IA::getX() const
{
	return this->_x;
}

/**
* \fn std::string IA::getPlayerDead() const
* \brief get player dead
* \return return std::string _playerDead
**/

std::string IA::getPlayerDead() const
{
	return this->_playerDead;
}