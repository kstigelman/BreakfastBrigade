/** The Breakfast Brigade
 *  
 *  A 2D arcade style game by Kyler Stigelman
 * 
 *  After the S.S Frying Pan crash lands on the planet Colifor-B,
 *  the Breakfast Brigade must find a way home while surviving the 
 *  monsters that lurk in the forest.
 */

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Engine/Game.hpp"

int main (int argc, char* argv[])
{
	Game game("The Breakfast Brigade");
	game.run ();

	return 0;
}