#pragma once

#define BRUSH_COUNT 100
#define SCENE_COUNT	5
#define PLAYER_ANIMATION_COUNT 11
#define NEFENDES_ANIMATION_COUNT 1
#define MAP_COUNT 5
#define TILESIZE 16
#define A 65
#define S 83
#define D 68
#define cameraW	207
#define cameraH 155
#define powerX 2
#define powerY 2
#define JUMP_MAX 40
#define JUMP_POWER 3
#define mapSqList const char* mapSq [] = {"stage1.map", "battle1.map", "stage2.map", "battle2.map", "stage3.map"};
#define animationSqList const const char* AnimationSeq[] = { "playerLeftMove2.spr", "playerDownMove.spr", "playerUpMove.spr", "playerIdle.spr", "playerBattleAttack.spr", "playerBattleIdel.spr", "playerBattleMove.spr", "playerBattleLAttack.spr", "playerBattleJump.spr", "playerDead.spr", "playerBattleWin.spr" };