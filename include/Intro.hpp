/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** INTRO_HPP_
*/

#ifndef INTRO_HPP_
	#define INTRO_HPP_

#define PERSO_PATH "introPerso.jpg"

#include "Graphical.hpp"

class Intro
{
public:
	Intro();
	~Intro();
	actualState displayAll(
		std::shared_ptr<Graphical> Graphical
	);
	bool displayLbyL(
		std::shared_ptr<Graphical> Graphical
	);
	void displayText(
		std::shared_ptr<Graphical> Graphical
	);
	void displayPic();
private:
	int _initialPosY;
	int _initialPosX;
	int _toMove;
	int _timer;
	std::vector<std::string> _toDisplay;
	std::vector<std::string>::iterator _actualIt;
};

#endif /* !INTRO_HPP_ */
