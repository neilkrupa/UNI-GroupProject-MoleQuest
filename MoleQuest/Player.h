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
  
  //Takes an int to indicated direction of the switch then chnages the active weapon to the next owned one
  void Switch(int dir);
 
  //This is just a placeholder as shooting is subject to change based on projectile code. 
  //As of now, it calls a fire fucntion in the weapon class
  void Shoot();
  
  //Takes an int as the damage value and reduces player health by the amount. 
  //It uses a algorithm to update the health bar to correspond to the reduced health
  void Damage(int value);
  
  //Like the damage, takes an int to increase the coins amount and update HUD
  void Collect(int amount);
  
  //This function is called in the game loop to update the HUD each time a change occurs.
  void DrawHUD(sf::RenderWindow &window);
  
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

		//Max and current health
		int value;
		int max;

		int cost;
		//Max and current level
		int level;
		int maxlevel;
		//This is the amount the cost will increase per level
		int increase;
		//This is the amount each level will increase the value
		int amount;
  }; 

  int coins;

  float velocity_x_;
  float velocity_y_;
  bool is_moving_;
  
   //HUD Variables
  sf::Sprite hpBar;
  sf::Texture hpTex;
  sf::Text hpVal;

  sf::Sprite coinBar;
  sf::Texture coinTex;
  sf::Text coinVal;

  sf::Sprite ammoBar;
  sf::Texture ammoTex;
  sf::Text clipVal;
  sf::Text maxclipVal;

  sf::Font f;
  
  std::list<Weapon> weapons_;
  std::list<Stat> stats_;
  
};

#endif