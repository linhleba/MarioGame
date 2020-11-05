#pragma once
#include <windows.h>

//Define main.
#define WINDOW_CLASS_NAME L"MARIO"
#define MAIN_WINDOW_TITLE L"MARIO GAME"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(156, 252, 240)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

// Define Play Scene
#define SCENE_SECTION_UNKNOWN			-1
#define SCENE_SECTION_TEXTURES			2
#define SCENE_SECTION_SPRITES			3
#define SCENE_SECTION_ANIMATIONS		4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS			6

#define OBJECT_TYPE_MARIO				0
#define OBJECT_TYPE_BRICK				1
#define OBJECT_TYPE_GOOMBA				2
#define OBJECT_TYPE_KOOPAS				3
#define OBJECT_TYPE_BOBJECT				4
#define OBJECT_TYPE_QUESTION			5
#define OBJECT_TYPE_PIPE				6
#define OBJECT_TYPE_COLORBRICK			7
#define OBJECT_TYPE_COIN				8
#define OBJECT_TYPE_FIREBALL			9
#define OBJECT_TYPE_ITEM				10
#define OBJECT_TYPE_PORTAL				50

#define MAX_SCENE_LINE					1024



//Define Game
#define DIRECTINPUT_VERSION				0x0800
#define KEYBOARD_BUFFER_SIZE			1024

// Define Gameobject
#define ID_TEX_BBOX						-100		// special texture to draw object bounding box

// Define Mario.h
#define INDEX_ANI_HIGH_SPEED_LEFT		0
#define INDEX_ANI_HIGH_SPEED_RIGHT		1
#define INDEX_ANI_HOLD_RIGHT_IDLE		2
#define	INDEX_ANI_HOLD_LEFT_IDLE		3
#define INDEX_ANI_IDLE_RIGHT			4
#define INDEX_ANI_IDLE_LEFT				5
#define INDEX_ANI_HOLD_RIGHT_WALK		6
#define	INDEX_ANI_HOLD_LEFT_WALK		7
#define INDEX_ANI_BRAKE_LEFT			8
#define INDEX_ANI_RUNNING_RIGHT			9
#define INDEX_ANI_WALKING_RIGHT			10
#define INDEX_ANI_BRAKE_RIGHT			11
#define INDEX_ANI_RUNNING_LEFT			12
#define INDEX_ANI_WALKING_LEFT			13
#define INDEX_ANI_JUMPING_RIGHT			14
#define INDEX_ANI_JUMPING_LEFT			15
#define INDEX_ANI_FLYING_RIGHT			16
#define INDEX_ANI_FLYINNG_LEFT			17
#define INDEX_ANI_SHOOT_RIGHT			18
#define INDEX_ANI_SHOOT_LEFT			19

#define MARIO_WALKING_SPEED				0.08f
#define MARIO_MAX_WALKING_SPEED			0.09f
#define MARIO_MIN_WALKING_SPEED			0.07f
#define MARIO_JUMP_SPEED_Y				0.5f
#define MARIO_JUMP_HIGH_SPEED_Y			0.7f
#define MARIO_JUMP_DEFLECT_SPEED		0.4f
#define MARIO_GRAVITY					0.002f
#define MARIO_DIE_DEFLECT_SPEED			0.5f

#define MARIO_FLYING_SPEED				0.1f
// set mario fly spped
#define MARIO_FLY_SPEED_Y				0.3f

#define MARIO_ACCELERATION_SPEED		0.00010f

#define MARIO_STATE_IDLE				0
#define MARIO_STATE_WALKING_RIGHT		100
#define MARIO_STATE_WALKING_LEFT		200
#define MARIO_STATE_JUMP				300
#define MARIO_STATE_DIE					400
//#define MARIO_STATE_BRAKE			500

#define MARIO_STATE_FLYING_RIGHT		600
#define MARIO_STATE_TURN				700
#define MARIO_STATE_FLYING_LEFT			800
#define MARIO_STATE_FLYING_IDLE			900
#define MARIO_STATE_FALL_RIGHT			1000
#define MARIO_STATE_FALL_LEFT			1100
#define MARIO_STATE_FALL_IDLE			1200
#define MARIO_STATE_HIGH_SPEED_RIGHT	1300
#define MARIO_STATE_HIGH_SPEED_LEFT		1400
#define MARIO_STATE_JUMP_HIGH_SPEED		1500
#define MARIO_STATE_SITDOWN				1600

