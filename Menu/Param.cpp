/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** PARAM_CPP_
*/

#include "Param.hpp"

/**
* \fn Param::Param()
* \brief building of all parameters
* \return nothing
**/

Param::Param()
{
	_buttonName = {
		"SPEED_LESS",
		"SPEED_MORE",
		"RANGE_LESS",
		"RANGE_MORE",
		"NBOMB_LESS",
		"NBOMB_MORE",
		"BOOST_LESS",
		"BOOST_MORE",
		"FILL_LESS",
		"FILL_MORE",
		"WIDTH_LESS",
		"WIDTH_MORE",
		"HEIGHT_LESS",
		"HEIGHT_MORE"
	};
}

/**
* \fn Param::~Param()
* \brief destructor of Param
* \return nothing
**/

Param::~Param() {}

/**
* \fn bool Param::initButton()
* \brief initialization of all buttons in param
* \return true or false
**/

bool Param::initButton()
{
	std::vector<std::string>::iterator itNameButton =
	this->_buttonName.begin();
	int pos[2] = {
		(WINDOW_WIDTH / 2),
		(WINDOW_HEIGHT / static_cast<int>(this->_buttonName.size()))
	};
	int len[2] = {
		(WINDOW_WIDTH / static_cast<int>(this->_buttonName.size())),
		(WINDOW_HEIGHT / static_cast<int>(this->_buttonName.size()) / 2)
	};

	for (; itNameButton != this->_buttonName.end(); itNameButton++) {
		if ((*itNameButton).find("LESS") != std::string::npos) {
			pos[0] -= (WINDOW_WIDTH / 4);
			Button b1(pos, len, *itNameButton, -1);
			this->_button.push_back(b1);
			pos[0] += (WINDOW_WIDTH / 4);
		} else {
			pos[0] += (WINDOW_WIDTH / 4);
			Button b1(pos, len, *itNameButton, 1);
			this->_button.push_back(b1);
			pos[1] += (len[1] * 3);
			pos[0] -= (WINDOW_WIDTH / 4);
		}
	}
	pos[0] -= (WINDOW_WIDTH / 4);
	len[0] = (2 * (WINDOW_WIDTH / 4))
	+ (WINDOW_WIDTH / static_cast<int>(this->_buttonName.size()));
	len[1] *= 2;
	_returnBtn = std::shared_ptr<Button>(
		new Button(pos, len, "Return", 0)
	);
	return true;
}

/**
* \fn void Param::initIntoButton()
* \brief initalize the value of paramaters into their buttons
* \return void
**/

void Param::initIntoButton()
{
	this->setIntoButton("BOOST", 50);
	this->setIntoButton("FILL", 50);
	this->setIntoButton("WIDTH", 30);
	this->setIntoButton("HEIGHT", 30);
	this->setIntoButton("SPEED", 3);
	this->setIntoButton("RANGE", 3);
	this->setIntoButton("NBOMB", 3);
}

/**
* \fn void Param::setIntoButton()
* \brief assign a string to an enumeration
* \return void
**/

void Param::setIntoButton(
	const std::string &nameAction, int value)
{
	this->_intoButton[nameAction] = value;
}

/**
* \fn void Param::initEquivAction()
* \brief initialization of events with button into parameter
* \return void
**/

void Param::initEquivAction()
{
	this->setEquivButton("BOOST_LESS", "BOOST");
	this->setEquivButton("BOOST_MORE", "BOOST");
	this->setEquivButton("FILL_LESS", "FILL");
	this->setEquivButton("FILL_MORE", "FILL");
	this->setEquivButton("WIDTH_LESS", "WIDTH");
	this->setEquivButton("WIDTH_MORE", "WIDTH");
	this->setEquivButton("HEIGHT_LESS", "HEIGHT");
	this->setEquivButton("HEIGHT_MORE", "HEIGHT");
	this->setEquivButton("SPEED_LESS", "SPEED");
	this->setEquivButton("SPEED_MORE", "SPEED");
	this->setEquivButton("RANGE_LESS", "RANGE");
	this->setEquivButton("RANGE_MORE", "RANGE");
	this->setEquivButton("NBOMB_LESS", "NBOMB");
	this->setEquivButton("NBOMB_MORE", "NBOMB");
}

/**
* \fn void Param::setEquivAction(const std::string &nameButton,
* const std::string &equivbutton)
* \param std::string &namebutton: button name
* \param std::string &equivbutton button equiv
* \brief selection of the good parameter to modfify
* \return void
**/

void Param::setEquivButton(
		const std::string &nameButton,
		const std::string &equivButton)
{
	this->_equivButton[nameButton] = equivButton;
}

/**
* \fn std::vector<Button> Param::getButton()
* \brief get the button
* \return void
**/

std::vector<Button> Param::getButton() const
{
	return this->_button;
}

/**
* \fn void Param::drawReturnButton(std::shared_ptr<Graphical> Graphical)
* \param Graphical: handle the graphics to display
* \brief draw the button return
* \return void
**/

void Param::drawReturnButton(std::shared_ptr<Graphical> Graphical)
{
	int pos[4] = {0, 0, 0, 0};

	pos[0] = this->_returnBtn->getPosX();
	pos[1] = this->_returnBtn->getPosY();
	pos[2] = pos[0] + this->_returnBtn->getLenX();
	pos[3] = pos[1] + this->_returnBtn->getLenY();

	Graphical->drawButton(
		this->_returnBtn->getName(),
		pos, "");
}

