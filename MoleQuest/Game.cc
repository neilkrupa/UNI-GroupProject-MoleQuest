//  Game.cpp
//  This file is part of MoleQuest
//
//  For purpose, see Game.h

#include "stdafx.h"
#include "Game.h"

void Game::Start() {
  // If the game state is kUninitialised then return as the game has already
  // been set up before
  if (game_state_ != kUninitialised)
    return;

  // Create the main window
  main_window_.create(sf::VideoMode(1024, 768, 32), "Mole Quest");

  // Set the game state to kPlaying
  game_state_ = Game::kPlaying;

  // Continously call the game loop
  while (!IsExiting())
    GameLoop();

  // Call Exit() to clean up all resources and exit the program
  Exit();
}

void Game::Exit() {

}

void Game::GameLoop() {
  sf::Event event;

  // Get the last event. The while loop will make it wait for an event to occur
  while (main_window_.pollEvent(event)) {
    // Handle the event based upon what state the game is currently in
    switch (game_state_) {
      case kPlaying: {
        main_window_.clear(sf::Color(255, 0, 0));
        main_window_.display();

        if (event.type == sf::Event::Closed)
          game_state_ = Game::kExiting;

        break;
      }
      case kShowingSplash: {}
     
      case kPaused: {}

      case kShowingMenu: {}
    }
  }
}

// Initialise some variables 
Game::GameState Game::game_state_ = kUninitialised;
sf::RenderWindow Game::main_window_;