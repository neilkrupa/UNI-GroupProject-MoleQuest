//  MainMenu.cc
//  This file is part of MoleQuest
//
//  For purpose, see MainMenu.h

#include "stdafx.h"
#include "MainMenu.h"
#include <windows.h>

MainMenu::MainMenu() {
  // Load the main menu image
  texture_.loadFromFile("images/mainmenu.png");
  sprite_.setTexture(texture_);

  // Add clickable regions around the buttons
  MenuItem play;
  play.rect.top = 406;
  play.rect.left = 391;
  play.rect.width = 234;
  play.rect.height = 80;
  play.result = kPlay;

  MenuItem settings;
  settings.rect.top = 489;
  settings.rect.left = 391;
  settings.rect.width = 234;
  settings.rect.height = 80;
  settings.result = kSettings;

  MenuItem exit;
  exit.rect.top = 574;
  exit.rect.left = 391;
  exit.rect.width = 234;
  exit.rect.height = 80;
  exit.result = kExit;

  // Add the items to the list
  menu_items_.push_back(play);
  menu_items_.push_back(settings);
  menu_items_.push_back(exit);
}

MainMenu::Result MainMenu::Show(sf::RenderWindow &window) {
  window.draw(sprite_);
  window.display();

  // Now drop into an event loop waiting for the user to click
  // a button on the image that is now displayed
  return GetMenuResponse(window);
}

MainMenu::Result MainMenu::HandleClick(int x, int y) {
  std::list<MenuItem>::iterator itr;

  // There is probably a smarter more efficient way to do this but doesn't
  // matter /too/ much with only 3 items
  for (itr = menu_items_.begin(); itr != menu_items_.end(); itr++) {
    sf::Rect<int> menuItemRect = itr->rect;

    // Check if mouse click was within the bounds of a given menu item
    if (menuItemRect.contains(sf::Vector2<int>(x, y)))
      return itr->result;
  }

  return kNothing;
}

MainMenu::Result MainMenu::GetMenuResponse(sf::RenderWindow &window) {
  sf::Event event;

  // Continously poll for events waiting for the user to click on a
  // button or close the program
  while (true) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::MouseButtonPressed) {
        Result result = HandleClick(event.mouseButton.x, event.mouseButton.y);

        if (result != kNothing)
          return result;
      }

      if (event.type == sf::Event::Closed)
        return kExit;
    }

    // Reduces cpu usage a lot during the main menu
    Sleep(1);
  }
}