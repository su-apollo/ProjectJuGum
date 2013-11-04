#pragma once

#define CHARIC_SPEED				300.f

#define MAX_BULLET_NUM			100
#define MAX_ACCELBULLET_NUM		100

#define BULLET_SPEED				300.f
#define ACCELBULLET_SPEED		100.f

#define ACCELBULLET_ACCELERATION	1.f

#define SHOTBULLET_COST			5
#define SHOTACCELBULLET_COST		10

enum Skill
{
	NORMAL,
	SHOTBULLET,
	SHOTACCELBULLET
};

enum Directions
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	LEFT_UP,
	RIGHT_UP,
	LEFT_DOWN,
	RIGHT_DOWN,
	WRONG_INPUT
};

enum MENU_LIST
{
	MENU_PLAY,
	MENU_TEST,
	MENU_QUIT,
	MENU_LAST,
};

