#include "HUD.h"
#include "Font.h"
#include <string>

CHUD::CHUD(float x, float y) {

	this->x = x;
	this->y = y;
	now_time = -1;
}

string CHUD::FillNumber(string s, UINT fillNumber)
{
	while (s.size() < fillNumber) {
		s = "0" + s;
	}
	return s;
}

void CHUD::Render(CMario* mario, int RemainingTime)
{
	now_time = GetTickCount64();
	CAnimations::GetInstance()->Get(ID_ANI_HUD)->Render(x, y);
	font.Draw(x - 62, y + 5, FillNumber(std::to_string(mario->GetScore()), 7)); //score
}
