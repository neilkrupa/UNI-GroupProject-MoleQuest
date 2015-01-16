#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

class MainMenu {
 public:
  enum Result { kPlay, kSettings, kExit, kNothing };

  struct MenuItem {
   public:
    sf::Rect<int> rect;
    Result result;
  };

  Result Show(sf::RenderWindow &window);

 private:
  Result GetMenuResponse(sf::RenderWindow &window);
  Result HandleClick(int x, int y);
  std::list<MenuItem> menu_items_;
};

#endif