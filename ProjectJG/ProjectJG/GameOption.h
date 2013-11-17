#pragma once

#define CHAR_SPEED						200.f
#define CHAR_FAST_SPEED					300.f
#define CHAR_HIT_RADIUS					5.f

#define BULLET_HIT_RADIUS				10.f

#define MAX_BULLET_NUM					500
#define MAX_SATELLITE_NUM				20

#define BULLET_SPEED						200.f
#define ACCELBULLET_SPEED				100.f
#define CURVEBULLET_SPEED				200.f

#define ACCELBULLET_ACCEL				300.f
#define CURVEBULLET_ANGULAR_ACCEL		30.f

#define SHOT_BULLET_COST					5
#define SHOT_ACCELBULLET_COST			10
#define SECTOR_SINGLE_COST				3
#define TORNADO_SINGLE_COST				3
#define SETUP_SATELLITE_COST				10
#define SL_SECTORNORMAL_COST				10

#define SHOT_POINT						20.f

enum ECharcterStage
{
	FIRST_STAGE_CHAR,
};

enum EBulletType
{
	NORMAL_BULLET,
	ACCEL_BULLET,
	CURVE_BULLET
};

enum ESkill
{
	NORMAL,
	SHOT_BULLET,
	SHOT_ACCELBULLET,
	SHOT_SECTOR_NORMAL,
	SHOT_SECTOR_MIX,
	SHOT_TORNADO,
	SETUP_SATELLITE,
	SL_SECTORNORMAL,
};

enum EInputSetUp
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	LEFT_UP,
	RIGHT_UP,
	LEFT_DOWN,
	RIGHT_DOWN,
	SKILL_KEY_ONE,
	SKILL_KEY_TWO,
	SKILL_KEY_THREE,
	SKILL_KEY_FOUR,
	SKILL_KEY_FIVE,
	SKILL_KEY_SIX,
	UPGRADE_KEY,
	CHANGE_SPEED,
	PAUSE
};

enum EMenuList
{
	MENU_PLAY,
	MENU_TEST,
	MENU_QUIT,
	MENU_LAST,
};

