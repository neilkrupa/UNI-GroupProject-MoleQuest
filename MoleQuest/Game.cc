//  Game.cc
//  This file is part of MoleQuest
//
//  For purpose, see Game.h

#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"

void Game::Start() {
  // If the game state isn't kUninitialised then return so that nothing weird
  // happens from reinitialising the game
  if (game_state_ != kUninitialised)
    return;

  main_window_.create(sf::VideoMode(1024, 768, 32), "Mole Quest");

  game_state_ = kShowingMenu;

  last_time_ = clock_.getElapsedTime();
  while (!IsExiting())
    GameLoop();

  Exit();
}

void Game::Exit() {
  main_window_.close();
}

void Game::GameLoop() {
  sf::Time current_time = clock_.getElapsedTime();
  int elapsed_time = current_time.asMilliseconds - last_time_.asMilliseconds;

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
      main_window_.clear(sf::Color(0, 0, 0));

      game_object_manager_.UpdateAll(elapsed_time);

      game_object_manager_.DrawAll(main_window_);

      main_window_.display();

      break;
    }
  }

  last_time_ = current_time;
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

Game::GameState Game::game_state_;
sf::RenderWindow Game::main_window_;
GameObjectManager Game::game_object_manager_;

sf::Clock Game::clock_;
sf::Time Game::last_time_;