/**
* \fn void Param::drawParam(std::shared_ptr<Graphical> Graphical)
* \param std::shared_ptr<Graphical> Graphical: handle the graphical side
* \brief draw parameters
* \return void
**/

void Param::drawParam(std::shared_ptr<Graphical> Graphical)
{
	this->drawSideButton(Graphical);
	this->drawNameButton(Graphical);
	this->drawReturnButton(Graphical);
}

/**
* \fn void Param::drawSideButton(std::shared_ptr<Graphical> Graphical)
* \param Graphical: handle the graphics to display
* \brief draw + or -
* \return void
**/

void Param::drawSideButton(std::shared_ptr<Graphical> Graphical)
{
	std::vector<Button>::iterator itButton = this->_button.begin();
	int pos[4] = {0, 0, 0, 0};
	std::string bName = "-";

	for (; itButton != this->_button.end(); itButton++) {
		pos[0] = itButton->getPosX();
		pos[1] = itButton->getPosY();
		pos[2] = pos[0] + itButton->getLenX();
		pos[3] = pos[1] + itButton->getLenY();
		bName = (itButton->getName().find("LESS")
		!= std::string::npos) ? "-" : "+";
		Graphical->drawButton(
			bName,
			pos, ""
		);
	}
}

/**
* \fn std::string Param::getFormatedStringButtonName(Button b1)
* \param b1: Button type
* \brief get a formatted string of button name
* \return std::string fButtonString
**/

std::string Param::getFormatedStringButtonName(Button b1)
{
	std::string fButtonString = this->_equivButton[b1.getName()]
	+ " "
	+ std::to_string(this->_intoButton[this->_equivButton[b1.getName()]]);
	return fButtonString;
}

/**
* \fn void Param::drawNameButton(std::shared_ptr<Graphical> Graphical)
* \param Graphical: handle the graphics to display
* \brief draw a name button
* \return nothing
**/

void Param::drawNameButton(std::shared_ptr<Graphical> Graphical)
{
	std::vector<Button>::iterator itButton = this->_button.begin();
	int pos[4] = {0, 0, 0, 0};
	std::string bName = "-";

	for (; itButton != this->_button.end(); itButton++) {
		pos[0] = (WINDOW_WIDTH / 2);
		pos[1] = itButton->getPosY();
		pos[2] = (WINDOW_WIDTH / 2);
		pos[3] = itButton->getPosY();
		if (itButton->getName().find("LESS") != std::string::npos)
			Graphical->drawText(
				this->getFormatedStringButtonName(*itButton),
				pos, true
			);
	}
}

/**
* \fn void Param::newStateButton(Button b1)
* \param b1: Button type
* \brief give the new state of button
* \return void
**/

void Param::newStateButton(Button b1)
{
	std::string buttonName = this->_equivButton[b1.getName()];
	int bValue = this->_intoButton[buttonName];

	if (b1.getName().find("LESS") != std::string::npos) {
		if (bValue > this->_buttonLimits[buttonName].first)
			this->_intoButton[buttonName] -= 1;
	} else {
		if (bValue < this->_buttonLimits[buttonName].second)
			this->_intoButton[buttonName] += 1;
	}
}

/**
* \fn actualState Param::getClickButton(const int &clickX,
* const int &clickY, bool isClick)
* \param clickX: position X of click
* \param clickY: position X of click
* \param isClick: is it clicked or no
* \brief get the button clicked and and check what state we are
* \return actualState
**/

actualState Param::getClickButton(
	const int &clickX, const int &clickY, bool isClick)
{
	std::vector<Button>::iterator itButton = this->_button.begin();

	for (; itButton != this->_button.end(); itButton++) {
		if (itButton->isClick(clickX, clickY) && isClick) {
			this->newStateButton(*itButton);
		}
	}
	if (this->_returnBtn->isClick(clickX, clickY) && isClick)
		return actualState::MENU;
	return actualState::PARAM;
}

/**
* \fn void Param::initButtonLimits()
* \brief init the
* limits of button with setters
* \return nothing
**/

void Param::initButtonLimits()
{
	this->setButtonLimits("BOOST", 0, 100);
	this->setButtonLimits("FILL", 0, 100);
	this->setButtonLimits("WIDTH", 10, 80);
	this->setButtonLimits("HEIGHT", 10, 80);
	this->setButtonLimits("SPEED", 0, 5);
	this->setButtonLimits("RANGE", 0, 5);
	this->setButtonLimits("NBOMB", 0, 5);
}

/**
* \fn void Param::setButtonLimits(const std::string &nameButton, int lBottom, int lTop)
* \param const::std::string &nameButton: button name
* \param int lBottom: bottom limit
* \param int lTop: top limit
* \brief set the buttons limit
* \return void
**/

void Param::setButtonLimits(
	const std::string &nameButton, int lBottom, int lTop)
{
	std::pair<int, int> toAdd = {lBottom, lTop};

	this->_buttonLimits[nameButton] = toAdd;
}

/**
* \fn std::map<std::string, int> Param::getParam() const
* \brief get param
* \return std::map<std::string, int> _intoButton
**/

std::map<std::string, int> Param::getParam() const
{
	return this->_intoButton;
}
