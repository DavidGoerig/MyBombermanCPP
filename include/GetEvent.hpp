/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** GETEVENT_HPP_
*/

#ifndef GETEVENT_HPP_
	#define GETEVENT_HPP_

#include "indieStudio.hpp"

class GetEvent: public irr::IEventReceiver
{
public:
	GetEvent();
	~GetEvent();
	bool OnEvent(const irr::SEvent& event);
	bool isLeftClick() const;
	bool isRightClick() const;
	irr::core::position2di getMousePos() const;
	bool isKeyPressed(int keyNum) const;
private:
	irr::core::position2di _mousePos;
	bool _leftClick;
	bool _rightClick;
	int _timer;
	bool _keyPressed[irr::KEY_KEY_CODES_COUNT];
};

#endif /* !GETEVENT_HPP_ */
