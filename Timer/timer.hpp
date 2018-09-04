/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** timer
*/

#ifndef TIMER_HPP_
	#define TIMER_HPP_

#include <iostream>
#include <cstdio>
#include <ctime>
#include <chrono>
#include <unistd.h>

class Timer
{
public:
	Timer();
	~Timer();
	void startClock();
	void stopClock();
	int bombTimer(int);
private:
	std::chrono::time_point<std::chrono::system_clock> _start;
	std::chrono::time_point<std::chrono::system_clock> _end;
	int _elapsedTotal;
	std::chrono::duration<double, std::milli> _elapsed;
	std::chrono::high_resolution_clock::time_point _startBomb;
	std::chrono::high_resolution_clock::time_point _endBomb;
};

#endif /* !TIMER_HPP_ */
