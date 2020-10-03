#include "Actor.h"

#include "Utils.h"

Actor::Actor(sf::Vector3f position, sf::Vector3f direction) : GameObject(position)
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

float Actor::getMoveSpeed()
{
	return moveSpeed;
}

void Actor::setMoveSpeed(float moveSpeed)
{
	this->moveSpeed = moveSpeed;
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

sf::Vector3f Actor::getDirection()
{
	return direction;
}

void Actor::setDirection(sf::Vector3f direction)
{
	this->direction = Utils::normalizeVector(direction);
	//yawAngle = Utils::convertToDegrees(Utils::getAngleFromUpwards(direction));
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
