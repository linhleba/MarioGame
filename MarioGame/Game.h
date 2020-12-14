#pragma once

#include <unordered_map>

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "Scence.h"
#include "define.h"

using namespace std;



class CGame
{
	static CGame* __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	double cam_x = 0.0f;
	double cam_y = -50.0f;

	int screen_width;
	int screen_height;

	unordered_map<int, LPSCENE> scenes;
	int current_scene;

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);

	// Define the default HUD Object
	int score = 90643;
	int life = 3;
	int money = 9;

public:
	void InitKeyboard();
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }
	void Init(HWND hWnd);
	void Draw(double x, double y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);

	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	void Load(LPCWSTR gameFile);
	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	void SwitchScene(int scene_id);

	int GetScreenWidth() { return screen_width; }
	int GetScreenHeight() { return screen_height; }

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

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	void SetCamPos(double x, double y) { cam_x = x; cam_y = y; }

	static CGame* GetInstance();

	// HUD - get the value
	int GetScore() { return score; }
	int GetMoney() { return money; }

	double GetCamX() { return cam_x; }
	double GetCamY() { return cam_y; }

	~CGame();
};


