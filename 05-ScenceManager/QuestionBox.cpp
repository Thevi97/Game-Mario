#include "QuestionBox.h"

CQuestion::CQuestion() : CGameObject() {
	isQuestion = true;
	ani = 0 ;
	mushroomRun = false;
	delMushroom = false;
}
void CQuestion::Render()
{
	if (delMushroom) return;

	else if (mushroomRun)
	{
		ani = 2;
	}
	/*else if (!isQuestion) {
		if (this->x == 220)
			ani = 2;
		else
			ani = 1;
	}*/

	else if (!isQuestion) {
		if (this->x != 220)
			ani = 1;
	}
	
	else
		ani = 0;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CQuestion::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + QUESTION_BBOX_WIDTH;
	b = y + QUESTION_BBOX_HEIGHT;
}
void CQuestion::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (mushroomRun)
	{
		y = 45;
		x += 0.2;
	}
	//y += dy;
}

