#include "TileEngine.h"

TileEngine::TileEngine()
{

}

TileEngine::~TileEngine()
{

}

TileEngine::TileEngine(std::string pFileLocation)
{
	LoadFromFile(pFileLocation);
}

TileEngine::TileEngine(Vector2 pVectorSize)
{
	for (int i = 0; i < pVectorSize.y; i++)
	{
		std::vector<Tile> Row;

		for (int j = 0; j < pVectorSize.x; j++)
		{
			Row.push_back(Tile());
		}

		mTiles.push_back(Row);
	}
}

TileEngine::TileEngine(Vector2 pTileSize, sf::Texture pTileSet, Vector2 pVectorSize)
{
	mTileSize = pTileSize;
	mTileSet = pTileSet;

	for (int i = 0; i < pVectorSize.y; i++)
	{
		std::vector<Tile> Row;

		for (int j = 0; j < pVectorSize.x; j++)
		{
			Row.push_back(Tile());
		}

		mTiles.push_back(Row);
	}
}

TileEngine::TileEngine(Vector2 pTileSize, sf::Texture pTileSet, std::vector<std::vector<Tile>> pTiles)
{
	mTileSize = pTileSize;
	mTileSet = pTileSet;
	mTiles = pTiles;
}


void TileEngine::LoadFromFile(std::string pFileLocation)
{
	//Load from File
}


void TileEngine::Render(sf::RenderWindow* pTarget)
{
	sf::Sprite Temp;
	Temp.setTexture(mTileSet);

	for (unsigned int i = 0; i < mTiles.size(); i++)
	{
		for (unsigned int j = 0; j < mTiles[i].size(); j++)
		{
			Temp.setPosition(j * mTileSize.x, i * mTileSize.y);
			Temp.setTextureRect(sf::IntRect(mTiles[i][j].mSpriteIndex % static_cast<int>(mTileSet.getSize().x / mTileSize.x), static_cast<int>(mTiles[i][j].mSpriteIndex / (static_cast<int>(mTileSet.getSize().x / mTileSize.x))), mTileSize.x, mTileSize.y));
			pTarget->draw(Temp);
		}
	}
}


bool TileEngine::CheckSolid(float px, float py) const
{
	if (px < 0 || py < 0 || py > mTiles.size() * mTileSize.y || px > mTiles.at(static_cast<int>(py / mTileSize.y)).size() * mTileSize.x)  //If out of the world, colision = true
	{
		std::cout << "Warning: Out of bounds point given to 'TileEngine::CheckSolid'\n";
		return true;
	}

	int TilesX = static_cast<int>(px / mTileSize.x);
	int TilesY = static_cast<int>(py / mTileSize.y);

	if (mTiles[TilesY][TilesX].mIsSolid)  //guarenteed not to throw out of range exeption because of previous if statement exclusing out of bounds values
		return true;

	return false;
}

Tile TileEngine::GetTile(unsigned int x, unsigned int y)
{
	if (y >= 0 && y < mTiles.size() && x >=0 && x < mTiles[y].size())
		return mTiles[y][x];
	else
		std::cout << "Invalid index given to 'TileEngine::GetTile'\n";
	return Tile();
}

void TileEngine::SetTile(unsigned int x, unsigned int y, Tile newTile)
{
	if (y >= 0 && y < mTiles.size() && x >= 0 && x < mTiles[y].size())
		mTiles[y][x] = newTile;
	else
		std::cout << "Invalid index given to 'TileEngine::SetTile'\n";
}
