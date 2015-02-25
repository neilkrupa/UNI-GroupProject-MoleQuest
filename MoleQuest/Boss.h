//  Boss.h
//  This file is part of MoleQuest
//
//  This class handles the Boss mole spawning and AI.
#ifndef BOSS_H_
#define BOSS_H_

#include "GameObject.h"
#include "AnimationHandler.h"
#include "Player.h"

class Boss : public GameObject {
 public:
	Boss(Player* Player_, int);
	~Boss();

	void Update(int lag);
	void Draw(int interp, sf::RenderWindow& window);

	//For the loading of boss moles head and body.
	sf::Texture texture_H_;
	sf::Sprite sprite_H_;

	void Damage(int value);
	void DealDamage(sf::Vector2f player_pos);
	
  bool IsDead();

  void Collision(GameObject*);

 private:
	Player *player_;

	struct Stat {
	 public:
		//Max and current health
		int curr_value;
		int max_value;

		// Coins boss gives on death
		int coins;

		// Damage
		int damage;

    // Attack speed for projectiles
    float attack_speed;
	};

	Stat stats_;

  bool dead;

  float last_attacked_ = 0.f;

  float spawning_delay = 3.f;
  float time_since_spawned = 0.f;
};

#endif