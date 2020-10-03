#pragma once

#include <SFML\System\Vector3.hpp>
#include <SFML\System\Vector2.hpp>
#include <vector>

#include "OBJECT_ID.h"
#include "CollisionGroups.h"

class GameObject
{
public:
	virtual ~GameObject();

	virtual void draw() = 0;

	virtual int getId();

	virtual bool getAlive();
	virtual void setAlive(bool alive);

	virtual sf::Vector3f getPosition();
	virtual void setPosition(sf::Vector3f postition);

	virtual float getHeight();
	virtual void setHeight(float height);

protected:
	GameObject();
	GameObject(sf::Vector3f position);

	int id;
	bool alive;

	sf::Vector3f position;	//Z for display purposes only

	float timer;
};