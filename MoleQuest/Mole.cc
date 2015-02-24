#include "stdafx.h"
#include "Mole.h"
#include "GameObjectManager.h"

Mole::Mole(Player* player){
	dead = false;
	GetSprite().scale(0.5, 0.5);
  GetSprite().setPosition(1024 / 2, 100);
	sf::Vector2f mole_pos = GetSprite().getPosition();
  // Store the player's memory address for use in AI logic
  player_ = player;

  Load("images/moles/normalMole.png");
}

Mole::~Mole() {}

void Mole::SetImage() {
	if (mole_.type==1){
		Load("images/moles/tankMole.png");
	}
	if (mole_.type==2){
		Load("images/moles/fastMole.png");
	}
}

void Mole::Update(int lag) {
	if (!(dead)){
		sf::Vector2f player_pos = player_->GetPosition();
		UpdatePosition();
		if ((player_pos.x - 5 > mole_pos.x) || (player_pos.x + 5 < mole_pos.x)){
			if (player_pos.x > mole_pos.x){
				mole_.velocity_x_ += mole_.max_velocity_;
			}
			if (player_pos.x < mole_pos.x){
				mole_.velocity_x_ -= mole_.max_velocity_;
			}
		}
		if ((player_pos.y - 5 > mole_pos.y) || (player_pos.y + 5 < mole_pos.y)){
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
void Mole::DealDamage(sf::Vector2f player_pos){
	if ((player_pos.x - 40< mole_pos.x) && (player_pos.x + 40 > mole_pos.x) && (player_pos.y - 40 < mole_pos.y) && (player_pos.y + 40 > mole_pos.y)){
		player_->Damage(mole_.damage);
		Damage(3);
	}
}

void Mole::Damage(int value){
	if (mole_.curr_value!=0){
		mole_.curr_value = (mole_.curr_value - value) > 0 ? mole_.curr_value - value : 0;
	}	else {
		dead = true;
		player_->Collect(mole_.coins);

    // Delete this mole
    GameObjectManager::Remove(GetObjectManagerIndex());
	}
}

void Mole::Draw(int interp, sf::RenderWindow& window) {
	if (!(dead)){
		sf::Vector2f player_pos = player_->GetPosition();
		UpdatePosition();
		float angle = atan2(mole_pos.y - player_pos.y, mole_pos.x - player_pos.x);
		angle *= (float)(180 / M_PI);
		GetSprite().setRotation(90 + angle);
		window.draw(GetSprite());
	}
}
void Mole::UpdatePosition(){
	mole_pos = GetSprite().getPosition();
}

void Mole::Collision(GameObject*) {}