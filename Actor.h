#pragma once

#include "GameObject.h"
#include "Effect.h"

class Actor : public GameObject
{
public:
	Actor(sf::Vector3f position, sf::Vector3f direction);
	virtual ~Actor();

	virtual void onCollision(Actor& other) = 0;
	virtual void act(float frameTime) = 0;

	virtual sf::Vector3f getDirection();
	virtual void setDirection(sf::Vector3f direction);

	virtual float getYawAngle();
	virtual void setYawAngle(float yawAngle);

	virtual float getMoveSpeed();
	virtual void setMoveSpeed(float speed);

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
	sf::Vector3f direction;
	float yawAngle;
	float moveSpeed;

	float collisionRadius2;
	int collisionIdentifier;
	int collisionGroup;

	int health;
	bool active;
	bool collideable;
};

