/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** IA_HPP_
*/

#ifndef IA_HPP_
	#define IA_HPP_

#include <vector>
#include <chrono>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

#include "Item.hpp"
#include "indieStudio.hpp"
#include "BombStandard.hpp"
#include "Graphical.hpp"
#include "Map.hpp"
#include "Collision.hpp"
#include "Song.hpp"

class IA
{
public:
	enum IaDir {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		LAST
	};
	IA(
		irr::scene::ISceneManager *smgr,
		irr::video::IVideoDriver *Driver,
		std::shared_ptr<Graphical> Graphical);
	~IA();
	void findSpawn(
		std::shared_ptr<Map> Map,
		std::shared_ptr<Collision> Collision);
	void moveIA(
		std::shared_ptr<Map> Map,
		std::shared_ptr<Collision> Collision);
	float getZ() const;
	float getX() const;
	std::pair<int, int> getIaNewPos(
	std::shared_ptr<Map> Map,
	std::shared_ptr<Collision> Collision);
	IaDir checkIfContinue(
	std::shared_ptr<Map> Map,
	std::shared_ptr<Collision> Collision);
	IaDir checkIfNotLast(
	std::shared_ptr<Map> Map,
	std::shared_ptr<Collision> Collision);
	void dropBomb(
	std::shared_ptr<Map> Map,
	std::shared_ptr<Collision> Collision);
	void timeToExplode(std::shared_ptr<Map> Map);
	void deleteBomb(std::shared_ptr<Map> Map);
	std::shared_ptr<IItem> getItem();
	void invExplodeBomb(
		int f, int s,
		std::shared_ptr<Map> Map);
	void setPPos(float a, float b);
	bool findPosNoSmash(
	std::shared_ptr<Map> Map,
	std::shared_ptr<Collision> Collision,
	std::pair<int, int> pos);
	bool nearPlayer();
	bool wallAround(
	std::shared_ptr<Map> Map,
	std::shared_ptr<Collision> Collision);
	std::string getPlayerDead() const;
	std::pair<int, int> BetterPosAround(
	std::shared_ptr<Map> Map,
	std::shared_ptr<Collision> Collision);
	float calcBombDirst(float _x, float _z);
private:
	float _x;
	float _z;
	std::string _playerDead;
	std::pair<int, int> _last;
	std::vector<float> _lpast;
	bool _isBomb;
	std::vector<std::shared_ptr<IItem>> _iaInv;
	irr::scene::IAnimatedMesh* _iaMesh;
	irr::scene::IAnimatedMeshSceneNode* _iaNode;
	std::shared_ptr<Graphical> _Graphical;
	IaDir _lastDir;
	std::vector<irr::scene::IAnimatedMeshSceneNode*> _bombList;
	std::vector<std::pair<int, int>> _bombPos;
	std::vector<std::chrono::high_resolution_clock::time_point> _bombTime;
	std::vector<std::chrono::high_resolution_clock::time_point>::iterator _bombTimeIt;
	std::pair<int, int> _ppos;

	std::vector<std::shared_ptr<IItem>> _inv;
	std::vector<std::pair<int, int>>::iterator _bombPosIt;
	std::vector<irr::scene::IAnimatedMeshSceneNode*>::iterator _actualIt;
	Song _doSong;
	std::vector<std::pair<int, int>> _playerPos;
};

#endif /* !IA_HPP_ */
