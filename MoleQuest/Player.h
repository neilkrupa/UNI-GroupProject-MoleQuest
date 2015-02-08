#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "AnimationHandler.h"

class Player : public GameObject {
 public:
  Player();
  ~Player();

  void Update(float lag);
  void Draw(float interp, sf::RenderWindow& window);

  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();
  void Jump();
  void Buy(std::string purchase);
  void Upgrade(std::string upgradable);

  int getHealthLevel();
  int getSpeedLevel();

  float GetVelocityX();
  float GetVelocityY();

 private:
  AnimationHandler* animation_handler_;

  struct Stat{
    public:
		std::string name;
		float value;
		int cost;
		int level;
		int max;
		//This is the amount the cost will increase per level
		int increase;
		//This is the amount each level will increase the value
		int amount;
  }; 

  int coins;

  float velocity_x_;
  float velocity_y_;
  bool is_moving_;
  
  std::list<Weapon> weapons_;
  std::list<Stat> stats_;
  
};

#endif