#pragma once
#include <vector>
#include "SpriteComponent.h"
#include "Math.h"

class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class Actor* owner, int drawOrder = 100);
	void Draw(SDL_Renderer* renderer) override;
	void SetTileTextures(const std::vector<SDL_Texture*>& textures);
	void SetTileSceenSize(const Vector2& size) { mTileSize = size; }
	void SetReadFile(const int fileNum) { mReadFile = fileNum; }
	void ReadFromCSVFile();
	

private:
	struct TileTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset; // from the math.h library
	};
	std::vector<TileTexture> mTileTextures;
	Vector2 mTileSize;
	int mReadFile;
	std::vector<std::vector<int>> file1;
};