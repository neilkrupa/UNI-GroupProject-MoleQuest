#ifndef LEVEL_H_
#define LEVEL_H_

class Level {
 public:
  // Change the level to next one
  void ChangeLevel(sf::RenderWindow&);

  // Change the level to a specific level 
  void ChangeLevel(sf::RenderWindow&, int);

  // Check to see if the texturerect needs to move because of the player position
  void UpdateLevel(sf::Vector2f, sf::RenderWindow&);

  void DrawLevel(sf::RenderWindow&);

  bool AtTopOfMap();

 private:
  int curr_level_ = 0;

  int level_move_speed_ = 1;
  int level_move_top_limit_ = 400;
  int level_move_bottom_limit_ = 500;

  sf::Texture level_texture_;
  sf::Sprite level_sprite_;

  // Loads the level texture and sets the sprite and texturerect
  void LoadLevel(sf::RenderWindow&);
};

#endif