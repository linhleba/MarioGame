#pragma once
#include <windows.h>

//Define main.
#define WINDOW_CLASS_NAME L"MARIO"
#define MAIN_WINDOW_TITLE L"MARIO GAME"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(156, 252, 240)
#define SCREEN_WIDTH 330
#define SCREEN_HEIGHT 300

#define MAX_FRAME_RATE 120
//Define ID Of Scene
#define ID_INTRO_SCENE	2
#define ID_PLAY_SCENE	1
#define ID_WORLD_MAP_SCENE	3
// Define SCENE
#define INDEX_OF_INTRO_SCENE	2
#define INDEX_OF_PLAY_SCENE		1
#define INDEX_OF_WORLD_MAP_SCENE	3
#define INDEX_OF_BASE_SCENE		4

#define OBJECT_TYPE_SCROLLING_BACKGROUND 51
#define OBJECT_TYPE_MARIO_GREEN			 52
#define OBJECT_TYPE_FIRST_BACKGROUND	 53
#define OBJECT_TYPE_SECOND_BACKGROUND	 54
#define OBJECT_TYPE_FINAL_BACKGROUND	 55
#define OBJECT_TYPE_NUMBER_THREE		 56
#define OBJECT_TYPE_STAR				 57
#define OBJECT_TYPE_KOOPAS_BLACK		 58
#define OBJECT_TYPE_BUSH_HIDING_MARIO	 59
#define OBJECT_TYPE_MENU_INTRO			 60
#define OBJECT_TYPE_KOOPAS_FINAL		 61
#define OBJECT_TYPE_KOOPAS_FASTER		 62

// Define Scroll Background
#define SCROLL_BACKGROUND_STATE_IDLE		100
#define SCROLL_BACKGROUND_STATE_MOVING_UP	200

#define SCROLL_BACKGROUNND_ANI			0


// Define Background 
#define BACKGROUND_STATE_DISAPPEAR	100
#define BACKGROUND_STATE_APPEAR		200
#define BACKGROUND_STATE_MOVING_DOWN 300
#define BACKGROUND_STATE_VIBRATING	400

#define FIRST_BACKGROUND_ANI		0
#define SECOND_BACKGROUND_ANI		1
#define	FINAL_BACKGROUND_ANI		2

// Define Number 3
#define NUMBER_THREE_STATE_DISAPPEAR 100
#define NUMBER_THREE_STATE_APPEAR	 200

// Define Star object
#define STAR_STATE_APPEAR			100
#define STAR_STATE_DISAPPEAR		200

// Define Menu Intro
#define MENU_INTRO_STATE_DISAPPEAR	100
#define MENU_INTRO_STATE_PLAYER1	200
#define MENU_INTRO_STATE_PLAYER2	300

#define MENU_INTRO_ANI_PLAYER1		0
#define MENU_INTRO_ANI_PLAYER2		1
// #=====END DEFINE SCENE =====#

// Define Wolrd Map
#define OBJECT_TYPE_MARIO				0
#define OBJECT_TYPE_HELP				1
#define OBJECT_TYPE_GOLD_DIGGER			2
#define OBJECT_TYPE_BUSH				3
#define OBJECT_TYPE_NODE				4
//#===== DEFINE HUD ======
#define OBJECT_TYPE_HUD_PANEL			100
#define OBJECT_TYPE_HUD_MARIO_LUIGI		101
#define OBJECT_TYPE_HUD_LIFE			102
#define OBJECT_TYPE_HUD_MONEY			103
#define OBJECT_TYPE_HUD_SCORE			104
#define OBJECT_TYPE_HUD_TIME_PICKER		105
#define	OBJECT_TYPE_HUD_WORLD			106
#define OBJECT_TYPE_HUD_STACK_NORMAL	107
#define OBJECT_TYPE_HUD_STACK_MAX		108
#define OBJECT_TYPE_HUD_CARD			109
#define OBJECT_TYPE_HUD_BLACK			110

