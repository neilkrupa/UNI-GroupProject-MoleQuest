//  MainMenu.h
//  This file is part of MoleQuest
//
//  This class handles the displaying of the main menu as well as 
//  geting the user input on the main menu. This input is then passed
//  back to Game.cc where the game state is handled based on what 
//  menu option was chosen.

#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

class MainMenu {
 public:
  MainMenu();

  // An enumeration to hold all the possible actions that can be invoked
  // on the main menu
  enum class Result { kPlay, kSettings, kExit, kNothing };

  // Displays the main menu sprite 
  Result Show(sf::RenderWindow &window);

 private:
  // A struct to hold data about the buttons on the main menu
  struct MenuItem {
   public:
    // The bounds of a button
    sf::Rect<int> rect;
    // The result of clicking on this button
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
  std::list<MenuItem> menu_items_;

  // For displaying the main menu image
  sf::Texture texture_;
  sf::Sprite sprite_;
};

#endif