#ifndef MOLE_H_
#define MOLE_H_

#include "GameObject.h"
#include "AnimationHandler.h"
#include "Player.h"

class Mole : public GameObject {
public:
	Mole(Player* Player_);
	~Mole();
	
  void Update(int lag);
	void Draw(int interp, sf::RenderWindow& window);
	void DealDamage(sf::Vector2f player_pos);
  void Damage(int value);

	struct Stat {
	public:
		//Max and current health
		int curr_value;
		int max_value;
		//Number of coins to be dropped
		int coins;
		//speed of the mole
		float velocity_x_;
		float velocity_y_;
	};
	
private:
  Player *player_;
	sf::Vector2f mole_pos;
	sf::Vector2f player_pos;
	bool dead;
	void UpdatePosition();
	struct Stat mole_;
};
#endif