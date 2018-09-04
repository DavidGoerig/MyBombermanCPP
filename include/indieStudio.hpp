/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** INDIE_STUDIO_HPP_
*/

#ifndef INDIE_STUDIO_HPP_
	#define INDIE_STUDIO_HPP_

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#include <iostream>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <vector>
#include <map>
#include <functional>

#include "irrlicht.h"

enum actualState {
	INTRO,
	MENU,
	GAME,
	CREDITS,
	PARAM,
	EXIT,
	MULTIPLAYER,
	NEWGAME,
	DEATH
};

#endif /* !INDIE_STUDIO_HPP_ */