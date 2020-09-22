#pragma once

#include "Actor.h"
#include "EnemyTurret.h"
#include "Player.h"

class EnemyBoat : public Actor
{
public:
	EnemyBoat(sf::Vector2f position, sf::Vector2f direction, Player* player);
	virtual ~EnemyBoat();

	static void setModel(std::vector<sf::Vector3f> model);
	static std::vector<sf::Vector3f> getModel();

	virtual void draw();
	virtual Actor* act(float frameTime);
	virtual Effect* onCollision(Actor* actor);

	virtual void setDirection(sf::Vector2f direction);

	void setActive(bool active); //ETC, has to be redone since active needs to be set for the boat and turret at the same time, and turret is only accessible through boat
	void setAlive(bool alive);
	void setCollideable(bool collideable);

	EnemyTurret* getTurret();
	void setTurret(EnemyTurret* turret);

private:
	static std::vector<sf::Vector3f> model;

	EnemyTurret* turret;
};

