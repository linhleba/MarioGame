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
			if (mario->GetIsDowningPipe())
			{
				// Set to check cam in the main game
				mario->SetIsInSecretRoom(true);
				mario->SetIsDowningPipe(false);

				// Set to check pipe and handle lock control
				mario->SetIsFallDowningPipe(true);
			}
			else if (mario->GetIsUppingPipe())
			{
				mario->SetIsUppingPipe(false);
				mario->SetIsInSecretRoom(false);
			}
			else if (mario->GetIsDownUpPipe())
			{
				mario->SetIsInSecretRoom(true);
				mario->SetIsDownUpPipe(false);
			}
			// Set the state is false if finish piping
			mario->SetIsReadyPiping(false);
		}
	}
}
