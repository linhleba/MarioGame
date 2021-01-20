#pragma once
#include "GameObject.h"
class CPipePortal: public CGameObject
{
private:
	int idPipe;
public:
	CPipePortal();
	CPipePortal(int id);
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	LPGAMEOBJECT FindPipePortal(int id)
	{
		if (this->idPipe == id)
		{
			return this;
		}
		else return NULL;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

