/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** STUDIOCORE_CPP_
*/

#include "StudioCore.hpp"

/**
 * \fn StudioCore::StudioCore()
 * \brief construction of the core of the game
 * \return nothing
 **/

StudioCore::StudioCore()
{
	_Graphical = std::make_shared<Graphical>();
	_Menu = std::make_shared<Menu>();
	_Intro = std::make_unique<Intro>();
	_Credits = std::make_unique<Credits>();
	_Param = std::make_unique<Param>();
	_Song = std::make_unique<Song>();
	_loopState = actualState::MENU;
	_mapInit = false;
	_menuSong = false;
	_gameSong = false;
	_lost = "";
}

/**
 * \fn StudioCore::~StudioCore()
 * \brief destructor of the core of the game
 * \return nothing
 **/

StudioCore::~StudioCore() {}

/**
 * \fn bool StudioCore::initCore()
 * \brief initialisation of menu and parameters
 * \return true or false
 **/

bool StudioCore::initCore()
{
	if (!this->_Graphical->initGraphical()) {
		std::cout << "Error: initGraphical()" << std::endl;
		return false;
	}
	if (!this->_Menu->initButton()) {
		std::cout << "Error: initButton()" << std::endl;
		return false;
	}
	this->_Menu->initEquivAction();
	this->_Param->initButton();
	this->_Param->initIntoButton();
	this->_Param->initEquivAction();
	this->_Param->initButtonLimits();
	this->initSelectState();
	return true;
}

/**
 * \fn void StudioCore::runCore()
 * \brief run the graphics and draw the scene and the GUI
 * \return nothing
 **/

void StudioCore::runCore()
{
	while (this->_Graphical->getDevice()->run()) {
		if (this->_loopState == actualState::EXIT)
			break;
		this->_Graphical->start();
		this->runDifferentCases();
		this->_Graphical->drawScene();
		this->_Graphical->drawGUI();
		this->_Graphical->end();
	}
	this->_Graphical->getDevice()->drop();
}

/**
 * \fn void StudioCore::runMenu()
 * \brief run the menu with graphics and song
 * \return nothing
 **/

void StudioCore::runMenu()
{
	irr::core::position2di mousePos = this->_Graphical->getEvent().getMousePos();
	bool leftClick = this->_Graphical->getEvent().isLeftClick();

	if (this->_gameSong) {
		this->_Song->stopLongSong();
		this->_gameSong = false;
	}
	if (!this->_menuSong) {
		this->_Song->playLongSong(
			"./Ressource/Song_Game/menu.ogg"
		);
		this->_menuSong = true;
	}
	this->_Menu->drawMenu(this->_Graphical);
	this->_loopState = this->_Menu->getClickButton(
		mousePos.X,
		mousePos.Y,
		leftClick
	);
}

/**
 * \fn void StudioCore::runCredits()
 * \brief run the credits
 * \return nothing
 **/

void StudioCore::runCredits()
{
	int ori[2] = {0, 0};
	int posi[4] = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

	this->_Graphical->getScene()->clear();
	_Graphical->drawTexture("./Ressource/credits.jpg", ori, posi);
	this->_loopState = this->_Credits->displayAll(
		this->_Graphical
	);
}

/**
 * \fn void StudioCore::runParam()
 * \brief get events and run to parameters
 * \return nothing
 **/

void StudioCore::runParam()
{
	irr::core::position2di mousePos = this->_Graphical->getEvent().getMousePos();
	bool leftClick = this->_Graphical->getEvent().isLeftClick();

	this->_Param->drawParam(
		this->_Graphical
	);
	this->_loopState = this->_Param->getClickButton(
		mousePos.X,
		mousePos.Y,
		leftClick
	);
}

/**
 * \fn void StudioCore::runIntro()
 * \brief run the intro
 * \return nothing
 **/

void StudioCore::runIntro()
{
	this->_loopState = this->_Intro->displayAll(
		this->_Graphical
	);
}

/**
 * \fn void StudioCore::runMultiplayerGame()
 * \brief play songs, start and run the multiplayer
 * \return nothing
 **/

