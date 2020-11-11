#pragma once

#include "GameObject.h"

#define TURLE_WALKING_SPEED 0.03f;

#define TURLE_BBOX_WIDTH 16
#define TURLE_BBOX_HEIGHT 26
#define TURLE_BBOX_HEIGHT_DIE 16

#define TURLE_STATE_WALKING 100
#define TURLE_STATE_DIE 200

#define TURLE_ANI_WALKING_LEFT 0
#define TURLE_ANI_WALKING_RIGHT 1
#define TURLE_ANI_DIE 2

class CTurle : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

public:
	CTurle();
	virtual void SetState(int state);
};