#include "PipePortal.h"
#include "Mario.h"
#include "PlayScence.h"
#include "Game.h"

CPipePortal::CPipePortal()
{
}

CPipePortal::CPipePortal(int id)
{
	idPipe = id;
}

void CPipePortal::Render()
{
}

void CPipePortal::GetBoundingBox(double& l, double& t, double& r, double& b)
{
}

void CPipePortal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetIsReadyPiping())
	{
		if (this->idPipe == mario->GetCurrentPipeIndex())
		{
			mario->SetPosition(this->x, this->y);
			mario->SetIsDowningPipe(false);
		}
	}
}
