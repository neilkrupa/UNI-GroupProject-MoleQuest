//  Shop.h
//  This file is part of MoleQuest
//
//  This class loads and displays the shop menu at the end of each level.
//	The buttons here are directly linked to the Player, increasing health,
//  speed, and damage. 
//  The input is managed in a simliar manner to the other menus

#ifndef SHOP_H_
#define SHOP_H_

class Shop {
public:
	Shop();

	enum class Result { kExit, kBuy, kNothing, kContinue, kUpgrade };

	Result Show(sf::RenderWindow &window);

	//This function updates the shop menu when an upgrade is made 
	void UpdateMenu(int hL, int sL, int coin);

	std::string toBuy;

private:
	struct ShopItem {
	public:
		sf::Rect<int> rect;

		//This is to identify the item that needs to be applied to the player
		std::string name;

		//This is for the upgrades
		int level;

		Result result;
	};


	sf::Text coins;
	// Continously polls for window events to see what the user clicks on on 
	// the main menu. Returns the result of HandleClick()
	Result GetMenuResponse(sf::RenderWindow &window);

	// Takes in the coordinates of the mouse click and checks if it intersects
	// the bounds of any of the button regions on the main menu. If it does it
	// will return the 'result' of the button clicked. See MenuItem struct.
	Result HandleClick(int x, int y);

	// A list of all the menu item structs to be used in HandleClick()
	std::list<ShopItem> shop_items_;

	// For displaying the main menu image
	sf::Texture texture_;
	sf::Sprite sprite_;

	//Used to display the updated menu	
	sf::Texture speed_tex_;
	sf::Sprite  speed_sprite_;
	sf::Texture health_tex_;
	sf::Sprite  health_sprite_;
};

#endif