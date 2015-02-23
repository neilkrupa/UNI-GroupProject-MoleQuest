#include "stdafx.h"
#include "Projectile.h"
#include "GameObjectManager.h"

Projectile::Projectile(sf::Vector2f player_pos, sf::Vector2i mouse_pos, sf::Vector2f player_origin) {
  Load("images/bullet.png");

  int y = player_pos.y - player_origin.y;

  GetSprite().setPosition(player_pos.x, y);
}

void Projectile::Update(int lag) {
  elapsed_time_ += lag;

  // Remove the projectile if has been alive too long
  if (elapsed_time_ > live_time_)
    GameObjectManager::Remove(GetObjectManagerIndex());

  // Update the projectile's position
}

void Projectile::Draw(int lag, sf::RenderWindow& window) {
  window.draw(GetSprite());
}