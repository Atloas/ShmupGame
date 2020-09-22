#include "Effect.h"

Effect::Effect(sf::Vector2f position) : GameObject(position)
{
	height = 70.0f;
}

Effect::~Effect()
{

}

bool Effect::operator<(Effect * effect)
{
	return this->getHeight() < effect->getHeight();
}
