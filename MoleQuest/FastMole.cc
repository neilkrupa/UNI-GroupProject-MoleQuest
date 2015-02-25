#include "stdafx.h"
#include "FastMole.h"

FastMole::FastMole(Player* p) :Mole(p){
	mole_.velocity_x_ = 0;
	mole_.velocity_y_ = 0;
	mole_.max_velocity_ = 0.25;
	mole_.max_value = 3;
	mole_.curr_value = mole_.max_value;
	mole_.coins = rand() % 30;
	mole_.type = 2;
	mole_.damage = 30;
	mole_.position_ = rand() % 1024;
	Set();
  GetSprite().setScale(1, 1);
}
FastMole::~FastMole() {}