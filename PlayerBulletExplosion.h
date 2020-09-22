#pragma once

#include "Effect.h"

class PlayerBulletExplosion : public Effect
{
public:
	PlayerBulletExplosion(sf::Vector2f position);
	virtual ~PlayerBulletExplosion();

	void draw();
	void tick(float frameTime);
};

