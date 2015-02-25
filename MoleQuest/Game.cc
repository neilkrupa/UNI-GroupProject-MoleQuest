//  Game.cc
//  This file is part of MoleQuest
//
//  For purpose, see Game.h

#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SettingsMenu.h"
#include "Shop.h"
#include "Pause.h"
#include "SoundEngine.h"
#include "Projectile.h"
#include "Boss.h"
#include "Intro.h"
#include "RangeMole.h"

Game::Game() {
  main_window_.create(sf::VideoMode(1024, 768, 32), "Mole Quest");
  //main_window_.setFramerateLimit(60);

  game_state_ = GameState::kShowingMenu;

  player_ = new Player();
  player_->SetObjectType(GameObject::kPlayer);
  game_object_manager_.Add(player_);

  mole_spawner_ = new MoleSpawner(player_);

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

  input.KeyCode = sf::Keyboard::Escape;
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

  while (!IsExiting()) {
    sf::Time elapsed_time = clock.restart();
    int lag = elapsed_time.asMilliseconds();

    switch (game_state_) {
      case GameState::kShowingMenu: {
        sound_engine_.PlaySong("mainmenu.wav", true);
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
      }

      case GameState::kPlaying: {
        main_window_.clear(sf::Color(0, 0, 0));

        ProcessInput();

        map_.UpdateLevel(player_->GetPosition(), main_window_);

        // If at top of map, spawn a boss
        if (map_.AtTopOfMap() && !boss_spawned) {
          boss_= new Boss(player_, map_.CurrentLevel());
          boss_->SetObjectType(GameObject::kBoss);
          game_object_manager_.Add(boss_);
          boss_spawned = true;
        }

        // Is boss was spawned but now dead, change level and remove boss
        if (boss_spawned && boss_->IsDead()) {
          // If on last menu go to main menu
          if (map_.CurrentLevel() == 6) {
            game_state_ = GameState::kShowingMenu;
            break;
          }

          game_state_ = GameState::kShopping;
          boss_spawned = false;
          game_object_manager_.Remove(boss_->GetObjectManagerIndex());
        }

        // Dont spawn more moles if at top of map (where the boss is)
        if (!map_.AtTopOfMap())
          mole_spawner_->Update(lag, map_.CurrentLevel());

        game_object_manager_.UpdateAll(lag);

        map_.DrawLevel(main_window_);
        game_object_manager_.DrawAll(lag, main_window_);
        
        // Draw FPS for testing
        sf::Font f;
        sf::Text fps;

        f.loadFromFile("fonts/Quest.ttf");        
        fps.setFont(f);

        float ffps = 1.f / elapsed_time.asSeconds();
        fps.setString("FPS: " + std::to_string(ffps));
        fps.setCharacterSize(24);
        fps.setColor(sf::Color::Red);
        fps.setStyle(sf::Text::Bold);

        main_window_.draw(fps);

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

  if (InputCheck("pause"))
    game_state_ = Game::GameState::kPaused;

  // This could all be done better using a map where the map key is the button 
  // pressed and the value is a function pointer to one of the player 
  // move functions.

  if (InputCheck("cyclel"))
	  player_->Switch(-1);

  if (InputCheck("cycler"))
	  player_->Switch(1);

  if (InputCheck("shoot")) {
    // Create new bullet projectile if attack speed allows for it
    if (player_->GetLastFiredTime() >= 1 / player_->GetWeapon().GetAttackSpeed() && player_->GetReload() == false) {
      
      Projectile* projectile = new Projectile(player_->GetWeapon().GetDamage(),
                                              player_->GetPosition(),
                                              sf::Mouse::getPosition(main_window_),
                                              player_->GetSprite().getOrigin(),
                                              player_->GetTextureRect());

      projectile->SetObjectType(GameObject::kProjectile);
     
      game_object_manager_.Add(projectile);

      player_->Shoot();
    }
  }

  if (InputCheck("left"))
    if ((player_->GetPosition().x - player_->GetVelocityX()) > 0)
      player_->MoveLeft();
 
  if (InputCheck("right"))
    if ((player_->GetPosition().x + player_->GetVelocityX()) < win_w)
      player_->MoveRight();

  if (InputCheck("foward"))
	  if ((player_->GetPosition().y - player_->GetVelocityY()) > 0)
      player_->MoveUp();

  if (InputCheck("backwards"))
    if ((player_->GetPosition().y + player_->GetVelocityY()) < win_h)
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
      // Stop menu music
      sound_engine_.StopSong();

      // Display the intro animation
      //Intro intro;
      //intro.Show(main_window_);

      // Start the game
      map_.ChangeLevel(main_window_, 1);
      game_state_ = GameState::kPlaying;
      break;
    }

    case MainMenu::Result::kSettings: {
      game_state_ = GameState::kShowingSettings;
      break;
    }
  }

}

void Game::ShowSettings(bool paused) {
	SettingsMenu settings_menu;
    settings_menu.UpdateMenu(key_map_);
	SettingsMenu::Result result = settings_menu.Show(main_window_);

	switch (result) {
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

void Game::ShowShop() {
  Shop shop;
  shop.UpdateMenu(player_->GetHealthLevel(), player_->GetSpeedLevel());
  Shop::Result result = shop.Show(main_window_);

  switch (result) {
    case Shop::Result::kExit: {
      game_state_ = GameState::kExiting;
      break;
    }

    case Shop::Result::kContinue: {
      map_.ChangeLevel(main_window_);
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

void Game::ShowPause() {
  Pause pause;
  Pause::Result result = pause.Show(main_window_);

  switch (result) {
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