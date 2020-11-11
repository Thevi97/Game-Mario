#include "CMushroom.h"

void CMushroom::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CMushroom::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + MUSHROOM_BBOX_WIDTH;
	b = y + MUSHROOM_BBOX_HEIGHT;
}