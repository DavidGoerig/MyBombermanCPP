//
// EPITECH PROJECT, 2018
// Floor.hpp
// File description:
// Floor
//

#ifndef __FLOOR_HPP__
#define __FLOOR_HPP__

#include <map>
#include <memory>

#include "Cube.hpp"
#include "irrlicht.h"

class Floor
{
public:
	Floor(
		int height,
		int width,
		irr::scene::ISceneManager *manager,
		irr::video::IVideoDriver *driver
	);
	~Floor();
	int getHeight() const;
	int getWidth() const;
private:
	int _height;
	int _width;
	std::map<std::pair<int, int>, std::unique_ptr<Cube>> _map;
	irr::scene::ISceneManager *_manager;
	irr::scene::IMeshSceneNode *_ground;
	irr::video::IVideoDriver *_driver;
};

#endif
