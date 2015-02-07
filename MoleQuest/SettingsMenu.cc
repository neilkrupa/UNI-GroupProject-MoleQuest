
#include "stdafx.h"
#include "SettingsMenu.h"
#include <Windows.h>

SettingsMenu::SettingsMenu() {
	texture_.loadFromFile("images/settingsmenu.png");
	sprite_.setTexture(texture_);

	// Add clickable regions around the buttons
	SettingsItem foward;
	foward.rect.top = 325;
	foward.rect.left = 170;
	foward.rect.width = 668;
	foward.rect.height = 44;
	foward.result = Result::kMap;
	foward.name = "foward";

	SettingsItem backwards;
	backwards.rect.top = 370;
	backwards.rect.left = 170;
	backwards.rect.width = 668;
	backwards.rect.height = 44;
	backwards.result = Result::kMap;
	backwards.name = "backwards";

	SettingsItem left;
	left.rect.top = 414;
	left.rect.left = 170;
	left.rect.width = 668;
	left.rect.height = 44;
	left.result = Result::kMap;
	left.name = "left";

	SettingsItem right;
	right.rect.top = 458;
	right.rect.left = 170;
	right.rect.width = 668;
	right.rect.height = 44;
	right.result = Result::kMap;
	right.name = "right";

	SettingsItem cyclel;
	cyclel.rect.top = 370;	//TODO: Adjust value when menu image has been updated
	cyclel.rect.left = 170;
	cyclel.rect.width = 668;
	cyclel.rect.height = 44;
	cyclel.result = Result::kMap;
	cyclel.name = "cyclel";

	SettingsItem cycler;
	cycler.rect.top = 370;	//TODO: Adjust value when menu image has been updated
	cycler.rect.left = 170;
	cycler.rect.width = 668;
	cycler.rect.height = 44;
	cycler.result = Result::kMap;
	cycler.name = "cycler";

	SettingsItem pause;
	pause.rect.top = 370;	
	pause.rect.left = 170;
	pause.rect.width = 668;
	pause.rect.height = 44;
	pause.result = Result::kMap;
	pause.name = "pause";

	SettingsItem back;
	back.rect.top = 690;
	back.rect.left = 414;
	back.rect.width = 179;
	back.rect.height = 54;
	back.result = Result::kBack;
	back.name = "back";

	// Add the items to the list
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

