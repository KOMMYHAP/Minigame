#include "stdafx_game.h"

#include "Game.h"

int main(int argc, char **argv)
{
	auto game = make_shared<Game>();
	game->Initialize(argc, argv);
	game->Run();
    return 0;
}
