#include "MathLib.h"
#include "TileEngine.h"
#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>

using namespace::MathLib;

TileEngine MyEngine(Vector2(10, 10));

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

	MyEngine.SetTileSize(Vector2(64, 64));
	sf::Texture MyTexture;
	MyTexture.loadFromFile("TestTileSet.png");
	MyEngine.SetTexture(MyTexture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		MyEngine.Render(&window);
		window.display();
	}

	return 0;
}