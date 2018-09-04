//
// EPITECH PROJECT, 2018
// Cube.hpp
// File description:
// Cube
//

#ifndef __CUBE_HPP__
#define __CUBE_HPP__

#include <iostream>
#include <map>

#include "irrlicht.h"

class Cube {
public:
	enum TypeBox {
		NORMAL,
		BORDER,
		SPEED,
		RANGE,
		BOMB,
		NOBOX,
		FLOOR
	};
	Cube(
		int width,
		int height,
		irr::scene::ISceneManager *manager,
		irr::video::IVideoDriver *driver,
		bool destructable,
		TypeBox type
	);
	~Cube();
	int getposx() const;
	int getposy() const;
	irr::scene::IMeshSceneNode *getMesh() const;
	bool isDestruct() const;
	void setDestruct();
	bool isDestructable() const;
	Cube::TypeBox getCubeType() const;
private:
	int _width;
	int _heigth;
	bool _isDestruct;
	bool _isDestructable;
	TypeBox	_type;
	irr::scene::IMeshSceneNode *_cube;
	irr::video::IVideoDriver *_driver;
	irr::scene::ISceneManager *_manager;
	std::map<TypeBox, std::string> _m;
};

#endif
