#include "Game.h"
#include "Misc.h"




void CMisc::Update(DWORD dt)
{
}

void CMisc::Render()
{
	LPANIMATION ani;

	ani = CAnimations::GetInstance()->Get(510);
	ani->Render(x, y);
}


