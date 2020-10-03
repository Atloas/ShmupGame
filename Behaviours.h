#pragma once

#include "Enemy.h"

class Behaviours
{
public:
	~Behaviours();

	static void moveForwards(Enemy& subject, float frameTime);

private:
	Behaviours();
};

