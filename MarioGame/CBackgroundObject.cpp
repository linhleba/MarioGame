#include "BackgroundObject.h"
#include "Mario.h"
#include "GameObject.h"
#include "Game.h"
#include "PlayScence.h"

CBackgroundObject::CBackgroundObject(int type)
{
	typeOfBackground = type;
}

void CBackgroundObject::Render()
{
	int ani = -1;
	if (CheckIsWord())
	{
		if (isRender)
		{
			CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			if (typeOfBackground == OBJECT_TYPE_SECOND_WORD)
			{
				if (mario->GetIsEndGame())
				{
					ani = SECOND_WORD_ANI;
				}
			}
			else if (typeOfBackground == OBJECT_TYPE_THIRD_WORD_ITEM)
			{
				if (mario->GetIsEndGame())
				{
					switch (mario->GetCardId())
					{
					case HUD_TYPE_FIREFLOWER_CARD_ANI:
						ani = THIRD_WORD_FIREFLOWER_ANI;
						break;
					case HUD_TYPE_MUSHROOM_CARD_ANI:
						ani = THIRD_WORD_MUSHROOM_ANI;
						break;
					case HUD_TYPE_STAR_CARD_ANI:
						ani = THIRD_WORD_STAR_ANI;
						break;
					}
				}
			}
			else if (typeOfBackground == OBJECT_TYPE_FIRST_WORD)
			{
				if (mario->GetIsEndGame())
				{
					ani = FIRST_WORD_ANI;
				}
			}
		}
	}
	else if (typeOfBackground != OBJECT_TYPE_BUSH_HIDING_MARIO)
	{
		ani = BACKGROUND_OBJECT_ANI;
	}
	else if (isRender)
	{
		ani = BACKGROUND_OBJECT_ANI;
	}
	
	if (ani != -1)
	{
		animation_set->at(ani)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CBackgroundObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (CheckIsWord())
	{
		CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		if (mario->GetIsEndGame())
		{
			if (!isTimeRender)
			{
				isTimeRender = true;
				timeRender_start = GetTickCount();
			}
			else
			{
				switch (typeOfBackground)
				{
				case OBJECT_TYPE_FIRST_WORD:
					if (GetTickCount() - timeRender_start > 1000)
					{
						isRender = true;
					}
					break;
				case OBJECT_TYPE_SECOND_WORD:
					if (GetTickCount() - timeRender_start > 1500)
					{
						isRender = true;
					}
					break;
				case OBJECT_TYPE_THIRD_WORD_ITEM:
					if (GetTickCount() - timeRender_start > 2000)
					{
						isRender = true;
					}
					break;
				}
			}
		}
	}
}

void CBackgroundObject::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}