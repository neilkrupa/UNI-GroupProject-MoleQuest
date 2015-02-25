//  Boss.cc
//  This file is part of MoleQuest
//
//  For purpose, see Boss.h
#include "stdafx.h"
#include "Boss.h"
#include "GameObjectManager.h"
#include "Player.h"
#include <Windows.h>

Boss::Boss(Player* Player_){
  // Load the introduction animation
  texture_H_.loadFromFile("images/boss_head.png");
  sprite_H_.setTexture(texture_H_);
  sprite_H_.setPosition(500, 100);
  sprite_H_.setScale(0.5, 0.5);
  sprite_H_.setOrigin(207, 280);


  texture_B_.loadFromFile("images/boss_body.png");
  sprite_B_.setTexture(texture_B_);
  sprite_B_.setOrigin(500, 500);
  sprite_B_.setPosition(500, 100);
  sprite_B_.setScale(0.5, 0.5);

  // Store the player's memory address for use in AI logic
  player_ = Player_;

  stats_.curr_value = 200;
  stats_.max_value = 200;
  stats_.coins = 200;
  stats_.curr_level = 0;
  stats_.level_increase = 200;
  stats_.damage = 25;

  boss_pos = sprite_H_.getPosition();
}

Boss::~Boss() {
}

void Boss::Update(int lag) {
}

void Boss::Draw(int interp, sf::RenderWindow& window) {
	window.draw(sprite_B_);
	window.draw(sprite_H_);

	DealDamage(player_pos);
	float x = player_->GetPosition().x;
	sprite_H_.setRotation(80 - x/6);
	window.draw(GetSprite());
}

void Boss::DealDamage(sf::Vector2f player_pos){
	if ((player_pos.x - 500< boss_pos.x) && (player_pos.x + 500 > boss_pos.x) && (player_pos.y - 500 < boss_pos.y) && (player_pos.y + 500 > boss_pos.y)){
		player_->Damage(stats_.damage);
		Damage(1);
	}
}

void Boss::Damage(int value){
	if (stats_.curr_value != 0){
		stats_.curr_value = (stats_.curr_value - value) > 0 ? stats_.curr_value - value : 0;
	} else {
		dead = true;
		player_->Collect(stats_.coins);

		// Delete this mole
		GameObjectManager::Remove(GetObjectManagerIndex());
	}
}
