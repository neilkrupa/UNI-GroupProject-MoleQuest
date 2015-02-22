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
	
  //void Damage(int value);
	
private:
  Player *player_;
  float velocity_x_;
  float velocity_y_;
  sf::Vector2f mole_pos;
  sf::Vector2f player_pos;
  void UpdatePosition();
  AnimationHandler* animation_handler_;
};
#endif