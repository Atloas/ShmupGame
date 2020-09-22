#pragma once

#include <SFML\System\Vector3.hpp>
#include <SFML\System\Vector2.hpp>
#include <vector>

#include "IDs.h"
#include "CollisionGroups.h"

class GameObject
{
public:
	GameObject(sf::Vector2f position);
	virtual ~GameObject();

	virtual void draw() = 0;

	virtual int getId();

	virtual bool getAlive();
	virtual void setAlive(bool alive);

	virtual sf::Vector2f getPosition();
	virtual void setPosition(sf::Vector2f postition);

	virtual float getHeight();
	virtual void setHeight(float height);

protected:
	int id;
	bool alive;

	sf::Vector2f position;
	float height;			//Height for display purposes only

	float timer;
};