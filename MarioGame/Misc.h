#pragma once 
#include "GameObject.h"
class CMisc : public CGameObject
{
public:
	CMisc(double x, double y);
	void Update(DWORD dt);
	void Render();
};

