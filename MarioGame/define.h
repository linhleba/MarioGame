#pragma once
#include <windows.h>

//Define main.
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"SAMPLE 05 - SCENCE MANAGER"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

//Define Game
#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024

// Define Gameobject
#define ID_TEX_BBOX -100		// special texture to draw object bounding box

// Define Mario.h
#define MARIO_WALKING_SPEED		0.1f 
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400

#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_SMALL_IDLE_RIGHT		2
#define MARIO_ANI_SMALL_IDLE_LEFT		3


#define MARIO_ANI_BIG_WALKING_RIGHT			4
#define MARIO_ANI_BIG_WALKING_LEFT			5
#define MARIO_ANI_SMALL_WALKING_RIGHT		6
#define MARIO_ANI_SMALL_WALKING_LEFT		7


#define MARIO_ANI_DIE					8
#define MARIO_ANI_BIG_BRAKING_RIGHT     9
#define MARIO_ANI_BIG_BRAKING_LEFT      10
#define MARIO_ANI_BIG_JUMPING_RIGHT     11
#define MARIO_ANI_BIG_JUMPING_LEFT		12
#define MARIO_ANI_SMALL_JUMPING_RIGHT	13
#define MARIO_ANI_SMALL_JUMPING_LEFT	14

#define MARIO_ANI_FIRE_IDLE_RIGHT		15
#define MARIO_ANI_FIRE_IDLE_LEFT		16
#define MARIO_ANI_FIRE_WALKING_RIGHT	17
#define MARIO_ANI_FIRE_WALKING_LEFT		18
#define MARIO_ANI_FIRE_JUMPING_RIGHT	19
#define MARIO_ANI_FIRE_JUMPING_LEFT		20

#define MARIO_ANI_TAIL_IDLE_RIGHT		21
#define MARIO_ANI_TAIL_IDLE_LEFT		22
#define MARIO_ANI_TAIL_WALKING_RIGHT	23
#define MARIO_ANI_TAIL_WALKING_LEFT		24
#define MARIO_ANI_TAIL_JUMPING_RIGHT	25
#define MARIO_ANI_TAIL_JUMPING_LEFT		26

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_FIRE	3
#define MARIO_LEVEL_TAIL	4

#define MARIO_BIG_BBOX_WIDTH  12
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  11
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_FIRE_BBOX_WIDTH 12
#define MARIO_FIRE_BBOX_HEIGHT 26

#define MARIO_TAIL_BBOX_WIDTH 11
#define MARIO_TAIL_BBOX_HEIGHT 28

#define MARIO_UNTOUCHABLE_TIME 5000



// Define Koopas

#define KOOPAS_WALKING_SPEED 0.03f;

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 16

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DIE 200

#define KOOPAS_ANI_WALKING_LEFT 0
#define KOOPAS_ANI_WALKING_RIGHT 1
#define KOOPAS_ANI_DIE 2
#define KOOPAS_ANI_RENEW 3
#define	KOOPAS_ANI_RUNNING_SHELL 4


// Define Goomba
#define GOOMBA_WALKING_SPEED 0.05f;

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

#define GOOMBA_ANI_WALKING 0
#define GOOMBA_ANI_DIE 1

