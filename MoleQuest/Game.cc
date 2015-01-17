//  Game.cc
//  This file is part of MoleQuest
//
//  For purpose, see Game.h

#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"

void Game::Start() {
  // If the game state isn't kUninitialised then return as the game has already
  // been set up before
  if (game_state_ != kUninitialised)
    return;

  // Create the main window
  main_window_.create(sf::VideoMode(1024, 768, 32), "Mole Quest");

  // Set the game to show the main menu
  game_state_ = kShowingMenu;

  // Continously call the game loop
  while (!IsExiting())
    GameLoop();

  // Call Exit() to clean up all resources and exit the program
  Exit();
}

void Game::Exit() {
  main_window_.close();
}

void Game::GameLoop() {
  switch (game_state_) {
    case kShowingMenu: {
      ShowMenu();
      break;
    }

    case kShowingSettings: {
      break;
    }

    case kPaused: {
      break;
    }

    case kPlaying: {
      sf::Event event;

      while (main_window_.pollEvent(event)) {
        main_window_.clear(sf::Color(255, 0, 0));
        main_window_.display();

        if (event.type == sf::Event::Closed)
          game_state_ = kExiting;
      }

      break;
    }
  }
}

void Game::ShowMenu() {
  MainMenu main_menu;
  MainMenu::Result result = main_menu.Show(main_window_);

  switch (result) {
    case MainMenu::kExit: {
      game_state_ = kExiting;
      break;
    }
    case MainMenu::kPlay: {
      game_state_ = kPlaying;
      break;
    }
    case MainMenu::kSettings: {
      game_state_ = kShowingSettings;
      break;
    }
  }
}

// Initialise some variables 
Game::GameState Game::game_state_ = kUninitialised;
sf::RenderWindow Game::main_window_;