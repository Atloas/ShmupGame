#include "Explosion.h"

#include <SFML\OpenGL.hpp>
#include <gl\GLU.h>
#include <cstdlib>

#include "IDs.h"

Explosion::Explosion(sf::Vector2f position, EXPLOSION_SIZE size) : Effect(position)
{
	id = EXPLOSION_ID;

	switch (size)
	{
	case EXPLOSION_SIZE::SMALL:
		radius = 0.5f;
		maxRadius = 1.0f;
		expansionTime = 0.1f;
		duration = 0.1f;
		fadeTime = 0.1f;
		break;
	case EXPLOSION_SIZE::MEDIUM:
		radius = 0.75f;
		maxRadius = 1.5f;
		expansionTime = 0.125f;
		duration = 0.15f;
		fadeTime = 0.125f;
		break;
	case EXPLOSION_SIZE::LARGE:
		radius = 1.0f;
		maxRadius = 2.5f;
		expansionTime = 0.15f;
		duration = 0.15f;
		fadeTime = 0.125f;
		break;
	}
	expansionSpeed = (maxRadius - radius) / expansionTime;
	opacity = 1.0f;
	fadeSpeed = 1.0f / fadeTime;

	height += (float)rand() / (float)RAND_MAX;
}

Explosion::Explosion(sf::Vector2f position, float radius, float maxRadius, float expansionTime, float duration, float fadeTime) : Effect(position)
{
	id = EXPLOSION_ID;

	this->radius = radius;
	this->maxRadius = maxRadius;
	this->expansionTime = expansionTime;
	this->duration = duration;
	this->fadeTime = fadeTime;

	expansionSpeed = (maxRadius - radius) / expansionTime;
	opacity = 0.0f;
	fadeSpeed = 1.0f / fadeTime;
}


Explosion::~Explosion()
{

}

void Explosion::draw()
{
	GLUquadric* quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	glPushMatrix();
	glTranslatef(position.x, position.y, height);
	glColor4f(1.0f, 0.7f, 0.0f, opacity);
	gluDisk(quadric, 0.0f, radius, 32, 4);
	glPopMatrix();
	gluDeleteQuadric(quadric);
}

void Explosion::tick(float frameTime)
{
	timer += frameTime;
	if (radius < maxRadius)
	{
		radius += expansionSpeed * frameTime;
		if (radius > maxRadius)
			radius = maxRadius;
	}
	else if (duration > 0.0f)
	{
		duration -= frameTime;
	}
	else if (opacity > 0.0f)
	{
		opacity -= fadeSpeed * frameTime;
		if (opacity < 0.0f)
			opacity = 0.0f;
	}
	else
	{
		setAlive(false);
	}
}

float Explosion::getRadius()
{
	return radius;
}

float Explosion::getMaxRadius()
{
	return maxRadius;
}

float Explosion::getExpansionTime()
{
	return expansionTime;
}

float Explosion::getDuration()
{
	return duration;
}

float Explosion::getOpacity()
{
	return opacity;
}

float Explosion::getFadeTime()
{
	return fadeTime;
}

float Explosion::getFadeSpeed()
{
	return fadeSpeed;
}
