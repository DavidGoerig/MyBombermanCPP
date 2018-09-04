/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** timer
*/

#include "timer.hpp"

int Timer::bombTimer(int sec)
{
	this->_startBomb = std::chrono::high_resolution_clock::now();
	while (1) {
		this->_endBomb = std::chrono::high_resolution_clock::now();
		this->_elapsed = (this->_endBomb - this->_startBomb);
		if (this->_elapsed.count() >= (sec * 1000)) {
			return (this->_elapsed.count());
		}
	}
}

void Timer::stopClock()
{
	this->_end = std::chrono::system_clock::now();
    	this->_elapsedTotal = std::chrono::duration_cast<std::chrono::seconds>
                             (this->_end-this->_start).count();
    	std::time_t end_time = std::chrono::system_clock::to_time_t(this->_end);
}

void Timer::startClock()
{
	this->_start = std::chrono::system_clock::now();
}

Timer::Timer() {}

Timer::~Timer() {}