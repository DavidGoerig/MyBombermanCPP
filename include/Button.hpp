/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** BUTTON_HPP_
*/

#ifndef BUTTON_HPP_
	#define BUTTON_HPP_

#include <string>
#include <iostream>

class Button
{
public:
	Button(
		const int pos[2],
		const int len[2],
		const std::string &name,
		int value
	);
	~Button();
	bool isClick(int clickX, int clickY) const;
	std::string getName() const;
	int getLenX() const;
	int getLenY() const;
	int getPosX() const;
	int getPosY() const;
private:
	int _lenX;
	int _lenY;
	int _posX;
	int _posY;
	int _value;
	std::string _name;
};

#endif /* !BUTTON_HPP_ */
