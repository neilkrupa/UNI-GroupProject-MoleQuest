#ifndef MOLE_H_
#define MOLE_H_

#include "GameObject.h"
#include "AnimationHandler.h"
#include "Player.h"

class Mole : public GameObject {
public:
	Mole(Player* Player_);
	~Mole();
	void SetImage();
  void Update(int lag);
	void Draw(int interp, sf::RenderWindow& window);
	void DealDamage(sf::Vector2f player_pos);
  void Damage(int value);
	sf::Texture moleImage;
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
		float max_velocity_;
		int damage;
		int type;
};
	struct Stat mole_;
	Player *player_;
private:
  
	sf::Vector2f mole_pos;
	sf::Vector2f player_pos;
	bool dead;
	void UpdatePosition();
	
};
#endif