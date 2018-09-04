/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** GETEVENT_CPP_
*/

#include "GetEvent.hpp"

/**
* \fn GetEvent::GetEvent()
* \brief constructor (init event values)
* \return nothing
**/

GetEvent::GetEvent()
{
	_leftClick = false;
	_rightClick = false;
	_mousePos.X = 0;
	_mousePos.Y = 0;
	_timer = 0;
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; i++) {
		_keyPressed[i] = false;
	}
}

/**
* \fn GetEvent::GetEvent()
* \brief destructor
* \return nothing
**/

GetEvent::~GetEvent() {}

/**
* \fn GetEvent::OnEvent(const SEvent& event)
* \param event: Handle event
* \brief getting the event clicked
* and the mouse position
* \return true or false
**/

bool GetEvent::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		switch (event.MouseInput.Event) {
			case irr::EMIE_LMOUSE_PRESSED_DOWN:
				this->_leftClick = true;
				break;

			case irr::EMIE_LMOUSE_LEFT_UP:
				this->_leftClick = false;
				break;

			case irr::EMIE_RMOUSE_PRESSED_DOWN:
				this->_rightClick = true;
				break;

			case irr::EMIE_RMOUSE_LEFT_UP:
				this->_rightClick = false;
				break;

			case irr::EMIE_MOUSE_MOVED:
		                this->_mousePos.X = event.MouseInput.X;
                		this->_mousePos.Y = event.MouseInput.Y;
				break;

			default:
				break;
		}
		return true;
	}
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		this->_keyPressed[event.KeyInput.Key]
		= event.KeyInput.PressedDown;
		return true;
	}
	return false;
}

/**
* \fn GetEvent::isLeftClick() const
* \brief catch left click
* \return nothing
**/

bool GetEvent::isLeftClick() const
{
	return this->_leftClick;
}

/**
* \fn GetEvent::isRightClick() const
* \brief catch right click
* \return nothing
**/

bool GetEvent::isRightClick() const
{
	return this->_rightClick;
}

/**
* \fn position2di GetEvent::getMousePos() const
* \brief get the mouse position
* \return position2di _mousePos
**/

irr::core::position2di GetEvent::getMousePos() const
{
	return this->_mousePos;
}

/**
* \fn bool GetEvent::isKeyPressed(int keyNum) const
* \brief know if a key is pressed
* \return true or false
**/

bool GetEvent::isKeyPressed(int keyNum) const
{
	return this->_keyPressed[keyNum];
}
