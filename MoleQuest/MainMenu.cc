#include "stdafx.h"
#include "MainMenu.h"
#include <windows.h>

MainMenu::Result MainMenu::Show(sf::RenderWindow &window) {
  

  // Load the main menu image
  sf::Texture texture;
  texture.loadFromFile("images/mainmenu.png");
  sf::Sprite sprite(texture);

  // Add clickable regions to the image around the buttons
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
  play.result = kSettings;

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

  // Draw the final image to screen
  window.draw(sprite);
  window.display();

  return GetMenuResponse(window);
}

MainMenu::Result MainMenu::HandleClick(int x, int y) {
  std::list<MenuItem>::iterator itr;

  // Go through each menu item to see if the mouse click was on one of the items
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

  while (true) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::MouseButtonPressed)
        return HandleClick(event.mouseButton.x, event.mouseButton.y);

      if (event.type == sf::Event::Closed)
        return kExit;
    }
  }
}