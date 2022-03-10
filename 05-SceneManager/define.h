#pragma once

#define HUD_HEIGHT 32

#define TYPE_MARIO 0
#define TYPE_OBJECT 1
#define TYPE_ENEMY 2
#define TYPE_COIN 3
enum EType {
	MARIO =TYPE_MARIO,
	OBJECT = TYPE_OBJECT,
	ENEMY = TYPE_ENEMY,
	COIN = TYPE_COIN,
};


#define ENEMY_STATE_IS_ATTACKED 900 // koopas is kicked attack or tail attack
#define ENEMY_STATE_IS_FIRE_ATTACKED 901


#define ID_ANI_SCORE_EFFECT_100 500
#define ID_ANI_SCORE_EFFECT_200 501
#define ID_ANI_SCORE_EFFECT_400 502
#define ID_ANI_SCORE_EFFECT_800 503
#define ID_ANI_SCORE_EFFECT_1000 504
#define ID_ANI_SCORE_EFFECT_2000 505
#define ID_ANI_SCORE_EFFECT_4000 506
#define ID_ANI_SCORE_EFFECT_8000 507
#define ID_ANI_SCORE_EFFECT_1_UP 508