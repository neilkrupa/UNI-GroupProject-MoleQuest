#include "stdafx.h"
#include "Projectile.h"
#include "GameObjectManager.h"
#include "Mole.h"

Projectile::Projectile(int damage, sf::Vector2f player_pos, sf::Vector2i mouse_pos, sf::Vector2f player_origin, sf::IntRect player_bounds) {
  Load("images/bullet.png");

  // Set projectile damage
  damage_ = damage;

  // Set bullet position to just above the gun
  GetSprite().setPosition(player_pos.x, player_pos.y);

  // Change the angle of the bullet based on mouse position
  float bulletDirection = atan2(mouse_pos.y - GetPosition().y, mouse_pos.x - GetPosition().x);
  bulletDirection *= (float) (180 / M_PI);
  GetSprite().setRotation(90 + bulletDirection);

  // Rotate bullet about player 
  GetSprite().setOrigin(0, sin(bulletDirection) + player_bounds.height - (player_bounds.height - player_origin.y));

  // Noramlise the vector between initial bullet pos and mouse pos
  // so the projectile will travel at same speed regardless of actual distance of mouse
  // from the initial bullet position
  Dx_ = mouse_pos.x - GetSprite().getPosition().x;
  Dy_ = mouse_pos.y - GetSprite().getPosition().y;
  float normal = sqrt(Dx_*Dx_ + Dy_*Dy_);
  Dx_ /= normal;
  Dy_ /= normal;
}


void Projectile::Update(int lag) {
  elapsed_time_ += lag;

  // Remove the projectile if it has been alive too long
  if (elapsed_time_ >= live_time_)
    GameObjectManager::Remove(GetObjectManagerIndex());

  GetSprite().move(Dx_ * velocity * lag, Dy_ * velocity * lag);
}

void Projectile::Draw(int lag, sf::RenderWindow& window) {
  window.draw(GetSprite());
}

void Projectile::Collision(GameObject* other_object) {
  if (other_object->GetObjectType() == GameObject::kMole && GetObjectType() != GameObject::kMoleProjectile) {
    // Deal damage to mole
    dynamic_cast<Mole*> (other_object)->Damage(damage_);

    // Remove this projectile
    GameObjectManager::Remove(GetObjectManagerIndex());
  }
}

int Projectile::GetDamage() const {
  return damage_;
}