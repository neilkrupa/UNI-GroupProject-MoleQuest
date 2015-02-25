//  Boss.cc
//  This file is part of MoleQuest
//
//  For purpose, see Boss.h
#include "stdafx.h"
#include "Boss.h"
#include "GameObjectManager.h"
#include "Player.h"
#include "Projectile.h"

Boss::Boss(Player* Player_){
  Load("images/boss_body.png");
  GetSprite().setPosition(500, 100);
  GetSprite().setScale(0.5, 0.5);
  GetSprite().setOrigin(500, 500);

  texture_H_.loadFromFile("images/boss_head.png");
  sprite_H_.setTexture(texture_H_);
  sprite_H_.setPosition(500, 100);
  sprite_H_.setScale(0.5, 0.5);
  sprite_H_.setOrigin(207, 280);
  
  player_ = Player_;

  stats_.curr_value = 200;
  stats_.max_value = 200;
  stats_.coins = 200;
  stats_.curr_level = 0;
  stats_.level_increase = 200;
  stats_.damage = 25;

  dead = false;
}

Boss::~Boss() {
}

void Boss::Update(int lag) {
}

void Boss::Draw(int interp, sf::RenderWindow& window) {
	float x = player_->GetPosition().x;
	sprite_H_.setRotation(80 - x/6);

	window.draw(GetSprite());
  window.draw(sprite_H_);
}

void Boss::Damage(int value){
	if (stats_.curr_value != 0){
		stats_.curr_value = (stats_.curr_value - value) > 0 ? stats_.curr_value - value : 0;
	} else {
		dead = true;
		player_->Collect(stats_.coins);

    

		// Delete this mole
		//GameObjectManager::Remove(GetObjectManagerIndex());
	}
}

void Boss::Collision(GameObject* other_object) {
  if (other_object->GetObjectType() == GameObject::kProjectile) {
    int damage = dynamic_cast<Projectile*> (other_object)->GetDamage();
    Damage(damage);
  }
}

bool Boss::IsDead() {
  return dead;
}