// Define ani of HUD
#define	HUD_TYPE_WORLD_ANI			1
#define	HUD_TYPE_MARIO_LUIGI_ANI	0
#define HUD_TYPE_PANEL_ANI			0
#define HUD_TYPE_BLACK_ANI			0

// Define card of HUD
#define HUD_TYPE_EMPTY_CARD_ANI			0
#define HUD_TYPE_MUSHROOM_CARD_ANI		1
#define HUD_TYPE_FIREFLOWER_CARD_ANI	2
#define HUD_TYPE_STAR_CARD_ANI			3

// Define ani of stack 
#define HUD_TYPE_STACK_NORMAL_FILLED_ANI	0
#define HUD_TYPE_STACK_MAX_FILLED_ANI		1
#define HUD_TYPE_STACK_NORMAL_EMPTY_ANI		2
#define HUD_TYPE_STACK_MAX_EMPTY_ANI		3

// Define ani number
#define HUD_TYPE_NUMBER_ZERO_ANI	0
#define HUD_TYPE_NUMBER_ONE_ANI		1
#define HUD_TYPE_NUMBER_TWO_ANI		2
#define HUD_TYPE_NUMBER_THREE_ANI	3
#define HUD_TYPE_NUMBER_FOUR_ANI	4
#define HUD_TYPE_NUMBER_FIVE_ANI	5
#define HUD_TYPE_NUMBER_SIX_ANI		6
#define HUD_TYPE_NUMBER_SEVEN_ANI	7
#define HUD_TYPE_NUMBER_EIGHT_ANI	8
#define HUD_TYPE_NUMBER_NINE_ANI	9




// ==== END DEFINE HUD====
// Dfine ani of Object world map
#define BUSH_ANI_APPEAR					0
#define HELP_ANI_APPEAR					1
#define GOLD_DIGGER_ANI_WALKING_RIGHT	2
#define GOLD_DIGGER_ANI_WALKING_LEFT	3


#define MARIO_WORLDMAP_ANI_APPEAR		0

// Define state
#define OBJECT_STATE_APPEAR				100
#define OBJECT_STATE_DISAPPEAR			200
#define GOLD_DIGGER_STATE_WALKING_RIGHT	300
#define GOLD_DIGGER_STATE_WALKING_LEFT	400

// Define direction of vector
#define VECTOR_INDEX_LEFT_DIRECTION		0
#define VECTOR_INDEX_RIGHT_DIRECTION	1
#define VECTOR_INDEX_TOP_DIRECTION		2
#define VECTOR_INDEX_BOTTOM_DIRECTION	3

// Define mario state
#define MARIO_STATE_NOT_MOVING			100
#define MARIO_STATE_MOVING_UP			200
#define MARIO_STATE_MOVING_DOWN			300
#define MARIO_STATE_MOVING_LEFT			400
#define MARIO_STATE_MOVING_RIGHT		500



// #=== END OF DEFINE WORLD MAP===#


// Define Play Scene
#define SCENE_SECTION_UNKNOWN			-1
#define SCENE_SECTION_TEXTURES			2
#define SCENE_SECTION_SPRITES			3
#define SCENE_SECTION_ANIMATIONS		4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS			6

#define OBJECT_TYPE_MARIO_RED				0
#define OBJECT_TYPE_BRICK				1
#define OBJECT_TYPE_GOOMBA				2
#define OBJECT_TYPE_KOOPAS_GREEN_NORMAL	3
#define OBJECT_TYPE_BOBJECT				4
#define OBJECT_TYPE_QUESTION			5
#define OBJECT_TYPE_PIPE				6
#define OBJECT_TYPE_COLORBRICK			7
#define OBJECT_TYPE_COIN				8
#define OBJECT_TYPE_FIREBALL			9
#define OBJECT_TYPE_ITEM				10
#define OBJECT_TYPE_FLOWER				11
#define OBJECT_TYPE_FIREFLOWER			12	
#define OBJECT_TYPE_BREAKABLEBRICK		13
#define OBJECT_TYPE_PLETTER				14
#define	OBJECT_TYPE_COINQUESTION		15
#define OBJECT_TYPE_KOOPAS_GREEN_FLYING	16
#define OBJECT_TYPE_KOOPAS_RED_NORMAL	17
#define OBJECT_TYPE_GOOMBA_FLYING		18
#define OBJECT_TYPE_SCORE				19
#define OBJECT_TYPE_TAIL				20

