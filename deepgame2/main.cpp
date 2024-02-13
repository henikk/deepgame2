#include "Game.h"

int main(int argv, char* argc[])
{	
	srand(static_cast<unsigned>(time(nullptr)));

	Game game;

	while(game.GetWindow()->isRunning())
	{
		game.Update();
		game.Render();
	}
		
	return 0;
}