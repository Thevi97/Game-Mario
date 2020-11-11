
#include "game_map.h"
#include "Game.h"
#define BACKGROUND_TEXTURE_PATH1 L"0.png"
#include "Background.h"

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"

void GameMap::LoadMap(char* name, LPDIRECT3DTEXTURE9 d3dtt)
{
	FILE *fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL)
	{
		return;
	}

	game_map_.max_x_ = 0;    //set start x  = 0 positon
	game_map_.max_y_ = 0;    //set start x  = 0 positon
	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			fscanf_s(fp, "%d", &game_map_.tile[i][j]);
			int val = game_map_.tile[i][j];

			if (val > 0)
			{
				LoadTiles(val, d3dtt);
				if (j > game_map_.max_x_)
				{
					game_map_.max_x_ = j;
				}

				if (i > game_map_.max_y_)
				{
					game_map_.max_y_ = i;
				}
			}
		}
	}

	game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE;
	game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE;


	game_map_.start_x_ = 0;              //start_x_   length position x
	game_map_.start_y_ = 0;
	game_map_.file_name_ = name;
	fclose(fp);
	DebugOut(L"[ERR] game_map max_x_: %d\n", game_map_.max_x_/ TILE_SIZE );
	DebugOut(L"[ERR] game_map max__: %d\n", game_map_.max_y_ / TILE_SIZE);
	DebugOut(L"[ERR] game_map_ game_map_ game_map_ 0: %d\n", game_map_.tile[1][1]);
}

void GameMap::LoadTiles(int val,LPDIRECT3DTEXTURE9 d3dtt)
{
	/*char file_img[40];
	FILE* fp = NULL;*/
	//for (int i = 0; i <= MAX_TILE; i++)
	//{
		tile_map[val] = getTileMapSwitch(val, d3dtt);
	//}
	//for (int i = 0; i < MAX_TILE; i++)
	//{
	//	sprintf_s(file_img, "map/%d.png", 0);
	//	fopen_s(&fp, file_img, "rb");
	//	if (fp == NULL)
	//	{
	//		continue;
	//	}
	//	fclose(fp);

	//	//CBackground* s = new CBackground(1.3f, 1.0f, BACKGROUND_TEXTURE_PATH1);
	//	CGame * game = CGame::GetInstance();
	//	LPDIRECT3DTEXTURE9 texBackground = game->LoadTexture(BACKGROUND_TEXTURE_PATH1);
	//	//tile_map[i] = new CBackground(10.0f,10.0f, texBackground);
	//	//tile_map[i].Render()// tile_map[i].LoadImg(file_img,screen);

	//}
}

void GameMap::DrawMap(LPDIRECT3DTEXTURE9 d3dtt) {
	/*CBackground* brick = new CBackground(100, 5, d3dtt);
				brick->SetPosition(100, 100);
				brick->Render();
*/

	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	int map_x = 0;
	int map_y = 0;

	map_x = game_map_.start_x_ / TILE_SIZE;

	x1 = (game_map_.start_x_%TILE_SIZE)*-1;
	//x2 = x1 + CGame::GetInstance()->GetScreenHeight() + (x1 == 0 ? 0 : TILE_SIZE);
	x2 = 17 * 100;

	map_y = game_map_.start_y_ / TILE_SIZE;
	y1 = (game_map_.start_y_%TILE_SIZE)*-1;
	//y2 = y1 + CGame::GetInstance()->GetScreenWidth() + (y1 == 0 ? 0 : TILE_SIZE);
	y2 = 17 * 12;

	for (int i = y1; i < y2; i += TILE_SIZE)
	{

		map_x = game_map_.start_x_ / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			int val = game_map_.tile[map_y][map_x];
			if (val > 0) {
				/*brick = new CBackground(100, 5, *d3dtt);
				brick = new CBackground(100, 5, *d3dtt);
				brick = new CBackground(100, 5, *d3dtt);
				brick = new CBackground(100, 5, *d3dtt);*/
				//tile_map[1] = new CBackground(10, 10, *d3dtt);
				//brick->SetPosition(100, 100);
				//tile_map[1]->Render();
				try {
					//tile_map[i] = new CBackground(1, 0, 0, 64, 64, *d3dtt);
					//tile_map[i] = getTileMapSwitch(val,d3dtt);

					//tile_map[1]->SetPosition(10, 10);
					tile_map[val]->Draw(j, i, 255);
				}
				catch (exception e)
				{

				}

				//tile_map[val].SetReact(j,i)   //set vi tri
				//tile_map[val].Render(screen)  //render
			}
			map_x++;
		}
		map_y++;
	}
}

