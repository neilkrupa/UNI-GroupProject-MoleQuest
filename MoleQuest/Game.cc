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
  
  game_state_ = kShowingMenu;

  Player* player = new Player();
  player->Load("images/player.png");
  player->SetPosition(1024 / 2, 768 / 2);

  game_object_manager_.Add("player", player);
}

Game::~Game() {
  main_window_.close();
}

void Game::GameLoop() {
  sf::Clock clock;

  SoundEngine sound_engine;
  sound_engine.PlaySong("mainmenu.wav", true);

  double lag = 0.0;
  while (!IsExiting()) {
    sf::Time elapsed_time = clock.restart();
    lag += elapsed_time.asMilliseconds();

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

        while (lag >= kMSPerUpdate) {
          game_object_manager_.UpdateAll();
          lag -= kMSPerUpdate;
        }

        float interp = lag / kMSPerUpdate;
        game_object_manager_.DrawAll(interp, main_window_);

        main_window_.display();

        break;
      }
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