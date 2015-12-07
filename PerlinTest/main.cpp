#include "MathLib.h"
#include "TileEngine.h"
#include "Perlin.h"
#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>

using namespace::MathLib;

TileEngine MyEngine(Vector2(20, 20));

const float Magnitude = 6;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1500, 1000), "SFML works!");

	MyEngine.SetTileSize(Vector2(64, 64));
	sf::Texture MyTexture;
	MyTexture.loadFromFile("TileSet.png");
	MyEngine.SetTexture(MyTexture);
	MyEngine.CheckSolid(1000, 1000);

	Perlin *perlin = new Perlin(4, 3, Magnitude / 2, 0.7, 7);
	sf::Texture PerlinTexture;
	sf::Uint8* PerlinPixles = new sf::Uint8[500 * 500 * 4];

	int f = 0.1;

	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			float value = perlin->Get(static_cast<float>(i) / 500, static_cast<float>(j) / 500);
			PerlinPixles[(i * 500 + j) * 4] = (value + Magnitude / 2) * (255 / 6);
			PerlinPixles[(i * 500 + j) * 4 + 1] = (value + Magnitude / 2) * (255 / 6);
			PerlinPixles[(i * 500 + j) * 4 + 2] = (value + Magnitude / 2) * (255 / 6);
			PerlinPixles[(i * 500 + j) * 4 + 3] = 255;
		}
	}

	PerlinTexture.create(500, 500);
	PerlinTexture.update(PerlinPixles);
	sf::Sprite MySprite;
	MySprite.setPosition(640, 0);
	MySprite.setTexture(PerlinTexture);

	MyEngine.GenerateFromPerlin(4, 3, Magnitude, 0.5, 7);

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
		//window.draw(MySprite);
		window.display();
	}

	return 0;
}