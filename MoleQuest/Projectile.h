#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "GameObject.h"

class Projectile : public GameObject {
 public:
  Projectile(sf::Vector2f, sf::Vector2i, sf::Vector2f);
  
  void Update(int lag);
  void Draw(int lag, sf::RenderWindow& window);

 private:
   int elapsed_time_ = 0;
   int live_time_ = 5000;
};

#endif