#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"

class Player : public GameObject {
 public:
  Player();
  ~Player();

  void move(unsigned int w, unsigned int h);
};

#endif