#include "Background.h"
#include "Game.h"

CBackground::CBackground(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture):CSprite(id, left, top, right, bottom, texture)
{
	//CSprite::CSprite(id, left, top, right, bottom, texture);
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = texture;
	
}

void CBackground::Draw(float x, float y, int alpha)
{
	CSprite::Draw(x, y, 255);
}
