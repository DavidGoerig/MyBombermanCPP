/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** GRAPHICAL_HPP_
*/

#ifndef GRAPHICAL_HPP_
	#define GRAPHICAL_HPP_

#include "indieStudio.hpp"
#include "GetEvent.hpp"

#define FONT_PATH "./Ressource/bigfont.png"
#define FTB "./Ressource/ftbW.png"

#define S_TO_WS(path) std::wstring(path.begin(), path.end()).c_str()

class Graphical
{
public:
	Graphical();
	~Graphical();
	bool initGraphical();
	void drawText(
		const std::string &toDisplay,
		int pos[4], bool adapToText);
	void addCamera(
		const irr::core::vector3df &position,
		const irr::core::vector3df &lookat);
	void drawButton(
		const std::string &toDisplay,
		int pos[4],
		const std::string &backPic);
	void drawMessageBox(
		const std::string &toDisplay,
		int pos[2], int len[2]);
	void drawTexture(
		const std::string &picPath,
		int origPos[2], int picLen[4]);
	void start();
	void end();
	void drawGUI();
	void drawScene();
	irr::core::position2di getMousePos();
	GetEvent getEvent();
	irr::scene::ISceneManager *getScene();
	irr::video::IVideoDriver *getVideo();
	irr::IrrlichtDevice *getDevice();
	bool isRightClick();
	bool isLeftClick();
	void initCamera();
	void setCamera(float x, float y, float z);
private:
	irr::IrrlichtDevice *_device;
	irr::video::IVideoDriver *_video;
	irr::scene::ISceneManager *_scene;
	irr::gui::IGUIEnvironment *_gui;
	GetEvent _event;
	irr::gui::IGUIFont *_textFont;
};

#endif /* !GRAPHICAL_HPP_ */
