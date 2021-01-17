#include <d3dx9.h>
#include <algorithm>


#include "Utils.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"
#include "Koopas.h"
#include "Goomba.h"
#include "Flower.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;
	ny = 1;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}


void CGameObject::Reset()
{
	/*if (this->GetState() != OBJECT_STATE_DIE && this->GetState() != OBJECT_STATE_DIE_FALL)
	{
		this->x = this->originX;
		this->y = this->originY;
		this->SetState(OBJECT_STATE_WALKING);
	}*/
}

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p((float) x, (float) y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	double l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;
	CGame::GetInstance()->Draw(x, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 64);
}


CGameObject::~CGameObject()
{

}