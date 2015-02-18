#include "stdafx.h"
#include "Level.h"

void Level::ChangeLevel(sf::RenderWindow& window) {
  curr_level_++;
  LoadLevel(window);
}

void Level::ChangeLevel(sf::RenderWindow& window, int level) {
  curr_level_ = level;
  LoadLevel(window);
}

void Level::LoadLevel(sf::RenderWindow& window) {
  // Load the level texture
  std::string level_name = "images/map" + std::to_string(curr_level_) + ".png";
  level_texture_.loadFromFile(level_name);
  level_sprite_.setTexture(level_texture_);

  // Show the lowest part of the level to the player
  int win_w = window.getSize().x;
  int win_h = window.getSize().y;
  level_sprite_.setTextureRect(sf::IntRect(0, 3500 - win_h, win_w, win_h));
}

void Level::UpdateLevel(sf::Vector2f player_pos, sf::RenderWindow& window) {
  // Is the player near the top of the map?
  int top = level_sprite_.getTextureRect().top;

  if (player_pos.y <= level_move_top_limit_ && top > 0) {
    int win_w = window.getSize().x;
    int win_h = window.getSize().y;
    level_sprite_.setTextureRect(sf::IntRect(0, top - level_move_speed_, win_w, win_h));
  }
}

void Level::DrawLevel(sf::RenderWindow& window) {
  window.draw(level_sprite_);
}