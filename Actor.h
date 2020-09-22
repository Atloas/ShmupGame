#pragma once

#include "GameObject.h"
#include "Effect.h"

class Actor : public GameObject
{
public:
	Actor(sf::Vector2f position, sf::Vector2f direction);
	virtual ~Actor();

	virtual Effect* onCollision(Actor* actor) = 0;
	virtual Actor* act(float frameTime) = 0;

	virtual sf::Vector2f getDirection();
	virtual void setDirection(sf::Vector2f direction);

	virtual float getYawAngle();
	virtual void setYawAngle(float yawAngle);

	virtual float getSpeed();
	virtual void setSpeed(float speed);

	virtual float getCollisionRadius2();
	virtual int getCollisionIdentifier();
	virtual int getCollisionGroup();

	virtual int getHealth();
	virtual void setHealth(int health);

	virtual bool getActive();
	virtual void setActive(bool active);

	virtual bool getCollideable();
	virtual void setCollideable(bool collideable);

protected:
	sf::Vector2f direction;
	float yawAngle;
	float speed;

	float collisionRadius2;
	int collisionIdentifier;
	int collisionGroup;

	int health;
	bool active;
	bool collideable;
};

