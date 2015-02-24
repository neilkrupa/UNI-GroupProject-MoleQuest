#ifndef RANGEMOLE_H_
#define RANGEMOLE_H_
#include "GameObjectManager.h"
#include "Player.h"
#include "Mole.h"
#include "Projectile.h"
class RangeMole :public Mole{
public:
	int randomNumber;
	RangeMole(Player* p);
	~RangeMole();
	void RangeMole::SetProjectile();
	void RangeMole::Update(int lag);
	GameObjectManager game_object_manager_;
private:
	//Projectile projectile_;
};
#endif