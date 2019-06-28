#include "stdafx_game.h"
#include "LogMessageManager.h"

#include <SFML/Window.hpp>
#include <thread>

int WinMain(int argc, char **argv)
{
	{
		LogMessageManager manager;
		manager.WriteMessage("%d", 123);
		manager.WriteMessage("%1% %2% %1%", 123, "ssss");
		manager.WriteMessage("qweqweqwe");	
	}

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
