#include "MathLib.h"
#include "TileEngine.h"
#include "Perlin.h"
#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>

using namespace::MathLib;

const unsigned int Octives = 4;
const float Frequency = 3;
const float Magnitude = 6;
const float Persistance = 1 / sqrt(2);
const int Seed = 6;

const Vector2 WorldSize(20, 20);

TileEngine MyEngine(WorldSize);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");

	MyEngine.SetTileSize(Vector2(64, 64));
	sf::Texture MyTexture;
	MyTexture.loadFromFile("TileSet.png");
	MyEngine.SetTexture(MyTexture);

	MyEngine.GenerateFromPerlin(Octives, Frequency, Magnitude, Persistance, Seed);

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