#include "Actor.h"

#include "Utils.h"

Actor::Actor(sf::Vector2f position, sf::Vector2f direction) : GameObject(position)
{
	active = true;
	collideable = false;
	setDirection(direction);
}


Actor::~Actor()
{

}

float Actor::getYawAngle()
{
	return yawAngle;
}

void Actor::setYawAngle(float yawAngle)
{
	this->yawAngle = yawAngle;
}

float Actor::getSpeed()
{
	return speed;
}

void Actor::setSpeed(float speed)
{
	this->speed = speed;
}

float Actor::getCollisionRadius2()
{
	return collisionRadius2;
}

int Actor::getCollisionIdentifier()
{
	return collisionIdentifier;
}

int Actor::getCollisionGroup()
{
	return collisionGroup;
}

sf::Vector2f Actor::getDirection()
{
	return direction;
}

void Actor::setDirection(sf::Vector2f direction)
{
	this->direction = direction;
	yawAngle = Utils::convertToDegrees(Utils::getAngleFromUpwards(direction));
}

int Actor::getHealth()
{
	return health;
}

void Actor::setHealth(int health)
{
	this->health = health;
}

bool Actor::getActive()
{
	return active;
}

void Actor::setActive(bool active)
{
	this->active = active;
}

bool Actor::getCollideable()
{
	return collideable;
}

void Actor::setCollideable(bool collideable)
{
	this->collideable = collideable;
}
