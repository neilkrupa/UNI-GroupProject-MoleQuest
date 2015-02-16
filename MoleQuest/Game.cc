//  Game.cc
//  This file is part of MoleQuest
//
//  For purpose, see Game.h

#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SettingsMenu.h"
#include "SoundEngine.h"

Game::Game() {
  main_window_.create(sf::VideoMode(1024, 768, 32), "Mole Quest");
  main_window_.setFramerateLimit(60);
  
  game_state_ = GameState::kShowingMenu;

  player_ = new Player();

  game_object_manager_.Add("player", player_);

  Input input;
  input.type = InputType::kKey;
  input.KeyCode = sf::Keyboard::W;
  key_map_["foward"] = input;
  input.KeyCode = sf::Keyboard::S;
  key_map_["backwards"] = input;
  input.KeyCode = sf::Keyboard::A;
  key_map_["left"] = input;
  input.KeyCode = sf::Keyboard::D;
  key_map_["right"] = input;

  input.KeyCode = sf::Keyboard::Q;
  key_map_["cyclel"] = input;
  input.KeyCode = sf::Keyboard::E;
  key_map_["cycler"] = input;

  input.KeyCode = sf::Keyboard::Tab;
  key_map_["pause"] = input;

  input.type = InputType::kMouse;
  input.MouseButton = sf::Mouse::Left;
  key_map_["shoot"] = input;

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
      
      case GameState::kShopping: {
		  ShowShop();
		  break;
	  }
 
      case GameState::kShowingSettingsPaused: {
        ShowSettings(true);
        break;
      }

	  case GameState::kShowingSettings: {
		  ShowSettings(false);
		  break;
	  }
	  
      case GameState::kPaused: {
        ShowPause(); 
        break;
	  
      case GameState::kPaused: {
        ShowMenu(); // Temporary - easier to test settings menu like this
        break;
      }

      case GameState::kPlaying: {
        main_window_.clear(sf::Color(0, 0, 0));

        ProcessInput();
        
		player_->DrawHUD(main_window_);

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

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    game_state_ = Game::GameState::kPaused;

  //TODO: Make this bounds checking nicer. No magic numbers like '140'
  // This could all be done better using a map where the map key is the button 
  // pressed and the value is a function pointer to one of the player 
  // move functions.

   if (InputCheck("cyclel"))
	player_->Switch(-1);

  if (InputCheck("cycler"))
	  player_->Switch(1);

  if (InputCheck("shoot"))
	  player_->Shoot();        //This is a placeholder function that tests the clip value on the HUD

  if (InputCheck("left"))
    if ((player_->GetPosition().x - player_->GetVelocityX()) > 0)
      player_->MoveLeft();
 
  if (InputCheck("right"))
    if ((player_->GetPosition().x + player_->GetVelocityX()) < win_w - 140)
      player_->MoveRight();

  if (InputCheck("foward"))
	  if ((player_->GetPosition().y - player_->GetVelocityY()) > 0)
      player_->MoveUp();

  if (InputCheck("backwards"))
    if ((player_->GetPosition().y + player_->GetVelocityY()) < win_h - 140)
      player_->MoveDown();
}

bool Game::InputCheck(std::string key) {
	if (key_map_.find(key)->second.type == InputType::kKey) {
		if (sf::Keyboard::isKeyPressed(key_map_.find(key)->second.KeyCode))
			return true;

	} else if (key_map_.find(key)->second.type == InputType::kMouse) {
		if (sf::Mouse::isButtonPressed(key_map_.find(key)->second.MouseButton))
			return true;
	}

	return false;
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

void Game::ShowSettings(bool paused)
	SettingsMenu settings_menu;
	SettingsMenu::Result result = settings_menu.Show(main_window_);

	switch (result){
      case SettingsMenu::Result::kMap: {
		key_map_[settings_menu.tomap] = Map((key_map_.find(settings_menu.tomap)->second));
        break;
      }

      case SettingsMenu::Result::kExit: {
		game_state_ = GameState::kExiting;
		break;
      }

      case SettingsMenu::Result::kBack: {
		if (paused == true)
		  game_state_ = GameState::kPaused;
		else
		  game_state_ = GameState::kShowingMenu;
		break;
      }
	}
}

Game::Input Game::Map(Game::Input input){
	sf::Event event;

	while (true) {
      while (main_window_.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
          input.type = InputType::kKey;
		  input.KeyCode = event.key.code;
  		  return input;
		} else if (event.type == sf::Event::MouseButtonPressed) {
          input.type = InputType::kMouse;
		  input.MouseButton = event.mouseButton.button;
		  return input;
		}
      }
    }
}

void Game::ShowShop(){
  Shop shop;
  shop.UpdateMenu(player_->getHealthLevel(), player_->getSpeedLevel());
  Shop::Result result = shop.Show(main_window_);

  switch (result) {
    case Shop::Result::kExit: {
      game_state_ = GameState::kExiting;
      break;
    }

    case Shop::Result::kContinue: {
      game_state_ = GameState::kPlaying;
      break;
	 }

    case Shop::Result::kBuy: {
      player_->Buy(shop.toBuy);
      break;
    }
 
    case Shop::Result::kUpgrade: {
      player_->Upgrade(shop.toBuy);
      break;
    }
  }
}

void Game::ShowPause(){
  Pause pause;
  Pause::Result result = pause.Show(main_window_);

  switch (result){
    case Pause::Result::kMenu: {
      game_state_ = GameState::kShowingMenu;
      break;
    }

    case Pause::Result::kSettings: {
      game_state_ = GameState::kShowingSettingsPaused;
      break;
    }

    case Pause::Result::kExit: {
      game_state_ = GameState::kExiting;
      break;
    }
  
    case Pause::Result::kPlay: {
      game_state_ = GameState::kPlaying;
      break;
    }
  }
}