#define OBJECT_TYPE_FINAL_CARD			120
#define OBJECT_TYPE_PORTAL				50

#define MAX_SCENE_LINE					1024

// Define score ani
#define SCORE_STATE_DISAPPEAR			100
#define SCORE_STATE_APPEAR				200

#define SCORE_APPEAR_ANI				0
#define TIME_OF_SCORE_DISAPPEARING		300

// Define item final cards
#define CARD_STATE_MUSHROOM				100
#define CARD_STATE_FIRE_FLOWER			200
#define CARD_STATE_STAR					300
#define CARD_STATE_MUSHROOM_MOVING		400
#define CARD_STATE_FIRE_FLOWER_MOVING	500
#define CARD_STATE_STAR_MOVING			600

#define CARD_SPEED_OF_MOVING			-0.09f

// Define ani of the final cards
#define CARD_ANI_FLOWER_IDLE			0
#define CARD_ANI_MUSHROOM_IDLE			1
#define CARD_ANI_STAR_IDLE				2
#define CARD_ANI_FLOWER_UP				3
#define CARD_ANI_MUSHROOM_UP			4
#define CARD_ANI_STAR_UP				5

// Define the pos of number
#define VECTOR_INDEX_HUNDREDS_POSITION	0
#define VECTOR_INDEX_TENS_POSITION		1
#define VECTOR_INDEX_UNITS_POSITION		2

//Define time
#define	TIME_MARIO_APPEARED				1800
#define TIME_MARIO_GREEN_JUMP			2940

//Define Game
//#define DIRECTINPUT_VERSION				0x0800
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
#define MARIO_JUMP_DEFLECT_SPEED		0.5f
#define MARIO_GRAVITY					0.002f
#define MARIO_DIE_DEFLECT_SPEED			0.5f
#define MARIO_FALLING_SPEED_Y			0
#define MARIO_GRAVITY_FALLING_SPEED		0.001f

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

//DEFINE STATE FOR INTRO SCENE
#define MARIO_STATE_BEING_HITTED		1700
#define MARIO_STATE_LOOKING_AHEAD		1800

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
#define MARIO_ANI_SMALL_RUNNING_RIGHT	81
#define MARIO_ANI_SMALL_RUNNING_LEFT	82
#define	MARIO_ANI_SMALL_SHOOT_RIGHT		83
#define MARIO_ANI_SMALL_SHOOT_LEFT		84

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
#define MARIO_ANI_FIRE_HOLD_RIGHT_IDLE	85
#define MARIO_ANI_FIRE_HOLD_LEFT_IDLE	86
#define MARIO_ANI_FIRE_HOLD_RIGHT_WALK	87
#define MARIO_ANI_FIRE_HOLD_LEFT_WALK	88
#define	MARIO_ANI_FIRE_SHOOT_RIGHT		89
#define MARIO_ANI_FIRE_SHOOT_LEFT		90
#define MARIO_ANI_FIRE_RUNNING_RIGHT	91
#define MARIO_ANI_FIRE_RUNNING_LEFT		92
#define MARIO_ANI_FIRE_FIRING_RIGHT		99
#define MARIO_ANI_FIRE_FIRING_LEFT		100



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
#define MARIO_ANI_TAIL_HOLD_RIGHT_IDLE	93
#define MARIO_ANI_TAIL_HOLD_LEFT_IDLE	94
#define MARIO_ANI_TAIL_HOLD_RIGHT_WALK	95
#define MARIO_ANI_TAIL_HOLD_LEFT_WALK	96
#define	MARIO_ANI_TAIL_SHOOT_RIGHT		97
#define MARIO_ANI_TAIL_SHOOT_LEFT		98

