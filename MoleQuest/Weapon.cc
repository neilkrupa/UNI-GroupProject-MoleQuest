#include "stdafx.h"
#include "Weapon.h"
#include <sstream>

Weapon::Weapon(){}

Weapon::Weapon (std::string n, int p, float aS, int c, int d, bool s){
	name = n;
	price = p;
	atkSpe = aS;
	fullClip = c;
	damage = d;
	spread = s;	

	clip = fullClip;
	owned = false;

}

void Weapon::fire(){
	clip -= 1;
}

void Weapon::reload(){
	clip = fullClip;
}

void Weapon::setOwned(){
	owned = true;
}

bool Weapon::Owned(){
	return owned;
}

int Weapon::getClip(){
	return clip;
}

int Weapon::getFullClip(){
	return fullClip;
}

int Weapon::getPrice(){
	return price;
}

int Weapon::GetDamage() {
  return damage;
}

std::string Weapon::getName(){
	return name;
}

float Weapon::GetAttackSpeed() const {
  return atkSpe;
}