void StudioCore::runMultiplayerGame()
{
 	this->_multiplayer = true;
	this->_Menu->setMultiplayer(true);
	if (this->_menuSong) {
		this->_Song->stopLongSong();
		this->_menuSong = false;
	}
	if (!this->_gameSong) {
		this->_Song->playLongSong(
			"./Ressource/Song_Game/game.ogg"
		);
		this->_gameSong = true;
	}
	if (!this->_mapInit) {
 		this->initMultiplayerBomberman();
 		this->computeMapParam();
 	}
	int ori[2] = {0, 0};
	int posi[4] = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	_Graphical->drawTexture(FONT_MENU, ori, posi);
 	if (this->_Graphical->getEvent().isKeyPressed(irr::KEY_ESCAPE))
 		this->_loopState = actualState::MENU;
 	this->_Game->moveBomberman(this->_Map, this->_Collision);
 	if (!this->_Game->getPlayerDead().empty()) {
		this->_lost = this->_Game->getPlayerDead();
		this->_loopState = actualState::DEATH;
	}
	this->_SGame->moveBomberman(this->_Map, this->_Collision);
	if (!this->_SGame->getPlayerDead().empty()) {
		this->_lost = this->_SGame->getPlayerDead();
		this->_loopState = actualState::DEATH;
	}
}

/**
 * \fn void StudioCore::runGame()
 * \brief playing song starting and running a game
 * \return nothing
 **/

void StudioCore::runGame()
{
	this->_Menu->setGame(true);
	if (this->_menuSong) {
		this->_Song->stopLongSong();
		this->_menuSong = false;
	}
	if (!this->_gameSong) {
		this->_Song->playLongSong(
			"./Ressource/Song_Game/game.ogg"
		);
		this->_gameSong = true;
	}
	if (!this->_mapInit) {
		this->initBomberman();
		this->computeMapParam();
	}
	int ori[2] = {0, 0};
	int posi[4] = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	_Graphical->drawTexture(FONT_MENU, ori, posi);
	if (this->_Graphical->getEvent().isKeyPressed(irr::KEY_ESCAPE))
		this->_loopState = actualState::MENU;
	this->_Game->moveBomberman(this->_Map, this->_Collision);
	if (!this->_Game->getPlayerDead().empty()) {
		this->_lost = this->_Game->getPlayerDead();
		this->_loopState = actualState::DEATH;
	}
	this->_IA->setPPos(_Game->getX(), _Game->getZ());
	this->_IA->moveIA(this->_Map, this->_Collision);
	if (!this->_IA->getPlayerDead().empty()) {
		this->_lost = this->_IA->getPlayerDead();
		this->_loopState = actualState::DEATH;
	}
}

/**
 * \fn void StudioCore::runDifferentCases()
 * \brief select the action assiociated to the state
 * \return nothing
 **/

void StudioCore::runDifferentCases()
{
	this->_selectState[this->_loopState]();
}

/**
 * \fn bool StudioCore::initSelectState()
 * \brief initialisation of states
 * \return true or false
 **/

bool StudioCore::initSelectState()
{
	this->_selectState[actualState::MENU] = std::bind(
		&StudioCore::runMenu, this);
	this->_selectState[actualState::GAME] = std::bind(
		&StudioCore::runGame, this);
	this->_selectState[actualState::CREDITS] = std::bind(
		&StudioCore::runCredits, this);
	this->_selectState[actualState::PARAM] = std::bind(
		&StudioCore::runParam, this);
	this->_selectState[actualState::INTRO] = std::bind(
		&StudioCore::runIntro, this);
	this->_selectState[actualState::MULTIPLAYER] = std::bind(
		&StudioCore::runMultiplayerGame, this);
	this->_selectState[actualState::NEWGAME] = std::bind(
		&StudioCore::runNewGame, this);
	this->_selectState[actualState::DEATH] = std::bind(
		&StudioCore::runDeath, this);
	return true;
}

/**
 * \fn void StudioCore::computeMapParam()
 * \brief computing the parameter of map
 * \return nothing
 **/

