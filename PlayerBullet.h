#pragma once

#include "Actor.h"

#include <vector>

class PlayerBullet : public Actor
{
public:
	PlayerBullet(sf::Vector3f position, sf::Vector3f direction);
	virtual ~PlayerBullet();

	static void setModel(std::vector<sf::Vector3f> model);
	static std::vector<sf::Vector3f> getModel();

	virtual void draw();
	virtual void act(float frameTime);
	virtual Effect* onCollision(Actor* actor);

private:
	static std::vector<sf::Vector3f> model;
};

