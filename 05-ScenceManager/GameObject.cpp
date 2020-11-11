#include <d3dx9.h>
#include <algorithm>


#include "Utils.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
	on_ground_ = false;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx*dt;
	float sdy = svy*dt;

	// (rdx, rdy) is RELATIVE movement distance/velocity 
	float rdx = this->dx - sdx;
	float rdy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		rdx, rdy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, rdx, rdy, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects 
	
	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects, 
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty, 
	float &nx, float &ny, float &rdx, float &rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}

	if (min_ix>=0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy>=0) coEventsResult.push_back(coEvents[min_iy]);
}


void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l,t,r,b; 

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	CGame::GetInstance()->Draw(x, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 32);
}


CGameObject::~CGameObject()
{

}

//void CGameObject::CheckToMap(Map& map_data)
//{
//	int x1 = 0;
//	int x2 = 0;
//	int y1 = 0;
//	int y2 = 0;
//
//	//check horizontal
//	int height_min = 12 < TILE_SIZE ? 12 : TILE_SIZE;   // height_frame_ =12
//
//	x1 = (x + dx) / TILE_SIZE;
//	x2 = (x + dx + 12 - 1) / TILE_SIZE;   //_width_frame_ =12 , x2 = (x_pos_ + x_val_ + _width_frame_ - 1) / TILE_SIZE; 
//
//	y1 = (y) / TILE_SIZE;
//	y2 = (y + height_min - 1) / TILE_SIZE;
//
//
//	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
//	{
//		if (x > 0) //main object is moving to right
//		{
//			if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
//			{
//				y = x2 * TILE_SIZE;
//				x -= 12 + 1;   ///_width_frame_ =12
//				x = 0;
//			}
//		}
//		else if (x < 0)
//		{
//			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
//			{
//				x = (x1 + 1)* TILE_SIZE;
//				dx = 0;
//			}
//
//		}
//	}
//
//	//check vertical
//
//	int width_min = 12 < TILE_SIZE ? 12 : TILE_SIZE;   //_width_frame_ =12
//	x1 = (x) / TILE_SIZE;
//	x2 = (x + width_min) / TILE_SIZE;
//
//	y1 = (y + y) / TILE_SIZE;
//	y2 = (y + dy + 12 - 1) / TILE_SIZE;    // height_frame_ =12
//
//	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
//	{
//		if (dy > 0)
//		{
//			if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
//			{
//				y = y2 * TILE_SIZE;
//				y -= (12 + 1);      // height_frame_ =12
//				dy = 0;
//				on_ground_ = true;
//			}
//		}
//		else if (dy < 0)
//		{
//			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
//			{
//				y = (y1 + 1)*TILE_SIZE;
//				dy = 0;
//			}
//		}
//	}
//
//	x += dx;
//	y += dy;
//
//	if (x < 0)
//	{
//		x = 0;
//	}
//	else if (x + 12 > map_data.max_x_)  // width_frame_=12
//	{
//		x = map_data.max_x_ = 12 - 1;   // width_frame_=12
//	}
//
//
//
//}