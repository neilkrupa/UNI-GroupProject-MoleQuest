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

  // Returns true if the game state is set to kExiting
  inline bool IsExiting() { return game_state_ == Game::kExiting; }

  // An enumeration to hold all possible states the game can be in
  enum GameState { kPaused, kShowingMenu, kPlaying, kExiting, kShowingSettings };

  // Hold the current state of the game
  GameState game_state_;

  // The main game window
  sf::RenderWindow main_window_;
  // Object manager to hold all objects and easily manage all of them
  GameObjectManager game_object_manager_;

  const int kMSPerUpdate = 16;
  Player* player;

};

#endif