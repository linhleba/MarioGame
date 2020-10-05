#include "Game.h"
#include "Misc.h"


CMisc::CMisc(float x, float y) : CGameObject(x, y)
{

};

void CMisc::Update(DWORD dt)
{
}

void CMisc::Render()
{
	LPANIMATION ani;

	ani = CAnimations::GetInstance()->Get(510);
	ani->Render(x, y);
}


