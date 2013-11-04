#pragma once

#define CHARIC_SPEED		500.f

#define MAX_BULLET_NUM	100
#define BULLET_SPEED		300.f

#define SHOTBULLETCOST	5

enum Skill
{
	NORMAL,
	SHOTBULLET,
	BULLETSHOWERSHOT
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

