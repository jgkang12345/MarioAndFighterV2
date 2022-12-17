#pragma once

#define BRUSH_COUNT 100
#define SCENE_COUNT	5
#define PLAYER_ANIMATION_COUNT 7
#define NEFENDES_ANIMATION_COUNT 1
#define MAP_COUNT 3
#define TILESIZE 16
#define A 65
#define S 83
#define D 68
#define cameraW	150
#define cameraH 150
#define boundW 30
#define boundH 30
#define powerX 2
#define powerY 2

#define mapSqList const char* mapSq [] = {"stage1.map", "battle1.map", "stage2.map"};
#define animationSqList const const char* AnimationSeq[] = { "playerLeftMove2.spr", "playerDownMove.spr", "playerUpMove.spr", "playerIdle.spr", "playerBattleAttack.spr", "playerBattleIdel.spr", "playerBattleMove.spr", "playerBattleLAttack.spr", "playerBattleJump.spr" };