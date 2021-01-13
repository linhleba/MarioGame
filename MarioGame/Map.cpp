
#include <fstream>
#include <iostream>
#include "Map.h"
#include "Textures.h"
#include "Game.h"
#include "Utils.h"

Map::Map(int _idTileSet, int _totalRowsTileSet, int _totalColumnsTileSet, int _totalRowsMap, int _totalColumnsMap, int _totalTiles)
{
	this->TileSet = CTextures::GetInstance()->Get(_idTileSet);
	this->TotalRowsOfTileSet = _totalRowsTileSet;
	this->TotalColumnsOfTileSet = _totalColumnsTileSet;
	this->TotalRowsOfMap = _totalRowsMap;
	this->TotalColumnsOfMap = _totalColumnsMap;
	this->TotalTiles = _totalTiles;
}

Map::~Map()
{
	if (TileMap)
	{
		for (int i = 0; i < TotalRowsOfMap; i++)
		{
			delete TileMap[i];
		}
		delete TileMap;
		TileMap = nullptr;
	}
}

void Map::Render()
{
	CGame* game = CGame::GetInstance();
	int indexLeftX = max(0, (game->GetCamX() / TILE_WIDTH));
	int indexTopY = max(0, (game->GetCamY() / TILE_HEIGHT));
	int indexRightX = min((game->GetCamX() + game->GetScreenWidth()) / TILE_WIDTH + 1, TotalColumnsOfMap);
	int indexBottomY = min((game->GetCamY() + game->GetScreenHeight()) / TILE_HEIGHT, TotalRowsOfMap);

	for (int r = indexTopY; r < indexBottomY; r++)
		for (int c = indexLeftX; c < indexRightX; c++)
		{
			Tiles[TileMap[r][c] - 1]->Draw(c * TILE_WIDTH, r * TILE_HEIGHT, 255); //(x,y,alpha)
		}

	DebugOut(L"chi so r la %d \n", indexRightX);
	DebugOut(L"chi so c la %d \n", indexBottomY);
	//for (int r = 0; r < TotalRowsOfMap; r++)
	//	for (int c = 0; c < TotalColumnsOfMap; c++)
	//	{
	//		Tiles[TileMap[r][c] - 1]->Draw(c * TILE_WIDTH, r * TILE_HEIGHT, 255); //(x,y,alpha)
	//	}
}

void Map::ExtractTileFromTileSet()
{
	for (int TileNumber = 0; TileNumber < TotalTiles; TileNumber++) //total tiles = 91
	{
		int left = TileNumber % TotalColumnsOfTileSet * TILE_WIDTH;
		int top = TileNumber / TotalColumnsOfTileSet * TILE_HEIGHT;
		int right = left + TILE_WIDTH;
		int bottom = top + TILE_HEIGHT;
		LPSPRITE newTile = new CSprite(TileNumber, left, top, right, bottom, TileSet);
		this->Tiles.emplace_back(newTile);
	}
}

void Map::LoadMap(LPCWSTR path)
{
	ifstream f;

	f.open(path);

	// init tilemap
	this->TileMap = new int* [TotalRowsOfMap];
	for (int i = 0; i < TotalRowsOfMap; i++)
	{
		TileMap[i] = new int[TotalColumnsOfMap];
		for (int j = 0; j < TotalColumnsOfMap; j++)
		{
			f >> TileMap[i][j];
		}
	}
	f.close();
}

int Map::GetMapWidth()
{
	return TotalColumnsOfMap * TILE_WIDTH;
}

int Map::GetMapHeight()
{
	return TotalRowsOfMap * TILE_HEIGHT;
}