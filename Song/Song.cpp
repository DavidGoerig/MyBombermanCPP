//
// EPITECH PROJECT, 2018
// Indiestudio
// File description: Handling the sound
//
//

#include "Song.hpp"

/**
* \fn Song::Song()
* \brief: constructor of Song
* \return void
**/

Song::Song() {}

/**
* \fn Song::Song()
* \brief: destructor of Song
* \return void
**/

Song::~Song() {}

/**
* \fn void Song::playShortSong(const char *song)
* \param song: name of song
* \brief creating a engine and playing a bref song one time
* \return void
**/

void Song::playShortSong(const char *song)
{
	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
	engine->play2D(song);
}

/**
* \fn void Song::playLongSong(const char *song)
* \param song: name of song
* \brief creating the Engine and play song while the fn stop long
* song is not called
* \return void
**/

void Song::playLongSong(const char *song)
{
	this->_longEngine = irrklang::createIrrKlangDevice();
	this->_longMusic = _longEngine->play2D(song, true);
}

/**
* \fn void Song::stopLongSong()
* \brief destroying the engine and stoping a long song like menu
* or the song of the game
* \return void
**/

void Song::stopLongSong()
{
	this->_longEngine->drop();
}