//DEFINE TAIL MARIO
#define TAIL_STATE_DISAPPEARING			100
#define TAIL_STATE_MOVING				200

#define TAIL_ANI_MOVING					0
#define SPEED_OF_MOVING_TAIL			0.3

// DEFINE IN INTRO SCENE
#define MARIO_GREEN_ANI_BIG_IDLE_RIGHT			101
#define MARIO_GREEN_ANI_BIG_IDLE_LEFT			102
#define MARIO_GREEN_ANI_BIG_WALKING_RIGHT		103
#define MARIO_GREEN_ANI_BIG_WALKING_LEFT		104
#define MARIO_GREEN_ANI_BIG_JUMPING_RIGHT		105
#define MARIO_GREEN_ANI_BIG_JUMPING_LEFT		106
#define MARIO_GREEN_ANI_BIG_HOLDING_IDLE_RIGHT	107
#define MARIO_GREEN_ANI_BIG_HOLDING_IDLE_LEFT	108
#define MARIO_GREEN_ANI_BIG_HOLDING_RIGHT		109
#define MARIO_GREEN_ANI_BIG_HOLDING_LEFT		110
#define MARIO_GREEN_ANI_BIG_KICKING_RIGHT		111
#define MARIO_GREEN_ANI_BIG_KICKING_LEFT		112
#define MARIO_GREEN_ANI_JUMP_FALL_RIGHT			113
#define MARIO_GREEN_ANI_JUMP_FALL_LEFT			114
#define MARIO_GREEN_ANI_BIG_RUNNING_RIGHT		115
#define MARIO_GREEN_ANI_BIG_RUNNING_LEFT		116
#define MARIO_RED_ANI_KOOPAS_HIT				117
#define MARIO_RED_ANI_LEFT_LOOK_AHEAD			118
// END DEFINE IN INTRO SCENE
#define MARIO_ANI_BIG_SHOOT_LEFT		27
#define MARIO_ANI_BIG_SHOOT_RIGHT		28


#define	MARIO_LEVEL_SMALL				1
#define	MARIO_LEVEL_BIG					2
#define MARIO_LEVEL_TAIL				3
#define MARIO_LEVEL_FIRE				4

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
#define KOOPAS_STATE_RENEW				600
#define KOOPAS_STATE_FLYING				700
#define KOOPAS_STATE_DISAPPEAR			800
#define KOOPAS_STATE_FALL				900

#define KOOPAS_ANI_WALKING_LEFT			0
#define KOOPAS_ANI_WALKING_RIGHT		1
#define KOOPAS_ANI_DIE					2
#define KOOPAS_ANI_RENEW				3
#define	KOOPAS_ANI_RUNNING_SHELL		4
#define KOOPAS_ANI_FLYING				5
#define KOOPAS_RED_ANI_RENEW			6
#define KOOPAS_RED_ANI_RUNNING_SHELL	7
#define KOOPAS_RED_ANI_WALKING_LEFT		8
#define KOOPAS_RED_ANI_WALKING_RIGHT	9
#define KOOPAS_RED_ANI_DIE				10
// DEFINE IN INTRO SCENE
#define KOOPAS_BLACK_ANI_DIE_FACEDOWN	11
#define KOOPAS_BLACK_ANI_DIE_FACEUP		12



// Define Goomba
#define GOOMBA_WALKING_SPEED			0.03f

#define GOOMBA_BBOX_WIDTH				16
#define GOOMBA_BBOX_HEIGHT				15
#define GOOMBA_BBOX_HEIGHT_DIE			9
#define GOOMBA_RED_FLY_BBOX_HEIGHT		24
#define GOOMBA_FLYING_BBOX_WIDTH		20

