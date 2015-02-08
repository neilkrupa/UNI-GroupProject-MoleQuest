#ifndef WEAPON_H_
#define WEAPON_H_

#include "GameObject.h"

class Weapon : public GameObject  {
	public:
		Weapon(std::string n, int p,float aS, int c, int d, bool s);

		int Purchase();

		std::string getName();

		//Currently, these are just placeholder functions. 
		void shoot();

		void reload();

		void equip();

    private:
		std::string name;
		int price;
		float atkSpe;
		int clip;
		int damage;

		//This is to indicate whether it fires in a cone fashion
		bool spread;

		//This is indicate whether it has been purchased
		bool owned;

		//This will be where the texture for the different weapons is held
		//sf::Texture texture_;
};
#endif