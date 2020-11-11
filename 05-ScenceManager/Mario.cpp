#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "BrickTop.h"
#include "QuestionBox.h"

CMario::CMario(float x, float y) : CGameObject()
{
	//this->CheckToMap(test->game_map_);
	level = MARIO_LEVEL_SMALL;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);

	start_x = x; 
	start_y = y; 
	this->x = x; 
	this->y = y; 
	checkMarioColision = false;
	ani = MARIO_ANI_SMALL_IDLE_RIGHT;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += MARIO_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state!=MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{
		checkMarioColision = false;
		x += dx; 
		y += dy;
	}
	else
	{
		checkMarioColision = true;									//mario co va cham
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0; 
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 
		
		// block every object first!
		x += min_tx*dx + nx*0.4f;
		y += min_ty*dy + ny*0.4f;

		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				DebugOut(L"kill 0");
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					DebugOut(L"kill");

					if (goomba->GetState()!= GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					DebugOut(L"kill 2");
					if (untouchable==0)
					{
						if (goomba->GetState()!=GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else 
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			} // if Goomba
			else if (dynamic_cast<CBrickTop *>(e->obj)) // if e->obj is Goomba 
			{
				if (e->ny > 0)
					this->y = y-0.5;

			} // if brickTop
			else if (dynamic_cast<CQuestion *>(e->obj)) // if e->obj is Goomba 
			{
				CQuestion *question = dynamic_cast<CQuestion *>(e->obj);
				question->isQuestion = false;
				if (question -> x == 220)
					question -> ani = 2;
				if (question -> ani == 2) {
					if (!question -> mushroomRun) 
					{
						question -> mushroomRun = true ;
					}
					else
					{
						DebugOut(L" ccccc xuat hienc cccccccc :\n") ;
						question->delMushroom = true ;
						this->level = MARIO_LEVEL_BIG ;
						
						//delete question;
					}
				}
				
			} // if box question
			else if (dynamic_cast<CBrickTop *>(e->obj)) // if e->obj is Goomba 
			{
				//DebugOut(L" kill brick top");
				if (e->ny > 0)
					this->y = y - 0.5;

			} // if brickTop
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	//Map* map = new Map();
	
}

void CMario::Render()
{
	/*int ani = MARIO_ANI_SMALL_IDLE_RIGHT; */            
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else if (level == MARIO_LEVEL_BIG)
	{
		if (vx == 0)
		{
			if (nx > 0) {
				if (state == MARIO_STATE_JUMP) {
					DebugOut(L"vaossssss");
					ani = MARIO_ANI_BIG_JUMP_RIGHT;
				}
				else
					ani = MARIO_ANI_BIG_IDLE_RIGHT;
				/*
				try {
					if (state == MARIO_STATE_JUMP) {
						DebugOut(L"vao day jump");
						ani = MARIO_ANI_SMALL_JUMP_LEFT;
					}
				}
				catch (exception e) { ; }*/

			}
			else
			{
				if (state == MARIO_STATE_JUMP) {
					ani = MARIO_ANI_BIG_JUMP_LEFT;
				}
				else
					ani = MARIO_ANI_BIG_IDLE_LEFT;
			}
		}
		else if (vx > 0)
		{
			if (state == MARIO_STATE_JUMP && checkMarioColision == false)                    //ANI JUMP RIGHT
				ani = MARIO_ANI_BIG_JUMP_RIGHT;
			else if (state == MARIO_STATE_RUN_RIGHT)
			{
				ani = MARIO_ANI_BIG_RUN_RIGHT;
			}
			else
				ani = MARIO_ANI_BIG_WALKING_RIGHT;
		}
		else
		{
			if (state == MARIO_STATE_JUMP && checkMarioColision == false)				   //ANI JUMP LEFT
				ani = MARIO_ANI_BIG_JUMP_LEFT;
			else if (state == MARIO_STATE_RUN_LEFT)
			{
				ani = MARIO_ANI_BIG_RUN_LEFT;
			}
			else
				ani = MARIO_ANI_BIG_WALKING_LEFT;
		}
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		if (vx == 0)
		{
			//DebugOut(L"vao1111%d",state);
			/*if (state == MARIO_STATE_JUMP) {
				DebugOut(L"vaossssss");
				ani = MARIO_ANI_SMALL_JUMP_RIGHT;
			}*/
			if (nx > 0) {
				if (state == MARIO_STATE_JUMP) {
					DebugOut(L"vaossssss");
					ani = MARIO_ANI_SMALL_JUMP_RIGHT;
				}
				else
					ani = MARIO_ANI_SMALL_IDLE_RIGHT;
				/*
				try {
					if (state == MARIO_STATE_JUMP) {
						DebugOut(L"vao day jump");
						ani = MARIO_ANI_SMALL_JUMP_LEFT;
					}
				}
				catch (exception e) { ; }*/
				
			}
			else 
			{
				if (state == MARIO_STATE_JUMP) {
					ani = MARIO_ANI_SMALL_JUMP_LEFT;
				}
				else
					ani = MARIO_ANI_SMALL_IDLE_LEFT;
			}
		}
		else if (vx > 0) 
		{
			
			if(state == MARIO_STATE_JUMP && checkMarioColision == false)                    //ANI JUMP RIGHT
				ani = MARIO_ANI_SMALL_JUMP_RIGHT;
			else if (state == MARIO_STATE_RUN_RIGHT)
			{
				ani = MARIO_ANI_SMALL_RUN_RIGHT;
			}
			else
				ani = MARIO_ANI_SMALL_WALKING_RIGHT;
		}
		else 
		{
			if (state == MARIO_STATE_JUMP && checkMarioColision == false)				   //ANI JUMP LEFT
				ani = MARIO_ANI_SMALL_JUMP_LEFT;
			else if (state == MARIO_STATE_RUN_LEFT)
			{
				ani = MARIO_ANI_SMALL_RUN_LEFT;
			}
			else
				ani = MARIO_ANI_SMALL_WALKING_LEFT;
		}
	}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT: 
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_RUN_LEFT:
		vx = -0.5;
		nx = -1;
		break;
	case MARIO_STATE_RUN_RIGHT:
		vx = 0.5;
		nx = 1;
		break;
	case MARIO_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		if (checkMarioColision == true) {
			//DebugOut(L"va cham");
			vy = -MARIO_JUMP_SPEED_Y;
			//vy = -0.7;
			break;
		}
		else 
		{
			//DebugOut(L" khong va cham");
			//vy = -0.1;//
			break;
		}
	case MARIO_STATE_IDLE: 
		vx = 0;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 
	/*right = x + MARIO_BIG_BBOX_WIDTH;
	bottom = y + MARIO_BIG_BBOX_HEIGHT;*/
	if (level == MARIO_LEVEL_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_SMALL);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

