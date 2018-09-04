/*
** EPITECH PROJECT, 2018
** INDIE_STUDIO
** File description:
** MAIN_CPP_
*/

#include "StudioCore.hpp"

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	StudioCore indie;
	indie.initCore();
	indie.runCore();
	return 0;
}