#ifndef NORMAL_MOLE_H_
#define MORMAL_MOLE_H_

#include "Player.h"
#include "Mole.h"

class NormalMole : public Mole {
public:
  NormalMole(Player* p, int);
  ~NormalMole();
private:
};

#endif