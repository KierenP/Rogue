#include "MathLib.h"
#include "TileEngine.h"
#include "Perlin.h"
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
	MyEngine.CheckSolid(1000, 1000);

	Perlin *perlin = new Perlin(1, 5, 512, 94);
	sf::Texture PerlinTexture;
	sf::Uint8* PerlinPixles = new sf::Uint8[500 * 500 * 4];

	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			float value = perlin->Get(static_cast<float>(i) / 500, static_cast<float>(j) / 500);
			PerlinPixles[(i * 500 + j) * 4] = value + 255;
			PerlinPixles[(i * 500 + j) * 4 + 1] = value + 255;
			PerlinPixles[(i * 500 + j) * 4 + 2] = value + 255;
			PerlinPixles[(i * 500 + j) * 4 + 3] = 255;
		}
	}

	PerlinTexture.create(500, 500);
	PerlinTexture.update(PerlinPixles);
	sf::Sprite MySprite;
	MySprite.setTexture(PerlinTexture);

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
		window.draw(MySprite);
		window.display();
	}

	return 0;
}