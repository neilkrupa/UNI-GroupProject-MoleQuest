// Game.h
// This file is part of MoleQuest
//
// Handles the game loop and starting and stopping the game. Also invokes
// other parts of the game such as the main menu and settings menu based
// on the given game state. Holds a reference to the main window and the
// game state.

#ifndef GAME_H_
#define GAME_H_

#include "GameObjectManager.h"
#include "Player.h"

class Game {
 public:
  Game();
  ~Game();

  // The main loop of the game
  void GameLoop();

 private:
  // Will call the Show() function in MainMenu.cc to display the main menu
  // and proceed to continously listen for mouse clicks on any of the main
  // menu buttons. If a button is clicked, it will change the game 
  // to the appropriate state
  void ShowMenu();

  void ShowSettings(bool paused);

  void ShowShop();
  
  void ShowPause();

  void ProcessInput();

  void ChangeLevel();

  // Checks if the texture rect on the map texture needs to be moved because
  // the player is near the top
  void UpdateMap();

  //This is a simple check to make sure that the control is definitly being controlled by the correct button/key
  bool InputCheck(std::string key);

  // Returns true if the game state is set to kExiting
  inline bool IsExiting() { return game_state_ == Game::GameState::kExiting; }

  // An enumeration to hold all possible states the game can be in
  enum class GameState { kPaused, kShowingMenu, kPlaying, kExiting, 
                         kShowingSettings, kShowingSettingsPaused , kShopping };

  // Hold the current state of the game
  GameState game_state_;

  // The main game window
  sf::RenderWindow main_window_;
  // Object manager to hold all objects and easily manage all of them
  GameObjectManager game_object_manager_;

  enum InputType { kKey, kMouse };

  //Struct to manage different types of input
  struct Input {
   public:
    InputType type;
	  sf::Keyboard::Key KeyCode;
	  sf::Mouse::Button MouseButton;
  };
 
  //This is the map that holds the key controls for the game
  std::map<std::string, Input> key_map_;

  //This function polls for an input to map a control to and then edits the input struct for that control
  //accordingly. Its in Game.cc to avoid the awkwardness trying to stikc in SettingsMenu.cc
  Game::Input Map(Game::Input);

  Player* player_;

  int level_ = 0;
  int map_move_speed_ = 2;
  int map_move_top_limit_ = 300;

  sf::Texture level_texture_;
  sf::Sprite level_sprite_;
};

#endif