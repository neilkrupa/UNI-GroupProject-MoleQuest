#include "stdafx.h"
#include "HeavyMole.h"

HeavyMole::HeavyMole(Player* p, int xpos):Mole(p, xpos){
	srand(time(NULL));
	mole_.velocity_x_ = 0;
	mole_.velocity_y_ = 0;
	mole_.max_velocity_ = 0.03;
	mole_.max_value = 200;
	mole_.curr_value = mole_.max_value;
	mole_.coins = rand() %30;
	mole_.type = 1;
	mole_.damage = 1;
	mole_.position_ = rand() % 1024;
	Set();
}
HeavyMole::~HeavyMole() {}