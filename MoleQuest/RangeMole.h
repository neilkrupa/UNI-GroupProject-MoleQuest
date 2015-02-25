#ifndef RANGEMOLE_H_
#define RANGEMOLE_H_

#include "Player.h"
#include "Mole.h"


class RangeMole : public Mole {
public:
	int randomNumber;
	
  RangeMole(Player* p, int);
	~RangeMole();
	float atkSpe;
	float last_fired;
	void RangeMole::SetProjectile();
	void RangeMole::Update(int lag);
	void DealDamage(sf::Vector2f player_pos);

private:
};

#endif