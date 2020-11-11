#pragma once
#include "GameObject.h"

#define MUSHROOM_BBOX_WIDTH  17
#define MUSHROOM_BBOX_HEIGHT 17

class CMushroom : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};