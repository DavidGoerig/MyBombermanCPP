//
// EPITECH PROJECT, 2018
// Cube.cpp
// File description:
// create_cube
//

#include "Cube.hpp"

/**
 * \fn Cube::Cube(int height, int width, irr::scene::IsceneManager *manager,
 * irr::video::IVideoDriver *driver, bool destructable, TypeBox type)
 * \param height: height of the cube
 * \param width: width of the cube
 * \param manager: manager of the Scene
 * \param driver: vidéo handling
 * \param destructable: Cube destructable or no
 * \param TypeBox: the type of box
 * \brief Construction of the object cube.
 * \return nothing
 **/

Cube::Cube(
	int width,
	int height,
	irr::scene::ISceneManager *manager,
	irr::video::IVideoDriver *driver,
	bool destructable,
	TypeBox type)
{
	_m = {
		{NORMAL, "./Ressource/normal.png"},
		{BORDER, "./Ressource/border.bmp"},
		{SPEED, "./Ressource/speed.jpg"},
		{RANGE, "./Ressource/range.jpg"},
		{BOMB, "./Ressource/bomb.jpg"},
		{NOBOX, "./Ressource/violet.bmp"},
		{FLOOR, "./Ressource/floor.jpg"},
	};
	auto search = _m.find(type);
	irr::core::vector3df pos(10.0f * width, 0.0f, 10.0f * height);

	if (type == FLOOR)
		pos.Y = -10.0f;
	_type = type;
	if (_type == NORMAL)
		_isDestructable = false;
	else
		_isDestructable = destructable;
	_isDestruct = false;
	_manager = manager;
	_cube = _manager->addCubeSceneNode(10.0f, 0, -1, pos);
	_driver = driver;
	_cube->setMaterialTexture(
		0,
		_driver->getTexture(
			search->second.c_str()
		)
	);
	_cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_cube->getMaterial(0).Shininess = 20.0f;
	_heigth = height;
	_width = width;
}

/**
 * \fn Cube::~Cube()
 * \brief destruction of the cube object.
 * \return nothing
 **/

Cube::~Cube() {}

/**
 * \fn int Cube::getposx()
 * \brief get x pos.
 * \return int _width
 **/

int Cube::getposx() const
{
	return _width;
}

/**
 * \fn int Cube::getposy()
 * \brief get y pos.
 * \return int _height
 **/

int Cube::getposy() const
{
	return _heigth;
}

/**
 * \fn irr::scene::IMeshSceneNode *Cube::getMesh() const
 * \brief get the mesh
 * \return irr::scene::IMeshSceneNode *_cube
 **/

irr::scene::IMeshSceneNode *Cube::getMesh() const
{
	return _cube;
}

/**
 * \fn bool Cube::isDestruct() const
 * \brief know if the block is detroyed
 * \return true or false
 **/

bool Cube::isDestruct() const
{
	return _isDestruct;
}

/**
 * \fn Cube::TypeBox Cube::getCubeType() const
 * \brief get the cube type
 * \return Cube::TypeBox _type
 **/

Cube::TypeBox Cube::getCubeType() const
{
	return this->_type;
}

/**
 * \fn void Cube::setDestruct()
 * \brief destroy box
 * \return nothing
 **/

void Cube::setDestruct()
{
	this->_isDestruct = true;
	if (!this->_cube)
		return;
	this->_cube->remove();
}

/**
 * \fn bool Cube::isDestructable() const
 * \brief know if i can destroy a block
 * \return true or false
 **/

bool Cube::isDestructable() const
{
	return this->_isDestructable;
}
