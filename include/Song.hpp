//
// EPITECH PROJECT, 2018
// yazid
// File description:
//
//

#ifndef SONG_HPP
#define SONG_HPP

#include "irrKlang.h"
#include "indieStudio.hpp"

class Song
{
public:
	Song();
	~Song();
	void playShortSong(const char *song);
	void playLongSong(const char *song);
	void stopLongSong();
private:
	irrklang::ISoundEngine*	_longEngine;
	irrklang::ISound*	_longMusic;
};

#endif /* SONG_HPP */
