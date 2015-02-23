#include "stdafx.h"
#include "Projectile.h"
#include "GameObjectManager.h"

Projectile::Projectile(sf::Vector2f player_pos, sf::Vector2i mouse_pos, sf::Vector2f player_origin, sf::IntRect player_bounds) {
  Load("images/bullet.png");

  // Set bullet position to just above the gun
  GetSprite().setPosition(player_pos.x, player_pos.y);

  // Change the angle of the bullet based on mouse position
  float bulletDirection = atan2(mouse_pos.y - GetPosition().y, mouse_pos.x - GetPosition().x);
  bulletDirection *= (180 / M_PI);
  GetSprite().setRotation(90 + bulletDirection);

  // Rotate bullet about player 
  GetSprite().setOrigin(0, sin(bulletDirection) + player_bounds.height - (player_bounds.height - player_origin.y));

  // Store angle variables for use in Update
  mouse_pos_ = mouse_pos;
  initial_pos_ = GetSprite().getPosition();
}


void Projectile::Update(int lag) {
  elapsed_time_ += lag;
  
  // Remove the projectile if has been alive too long
  if (elapsed_time_ > live_time_)
    GameObjectManager::Remove(GetObjectManagerIndex());

  // Update the projectile's position
  float Dx = mouse_pos_.x - initial_pos_.x;
  float Dy = mouse_pos_.y - initial_pos_.y;
  float Dlen = sqrt(Dx*Dx + Dy*Dy);
  Dx /= Dlen;
  Dy /= Dlen;

  GetSprite().move(Dx * velocity * lag, Dy * velocity * lag);
}

void Projectile::Draw(int lag, sf::RenderWindow& window) {
  window.draw(GetSprite());
}