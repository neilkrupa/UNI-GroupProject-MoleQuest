//  SettingsMenu.h
//  This file is part of MoleQuest
//
//  This class loads and displays the settings menu in a simliar manner
//  to the main menu. The input also handled here and then passed
//  back to Game.cc where the game state is handled based on what 
//  option is picked. Key mapping is also handled here via a hashmap which
//  maps a key to the function, such as 'Foward' to 'W' and so on. 
//  Majority of this code is a copy of Mark's MainMenu.cc

#ifndef SETTINGS_MENU_H_
#define SETTINGS_MENU_H_

#include "Game.h"

class SettingsMenu {
public:
	SettingsMenu();

	enum class Result { kExit, kMap, kNothing, kBack };

	Result Show(sf::RenderWindow &window);
	
	void UpdateMenu(std::map<std::string, Game::Input> key_map_);
	
	std::string tomap;

private:
	struct SettingsItem {
	 public:
		sf::Rect<int> rect;

		//This is to identify the control that needs mapping
		std::string name;

    sf::Text key;

		Result result;
	};

	// Continously polls for window events to see what the user clicks on on 
	// the main menu. Returns the result of HandleClick()
	Result GetMenuResponse(sf::RenderWindow &window);

	// Takes in the coordinates of the mouse click and checks if it intersects
	// the bounds of any of the button regions on the main menu. If it does it
	// will return the 'result' of the button clicked. See MenuItem struct.
	Result HandleClick(int x, int y);
	
	// A list of all the menu item structs to be used in HandleClick()
	std::list<SettingsItem> settings_items_;

	// For displaying the main menu image
	sf::Texture texture_;
	sf::Sprite sprite_;

  
};

#endif