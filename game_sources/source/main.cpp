#include "stdafx_game.h"
#include "LogMessageManager.h"
#include <filesystem>

int WinMain(int argc, char **argv)
{
	LOG_ERROR("qwe");
	{
		sf::Window w(sf::VideoMode(800, 600), "SuperDuperGame");
		while (w.isOpen())
	    {
	        sf::Event event;
	        while (w.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	            {
					w.close();   
	            }   
	        }
			sf::sleep(sf::milliseconds(25));
	    }
	}

	return 0;
}
