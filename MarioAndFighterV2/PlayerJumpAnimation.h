#pragma once
#include "Animation.h"
class Sprite;
class PlayerJumpAnimation : public Animation
{
public:
	Sprite* Jumping();
	Sprite* JumpEnd();
	Sprite* JumpDone();
};

