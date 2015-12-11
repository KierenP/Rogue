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


void TileEngine::GenerateFromPerlin(int octaves, float freq, float persistance, int seed)
{
	Perlin* Noise = new Perlin(octaves, freq, 0.5, persistance, seed);		

	srand(seed);

	std::vector<Vector2> HillTops;

	for (int i = 0; i < 3; i++)	//TODO: replace 3 with passed value, 'HillCount' maybe?
	{
		float DistanceFromCenter = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);		//random number between 0 and and 1
		DistanceFromCenter = pow(DistanceFromCenter, 2) / 2;											//square it, this is now the distance the island will be from the center of the map (halved because from the middle, you only can go 1/2 the screen to the edge)
		float Direction = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (2 * M_PI));	//Random direction, from 0 to 2pi radians

		HillTops.push_back(Vector2(cos(Direction) * DistanceFromCenter + 0.5f, sin(Direction) * DistanceFromCenter + 0.5f));

		std::cout << "X = " << HillTops[i].x << " Y = " << HillTops[i].y << "\n";
	}

	for (unsigned int i = 0; i < mTiles.size(); i++)
	{
		for (unsigned int j = 0; j < mTiles[i].size(); j++)
		{
			float PerlinHeight = Noise->Get(static_cast<float>(i) / mTiles.size(), static_cast<float>(j) / mTiles[i].size()) + 0.5f;								//random between -0.5 and 0.5, because I add 0.5 its now random between 0 and 1
			float HillHeightBias = 1;

			for (unsigned int k = 0; k < HillTops.size(); k++)
			{			
				float NormilisedDistance = sqrt((HillTops[k].x - (float(j) / mTiles[i].size())) * (HillTops[k].x - (float(j) / mTiles[i].size())) + (HillTops[k].y - (float(i) / mTiles.size())) * (HillTops[k].y - (float(i) / mTiles.size()))) / float(sqrt(2)) * 3;

				NormilisedDistance = NormilisedDistance * NormilisedDistance * NormilisedDistance * (NormilisedDistance * (NormilisedDistance * 6 - 15) + 10) - 0.2f;	//hight modifier h(d) = 6d ^ 5 - 15d ^ 4 + 10t ^ 3 (standard ease curve)

				if (HillHeightBias > NormilisedDistance)
					HillHeightBias = NormilisedDistance;
			}

			//HillHeightBias /= HillTops.size();	//Get average, by dividing sum be quantity
			if (HillTops.size() > 0)
			{
				PerlinHeight -= HillHeightBias;
			}

			if (PerlinHeight < 0)
				PerlinHeight = 0;
			if (PerlinHeight > 1)	//shouldnt be a issue, but just in case
				PerlinHeight = 1;

			mTiles[i][j].mPerlinHeight = PerlinHeight;
			mTiles[i][j].mSpriteIndex = static_cast <unsigned int> (PerlinHeight * 10);		
		}
	}
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
			unsigned int TilesPerRow = static_cast<int>(mTileSet.getSize().x / mTileSize.x);

			Temp.setPosition(j * mTileSize.x, i * mTileSize.y);
			Temp.setTextureRect(sf::IntRect((mTiles[i][j].mSpriteIndex % TilesPerRow) * (int)mTileSize.x, static_cast<int>(mTiles[i][j].mSpriteIndex / TilesPerRow) * (int)mTileSize.y, (int)mTileSize.x, (int)mTileSize.y));
			pTarget->draw(Temp);

			//sf::RectangleShape MyShape;
			//MyShape.setPosition(j * mTileSize.x, i * mTileSize.y);
			//MyShape.setSize(sf::Vector2f(32, 32));
			//MyShape.setFillColor(sf::Color(mTiles[i][j].mPerlinHeight * 255, mTiles[i][j].mPerlinHeight * 255, mTiles[i][j].mPerlinHeight * 255, 255));
			//pTarget->draw(MyShape);
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
