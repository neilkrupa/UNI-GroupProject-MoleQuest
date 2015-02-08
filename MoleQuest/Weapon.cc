#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon (std::string n, int p, float aS, int c, int d, bool s){
	name = n;
	price = p;
	atkSpe = aS;
	clip = c;
	damage = d;
	spread = s;

	owned = false;

}

int Weapon::Purchase(){
	if (owned == false){
		owned = true;
		return price;
	}
	return 0;

}

std::string Weapon::getName(){
	return name;
}