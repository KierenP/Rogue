#include "MathLib.h"
#include "TileEngine.h"
#include "Perlin.h"
#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>

using namespace::MathLib;

const unsigned int Octives = 8;
const float Frequency = 4;
const float Persistance = 0.5;
const int Seed = 3;

const Vector2 TileSize(32, 32);
const Vector2 WorldSize(500, 500);

float MinimapScale = 1;

TileEngine MyEngine(WorldSize);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	sf::View Minimap;
	Minimap.setCenter(WorldSize.x * TileSize.x / 2, WorldSize.y * TileSize.y / 2);
	Minimap.setSize(WorldSize.x * TileSize.x, WorldSize.y * TileSize.y);
	Minimap.setViewport(sf::FloatRect(1.f - (WorldSize.x * MinimapScale / window.getSize().x), 0, WorldSize.x * MinimapScale / window.getSize().x, WorldSize.y * MinimapScale / window.getSize().y));
	window.setView(Minimap);
	

	MyEngine.SetTileSize(TileSize);
	sf::Texture MyTexture;
	MyTexture.loadFromFile("TileSet.png");
	MyEngine.SetTexture(MyTexture);

	MyEngine.GenerateFromPerlin(Octives, Frequency, Persistance, Seed);

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