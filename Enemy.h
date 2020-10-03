#pragma once

#include "Actor.h"
#include "Weapon.h"
#include "Model.h"
#include "OBJECT_ID.h"

#include <SFML\System\Vector2.hpp>

class Enemy :
	public Actor
{
public:
	Enemy(sf::Vector3f position, sf::Vector3f direction, OBJECT_ID id, Model& model);
	Enemy(sf::Vector3f position, sf::Vector3f direction, OBJECT_ID id, Model& model, std::vector<void(*)(Enemy&, float)> behaviours);
	virtual ~Enemy();

	void setBehaviours(std::vector<void(*)(Enemy&, float)> behaviours);
	std::vector<void(*)(Enemy&, float)> getBehaviours();

	virtual void act(float frameTime) override;
	virtual void onCollision(Actor& other) override;
	virtual void draw() override;

private:
	OBJECT_ID id;
	sf::Vector2<float> direction;

	std::vector<void (*)(Enemy&, float)> behaviours;

	Model& model;
	std::vector<Weapon> weapons;

};

class EnemyFactory
{
public:
	static Enemy* getEnemy(sf::Vector3f position, sf::Vector3f direction, OBJECT_ID id);

private:
	EnemyFactory();
};