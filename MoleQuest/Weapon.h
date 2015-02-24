#ifndef WEAPON_H_
#define WEAPON_H_


class Weapon{
	public:
		Weapon();

		Weapon(std::string n, int p,float aS, int c, int d, bool s);

		bool Owned();

		void setOwned();

    float GetAttackSpeed() const;

		std::string getName();

		int getPrice();

		int getClip();

    int GetDamage();
		
		int getFullClip();

		//Currently, these are just placeholder functions. 
		void fire();

		void reload();

		void equip();

    private:
		std::string name;
		int price;
		float atkSpe;
		int fullClip;
		int clip;
		int damage;

		//This is to indicate whether it fires in a cone fashion
		bool spread;

		//This is indicate whether it has been purchased
		bool owned;

	
	

};
#endif