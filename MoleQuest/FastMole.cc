#include "stdafx.h"
#include "FastMole.h"

FastMole::FastMole(Player* p) :Mole(p){
	mole_.velocity_x_ = 0;
	mole_.velocity_y_ = 0;
	mole_.max_velocity_ = 0.3;
	mole_.max_value = 3;
	mole_.curr_value = mole_.max_value;
	mole_.coins = 5;
	mole_.type = 2;
	mole_.damage = 30;
	SetImage();
}
FastMole::~FastMole() {}