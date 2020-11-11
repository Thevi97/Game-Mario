#pragma once
#define TILE_SIZE 17
#include "GameObject.h"
#define MAX_TILE 100 
#include "Background.h"
#include "Map.h"

class GameMap
{
	float m;
public:
	GameMap() { ; };
	~GameMap() { ; }

	void LoadMap(char* name, LPDIRECT3DTEXTURE9 d3dtt);
	void LoadTiles(int val, LPDIRECT3DTEXTURE9 d3dtt);
	CBackground* getTileMapSwitch(int id,LPDIRECT3DTEXTURE9 d3dtt);                    //get tile map theo tham so truyen vao
	void DrawMap(LPDIRECT3DTEXTURE9 d3ddv);
	////CBackground* brick;
	
public:
	Map game_map_;       // save position number
	CBackground* tile_map[MAX_TILE];   // save image


};



