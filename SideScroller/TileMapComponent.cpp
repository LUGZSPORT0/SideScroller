#include "TileMapComponent.h"
#include "Actor.h"
#include "Math.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <cstdlib>

TileMapComponent::TileMapComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
{

}

void TileMapComponent::Draw(SDL_Renderer* renderer)
{
	// Draw each tile texture
	for (auto& tile : mTileTextures)
	{
		int count = 0;
		int yCount = 0;
		
		for (int i = 0; i < file1.size(); i++)
		{
			int count = 0;
			int yCount = 0;
			for (auto& loc : file1[i])
			{
				SDL_Rect r;
				// Assume screen size dimensions
				r.w = static_cast<int>(mTileSize.x);
				r.h = static_cast<int>(mTileSize.y);
				// Center the rectangle around the position of the owner
				r.x = static_cast<int>(mOwner->GetPosition().x + count);
				r.y = static_cast<int>(mOwner->GetPosition().y + yCount);

				div_t result = std::div(loc, 8);
				SDL_Rect s;
				s.w = 32;
				s.h = 32;
				s.x = result.rem * 32;
				s.y = result.quot * 32;
				SDL_RenderCopy(renderer,
					tile.mTexture,
					&s,
					&r
				);
				count += 32;
				if (count % 1024 == 0)
				{
					count = 0;
					yCount += 32;
				}
			}
		}
	}
}

void TileMapComponent::SetTileTextures(const std::vector<SDL_Texture*>& textures)
{
	
	for (auto tex : textures)
	{
		int count = 0;
		TileTexture temp;
		temp.mTexture = tex;
		// Each texture is screen width in offset
		temp.mOffset.x = count * mTileSize.x;
		temp.mOffset.y = count * mTileSize.y;
		mTileTextures.emplace_back(temp);
		count++;
	}
}

// Add to Tile Map Component
void TileMapComponent::ReadFromCSVFile()
{	
	std::vector<int> num;
	std::string arr[3] = { "./Assets/MapLayer1.csv","./Assets/MapLayer2.csv" ,"./Assets/MapLayer3.csv" };
		
	std::ifstream tileMapFile(arr[mReadFile]);

	std::string lineFromFile;
	while (getline(tileMapFile, lineFromFile))
	{
		std::istringstream stream(lineFromFile);
		std::string numberToken;
		while (getline(stream, numberToken, ','))
		{
			int number = std::stoi(numberToken);
			num.push_back(number);
		}
	}
	file1.push_back(num);
}