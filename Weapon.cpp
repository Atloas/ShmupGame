#include "Weapon.h"

Weapon::Weapon(sf::Vector3f position, sf::Vector3f direction) : Actor(position, direction)
{
}

Weapon::~Weapon()
{
}

void Weapon::draw()
{
}

void Weapon::onCollision(Actor & other)
{
}

void Weapon::act(float frameTime)
{
}
