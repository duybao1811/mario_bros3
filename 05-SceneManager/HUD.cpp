#include "HUD.h"
#include "Font.h"
#include <string>

CHUD::CHUD(float x, float y) {

	this->x = x;
	this->y = y;
	now_time = GetTickCount64();
}

string CHUD::FillNumber(string s, UINT fillNumber)
{
	while (s.size() < fillNumber) {
		s = "0" + s;
	}
	return s;
}

void CHUD::Render(CMario* mario, int remainingTime)
{
	now_time = GetTickCount64();
	CAnimations::GetInstance()->Get(ID_ANI_HUD)->Render(x, y);
	font.Draw(x - 62, y + 5, FillNumber(std::to_string(mario->GetScore()), 7)); //score
	font.Draw(x + 12, y + 5, FillNumber(std::to_string(remainingTime), 3));
	font.Draw(x - 76, y -4, FillNumber(std::to_string(1), 1));
	font.Draw(x + 20, y - 4, FillNumber(std::to_string(mario->GetCoin()), 1));

	power = new CPower(x - 62, y - 3, mario->powerStack);
	power->Render();
}
