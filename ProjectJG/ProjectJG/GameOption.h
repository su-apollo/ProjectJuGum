#pragma once

#define WINDOW_WIDTH						1280
#define WINDOW_HEIGHT					800

#define MAIN_MAP_WIDTH					1600.f
#define MAIN_MAP_HEIGHT					1200.f
#define FRAME_WIDTH						750.f
#define FRAME_HEIGHT						750.f


#define CHAR_SPEED						200.f
#define CHAR_FAST_SPEED					300.f
#define CHAR_HIT_RADIUS					5.f
#define ASTEROID_HIT_RADIUS				50.f

#define BULLET_HIT_RADIUS				10.f

#define MAX_BULLET_NUM					1000
#define MAX_SATELLITE_NUM				50
#define MAX_ASTEROID_NUM					30

#define BULLET_SPEED						200.f
#define ACCELBULLET_SPEED				200.f
#define CURVEBULLET_SPEED				200.f

#define ACCELBULLET_ACCEL				200.f
#define CURVEBULLET_ANGULAR_ACCEL		30.f

#define SHOT_BULLET_COST					1
#define SHOT_ACCELBULLET_COST			2
#define SECTOR_SINGLE_COST				3
#define TORNADO_SINGLE_COST				3
#define SETUP_SATELLITE_COST				10
#define SL_SECTORNORMAL_COST				30

#define SHOT_POINT						20.f




#define MAIN_MENU_SCENE_BACKGROUND_SOUND		"Sound/Space_Sprinkles.mp3"
#define MAIN_MENU_SCENE_BACKGROUND_IMAGE		L"Sprite/Background.jpg"
#define MAIN_MENU_SCENE_LOGO					L"Sprite/logo.png"
#define MAIN_MAP_BACKGROUND_IMAGE				L"Sprite/Space-Background.jpg"
#define GAME_FONT_RESOURCE						L"Font/모리스-9.ttf"
#define GAME_FONT								L"모리스-9"


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

enum ESatelliteType
{
	NORMAL_SATELLITE,
	MOVE_SATELLIE,
	RUSH_SATELLIE
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
	MENU_NUM,
};


enum ENetworkMode
{
	NET_MENU_FIRST = 0,
	TEST_MODE = 0,
	CLIENT_MODE,
	SERVER_MODE,
	NET_MENU_LAST,
	NET_MENU_NONE,
};