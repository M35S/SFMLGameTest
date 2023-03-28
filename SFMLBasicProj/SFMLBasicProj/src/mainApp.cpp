#include "Game.h"

/*
==================================================
File tite:		Main game's entry point
File Name:		mainApp.cpp
Purpose:		Creates the Game object and is an
				entry point to the SFML application.
==================================================
*/

/*
/////////////////////////////////////////////////////////
Name:		Main
Purpose:	Initialises Game object and runs its member
			function member "runGameLoop()". 
			"try" & "catch" keywords are used to handle
			any exceptions. 
Arguments:	NONE.
*/
int main()
{
	try
	{
		Game game_t;
		game_t.runGameLoop();
	}

	// catch block executed after exception occurs (e.g. textures failed to load).
	catch (std::runtime_error e)
	{
		system("pause");
	}
}