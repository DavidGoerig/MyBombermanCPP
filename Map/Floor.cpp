//
// EPITECH PROJECT, 2018
// Floor.cpp
// File description:
// Floor
//

#include "Floor.hpp"

/**
 * \fn Floor::Floor(int height, int width, irr::scene::IsceneManager *manager,
 * irr::video::IVideoDriver *driver)
 * \param height: height of the floor
 * \param width: width of the floor
 * \param manager: manager of the Scene
 * \param driver: vidéo handling
 * \brief Construction of the map floor.
 * \return nothing
 **/

Floor::Floor(
	int height,
	int width,
	irr::scene::ISceneManager *manager,
	irr::video::IVideoDriver *driver)
{
	_height = height;
	_width = width;
	_manager = manager;
	_driver = driver;

	for (int y = 0; y <= _height - 1; y++) {
		for (int x = 0; x <= _width; x++) {
			std::pair<int, int> pos;
			pos.first = x;
			pos.second = y;
			_map.insert(std::make_pair(pos,
			std::unique_ptr<Cube>(new Cube(
			x, y, _manager, _driver, true, Cube::TypeBox::FLOOR))
			));
		}
	}
}

/**
 * \fn Floor::~Floor() const
 * \brief destructor
 * \return nothing
 **/

Floor::~Floor() {}

/**
 * \fn Floor::getHeight() const
 * \brief get the width of the floor
 * \return int _height
 **/

int Floor::getHeight() const
{
	return this->_height;
}

/**
 * \fn Floor::getWidth() const
 * \brief get the width of the floor
 * \return int _width
 **/

int Floor::getWidth() const
{
	return this->_width;
}