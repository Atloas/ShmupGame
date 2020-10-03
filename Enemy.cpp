#include "Enemy.h"

#include "ModelManager.h"
#include "Behaviours.h"

Enemy::Enemy(sf::Vector3f position, sf::Vector3f direction, OBJECT_ID id, Model& model): Actor(position, direction), model(model)
{
	this->id = id;
}

Enemy::Enemy(sf::Vector3f position, sf::Vector3f direction, OBJECT_ID id, Model & model, std::vector<void(*)(Enemy&, float)> behaviours): Enemy(position, direction, id, model)
{
	this->behaviours = behaviours;
}


Enemy::~Enemy()
{
}

void Enemy::setBehaviours(std::vector<void(*)(Enemy&, float)> behaviours)
{
	this->behaviours = behaviours;
}

std::vector<void(*)(Enemy&, float)> Enemy::getBehaviours()
{
	return behaviours;
}

void Enemy::act(float frameTime)
{
	for (unsigned int i = 0; i < behaviours.size(); i++)
	{
		behaviours.at(i)(*this, frameTime);
	}
	for (unsigned int i = 0; i < weapons.size(); i++)
	{
		weapons.at(i).act(frameTime);
	}
}

void Enemy::onCollision(Actor & other)
{
	if (other.getId() == OBJECT_ID::PLAYER)
		health = 0;

	//TODO: Check other party's collision damage
	health--;
	if (health > 0)
		return;
	else
	{
		setActive(false);
		setAlive(false);
		//TODO: Put an event on the queue that states this enemy died, with enemy type and coordinates
		return;
	}
}

void Enemy::draw()
{
	model.draw(getPosition(), getDirection());
}

EnemyFactory::EnemyFactory()
{

}

Enemy* EnemyFactory::getEnemy(sf::Vector3f position, sf::Vector3f direction, OBJECT_ID id)
{
	Model& model = ModelManager::getModel(id);
	std::vector<void(*)(Enemy&, float)> behaviours;
	Enemy* enemy = new Enemy(position, direction, id, model);
	switch (id) {
	case OBJECT_ID::ENEMY_PLANE:
		behaviours.push_back(Behaviours::moveForwards);
		enemy->setBehaviours(behaviours);
		enemy->setMoveSpeed(1.0f);
		break;
	}
	return enemy;
}

