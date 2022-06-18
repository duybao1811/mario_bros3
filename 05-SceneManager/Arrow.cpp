#include "Arrow.h"

CArrow::CArrow(float x, float y) {
	this->x = x;
	this->y = y;
}

void CArrow::Render() {
	CAnimations::GetInstance()->Get(ARROW_ANI_ID)->Render(x, y);
}