#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "GameObject.h"

class Projectile : public GameObject {
 public:
  Projectile(int, sf::Vector2f, sf::Vector2i, sf::Vector2f, sf::IntRect);
  
  void Update(int lag);
  void Draw(int lag, sf::RenderWindow& window);
  void Collision(GameObject*);
  
  int GetDamage() const;

 private:
   int elapsed_time_ = 0;
   int live_time_ = 3000;

   float velocity = 1.f;

   float Dx_ = 0.f;
   float Dy_ = 0.f;

   int win_w_;
   int win_h_;

   int damage_;
};

#endif