#pragma once

#include "Effect.h"

enum EXPLOSION_SIZE 
{
	SMALL,
	MEDIUM,
	LARGE
};

class Explosion : public Effect
{
public:
	Explosion(sf::Vector2f position, EXPLOSION_SIZE size);
	Explosion(sf::Vector2f position, float radius, float maxRadius, float expansionTime, float duration, float fadeTime);
	virtual ~Explosion();

	void draw();
	void tick(float frameTime);

	float getRadius();

	float getMaxRadius();

	float getExpansionTime();

	float getDuration();

	float getOpacity();

	float getFadeTime();

	float getFadeSpeed();

private:
	float radius;
	float maxRadius;
	float expansionTime;
	float expansionSpeed;
	float duration;
	float opacity;
	float fadeTime;
	float fadeSpeed;
};