void StudioCore::computeMapParam()
{
	this->_Map = std::make_shared<Map>(
		this->_Graphical->getScene(),
		this->_Graphical->getVideo(),
		this->_Param->getParam()
	);
	this->_Map->generateBorder();
	this->_Map->generateMap();
	this->_mapInit = true;
	this->_Collision = std::make_shared<Collision>(100, 100);
	this->_Game->findSpawn(this->_Map, this->_Collision);
	if (this->_multiplayer)
		this->_SGame->findSpawn(this->_Map, this->_Collision);
	else
		this->_IA->findSpawn(this->_Map, this->_Collision);
}

/**
 * \fn void StudioCore::initBomberman()
 * \brief initialisation of the bomberman character
 * \return nothing
 **/

void StudioCore::initBomberman()
{
	std::map<std::string, int> vParam = this->_Param->getParam();
	int nbrBomb = vParam["NBOMB"];

	_Game = std::make_shared<Bomberman>(true, false, nbrBomb);
	_IA = std::make_shared<IA>(
		this->_Graphical->getScene(),
		this->_Graphical->getVideo(),
		this->_Graphical
	);
	this->_Game->initBomberman(
		this->_Graphical->getScene(),
		this->_Graphical->getVideo(),
		this->_Graphical
	);
	this->_Game->setEnemy(this->_IA);
}

/**
 * \fn void StudioCore::initMultiplayerBomberman()
 * \brief initialisation of the bomberman for the multiplayer
 * \return nothing
 **/

void StudioCore::initMultiplayerBomberman()
{
	std::map<std::string, int> vParam = this->_Param->getParam();
	int nbrBomb = vParam["NBOMB"];

	_Game = std::make_shared<Bomberman>(true, false, nbrBomb);
	_SGame = std::make_shared<Bomberman>(false, false, nbrBomb);

	this->_Game->initBomberman(
		this->_Graphical->getScene(),
		this->_Graphical->getVideo(),
		this->_Graphical
	);
	this->_SGame->initBomberman(
		this->_Graphical->getScene(),
		this->_Graphical->getVideo(),
		this->_Graphical
	);
	this->_SGame->setEnemy(this->_Game);
	this->_Game->setEnemy(this->_SGame);
	this->_Game->setMulti();
	this->_SGame->setMulti();
}

/**
 * \fn void StudioCore::runNewGame()
 * \brief restart a new game
 * \return nothing
 **/

void StudioCore::runNewGame()
{
	int ori[2] = {0, 0};
	int posi[4] = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

	this->_Graphical->getScene()->clear();
	_Graphical->drawTexture(FONT_MENU, ori, posi);
	if (this->_menuSong) {
		this->_Song->stopLongSong();
		this->_menuSong = false;
	}
	if (!this->_gameSong) {
		this->_Song->playLongSong(
			"./Ressource/Song_Game/game.ogg"
		);
		this->_gameSong = true;
	}
	_Map.reset();
	if (this->_multiplayer) {
		this->initMultiplayerBomberman();
		this->computeMapParam();
		this->_loopState = actualState::MULTIPLAYER;
	}
	else {
		this->initBomberman();
		this->computeMapParam();
		this->_loopState = actualState::GAME;
	}
}

/**
 * \fn void StudioCore::runDeath()
 * \brief end the game when you die and run a new game
 * \return nothing
 **/

void StudioCore::runDeath()
{
	std::string toDisplay = this->_lost + ": LOOSEE";

	int pos[4] = {
		(WINDOW_WIDTH / 2) - (WINDOW_WIDTH / static_cast<int>(this->_lost.length())),
		(WINDOW_HEIGHT / 2) - (WINDOW_HEIGHT / 4),
		(WINDOW_WIDTH / 2) - (WINDOW_WIDTH / static_cast<int>(this->_lost.length())),
		(WINDOW_HEIGHT / 2) - (WINDOW_HEIGHT / 4)
	};
	this->_Graphical->getScene()->clear();
	this->_Graphical->start();
	this->_Graphical->drawText(toDisplay, pos, true);
	this->_Graphical->drawScene();
	this->_Graphical->drawGUI();
	this->_Graphical->end();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	this->runNewGame();
}