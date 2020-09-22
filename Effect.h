#pragma once

#include "GameObject.h"

class Effect : public GameObject
{
public:
	Effect(sf::Vector2f position);
	virtual ~Effect();

	virtual void draw() = 0;
	virtual void tick(float frameTime) = 0;

	bool operator<(Effect* effect);
};

