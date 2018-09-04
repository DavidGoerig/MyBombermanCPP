/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** INTRO_CPP_
*/

#include "Credits.hpp"

/**
 * \fn Credits::Credits()
 * \brief credits constructor (init credits ressources)
 * \return nothing
 **/

Credits::Credits()
{
	_initialPosY = 0;
	_initialPosX = (WINDOW_WIDTH / 2) - (WINDOW_WIDTH / 4);
	_toMove = 0;
	_timer = 0;
	_toDisplay = {
		"Yazid DJOUDAD", "Guillaume BARTHE", "Florian BORD",
		"Benjamin GRACIA", "Matthew LIVOTI", "David GOERIG"
	};
	_actualIt = _toDisplay.begin();
}

/**
 * \fn Credits::~Credits()
 * \brief credits destructor
 * \return nothing
 **/

Credits::~Credits() {}

/**
 * \fn actualState Credits::displayAll(std::shared_ptr<Graphical> Graphical)
 * \param std::shared_ptr<Graphical> Graphical: graphical object
 * \brief display the credits
 * \return actualState::CREDITS
 **/

actualState Credits::displayAll(std::shared_ptr<Graphical> Graphical)
{
	if (this->_timer >= 150)
		return actualState::MENU;
	if (!this->displayLbyL(Graphical)) {
		this->displayText(Graphical);
		this->_timer += 1;
	}
	return actualState::CREDITS;
}

/**
 * \fn bool Credits::displayLbyL(std::shared_ptr<Graphical)
 * \param std::shared_ptr<Graphical> Graphical: graphical object
 * \brief do the credits movement
 * \return true or false
 **/

bool Credits::displayLbyL(std::shared_ptr<Graphical> Graphical)
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
		this->_initialPosX += (WINDOW_WIDTH / _toDisplay.size() / 3);
		this->_toMove = 0;
	} else {
		this->_toMove += 10;
	}
	Graphical->drawText(*this->_actualIt, pos, true);
	return true;
}

/**
 * \fn Credits::displayText(std::shared_ptr<Graphical> Graphical)
 * \param std::shared_ptr<Graphical> Graphical: graphical object
 * \brief draw the text
 * \return nothing
 **/

void Credits::displayText(std::shared_ptr<Graphical> Graphical)
{
	std::string toDisplay = "CPP TEK 2\nINDIE STUDIO";
	int pos[4] = {
		(WINDOW_WIDTH / 2) - (WINDOW_WIDTH / 16),
		(WINDOW_HEIGHT / 2) - (WINDOW_HEIGHT / 4),
		(WINDOW_WIDTH / 2) - (WINDOW_WIDTH / 16),
		(WINDOW_HEIGHT / 2) - (WINDOW_HEIGHT / 4)
	};
	Graphical->drawText(toDisplay, pos, true);
}

void Credits::displayPic()
{}
