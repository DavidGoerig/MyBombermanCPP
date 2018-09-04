//
// EPITECH PROJECT, 2018
// Credits.hpp
// File description:
// Credits
//

#ifndef CREDITS_HPP_
        #define CREDITS_HPP_

#define PERSO_PATH "introPerso.jpg"

#include "Graphical.hpp"

class Credits
{
public:
	Credits();
	~Credits();
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

#endif /* !CREDITS_HPP_ */
