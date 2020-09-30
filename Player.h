#pragma once

#include <vector>
#include <string>

#include <SFML\System\Vector3.hpp>

#include "Actor.h"
#include "Field.h"

class Player : public Actor
{
public:
	Player(sf::Vector3f position, sf::Vector3f direction, Field* playField);
	virtual ~Player();

	static void setModel(std::vector<sf::Vector3f> model);
	static std::vector<sf::Vector3f> getModel();

	virtual void setDirection(sf::Vector3f direction);

	virtual void draw();
	virtual void act(float frameTime);
	virtual void onCollision(Actor& actor);

	bool getShooting();
	void setShooting(bool shooting);

private:
	float getRollSpeed();

	static std::vector<sf::Vector3f> model;

	float rollAngle;
	float maxRollAngle;
	float desiredRollAngle;

	Field* playField;

	bool shooting;
};