
#pragma once
#include "GameObject.h"
#include "Utils.h"

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	double t, nx, ny;

	double dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(double t, double nx, double ny, double dx = 0, double dy = 0, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};

class CCollisionHandler
{

public:
	static void SweptAABB(
		double ml,			// move left 
		double mt,			// move top
		double mr,			// move right 
		double mb,			// move bottom
		double dx,			// 
		double dy,			// 
		double sl,			// static left
		double st,
		double sr,
		double sb,
		double& t,
		double& nx,
		double& ny);

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO, LPGAMEOBJECT co1, DWORD dt);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, LPGAMEOBJECT co1, vector<LPCOLLISIONEVENT>& coEvents, DWORD dt);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		double& min_tx,
		double& min_ty,
		double& nx,
		double& ny,
		double& rdx, double& rdy);

	bool CheckIntersectCollision(double left_object1, double right_object1, double top_object1, double bottom_object1, double left_object2, double right_object2, double top_object2, double bottom_object2);
};
