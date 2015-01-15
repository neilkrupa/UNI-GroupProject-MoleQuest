// Game.h
// This file is part of MoleQuest
//
// Handles the game loop and starting and stopping the game. Also holds a
// reference to the main window as well as the current game state.

#ifndef GAME_H_
#define GAME_H_

class Game {
public:
  // Creates a window, adds initial game objects to the object manager and
  // finally calls the game loop continously whilst the game state isn't
  // set to kExiting. The game state MUST be set to kUninitialised 
  // otherwise this function will just return without doing anything.
  static void Start();

private:
  // Will clean up any resources, kill the window and exit the program
  static void Exit();

  // Returns true if the game state is set to kExiting
  inline static bool IsExiting() { return game_state_ == Game::kExiting; }

  // The main loop of the game. Will continously poll events and then
  // proceed to deal with the events based on the current game state.
  // The loop will also handle the timing of each loop and getting
  // user input handled.
  static void GameLoop();

  // An enumeration to hold all possible states the game can be in
  enum GameState { kUninitialised, kShowingSplash, kPaused, kShowingMenu, 
                    kPlaying, kExiting };

  // A static reference to hold the current state of the game
  static GameState game_state_;

  // A static reference to the main game window
  static sf::RenderWindow main_window_;
};

#endif