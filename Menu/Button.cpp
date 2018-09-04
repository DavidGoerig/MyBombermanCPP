/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** BUTTON_CPP_
*/

#include "Button.hpp"

/**
* \fn Button::Button(const int pos[2], const len[2],
* const std::string &name, int value)
* \param pos[2]: pos x and y
* \param len[2]: len x and y
* \param &name: name of button
* \param value: value of button
* \brief constructor of the object button
* \return nothing
**/

Button::Button(
	const int pos[2],
	const int len[2],
	const std::string &name,
	int value
)
{
	_name = name;
	_lenX = len[0];
	_lenY = len[1];
	_posX = pos[0];
	_posY = pos[1];
	_value = value;
}

/**
* \fn Button::~Button()
* \brief destructor of the object button
* \return nothing
**/

Button::~Button() {}

/**
* \fn boll Button::isClikc(int clickX, int clickY) const
* \param clickX: position X of click
* \param clickY: position Y of click
* \brief check where is the click
* \return true or false
**/

bool Button::isClick(int clickX, int clickY) const
{
	if (clickX <= (this->_posX + this->_lenX)
	&& clickX >= (this->_posX)
	&& clickY <= (this->_posY + this->_lenY)
	&& clickY >= (this->_posY))
		return true;
	return false;
}

/**
* \fn std::string Button::getName()
* \brief get the button name
* \return std::string _name
**/

std::string Button::getName() const
{
	return this->_name;
}

/**
* \fn int Button::getLenX() const
* \brief get the x len
* \return int _lenX
**/

int Button::getLenX() const
{
	return this->_lenX;
}

/**
* \fn int Button::getLenY() const
* \brief get the y len
* \return int _lenY
**/

int Button::getLenY() const
{
	return this->_lenY;
}

/**
* \fn int Button::getPosX() const
* \brief get the x pos
* \return int _posX
**/

int Button::getPosX() const
{
	return this->_posX;
}

/**
* \fn int Button::getPosY() const
* \brief get the y pos
* \return int _posY
**/

int Button::getPosY() const
{
	return this->_posY;
}