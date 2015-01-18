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

class Game {
 public:
  // Creates a window, adds initial game objects to the object manager and
  // finally calls the game loop continously whilst the game state isn't
  // set to kExiting. The game state MUST be set to kUninitialised 
  // otherwise this function will just return without doing anything.
  static void Start();

 private:
  // Will call the Show() function in MainMenu.cc to display the main menu
  // and proceed to continously listen for mouse clicks on any of the main
  // menu buttons. If a button is clicked, it will change the game state 
  // to the appropriate state
  static void ShowMenu();

  // Will clean up any resources, kill the window and exit the program
  static void Exit();

  // Returns true if the game state is set to kExiting
  static inline bool IsExiting() { return game_state_ == Game::kExiting; }

  // The main loop of the game. Will continously poll events and then
  // proceed to deal with the events based on the current game state.
  // The loop will also handle the timing of each loop and getting
  // user input handled.
  static void GameLoop();

  // An enumeration to hold all possible states the game can be in
  static enum GameState { kUninitialised, kPaused, kShowingMenu, kPlaying, kExiting,
                   kShowingSettings };

  // A static reference to hold the current state of the game
  static GameState game_state_;

  // A static reference to the main game window
  static sf::RenderWindow main_window_;

  // Object manager to store all objects in the game
  static GameObjectManager game_object_manager_;

  static sf::Clock clock_;
  static sf::Time last_time_;
};

#endif