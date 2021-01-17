#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Animations.h"
#include "define.h"

using namespace std;



class CGameObject;
typedef CGameObject* LPGAMEOBJECT;




class CGameObject
{
public:

	double x;
	double y;

	double originX;
	double originY;
	int layerRender = 0;

	double dx;	// dx = vx*dt
	double dy;	// dy = vy*dt

	double vx;
	double vy;

	int nx;
	int ny;

	int state;

	bool isStaticObject = true;
	bool isActive = false;

	DWORD dt;

	LPANIMATION_SET animation_set;

public:

	virtual void Reset();
	void SetOriginPosition(double x, double y) { this->originX = x, this->originY = y; }
	void SetPosition(double x, double y) { this->x = x, this->y = y; }
	void SetSpeed(double vx, double vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(double& x, double& y) { x = this->x; y = this->y; }
	double GetDistanceX(){ return dx; }
	double GetDisTanceY(){ return dy; }
	void GetSpeed(double& vx, double& vy) { vx = this->vx; vy = this->vy; }

	int GetState() { return this->state; }

	void RenderBoundingBox();

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	CGameObject();

	virtual void GetBoundingBox(double& left, double& top, double& right, double& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	void SetIsStaticObject(bool value) { isStaticObject = value; }
	bool GetIsStaticObject() { return isStaticObject; }
	bool GetIsActive() { return isActive; }
	void SetIsActive(bool value) { isActive = value; }
	double GetOriginX() { return originX; }
	double GetOriginY() { return originY; }
	~CGameObject();
};

