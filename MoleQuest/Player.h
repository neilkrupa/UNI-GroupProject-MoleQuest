#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "AnimationHandler.h"

class Player : public GameObject {
 public:
  Player();
  ~Player();

  void Update(float lag);
  void Draw(float interp, sf::RenderWindow& window);

  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();
  void Jump();

  float GetVelocityX();
  float GetVelocityY();

 private:
  AnimationHandler* animation_handler_;

  float velocity_x_;
  float velocity_y_;
  bool is_moving_;
};

#endif