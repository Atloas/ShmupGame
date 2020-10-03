#pragma once

#include "Actor.h"

class Weapon :
	public Actor
{
public:
	//TODO: this
	Weapon(sf::Vector3f position, sf::Vector3f direction);
	virtual ~Weapon();

	virtual void draw() override;
	virtual void onCollision(Actor & other) override;
	virtual void act(float frameTime) override;
};

