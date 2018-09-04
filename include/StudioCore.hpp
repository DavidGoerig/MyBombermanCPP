/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** STUDIOCORE_HPP_
*/

#ifndef STUDIOCORE_HPP_
	#define STUDIOCORE_HPP_

#define MULTI_P 2

#include <thread>
#include <chrono>

#include "Graphical.hpp"
#include "Menu.hpp"
#include "Intro.hpp"
#include "Credits.hpp"
#include "Param.hpp"
#include "Map.hpp"
#include "Collision.hpp"
#include "Bomberman.hpp"
#include "Song.hpp"
#include "IA.hpp"

class StudioCore
{
public:
	StudioCore();
	~StudioCore();
	void runCore();
	bool initCore();
	bool initSelectState();
	void computeMapParam();
	void initBomberman();
	void initMultiplayerBomberman();
	void runDifferentCases();
	void runMenu();
	void runCredits();
	void runParam();
	void runGame();
	void runMultiplayerGame();
	void runIntro();
	void runNewGame();
	void runDeath();
private:
	std::shared_ptr<Graphical> _Graphical;
	std::shared_ptr<Map> _Map;
	std::shared_ptr<Bomberman> _Game;
	std::shared_ptr<IA> _IA;
	std::shared_ptr<Bomberman> _SGame;
	std::shared_ptr<Menu> _Menu;
	std::unique_ptr<Intro> _Intro;
	std::unique_ptr<Credits> _Credits;
	std::unique_ptr<Param> _Param;
	std::unique_ptr<Song> _Song;
	std::map<actualState, std::function<void(void)>> _selectState;
	std::shared_ptr<Collision> _Collision;
	std::string _lost;
	actualState _loopState;
	bool _mapInit;
	bool _multiplayer;
	bool _menuSong;
	bool _gameSong;
};

#endif /* !STUDIOCORE_HPP_ */
