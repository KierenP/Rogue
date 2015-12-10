#include "MathLib.h"
#include "TileEngine.h"
#include "Perlin.h"
#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>

//srand(time(NULL));

using namespace::MathLib;

const unsigned int Octives = 4;
const float Frequency = 4;
const float Persistance = 1 / sqrt(2);
const int Seed = time(NULL);
const Vector2 TileSize(32, 32);
const Vector2 WorldSize(250, 250);

float MinimapScale = 4;

TileEngine MyEngine(WorldSize);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	sf::View Minimap;
	Minimap.setCenter(WorldSize.x * TileSize.x / 2, WorldSize.y * TileSize.y / 2);
	Minimap.setSize(WorldSize.x * TileSize.x, WorldSize.y * TileSize.y);
	Minimap.setViewport(sf::FloatRect((1 - (WorldSize.x * MinimapScale / window.getSize().x)) / 2, (1 - (WorldSize.y * MinimapScale / window.getSize().y)) / 2, WorldSize.x * MinimapScale / window.getSize().x, WorldSize.y * MinimapScale / window.getSize().y));
	window.setView(Minimap);

	MyEngine.SetTileSize(TileSize);
	sf::Texture MyTexture;
	MyTexture.loadFromFile("TileSet.png");
	MyEngine.SetTexture(MyTexture);

	srand(Seed);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		MyEngine.GenerateFromPerlin(Octives, Frequency, Persistance, rand());

		window.clear();
		MyEngine.Render(&window);
		window.display();
	}

	return 0;
}