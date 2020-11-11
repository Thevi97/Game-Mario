#pragma once
#include "Sprites.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CBackground : public CSprite
{
		int id;
		int left;
		int top;
		int right;
		int bottom;
		LPDIRECT3DTEXTURE9 texture = NULL;
public:
	//LPDIRECT3DTEXTURE9 texture;
	CBackground(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture = NULL);
	void Draw(float x, float y, int alpha = 255);
	//virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	//CSprite* minh = new CSprite(1,0,0,10,10,texBackground);
		//minh->Draw(10,10,255);
};