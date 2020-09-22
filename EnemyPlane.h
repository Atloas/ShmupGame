#pragma once

#include "Actor.h"

#include <string>

class EnemyPlane : public Actor
{
public:
	EnemyPlane(sf::Vector2f position, sf::Vector2f direction);
	virtual ~EnemyPlane();

	static void setModel(std::vector<sf::Vector3f> model);
	static std::vector<sf::Vector3f> getModel();

	virtual void draw();
	virtual Actor* act(float frameTime);
	virtual Effect* onCollision(Actor* actor);

private:
	static std::vector<sf::Vector3f> model;
};

