//  Pause.cc
//  This file is part of MoleQuest


#include "stdafx.h"
#include "Pause.h"
#include <Windows.h>

Pause::Pause() {
	// Load the pause menu image
	texture_.loadFromFile("images/pause.png");
	sprite_.setTexture(texture_);

	// Add clickable regions around the buttons
	PauseItem play;
	play.rect.top = 340;
	play.rect.left = 395;
	play.rect.width = 215;
	play.rect.height = 70;
	play.result = Result::kPlay;

	PauseItem settings;
	settings.rect.top = 420;
	settings.rect.left = 395;
	settings.rect.width = 215;
	settings.rect.height = 70;
	settings.result = Result::kSettings;

	PauseItem menu;
	menu.rect.top = 500;
	menu.rect.left = 395;
	menu.rect.width = 215;
	menu.rect.height = 70;
	menu.result = Result::kMenu;

	// Add the items to the list
	pause_items_.push_back(play);
	pause_items_.push_back(settings);
	pause_items_.push_back(menu);
}

Pause::Result Pause::Show(sf::RenderWindow &window) {
	window.draw(sprite_);
	window.display();

	// Now drop into an event loop waiting for the user to click
	// a button on the image that is now displayed
	return GetMenuResponse(window);
}

Pause::Result Pause::HandleClick(int x, int y) {
	for (const auto obj : pause_items_) {
		sf::Rect<int> menuItemRect = obj.rect;

		if (menuItemRect.contains(sf::Vector2<int>(x, y)))
			return obj.result;
	}

	return Result::kNothing;
}

Pause::Result Pause::GetMenuResponse(sf::RenderWindow &window) {
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
        
		Sleep(1);
	}
}