#define GOOMBA_STATE_WALKING			100
#define GOOMBA_STATE_DIE				200
#define GOOMBA_STATE_DISAPPEAR			300
#define GOOMBA_STATE_FLYING				400
#define GOOMBA_STATE_FALL				500

#define GOOMBA_ANI_WALKING				0
#define GOOMBA_ANI_DIE					1
#define GOOMBA_ANI_FLYING				2
#define GOOMBA_ANI_RED_WALKING			3
#define GOOMBA_ANI_RED_DIE				4

//*** DEFINE IN INTRO SCENE ***
#define GOOMBA_ANI_IDLE					5


// Define Coin and coin question
#define COIN_STATE_DISAPPEAR			100


#define COIN_STATE_MOVING_UP			200
#define COIN_STATE_MOVING_DOWN			300

// Define Question
#define QUESTION_STATE_MOVEMENT			100
#define	QUESTION_STATE_BLANK			200

#define QUESTION_ANI_MOVEMENT			0
#define QUESTION_ANI_BLANK				1


// Define Item

#define ITEM_STATE_DISAPPEAR			100
#define ITEM_STATE_MUSHROOM_APPEAR		200
#define ITEM_STATE_LEAF_APPEAR			300
#define ITEM_STATE_LEAF_UP_MOVING		400
#define ITEM_STATE_LEAF_DOWN_MOVING		500

#define ITEM_ANI_MUSHROOM				0
#define	ITEM_ANI_LEAF_LEFT				1
#define ITEM_ANI_LEAF_RIGHT				2

// Define flower
#define FLOWER_STATE_LEFT_BOTTOM		100
#define FLOWER_STATE_RIGHT_BOTTOM		200
#define FLOWER_STATE_GROWING_UP			300
#define FLOWER_STATE_GROWING_DOWN		400
#define FLOWER_STATE_IDLE				500
#define FLOWER_STATE_DIE				600

#define FLOWER_ANI_RED_LEFT_BOTTOM		0
#define FLOWER_ANI_RED_RIGHT_BOTTOM		1
#define FLOWER_ANI_GREEN_LEFT_BOTTOM	2
#define FLOWER_ANI_GREEN_RIGHT_BOTTOM	3
#define FLOWER_ANI_RED_TOP				4
#define FLOWER_ANI_RED_TOP_LEFT			5
#define FLOWER_ANI_RED_TOP_RIGHT		6
#define FLOWER_ANI_GREEN_TOP_LEFT		7
#define FLOWER_ANI_GREEN_TOP_RIGHT		8


#define FLOWER_POSITION_RED				1	
#define FLOWER_POSITION_GREEN			2
#define FLOWER_POSITION_RED_UP			3

#define FLOWER_TOP_LIMITATION			70
#define FLOWER_BOTTOM_LIMITATION		118

#define FLOWER_TOP_RED_UP_LIMITATION	86

// Define fire flower
#define FIRE_FLOWER_STATE_DISAPPEAR		100
#define FIRE_FLOWER_STATE_APPEAR_LONG_DISTANCE	200
#define FIRE_FLOWER_STATE_APPEAR_SHORT_DISTANCE	300

// Define breakable brick
#define BREAKBRICK_STATE_DISAPPEAR		100
#define BREAKBRICK_STATE_APPEAR			200
#define BREAKBRICK_STATE_BLANK_QUESTION	300
#define BREAKBRICK_STATE_COIN			400

#define BREAKBRICK_ANI_APPEAR			0
#define BREAKBRICK_ANI_BLANKQUESTION	1
#define BREAKBRICK_ANI_COIN				2

// Define P Letter
#define PLETTER_STATE_DISAPPEAR			100
#define PLETTER_STATE_APPEAR			200
#define PLETTER_STATE_SMALL_APPEAR		300

#define PLETTER_ANI_APPEAR				0
#define PLETTER_ANI_SMALL_APPEAR		1
