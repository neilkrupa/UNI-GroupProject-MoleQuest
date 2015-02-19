#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "GameObject.h"

class Projectile : public GameObject {
 public:
  Projectile(sf::Vector2f, sf::Vector2i);
  
  void Update(int lag);
  void Draw(int lag, sf::RenderWindow& window);

 private:
};

#endif