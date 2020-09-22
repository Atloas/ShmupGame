#include "HurtFlash.h"

#include <SFML\OpenGL.hpp>

#include "Config.h"

HurtFlash::HurtFlash(float fadeTime)
{
	height = 98.0f;

	opacity = 0.0f;
	this->fadeTime = fadeTime;
	fadeSpeed = 1.0f;
}


HurtFlash::~HurtFlash()
{
}

void HurtFlash::tick(float frameTime)
{
	if (opacity > 0.0f)
	{
		opacity -= fadeSpeed * frameTime;
		if (opacity < 0.0f)
		{
			opacity = 0.0f;
		}
	}
}

void HurtFlash::draw()
{
	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.3f, 0.3f, opacity);
	glVertex3f(-PLAY_FIELD_WIDTH_2, -PLAY_FIELD_HEIGHT_2, height);
	glVertex3f(PLAY_FIELD_WIDTH_2, -PLAY_FIELD_HEIGHT_2, height);
	glVertex3f(PLAY_FIELD_WIDTH_2, PLAY_FIELD_HEIGHT_2, height);
	glVertex3f(-PLAY_FIELD_WIDTH_2, PLAY_FIELD_HEIGHT_2, height);
	glEnd();
}

void HurtFlash::setOpacity(float opacity)
{
	fadeSpeed = opacity / fadeTime;
	this->opacity = opacity;
}
