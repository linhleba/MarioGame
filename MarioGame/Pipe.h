#pragma once
#include "GameObject.h"

#define PIPE_BBOX_WIDTH  16
#define PIPE_BBOX_HEIGHT 16

class CPipe : public CGameObject
{
private:
	int typeOfPipe;
	int idPipe;
public:
	CPipe(int type, int id);
	CPipe();
	CPipe(int type);
	int GetTypeOfPipe() { return typeOfPipe; }
	int GetIdPipe() { return idPipe; }
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
};