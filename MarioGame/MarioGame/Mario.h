#pragma once

#include "GameObject.h"



class CMario : public CGameObject
{
private:
	float boostSpeed = 0;
public:

	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};