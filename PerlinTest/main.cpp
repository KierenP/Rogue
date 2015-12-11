#include "MathLib.h"
#include "TileEngine.h"
#include "Perlin.h"
#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>

//srand(time(NULL));

using namespace::MathLib;

const unsigned int Octives = 8;
const float Frequency = 16;
const float Persistance = 0.5;//1 / sqrt(2);
const int Seed = static_cast <const int> (time(NULL));
const Vector2 TileSize(32, 32);
const Vector2 WorldSize(1000, 1000);

float MinimapScale = 1;

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
			if (event.type == sf::Event::MouseWheelScrolled)
			{//todo fix bug
				MinimapScale *= 1 + (static_cast <float> (-event.mouseWheelScroll.delta) / 5);		//for each notch down, -20%, for each notch up, +20%
				Minimap.zoom(1 + (static_cast <float> (-event.mouseWheelScroll.delta) / 5));		
			}
		}

		MyEngine.GenerateFromPerlin(Octives, Frequency, Persistance, rand());

		window.setView(Minimap);

		window.clear();
		MyEngine.Render(&window);
		window.display();
	}

	return 0;
}