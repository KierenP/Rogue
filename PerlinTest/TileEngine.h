#pragma once
#include "MathLib.h"
#include "SFML\Graphics.hpp"
#include "Perlin.h"
#include <iostream>
#include <vector>

using namespace::MathLib;

struct Tile
{
	//Tile(unsigned int SpriteIndex = 0, bool IsSolid = false) { mSpriteIndex = SpriteIndex; mIsSolid = IsSolid; }

	unsigned int mSpriteIndex;			//The index of the position in the tileset of the spite
	float mPerlinHeight;				//A value assigned by the perlin algorithm. ranges from 0 to 1.  
	bool mIsSolid;								
};

class TileEngine
{
public:
	TileEngine();                               
	TileEngine(std::string pFileLocation);															//Generate from txt file
	TileEngine(Vector2 pVectorSize);																//Generate empty tile vector of given size
	TileEngine(Vector2 pTileSize, sf::Texture pTileSet, Vector2 pVectorSize);						//Generate empty tile vec from paramiters
	TileEngine(Vector2 pTileSize, sf::Texture pTileSet, std::vector<std::vector<Tile>> pTiles);		//Generate from already created vector of tiles
	~TileEngine();

	//Getters
	Vector2 GetTileSize() { return mTileSize; }
	sf::Texture GetTexture() { return mTileSet; }
	std::vector<std::vector<Tile> > GetTiles() { return mTiles; }

	//Setters
	void SetTileSize(Vector2 TileSize) { mTileSize = TileSize; }
	void SetTexture(sf::Texture texture) { mTileSet = texture; }
	void SetTiles(std::vector<std::vector<Tile> >& pTiles) { mTiles = pTiles; }

	//SpriteIndex will range from 0 to amp, seed is deterministic
	void GenerateFromPerlin(int octaves, float freq, float persistance, int seed = 0);
	void LoadFromFile(std::string pFileLocation);
	void Render(sf::RenderWindow* pTarget);
	bool CheckSolid(float px, float py) const;														//Check if the tile under a given location (in pixles) is solid or not

	Tile GetTile(unsigned int x, unsigned int y);													//Get individual tile, at given index {x, y}
	void SetTile(unsigned int x, unsigned int y, Tile newTile);										//Set individual tile, at given index {x, y}

private:

	Vector2 mTileSize;							//Tile width and height in pixles
	sf::Texture mTileSet;
	std::vector<std::vector<Tile> > mTiles;
};

