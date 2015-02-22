#include "stdafx.h"
#include "Mole.h"
#include "GameObjectManager.h"

Mole::Mole(Player* player){
	mole_.velocity_x_ = 0;
	mole_.velocity_y_ = 0;
	mole_.max_value = 50;
	mole_.curr_value = mole_.max_value;
	mole_.coins = 5;
	dead = false;
	Load("images/moles/normalMole.png");
	GetSprite().scale(0.5, 0.5);
  GetSprite().setPosition(1024 / 2, 100);
	sf::Vector2f mole_pos = GetSprite().getPosition();

  // Store the player's memory address for use in AI logic
  player_ = player;

	animation_handler_ = new AnimationHandler();
}

Mole::~Mole() {
	delete animation_handler_;
}

void Mole::Update(int lag) {
	if (!(dead)){
		sf::Vector2f player_pos = player_->GetPosition();
		UpdatePosition();
		if ((player_pos.x - 5 > mole_pos.x) || (player_pos.x + 5 < mole_pos.x)){
			if (player_pos.x > mole_pos.x){
				mole_.velocity_x_ += 0.1f;
			}
			if (player_pos.x < mole_pos.x){
				mole_.velocity_x_ -= 0.1f;
			}
		}
		if ((player_pos.y - 5 > mole_pos.y) || (player_pos.y + 5 < mole_pos.y)){
			if (player_pos.y > mole_pos.y){
				mole_.velocity_y_ += 0.1f;
			}
			if (player_pos.y < mole_pos.y){
				mole_.velocity_y_ -= 0.1f;
			}
		}
		DealDamage(player_pos);
		GetSprite().move(mole_.velocity_x_ * lag, mole_.velocity_y_ * lag);
		mole_.velocity_x_ = 0;
		mole_.velocity_y_ = 0;
	}
}
void Mole::DealDamage(sf::Vector2f player_pos){
	if ((player_pos.x - 10< mole_pos.x) && (player_pos.x + 10 > mole_pos.x) && (player_pos.y - 10 < mole_pos.y) && (player_pos.y + 10 > mole_pos.y)){
		player_->Damage(1);
		Damage(2);
	}
}

void Mole::Damage(int value){
	if (mole_.curr_value!=0){
		printf("Mole health current = %d\n", mole_.curr_value);
		printf("Mole damage = %d\n", value);
		mole_.curr_value = (mole_.curr_value - value) > 0 ? mole_.curr_value - value : 0;
	}
	else {
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