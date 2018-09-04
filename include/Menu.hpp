/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** MENU_HPP_
*/

#ifndef MENU_HPP_
	#define MENU_HPP_

#include "Graphical.hpp"
#include "Button.hpp"

#define FONT_MENU "./Ressource/disp.png"

class Menu
{
public:
	Menu();
	~Menu();
	bool initButton();
	void initEquivAction();
	void setEquivAction(
		const std::string &nameAction, actualState myAction);
	actualState getClickButton(
		const int &clickX, const int &clickY, bool isClick);
	bool isRun() const;
	std::vector<Button> getButton() const;
	void drawMenu(std::shared_ptr<Graphical> Graphical);
	void setMultiplayer(bool multi);
	void setGame(bool game);
private:
	bool _run;
	bool _multiplayer;
	bool _game;
	std::vector<Button> _button;
	std::vector<std::string> _buttonName;
	std::map<std::string, actualState> _equivAction;
};

#endif /* !MENU_HPP_ */
