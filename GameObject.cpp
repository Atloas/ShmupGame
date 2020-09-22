#include "GameObject.h"

#include "Utils.h"

GameObject::GameObject(sf::Vector2f position)
{
	setPosition(position);
	timer = 0.0f;
	alive = true;
}

GameObject::~GameObject()
{

}

int GameObject::getId()
{
	return id;
}

bool GameObject::getAlive()
{
	return alive;
}

void GameObject::setAlive(bool alive)
{
	this->alive = alive;
}

sf::Vector2f GameObject::getPosition()
{
	return position;
}

void GameObject::setPosition(sf::Vector2f position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}

float GameObject::getHeight()
{
	return height;
}

void GameObject::setHeight(float height)
{
	this->height = height;
}
