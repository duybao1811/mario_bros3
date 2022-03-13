#include "Platform.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l +	this->length;
	b = t + this->cellHeight;
}