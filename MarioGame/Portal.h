#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 

	double width;
	double height;
public:
	CPortal(double l, double t, double r, double b, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	int GetSceneId() { return scene_id; }
};