#pragma once
#include "GameObject.h"
#include "algorithm"
#include "Mario.h"
#include "PlayScence.h"
class CScrollBackground : public CGameObject
{
	public:

		virtual void GetBoundingBox(double& left, double& top, double& right, double& bottom);
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		virtual void Render();
		CScrollBackground();
		virtual void SetState(int state);
};