#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_SMALL_IDLE_RIGHT		2
#define MARIO_ANI_SMALL_IDLE_LEFT		3


#define MARIO_ANI_BIG_WALKING_RIGHT		4
#define MARIO_ANI_BIG_WALKING_LEFT		5
#define MARIO_ANI_BIG_RUNNING_RIGHT		57
#define MARIO_ANI_BIG_RUNNING_LEFT		58
#define MARIO_ANI_SMALL_WALKING_RIGHT	6
#define MARIO_ANI_SMALL_WALKING_LEFT	7


#define MARIO_ANI_DIE					8
#define MARIO_ANI_BIG_BRAKING_RIGHT     9
#define MARIO_ANI_BIG_BRAKING_LEFT      10
#define MARIO_ANI_BIG_JUMPING_RIGHT     11
#define MARIO_ANI_BIG_JUMPING_LEFT		12
#define MARIO_ANI_SMALL_JUMPING_RIGHT	13
#define MARIO_ANI_SMALL_JUMPING_LEFT	14
#define MARIO_ANI_SMALL_BRAKING_RIGHT	29
#define MARIO_ANI_SMALL_BRAKING_LEFT	30

#define MARIO_ANI_BIG_HOLD_RIGHT_IDLE	41
#define MARIO_ANI_BIG_HOLD_LEFT_IDLE	42
#define MARIO_ANI_BIG_HOLD_RIGHT_WALK	43
#define MARIO_ANI_BIG_HOLD_LEFT_WALK	44
#define MARIO_ANI_BIG_HIT_RIGHT			45
#define MARIO_ANI_BIG_HIT_LEFT			46
#define MARIO_ANI_BIG_HIGHSPEED_LEFT	61
#define MARIO_ANI_BIG_HIGHSPEED_RIGHT	62
#define MARIO_ANI_BIG_FLY_LEFT			63
#define MARIO_ANI_BIG_FLY_RIGHT			64
#define MARIO_ANI_BIG_SIT_RIGHT			75
#define	MARIO_ANI_BIG_SIT_LEFT			76	

#define MARIO_ANI_SMALL_HOLD_RIGHT_IDLE	47
#define MARIO_ANI_SMALL_HOLD_LEFT_IDLE	48
#define MARIO_ANI_SMALL_HOLD_RIGHT_WALK	49
#define MARIO_ANI_SMALL_HOLD_LEFT_WALK	50
#define MARIO_ANI_SMALL_HIT_RIGHT		51
#define MARIO_ANI_SMALL_HIT_LEFT		52
#define MARIO_ANI_SMALL_HIGHSPEED_LEFT	65
#define MARIO_ANI_SMALL_HIGHSPEED_RIGHT	66
#define MARIO_ANI_SMALL_FLY_LEFT		67
#define MARIO_ANI_SMALL_FLY_RIGHT		68

#define MARIO_ANI_FIRE_IDLE_RIGHT		15
#define MARIO_ANI_FIRE_IDLE_LEFT		16
#define MARIO_ANI_FIRE_WALKING_RIGHT	17
#define MARIO_ANI_FIRE_WALKING_LEFT		18
#define MARIO_ANI_FIRE_JUMPING_RIGHT	19
#define MARIO_ANI_FIRE_JUMPING_LEFT		20
#define MARIO_ANI_FIRE_BRAKING_RIGHT	31
#define MARIO_ANI_FIRE_BRAKING_LEFT		32
#define MARIO_ANI_FIRE_HIGHSPEED_LEFT	69
#define MARIO_ANI_FIRE_HIGHSPEED_RIGHT	70
#define MARIO_ANI_FIRE_FLY_LEFT			71
#define MARIO_ANI_FIRE_FLY_RIGHT		72
#define MARIO_ANI_FIRE_SIT_RIGHT		77
#define MARIO_ANI_FIRE_SIT_LEFT			78

