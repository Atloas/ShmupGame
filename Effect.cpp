#include "Effect.h"

Effect::Effect(sf::Vector3f position) : GameObject(position)
{
	position.z = 70.0f;
}

Effect::~Effect()
{

}

bool Effect::operator<(Effect * effect)
{
	return this->getHeight() < effect->getHeight();
}
