#include "BrickTop.h"

void CBrickTop::Render()
{
	//animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBrickTop::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + 1;
}
