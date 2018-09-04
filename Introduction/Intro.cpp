/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** INTRO_CPP_
*/

#include "Intro.hpp"

/**
* \fn Intro::Intro()
* \brief introduction constructor (init pos and text)
* \return nothing
**/

Intro::Intro()
{
	_initialPosY = 0;
	_initialPosX = (WINDOW_WIDTH / 2) - (WINDOW_WIDTH / 4);
	_toMove = 0;
	_timer = 0;
	_toDisplay = {
		"B", "O", "M", "B",
		"E", "R", "M", "A", "N"
	};
	_actualIt = _toDisplay.begin();
}

/**
* \fn Intro::~Intro()
* \brief introduction destructor
* \return nothing
**/

Intro::~Intro() {}

/**
* \fn actualState Intro::displayAll(std::shared_ptr<Graphical> Graphical)
* \param std::shared_ptr<Graphical> Graphical: graphical object
* \brief display the introduction
* \return actualState::INTRO
**/

actualState Intro::displayAll(
	std::shared_ptr<Graphical> Graphical)
{
	if (this->_timer >= 100)
		return actualState::MENU;
	if (!this->displayLbyL(Graphical)) {
		this->displayText(Graphical);
		this->_timer += 1;
	}
	return actualState::INTRO;
}

/**
* \fn bool Intro::displayLbyL(std::shared_ptr<Graphical> Graphical)
* \param std::shared_ptr<Graphical> Graphical: graphical object
* \brief do the introduction move
* \return true or false
**/

bool Intro::displayLbyL(
	std::shared_ptr<Graphical> Graphical)
{
	int pos[4] = {
		this->_initialPosX,
		_initialPosY + this->_toMove,
		this->_initialPosX,
		_initialPosY + this->_toMove
	};
	if ((this->_toMove + this->_initialPosY) > (WINDOW_HEIGHT / 2)) {
		if ((this->_actualIt + 1) != this->_toDisplay.end())
			this->_actualIt++;
		else
			return false;
		this->_initialPosX += (WINDOW_WIDTH / _toDisplay.size());
		this->_toMove = 0;
	} else {
		this->_toMove += 10;
	}
	Graphical->drawText(*this->_actualIt, pos, true);
	return true;
}

/**
* \fn void Intro::displayText(std::shared_ptr<Graphical> Graphical)
* \param std::shared_ptr<Graphical> Graphical: graphical object
* \brief draw the title
* \return nothing
**/

void Intro::displayText(std::shared_ptr<Graphical> Graphical)
{
	std::string toDisplay = "BOMBERMAN";
	int pos[4] = {
		(WINDOW_WIDTH / 2) - (WINDOW_WIDTH / 16),
		(WINDOW_HEIGHT / 2) - (WINDOW_HEIGHT / 4),
		(WINDOW_WIDTH / 2) - (WINDOW_WIDTH / 16),
		(WINDOW_HEIGHT / 2) - (WINDOW_HEIGHT / 4)
	};
	Graphical->drawText(toDisplay, pos, true);
}

void Intro::displayPic()
{}