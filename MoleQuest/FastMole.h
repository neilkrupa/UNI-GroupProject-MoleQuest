#ifndef FASTMOLE_H_
#define FASTMOLE_H_
#include "Player.h"
#include "Mole.h"
class FastMole :public Mole{
public:
	FastMole(Player* p, int);
	~FastMole();
private:

};
#endif