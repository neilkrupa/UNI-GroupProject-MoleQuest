//  Game.cc
//  This file is part of MoleQuest
//
//  For purpose, see Game.h

#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SoundEngine.h"

Game::Game() {
  main_window_.create(sf::VideoMode(1024, 768, 32), "Mole Quest");
  main_window_.setFramerateLimit(60);
  
  game_state_ = GameState::kShowingMenu;

  player_ = new Player();

  game_object_manager_.Add("player", player_);
}

Game::~Game() {
  main_window_.close();
}

void Game::GameLoop() {
  sf::Clock clock;

  //SoundEngine sound_engine;
  //sound_engine.PlaySong("mainmenu.wav", true);

  while (!IsExiting()) {
    sf::Time elapsed_time = clock.restart();
    float lag = elapsed_time.asMilliseconds();

    switch (game_state_) {
      case GameState::kShowingMenu: {
        ShowMenu();
        break;
      }

      case GameState::kShowingSettings: {
        break;
      }

      case GameState::kPaused: {
        break;
      }

      case GameState::kPlaying: {
        main_window_.clear(sf::Color(0, 0, 0));

        ProcessInput();

        game_object_manager_.UpdateAll(lag);

        game_object_manager_.DrawAll(lag, main_window_);

        main_window_.display();
        break;
      }
    }
  }
}

void Game::ProcessInput() {
  if (!main_window_.hasFocus())
    return;

  int win_w = main_window_.getSize().x;
  int win_h = main_window_.getSize().y;

  //TODO: Make this bounds checking nicer. No magic numbers like '140'

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
    if ((player_->GetPosition().x - player_->GetVelocityX()) > 0)
      player_->MoveLeft();

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    if ((player_->GetPosition().x + player_->GetVelocityX()) < win_w - 140)
      player_->MoveRight();

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    player_->MoveUp();

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    if ((player_->GetPosition().y + player_->GetVelocityY()) < win_h - 140)
      player_->MoveDown();
}

void Game::ShowMenu() {
  MainMenu main_menu;
  MainMenu::Result result = main_menu.Show(main_window_);

  switch (result) {
    case MainMenu::Result::kExit: {
      game_state_ = GameState::kExiting;
      break;
    }

    case MainMenu::Result::kPlay: {
      game_state_ = GameState::kPlaying;
      break;
    }

    case MainMenu::Result::kSettings: {
      game_state_ = GameState::kShowingSettings;
      break;
    }
  }
}