//  Boss.cc
//  This file is part of MoleQuest
//
//  For purpose, see Boss.h
#include "stdafx.h"
#include "Boss.h"
#include "GameObjectManager.h"
#include "Player.h"
#include "Projectile.h"

Boss::Boss(Player* Player_, int level) {
  Load("images/boss_body.png");
  GetSprite().setPosition(500, 0);
  GetSprite().setScale(0.3, 0.3);
  GetSprite().setOrigin(500, 230);

  texture_H_.loadFromFile("images/boss_head.png");
  sprite_H_.setTexture(texture_H_);
  sprite_H_.setPosition(500, 10);
  sprite_H_.setScale(0.3, 0.3);
  sprite_H_.setOrigin(220, 0);
  
  player_ = Player_;

  stats_.max_value = 200 * level;
  stats_.curr_value = stats_.max_value;
  stats_.coins = 200 * level;
  stats_.damage = 3 * level;
  stats_.attack_speed = 1.1f * level;

  dead = false;
}

Boss::~Boss() {
}

void Boss::Update(int lag) {
  time_since_spawned += lag / 1000.f;
  last_attacked_ += lag / 1000.f;

  if (last_attacked_ >= 1.f / stats_.attack_speed && time_since_spawned >= spawning_delay) {
    Projectile* projectile = new Projectile(stats_.damage, 
      sprite_H_.getPosition(),
      (sf::Vector2i) player_->GetPosition(),
      GetSprite().getOrigin(),
      GetSprite().getTextureRect());

    projectile->SetObjectType(GameObject::kMoleProjectile);

    GameObjectManager::Add(projectile);

    last_attacked_ = 0.f;
  }
}

void Boss::Draw(int interp, sf::RenderWindow& window) {
	float x = player_->GetPosition().x;
	sprite_H_.setRotation(80 - x/6);

	window.draw(GetSprite());
  window.draw(sprite_H_);
}

void Boss::Damage(int value){
	if (stats_.curr_value > 0){
		stats_.curr_value = (stats_.curr_value - value) > 0 ? stats_.curr_value - value : 0;
	} else {
		dead = true;
		player_->Collect(stats_.coins);

    // Boss deletion is handled in Game.cc 
	}
}

void Boss::Collision(GameObject* other_object) {
  if (other_object->GetObjectType() == GameObject::kProjectile) {
    int damage = dynamic_cast<Projectile*> (other_object)->GetDamage();
    Damage(damage);

    // Remove the projectile
    GameObjectManager::Remove(other_object->GetObjectManagerIndex());
  }
}

bool Boss::IsDead() {
  return dead;
}