CBackground* GameMap::getTileMapSwitch(int id, LPDIRECT3DTEXTURE9 d3dtt)
{
	switch (id) {
	case 1:
		return new CBackground(1, 222, 222, 239, 239, d3dtt);
	case 2:
		return new CBackground(2, 136, 18, 153, 35, d3dtt);
	case 3:
		return new CBackground(3, 136, 1, 153, 18, d3dtt);
	case 4:
		return new CBackground(4, 153, 1, 170, 18, d3dtt);
	case 5:
		return new CBackground(5, 153, 18, 170, 35, d3dtt);
	case 6:
		return new CBackground(6, 136, 35, 153, 52, d3dtt);
	case 7:
		return new CBackground(7, 153, 35, 170, 53, d3dtt);
	case 8:
		return new CBackground(8, 136, 52, 153, 69, d3dtt);
	case 9:
		return new CBackground(9, 222, 205, 237, 221, d3dtt);
	case 10:
		return new CBackground(10, 1, 52, 18, 68, d3dtt);
	case 11:
		return new CBackground(11, 18, 52, 35, 68, d3dtt);
	case 12:
		return new CBackground(12, 36, 52, 53, 68, d3dtt);
	case 13:
		return new CBackground(13, 1, 69, 18, 85, d3dtt);
	case 14:
		return new CBackground(14, 19, 69, 36, 85, d3dtt);
	case 15:
		return new CBackground(15, 37, 69, 54, 85, d3dtt);
	case 16:
		return new CBackground(16, 1, 86, 18, 102, d3dtt);
	case 17:
		return new CBackground(17, 19, 86, 36, 102, d3dtt);
	case 18:
		return new CBackground(18, 37, 86, 54, 102, d3dtt);
	case 19:
		return new CBackground(19, 256, 188, 272, 204, d3dtt);
	case 20:
		return new CBackground(20, 52, 52, 69, 69, d3dtt);
	case 21:
		return new CBackground(21, 69, 52, 86, 69, d3dtt);
	case 22:
		return new CBackground(22, 86, 52, 103, 69, d3dtt);
	case 23:
		return new CBackground(23, 52, 69, 69, 86, d3dtt);
	case 24:
		return new CBackground(24, 69, 69, 86, 86, d3dtt);
	case 25:
		return new CBackground(25, 86, 69, 103, 86, d3dtt);
	case 26:
		return new CBackground(26, 52, 103, 69, 101, d3dtt);
	case 27:
		return new CBackground(27, 69, 86, 86, 101, d3dtt);
	case 28:
		return new CBackground(28, 86, 86, 103, 101, d3dtt);
	case 29:
		return new CBackground(29, 290, 52, 307, 69, d3dtt);
	case 30:
		return new CBackground(30, 307, 52, 324, 69, d3dtt);
	case 31:
		return new CBackground(31, 290, 69, 307, 86, d3dtt);
	case 32:
		return new CBackground(32, 307, 68, 324, 86, d3dtt);
	case 33:
		return new CBackground(33, 52, 1, 69, 18, d3dtt);
	case 34:
		return new CBackground(34, 69, 1, 86, 18, d3dtt);
	case 35:
		return new CBackground(35, 86, 1, 103, 18, d3dtt);
	case 36:
		return new CBackground(36, 52, 18, 69, 35, d3dtt);
	case 37:
		return new CBackground(37, 69, 18, 86, 35, d3dtt);
	case 38:
		return new CBackground(38, 86, 18, 103, 35, d3dtt);
	case 39:
		return new CBackground(39, 52, 35, 69, 52, d3dtt);
	case 40:
		return new CBackground(40, 69, 35, 86, 52, d3dtt);
	case 41:
		return new CBackground(41, 86, 35, 103, 52, d3dtt);
	case 42:
		return new CBackground(42, 1, 1, 18, 18, d3dtt);
	case 43:
		return new CBackground(43, 18, 1, 35, 18, d3dtt);
	case 44:
		return new CBackground(44, 35, 1, 52, 18, d3dtt);
	case 45:
		return new CBackground(45, 1, 18, 18, 35, d3dtt);
	case 46:
		return new CBackground(46, 18, 18, 35, 35, d3dtt);
	case 47:
		return new CBackground(47, 35, 18, 52, 35, d3dtt);
	case 48:
		return new CBackground(48, 1, 35, 18, 52, d3dtt);
	case 49:
		return new CBackground(49, 18, 35, 35, 52, d3dtt);
	case 50:
		return new CBackground(50, 35, 35, 52, 52, d3dtt);
	case 51:
		return new CBackground(51, 426, 239, 443, 256, d3dtt);
	case 52:
		return new CBackground(52, 443, 239, 460, 256, d3dtt);
	case 53:
		return new CBackground(53, 426, 256, 443, 273, d3dtt);
	case 54:
		return new CBackground(54, 443, 256, 460, 273, d3dtt);
	case 55:
		return new CBackground(55, 324, 171, 341, 188, d3dtt);
	case 56:
		return new CBackground(56, 170, 137, 187, 154, d3dtt);
	default:
		return new CBackground(0, 52, 223, 67, 237, d3dtt);
	}

}