#define MARIO_ANI_TAIL_IDLE_RIGHT		21
#define MARIO_ANI_TAIL_IDLE_LEFT		22
#define MARIO_ANI_TAIL_WALKING_RIGHT	23
#define MARIO_ANI_TAIL_WALKING_LEFT		24
#define MARIO_ANI_TAIL_JUMPING_RIGHT	25
#define MARIO_ANI_TAIL_JUMPING_LEFT		26
#define MARIO_ANI_TAIL_BRAKING_RIGHT	33
#define MARIO_ANI_TAIL_BRAKING_LEFT		34
#define MARIO_ANI_TAIL_FLYING_LEFT_BOTTOM 35
#define MARIO_ANI_TAIL_FLYING_LEFT_TOP	36
#define MARIO_ANI_TAIL_FLYINNG_RIGHT_BOTTOM 37
#define MARIO_ANI_TAIL_FLYING_RIGHT_TOP		38
#define MARIO_ANI_TAIL_TURNING_LEFT		39
#define MARIO_ANI_TAIL_TURNING_RIGHT	40
#define MARIO_ANI_TAIL_FALL_RIGHT_BOTTOM 53
#define MARIO_ANI_TAIL_FALL_RIGHT_TOP	54
#define MARIO_ANI_TAIL_FALL_LEFT_BOTTOM	55
#define MARIO_ANI_TAIL_FALL_LEFT_TOP	56
#define MARIO_ANI_TAIL_RUNNING_RIGHT	59
#define MARIO_ANI_TAIL_RUNNING_LEFT		60
#define MARIO_ANI_TAIL_HIGHSPEED_LEFT	73
#define MARIO_ANI_TAIL_HIGHSPEED_RIGHT	74
#define MARIO_ANI_TAIL_SIT_RIGHT		79
#define MARIO_ANI_TAIL_SIT_LEFT			80

#define MARIO_ANI_BIG_SHOOT_LEFT		27
#define MARIO_ANI_BIG_SHOOT_RIGHT		28


#define	MARIO_LEVEL_SMALL				1
#define	MARIO_LEVEL_BIG					2
#define MARIO_LEVEL_FIRE				3
#define MARIO_LEVEL_TAIL				4

#define MARIO_BIG_BBOX_WIDTH			12
#define MARIO_BIG_BBOX_HEIGHT			27

#define MARIO_SMALL_BBOX_WIDTH			11
#define MARIO_SMALL_BBOX_HEIGHT			15

#define MARIO_FIRE_BBOX_WIDTH			12
#define MARIO_FIRE_BBOX_HEIGHT			26

#define MARIO_TAIL_BBOX_WIDTH			11
#define MARIO_TAIL_BBOX_HEIGHT			28

#define MARIO_UNTOUCHABLE_TIME			2000



// Define Koopas

#define KOOPAS_WALKING_SPEED			0.03f

#define KOOPAS_BBOX_WIDTH				16
#define KOOPAS_BBOX_HEIGHT				26
#define KOOPAS_BBOX_HEIGHT_DIE			16
// make a little to avoid collision with ground
#define KOOPAS_BBOX_HEIGHT_SHELL		14

#define KOOPAS_STATE_WALKING			100
#define KOOPAS_STATE_DIE				200
#define KOOPAS_STATE_RUNNING_SHELL_RIGHT 300
#define KOOPAS_STATE_RUNNING_SHELL_LEFT 400
#define KOOPAS_STATE_DIE_FALL			500

#define KOOPAS_ANI_WALKING_LEFT			0
#define KOOPAS_ANI_WALKING_RIGHT		1
#define KOOPAS_ANI_DIE					2
#define KOOPAS_ANI_RENEW				3
#define	KOOPAS_ANI_RUNNING_SHELL		4



// Define Goomba
#define GOOMBA_WALKING_SPEED			0.05f

#define GOOMBA_BBOX_WIDTH				16
#define GOOMBA_BBOX_HEIGHT				15
#define GOOMBA_BBOX_HEIGHT_DIE			9

#define GOOMBA_STATE_WALKING			100
#define GOOMBA_STATE_DIE				200
#define GOOMBA_STATE_DISAPPEAR			300

#define GOOMBA_ANI_WALKING				0
#define GOOMBA_ANI_DIE					1


// Define Coin
#define COIN_STATE_DISAPPEAR			100

// Define Question
#define QUESTION_STATE_MOVEMENT			100
#define	QUESTION_STATE_BLANK			200

#define QUESTION_ANI_MOVEMENT			0
#define QUESTION_ANI_BLANK				1


// Define Item

#define ITEM_STATE_DISAPPEAR			100
#define ITEM_STATE_MUSHROOM_APPEAR		200
#define ITEM_STATE_LEAF_APPEAR			300

#define ITEM_ANI_MUSHROOM				0
#define	ITEM_ANI_LEAF					1