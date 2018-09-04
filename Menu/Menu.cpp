/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** MENU_CPP_
*/

#include "Menu.hpp"

/**
* \fn Menu::Menu()
* \brief constructor of Menu
* \return nothing
**/

Menu::Menu()
{
	_run = true;
	_buttonName = {
		"GAME",
		"CREDITS",
		"PARAM",
		"EXIT",
		"MULTIPLAYER",
		"NEW GAME"
	};
	_multiplayer = false;
	_game = false;
}

/**
* \fn Menu::~Menu()
* \brief destructor of Menu
* \return nothing
**/

Menu::~Menu() {}

/**
* \fn void Menu::initEquivAction()
* \brief initalision action with state
* \return nothing
**/

void Menu::initEquivAction()
{
	this->setEquivAction("MENU", actualState::MENU);
	this->setEquivAction("GAME", actualState::GAME);
	this->setEquivAction("CREDITS", actualState::CREDITS);
	this->setEquivAction("PARAM", actualState::PARAM);
	this->setEquivAction("EXIT", actualState::EXIT);
	this->setEquivAction("MULTIPLAYER", actualState::MULTIPLAYER);
	this->setEquivAction("NEW GAME", actualState::NEWGAME);
}

/**
* \fn void Menu::setEquivAction()
* \brief assign a string to enumeration
* \return nothing
**/

void Menu::setEquivAction(
	const std::string &nameAction, actualState myAction)
{
	this->_equivAction[nameAction] = myAction;
}

/**
* \fn bool Menu::isRun() const
* \brief check if the menu is running
* \return true or false
**/

bool Menu::isRun() const
{
	return this->_run;
}

/**
* \fn std::vector<Button> Menu::getButton() const
* \brief get the button
* \return std::vector<Button> _button
**/

std::vector<Button> Menu::getButton() const
{
	return this->_button;
}

/**
* \fn bool Menu::initButton()
* \brief initialize the buttons
* \return true or false
**/

bool Menu::initButton()
{
	int len[2] = {
		(WINDOW_WIDTH / 2),
		(WINDOW_HEIGHT / 9)
	};
	int initialPos[2] = {
		((WINDOW_WIDTH / 2) - (len[0] / 2)),
		((WINDOW_HEIGHT / 9) - ((WINDOW_HEIGHT / 9) / 2))
	};

	for (int i = 0; i < 6; i++) {
		Button b1(initialPos, len, this->_buttonName[i], 0);
		this->_button.push_back(b1);
		initialPos[1] += (len[1] * 1.5);
	}
	return true;
}

/**
* \fn actualstate Menu::getClickButton(const int &clickX,
* const int &clickY, bool isClick)
* \param clickX: position X of click
* \param clickY: position Y of click
* \param isClick: is it clicked
* \brief get the action did by the user and handle the next
* \return actualstate of menu
**/

actualState Menu::getClickButton(
	const int &clickX, const int &clickY, bool isClick)
{
	std::vector<Button>::iterator itButton = this->_button.begin();

	for (; itButton != this->_button.end(); itButton++) {
		if (itButton->isClick(clickX, clickY) && isClick) {
			if (this->_game && itButton->getName() == "MULTIPLAYER")
				return actualState::MENU;
			else if (this->_multiplayer && itButton->getName() == "GAME")
				return actualState::MENU;
			else
				return this->_equivAction[itButton->getName()];
		}
	}
	return actualState::MENU;
}

/**
* \fn void Menu::drawMenu(std::shared_ptr<Graphical> Graphical)
* \param Graphical: handle the graphic side
* \brief drawing the menu
* \return nothing
**/

void Menu::drawMenu(std::shared_ptr<Graphical> Graphical)
{
	std::vector<Button>::iterator itButton = this->_button.begin();
	int pos[4] = {0, 0, 0, 0};

	for (; itButton != this->_button.end(); itButton++) {
		pos[0] = itButton->getPosX();
		pos[1] = itButton->getPosY();
		pos[2] = pos[0] + itButton->getLenX();
		pos[3] = pos[1] + itButton->getLenY();
		Graphical->drawButton(
			itButton->getName(),
			pos, ""
		);
	}
	int ori[2] = {0, 0};
	int posi[4] = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	Graphical->drawTexture(FONT_MENU, ori, posi);
}

/**
* \fn void Menu::setMultiplayer(bool multi)
* \param bool multi: multi state
* \brief set multiplayer mode
* \return nothing
**/

void Menu::setMultiplayer(bool multi)
{
	this->_multiplayer = multi;
}

/**
* \fn void Menu::setMultiplayer(bool game)
* \param bool game: game state
* \brief set game mode
* \return nothing
**/

void Menu::setGame(bool game)
{
	this->_game = game;
}