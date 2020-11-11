#include "Bullet.h"
#include "Plant.h"
#include "Utils.h"

CBullet::CBullet() {
	isStart = false;
}

CBullet * CBullet::__instance = NULL;

CBullet *CBullet::GetInstance()
{
	if (__instance == NULL) __instance = new CBullet();
	return __instance;
}
void CBullet::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBullet::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH;
	b = y + BULLET_BBOX_HEIGHT;
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (isStart)
	{
		x -= 0.1*dt;
		y += 0.5;
	}
	CPlant* plant = new CPlant();
	if (plant->start == true)
	{
		isStart = true;
		DebugOut(L"bat dau", plant->start);
		x = 350;
		y = 112;
	}
	/*if (y > 200) {
		isStart = false;
	}*/
	
}

