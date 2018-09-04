/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** PARAM_HPP_
*/

#ifndef PARAM_HPP_
	#define PARAM_HPP_

#include "Graphical.hpp"
#include "Button.hpp"

class Param
{
public:
	Param();
	~Param();
	bool initButton();
	void initIntoButton();
	void initEquivAction();
	void initButtonLimits();
	void setButtonLimits(
		const std::string &nameButton, int lBottom, int lTop
	);
	void setIntoButton(
		const std::string &nameButton, int value
	);
	void setEquivButton(
		const std::string &nameButton,
		const std::string &equivButton
	);
	bool isRun() const;
	std::vector<Button> getButton() const;
	void drawParam(std::shared_ptr<Graphical> Graphical);
	void drawSideButton(std::shared_ptr<Graphical> Graphical);
	void drawNameButton(std::shared_ptr<Graphical> Graphical);
	void drawReturnButton(std::shared_ptr<Graphical> Graphical);
	std::string getFormatedStringButtonName(Button b1);
	actualState getClickButton(
		const int &clickX, const int &clickY, bool isClick);
	void newStateButton(Button b1);
	std::map<std::string, int> getParam() const;
private:
	std::vector<Button> _button;
	std::vector<std::string> _buttonName;
	std::map<std::string, int> _intoButton;
	std::map<std::string, std::string> _equivButton;
	std::map<std::string, std::pair<int, int>> _buttonLimits;
	std::shared_ptr<Button> _returnBtn;
};

#endif /* !PARAM_HPP_ */