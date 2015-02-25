#ifndef MOLE_H_
#define MOLE_H_

#include "GameObject.h"
#include "AnimationHandler.h"
#include "Player.h"

class Mole : public GameObject {
public:
	Mole(Player* Player_, int xpos);
	~Mole();
	void Set();
  void Update(int lag);
	void Draw(int interp, sf::RenderWindow& window);
	void DealDamage(sf::Vector2f player_pos);
  void Collision(GameObject*);
  void Damage(int value);
	void UpdatePosition();
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
		int position_;
};
	sf::Vector2f mole_pos;
	struct Stat mole_;
	Player *player_;
	bool dead;
  int xpos_;
	
private:
	int randomNumber;
	sf::Vector2f player_pos;	
};
#endif