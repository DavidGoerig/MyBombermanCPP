/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** GRAPHICAL_CPP_
*/

#include "Graphical.hpp"

/**
* \fn bool Graphical::Graphical()
* \brief constructor
* \return nothing
**/

Graphical::Graphical() {}

/**
* \fn bool Graphical::~Graphical()
* \brief destructor
* \return nothing
**/

Graphical::~Graphical() {}

/**
* \fn bool Graphical::initGraphical()
* \brief initalisation of graphics
* \return true or false
**/

bool Graphical::initGraphical()
{
	this->_event = GetEvent();
	this->_device = irr::createDevice(
			irr::video::EDT_OPENGL,
			irr::core::dimension2d<irr::u32>(WINDOW_WIDTH, WINDOW_HEIGHT),
			64, false, false, false, &this->_event);
	if (!this->_device)
		return false;
	this->_device->setWindowCaption(L"Bomberman");
	this->_video = this->_device->getVideoDriver();
	this->_scene = this->_device->getSceneManager();
	this->_gui = this->_device->getGUIEnvironment();
	this->_textFont = _gui->getFont(FONT_PATH);
	return true;
}

/**
* \fn void Graphical::initGraphical(const std::string &toDisplay,
* int pos[4], bool adapToTex))
* \param toDisplay: string to display
* \param pos: position
* \param adapToText: is to adapt or no
* \brief fucntion to drawing the good text
* \return nothing
**/

void Graphical::drawText(
	const std::string &toDisplay, int pos[4], bool adapToText)
{
	if (adapToText) {
		irr::core::dimension2d<irr::u32> lenTxt = this->_textFont->getDimension(
			S_TO_WS(toDisplay));
		pos[2] += (lenTxt.Width + 5);
		pos[3] += (lenTxt.Height + 5);
	}
	irr::gui::IGUIStaticText *toDraw = this->_gui->addStaticText(
		S_TO_WS(toDisplay),
		irr::core::rect<irr::s32>(
			pos[0], pos[1], pos[2], pos[3]),
		true, true, 0, -1, true
	);
	toDraw->setOverrideFont(this->_textFont);
}

/**
* \fn void Graphical::drawButton(const std::string &toDisplay,
* int pos[4]), const std::string &backPick)
* \param toDisplay: string to display
* \param pos: position
* \param backPick: back picture
* \brief fucntion to drawing the button
* \return nothing
**/

void Graphical::drawButton(
	const std::string &toDisplay,
	int pos[4],
	const std::string &backPic)
{
	irr::gui::IGUIButton *btn = this->_gui->addButton(
		irr::core::rect<irr::s32>(pos[0], pos[1], pos[2], pos[3]),
		0, -1, S_TO_WS(toDisplay)
	);
	btn->setOverrideFont(this->_textFont);
	if (!backPic.empty())
		btn->setImage(this->_video->getTexture(S_TO_WS(backPic)));
}

/**
* \fn void Graphical::drawMessageBox(const std::string &toDisplay,
* int pos[4]), int len[2])
* \param toDisplay: string to display
* \param pos: position
* \param len: lenght
* \brief fucntion to draw a messageBox
* \return nothing
**/

void Graphical::drawMessageBox(
	const std::string &toDisplay,
	int pos[2], int len[2])
{
	(void)toDisplay;
	(void)pos;
	(void)len;
}

/**
* \fn void Graphical::addCamera(const irr::core::vector3df &position,
* const irr::core::vector3df &lookat)
* \param const irr::core::vector3df &position: (x,y,z) position of the eye
* \param const irr::core::vector3df &lookat: (x,y,z) position of the point of view
* \brief add a camera
* \return nothing
**/

void Graphical::addCamera(
	const irr::core::vector3df &position,
	const irr::core::vector3df &lookat
)
{
	this->_scene->addCameraSceneNode(0, position, lookat);
}

/**
* \fn GetEvent Graphical::getEvent()
* \brief get the event
* \return GetEvent _event
**/

GetEvent Graphical::getEvent()
{
	return this->_event;
}

/**
* \fn void Graphical::drawGUI()
* \brief draw the gui
* \return nothing
**/

void Graphical::drawGUI()
{
	this->_gui->drawAll();
}

/**
* \fn void Graphical::drawScene()
* \brief drew the scene
* \return nothing
**/

void Graphical::drawScene()
{
	this->_scene->drawAll();
}

/**
* \fn void Graphical::start()
* \brief start the scene
* \return nothing
**/

void Graphical::start()
{
	this->_gui->clear();
	this->_video->beginScene(
		true, true, irr::video::SColor(255, 255, 255, 255)
	);
}

/**
* \fn void Graphical::end()
* \brief end the scene
* \return nothing
**/

void Graphical::end()
{
	this->_video->endScene();
}

/**
* \fn void Graphical::drawTexture(const std::string &picPath,
* int originpos[4]), int)
* \param toDisplay: string to display
* \param pos: position
* \param piclen: lenght
* \brief fucntion to drawing the Texture
* \return nothing
**/

void Graphical::drawTexture(
	const std::string &picPath, int origPos[2], int picLen[4])
{
	irr::video::ITexture *toDisplay =
	this->_video->getTexture(S_TO_WS(picPath));

	if (!toDisplay)
		return;
	this->_video->draw2DImage(
		toDisplay, irr::core::position2d<irr::s32>(origPos[0], origPos[1]),
		irr::core::rect<irr::s32>(picLen[0], picLen[1], picLen[2], picLen[3]),
		0, irr::video::SColor(255, 255, 255, 255), true
	);
}

/**
* \fn IrrlichtDevice *Graphical::getDevice()
* \brief get the device
* \return IrrlcihtDevice *_device
**/

irr::IrrlichtDevice *Graphical::getDevice()
{
	return this->_device;
}

/**
* \fn IVideoDriver *Graphical::getVideo()
* \brief get the video driver
* \return IVideodriver *_video
**/

irr::video::IVideoDriver *Graphical::getVideo()
{
	return this->_video;
}

/**
* \fn ISceneManager *Graphical::getScene()
* \brief get the scene
* \return ISceneManager *_scene
**/

irr::scene::ISceneManager *Graphical::getScene()
{
	return this->_scene;
}

/**
* \fn void Graphical::setCamera(float x, float y, float z)
* \param float x: position on x
* \param float y: position on y
* \param float z: position on z
* \brief set the camera position then add it
* \return nothing
**/

void Graphical::setCamera(float x, float y, float z)
{
	irr::core::vector3df pos = {x, 100 + y, z};
	irr::core::vector3df look = {x, 50 + y, z + 30};
	this->addCamera(pos, look);
}