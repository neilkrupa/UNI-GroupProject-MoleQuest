
#include "stdafx.h"
#include "SettingsMenu.h"
#include <Windows.h>

SettingsMenu::SettingsMenu() {
	texture_.loadFromFile("images/settingsmenu.png");
	sprite_.setTexture(texture_);

	// Add clickable regions around the buttons
	SettingsItem shoot;
	shoot.rect.top = 280;
	shoot.rect.left = 155;
	shoot.rect.width = 678;
	shoot.rect.height = 44;
	shoot.result = Result::kMap;
	shoot.name = "shoot";
	shoot.key.setCharacterSize(20);
	shoot.key.setPosition( 475, 290);
	shoot.key.setString("Left Mouse");
	shoot.key.setColor(sf::Color::Black);

	SettingsItem foward;
	foward.rect.top = 326;
	foward.rect.left = 155;
	foward.rect.width = 678;
	foward.rect.height = 44;
	foward.result = Result::kMap;
	foward.name = "foward";
	foward.key.setCharacterSize(20);
	foward.key.setPosition(475, 336);
	foward.key.setString("W");
	foward.key.setColor(sf::Color::Black);

	SettingsItem backwards;
	backwards.rect.top = 372;
	backwards.rect.left = 155;
	backwards.rect.width = 678;
	backwards.rect.height = 44;
	backwards.result = Result::kMap;
	backwards.name = "backwards";
	backwards.key.setCharacterSize(20);
	backwards.key.setPosition(475, 381);
	backwards.key.setString("S");
	backwards.key.setColor(sf::Color::Black);

	SettingsItem left;
	left.rect.top = 415;
	left.rect.left = 155;
	left.rect.width = 678;
	left.rect.height = 44;
	left.result = Result::kMap;
	left.name = "left";
	left.key.setCharacterSize(20);
	left.key.setPosition(475, 425);
	left.key.setString("A");
	left.key.setColor(sf::Color::Black);

	SettingsItem right;
	right.rect.top = 461;
	right.rect.left = 155;
	right.rect.width = 678;
	right.rect.height = 44;
	right.result = Result::kMap;
	right.name = "right";
	right.key.setCharacterSize(20);
	right.key.setPosition(475, 469);
	right.key.setString("D");
	right.key.setColor(sf::Color::Black);

	SettingsItem cyclel;
	cyclel.rect.top = 504;	
	cyclel.rect.left = 155;
	cyclel.rect.width = 678;
	cyclel.rect.height = 44;
	cyclel.result = Result::kMap;
	cyclel.name = "cyclel";
	cyclel.key.setCharacterSize(20);
	cyclel.key.setPosition(475, 513);
	cyclel.key.setString("Q");
	cyclel.key.setColor(sf::Color::Black);

	SettingsItem cycler;
	cycler.rect.top = 552;	
	cycler.rect.left = 155;
	cycler.rect.width = 678;
	cycler.rect.height = 44;
	cycler.result = Result::kMap;
	cycler.name = "cycler";
	cycler.key.setCharacterSize(20);
	cycler.key.setPosition(475, 553);
	cycler.key.setString("E");
	cycler.key.setColor(sf::Color::Black);

	SettingsItem pause;
	pause.rect.top = 590;	
	pause.rect.left = 155;
	pause.rect.width = 678;
	pause.rect.height = 44;
	pause.result = Result::kMap;
	pause.name = "pause";
	pause.key.setCharacterSize(20);
	pause.key.setPosition(475, 603);
	pause.key.setString("ESC");
	pause.key.setColor(sf::Color::Black);


	SettingsItem back;
	back.rect.top = 674;
	back.rect.left = 401;
	back.rect.width = 179;
	back.rect.height = 54;
	back.result = Result::kBack;
	back.name = "back";

	// Add the items to the list
	settings_items_.push_back(shoot);
	settings_items_.push_back(foward);
	settings_items_.push_back(backwards);
	settings_items_.push_back(left);
	settings_items_.push_back(right);
	settings_items_.push_back(cyclel);
	settings_items_.push_back(cycler);
	settings_items_.push_back(pause);
	settings_items_.push_back(back);
}

SettingsMenu::Result SettingsMenu::Show(sf::RenderWindow &window) {
	window.draw(sprite_);
	sf::Font f; 
	f.loadFromFile("fonts/quest.ttf");
	for ( auto obj : settings_items_) {
			obj.key.setFont(f);
			window.draw(obj.key);
	}
	window.display();

	// Now drop into an event loop waiting for the user to click
	// a button on the image that is now displayed
	return GetMenuResponse(window);
}

SettingsMenu::Result SettingsMenu::HandleClick(int x, int y) {
	for (const auto obj : settings_items_) {
		sf::Rect<int> settingsItemRect = obj.rect;

		if (settingsItemRect.contains(sf::Vector2<int>(x, y))){
			if (obj.result == Result::kMap)
				tomap = obj.name;
			return obj.result;
		}
	}

	return Result::kNothing;
}

SettingsMenu::Result SettingsMenu::GetMenuResponse(sf::RenderWindow &window) {
	sf::Event event;

	// Continously poll for events waiting for the user to click on a
	// button or close the program
	while (true) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed) {
				Result result = HandleClick(event.mouseButton.x, event.mouseButton.y);

				if (result != Result::kNothing)
					return result;
			}

			if (event.type == sf::Event::Closed)
				return Result::kExit;
		}

		// Reduces cpu usage a lot during the main menu
		Sleep(1);
	}
}

void SettingsMenu::UpdateMenu(std::map<std::string, Game::Input> key_map_){
	std::map<std::string, Game::Input>::iterator mapCurr;
	std::list<SettingsItem>::iterator curr;

	for (mapCurr = key_map_.begin(); mapCurr != key_map_.end(); ++mapCurr){
		for (curr = settings_items_.begin(); curr != settings_items_.end(); ++curr){
			if (curr->name.compare(mapCurr->first) == 0){
				if (mapCurr->second.type == Game::InputType::kKey)
					curr->key.setString(std::to_string(mapCurr->second.KeyCode));
				else
					curr->key.setString(std::to_string(mapCurr->second.MouseButton));
				break;
			}
		}
	}
}







