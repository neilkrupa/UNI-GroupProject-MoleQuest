#include "stdafx.h"
#include "RangeMole.h"
#include "GameObjectManager.h"
#include "Projectile.h"

RangeMole::RangeMole(Player* p) :Mole(p) {
	mole_.velocity_x_ = 0;
	mole_.velocity_y_ = 0;
	mole_.max_velocity_ = 0.1;
	mole_.max_value = 50;
	mole_.curr_value = mole_.max_value;
	mole_.coins = rand() % 30;
	mole_.type = 3;
	mole_.damage = 5;
	mole_.position_ = rand() % 1024;
	atkSpe = 1;
	last_fired = 0;
	Set();
}

RangeMole::~RangeMole() {}

void RangeMole::Update(int lag) {
	if (!(dead)) {
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
	last_fired += lag / 1000.f;
}

void RangeMole::SetProjectile(){} 

void RangeMole::DealDamage(sf::Vector2f player_pos) {
	
	if ((player_pos.x - 550 < mole_pos.x) && (player_pos.x + 550 > mole_pos.x) && (player_pos.y - 550 < mole_pos.y) && (player_pos.y + 550 > mole_pos.y)) {
		if (last_fired >= 1 / atkSpe){
      Projectile* projectile = new Projectile(mole_.damage,
				mole_pos = GetSprite().getPosition(),
				(sf::Vector2i) player_->GetPosition(),
				GetSprite().getOrigin(),
				GetSprite().getTextureRect());

			projectile->SetObjectType(GameObject::kMoleProjectile);

			GameObjectManager::Add(projectile);
			last_fired = 0;
			
		}
	}

}

