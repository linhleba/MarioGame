#pragma once 
#include "GameObject.h"
class CMisc : public CGameObject
{
public:
	CMisc(float x, float y);
	void Update(DWORD dt);
	void Render();
};

