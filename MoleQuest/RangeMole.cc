#include "stdafx.h"
#include "RangeMole.h"

RangeMole::RangeMole(Player* p) :Mole(p){
	mole_.velocity_x_ = 0;
	mole_.velocity_y_ = 0;
	mole_.max_velocity_ = 0.1;
	mole_.max_value = 50;
	mole_.curr_value = mole_.max_value;
	mole_.coins = rand() % 30;
	mole_.type = 3;
	mole_.damage = 30;
	mole_.position_ = rand() % 1024;
	Set();
	SetProjectile();
/*	game_object_manager_.Add(new Projectile(*/
}
void RangeMole::Update(int lag){
	if (!(dead)){
		sf::Vector2f player_pos = player_->GetPosition();
		UpdatePosition();
		if ((player_pos.x - 250 > mole_pos.x) || (player_pos.x + 250 < mole_pos.x)){
			if (player_pos.x > mole_pos.x){
				mole_.velocity_x_ += mole_.max_velocity_;
			}
			if (player_pos.x < mole_pos.x){
				mole_.velocity_x_ -= mole_.max_velocity_;
			}
		}
		if ((player_pos.y - 250 > mole_pos.y) || (player_pos.y + 250 < mole_pos.y)){
			if (player_pos.y > mole_pos.y){
				mole_.velocity_y_ += mole_.max_velocity_;
			}
			if (player_pos.y < mole_pos.y){
				mole_.velocity_y_ -= mole_.max_velocity_;
			}
		}
		DealDamage(player_pos);
		GetSprite().move(mole_.velocity_x_ * lag, mole_.velocity_y_ * lag);
		mole_.velocity_x_ = 0;
		mole_.velocity_y_ = 0;
	}
}

void RangeMole::SetProjectile(){
	game_object_manager_.Add(new Projectile(mole_pos = GetSprite().getPosition(),
		player_->GetPosition(),
		GetSprite().getOrigin(),
		GetSprite().getTextureRect(), 1));
}
RangeMole::~RangeMole() {}