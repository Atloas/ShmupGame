#include "GameObject.h"

#include "Utils.h"

GameObject::GameObject()
{
	position = sf::Vector3<float>();
}

GameObject::GameObject(sf::Vector3f position)
{
	this->position = position;
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

sf::Vector3f GameObject::getPosition()
{
	return position;
}

void GameObject::setPosition(sf::Vector3f position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}

float GameObject::getHeight()
{
	return position.z;
}

void GameObject::setHeight(float height)
{
	this->position.z = height;
}
