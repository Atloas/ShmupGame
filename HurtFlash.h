#pragma once

#include "Effect.h"

class HurtFlash
{
public:
	HurtFlash(float fadeTime);
	~HurtFlash();

	void tick(float frameTime);
	void draw();

	void setOpacity(float opacity);

private:
	float height;
	float opacity;
	float fadeTime;
	float fadeSpeed;
};

