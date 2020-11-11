#pragma once
#include "GameObject.h"

#define PLANT_BBOX_WIDTH  15
#define PLANT_BBOX_HEIGHT 23

class CPlant : public CGameObject
{
public:
	static bool start;
	CPlant();
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};