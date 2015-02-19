#include "stdafx.h"
#include "Projectile.h"

Projectile::Projectile(sf::Vector2f player_pos, sf::Vector2i mouse_pos) {
  Load("images/bullet.png");
  GetSprite().setPosition(player_pos.x, player_pos.y - 45);
}

void Projectile::Update(int lag) {
  // Remove the projectile if it is no longer visible

  // Update the projectile's position
}

void Projectile::Draw(int lag, sf::RenderWindow& window) {
  window.draw(GetSprite());
}