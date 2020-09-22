#pragma once

#include "Actor.h"
#include "Player.h"

class EnemyTurret : public Actor
{
public:
	EnemyTurret(sf::Vector2f position, sf::Vector2f direction, Player* player, sf::Vector2f hostOriginOffset);
	virtual ~EnemyTurret();

	static void setModel(std::vector<sf::Vector3f> model);
	static std::vector<sf::Vector3f> getModel();

	virtual void draw();
	virtual Actor* act(float frameTime);
	virtual Effect* onCollision(Actor* actor);

	float getHostYawAngle();
	void setHostYawAngle(float hostYawAngle);

	sf::Vector2f getHostOriginOffset();
	void setHostOriginOffset(sf::Vector2f hostOriginOffset);

private:
	static std::vector<sf::Vector3f> model;

	sf::Vector2f hostOriginOffset;

	Player* player;
	float hostYawAngle;
};

