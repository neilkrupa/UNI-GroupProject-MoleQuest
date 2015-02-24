#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"
#include "AnimationHandler.h"
#include "Weapon.h"

class Player : public GameObject {
 public:
  Player();
  ~Player();

  void Update(int lag);
  void Draw(int interp, sf::RenderWindow& window);
  void Collision(GameObject*);

  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();
  void Jump();
  
  //Takes an int to indicated direction of the switch then chnages the active weapon to the next owned one
  void Switch(int dir);
 

  //These two functions make use of the basic Weapon functions to shoot and reload guns
  void Shoot();
  
  void Reload();
  //Takes an int as the damage value and reduces player health by the amount. 
  //It uses a algorithm to update the health bar to correspond to the reduced health
  void Damage(int value);
  
  //Like the damage, takes an int to increase the coins amount and update HUD
  void Collect(int amount);
  
  //This function is called by Draw() to update the HUD each time a change occurs.
  void DrawHUD(sf::RenderWindow &window);
  
  void Buy(std::string purchase);
  void Upgrade(std::string upgradable);

  int GetHealthLevel() const;
  int GetSpeedLevel() const;

  float GetVelocityX() const;
  float GetVelocityY() const;

  float GetLastFiredTime() const;

  bool GetReload();

  sf::IntRect GetTextureRect();

  Weapon GetWeapon() const;

 private:
  AnimationHandler* animation_handler_;

  struct Stat {
   public:
		//Max and current health
		int curr_value;
		int max_value;

    // Cost of upgrading this stat
		int cost;
    // Amount the cost will increase per level
    int cost_increase;

		//Max and current level
		int curr_level;
		int max_level;
		// Amount each level will increase the value
		int level_increase;
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

  std::map<std::string, int> weapon_indexes_;
  std::vector<Weapon> weapons_;

  Stat health_;
  Stat speed_;

  Weapon curr_weapon_;

  int weapon_switch_timeout_ = 200;
  int weapon_switch_elapsed_ = 0;
  float weapon_last_fired_ = 0;
  
  int reload_elapsed = 0;
  int reload_time = 1000;
  bool reload;  

  // A vector containing all the rect sizes for the different guns
  // to be used in the animation handler 
  std::vector<sf::IntRect> texture_sizes_;
  // A vector containing all the origins of the different gun textures
  std::vector<sf::Vector2f> texture_origins_;
};

#endif