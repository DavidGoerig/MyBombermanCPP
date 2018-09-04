/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** BOMBERMAN_HPP_
*/

#ifndef BOMBERMAN_HPP_
	#define BOMBERMAN_HPP_

#include <vector>
#include <chrono>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "Item.hpp"
#include "BombStandard.hpp"
#include "indieStudio.hpp"
#include "Graphical.hpp"
#include "Map.hpp"
#include "Collision.hpp"
#include "Song.hpp"
#include "IA.hpp"

#define MAXBOMB 3

class Bomberman
{
public:
	Bomberman(bool firstPlayer, bool ia, int maxBomb);
	~Bomberman();
	bool isRunning() const;
	std::shared_ptr<IItem> getItem();
	void setItem(enum Item);
	int initBomberman(
		irr::scene::ISceneManager *smgr,
		irr::video::IVideoDriver *Driver,
		std::shared_ptr<Graphical> Graphical);
	void moveBomberman(
		std::shared_ptr<Map> Map,
		std::shared_ptr<Collision> Collision);
	void timeToExplode(std::shared_ptr<Map> Map);
	void deleteBomb(std::shared_ptr<Map> Map);
	void invExplodeBomb(
		int f, int s,
		std::shared_ptr<Map> Map);
	void findSpawn(
		std::shared_ptr<Map> Map,
		std::shared_ptr<Collision> Collision);
	float getZ() const;
	float getX() const;
	void setKeyMove(int key, int x, int z);
	void initKeyMove();
	void realizeDeplacement();
	void dropBomb();
	void setMulti();
	void setEnemy(std::shared_ptr<Bomberman> enemy);
	void setEnemy(std::shared_ptr<IA> ia);
	std::string getPlayerDead() const;
	void addBonus(std::shared_ptr<Map> Map);
private:
	bool _ia;
	bool _alreadyPressed;
	bool _firstPlayer;
	bool _multi;
	bool _run;
	float _x;
	float _z;
	float _x_ia;
	float _z_ia;
	int _maxBomb;
	int _maxBombRet;
	int _nbBomb;
	Song _doSong;
	std::string _playerDead;
	irr::scene::ISceneManager *_scene;
	irr::video::IVideoDriver *_driver;
	std::shared_ptr<Graphical> _Graphical;
	std::shared_ptr<Bomberman> _enemy;
	std::shared_ptr<IA> _iaEnnemy;
	std::shared_ptr<IItem> _item;
	std::vector<std::shared_ptr<IItem>> _inv;
	std::vector<std::chrono::high_resolution_clock::time_point> _bombTime;
	std::vector<std::chrono::high_resolution_clock::time_point>::iterator _bombTimeIt;
	std::vector<irr::scene::IAnimatedMeshSceneNode*> _bombList;
	std::vector<int> _listDepla;
	std::vector<std::pair<int, int>> _bombPos;
	std::vector<std::pair<int, int>>::iterator _bombPosIt;
	std::vector<irr::scene::IAnimatedMeshSceneNode*>::iterator _actualIt;
	std::map<std::pair<int,int>, int> _keyMove;
	irr::scene::IAnimatedMesh* _bombermanMesh;
	irr::scene::IAnimatedMeshSceneNode* _bombermanNode;
	irr::scene::IAnimatedMeshSceneNode* _bombermanNodeIA;
	irr::scene::IAnimatedMeshSceneNode* _node;
	std::vector<std::pair<int, int>> _playerPos;
};

#endif /* !BOMBERMAN_HPP_ */
