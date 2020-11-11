#include "Turle.h"

CTurle::CTurle()
{
	SetState(TURLE_STATE_WALKING);
}

void CTurle::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + TURLE_BBOX_WIDTH;

	if (state == TURLE_STATE_DIE)
		bottom = y + TURLE_BBOX_HEIGHT_DIE;
	else
		bottom = y + TURLE_BBOX_HEIGHT;
}

void CTurle::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	if (vx < 0 && x < 530) {
		//x = 0; 
		vx = -vx;
	}

	if (vx > 0 && x > 600) {
		//x = 290; 
		vx = -vx;
	}
}

void CTurle::Render()
{
	int ani = TURLE_ANI_WALKING_LEFT;
	if (state == TURLE_STATE_DIE) {
		ani = TURLE_ANI_DIE;
	}
	else if (vx > 0) ani = TURLE_ANI_WALKING_RIGHT;
	else if (vx <= 0) ani = TURLE_ANI_WALKING_LEFT;

	animation_set->at(0)->Render(x, y);

	RenderBoundingBox();
}

void CTurle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case TURLE_STATE_DIE:
		y += TURLE_BBOX_HEIGHT - TURLE_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case TURLE_STATE_WALKING:
		vx = TURLE_WALKING_SPEED;
	}

}