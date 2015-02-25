#ifndef HEAVYMOLE_H_
#define HEAVYMOLE_H_

#include "Player.h"
#include "Mole.h"

class HeavyMole :public Mole{
public:
	HeavyMole(Player* p, int xpos);
	~HeavyMole();
private:

};
#endif