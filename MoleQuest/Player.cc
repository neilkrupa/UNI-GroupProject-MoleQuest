#include "stdafx.h"
#include "Player.h"

Player::Player() : velocity_x_(0), velocity_y_(0) {
  GetSprite().setPosition(100, 600);
  Load("images/player.png");
  GetSprite().scale(0.5, 0.5);
  GetSprite().setOrigin(49, 173);
  
  coins = 0;

  // Initialise the stats
  health_.curr_level = 0;
  health_.max_level = 4;
  health_.curr_value = 100;
  health_.max_value = 100;
  health_.level_increase = 100;
  health_.cost = 150;
  health_.cost_increase = 75;

  speed_.curr_level = 0;
  speed_.max_level = 4;
  speed_.curr_value = 1;
  speed_.max_value = 4;
  speed_.level_increase = 1;
  speed_.cost = 150;
  speed_.cost_increase = 75;

  Weapon potatoGun("potatoGun", 0, 0.5, 0, 10, false); 
  Weapon duelPistols("duelPistols", 650, 2, 12, 15, false);
  Weapon pdw("pdw", 1500, 3, 25, 25, false);
  Weapon shotgun("shotgun", 2500, 0.5, 5, 50, true);
  Weapon smg("smg",4500, 5, 35, 30, false);
  Weapon assaultRifle("assaultRifle", 7000, 4, 30, 45, false);
  Weapon minigun("minigun", 10000, 10, 50, 75, false);

  weapons_.push_back(potatoGun);
  weapons_.push_back(duelPistols);
  weapons_.push_back(pdw);
  weapons_.push_back(smg);
  weapons_.push_back(shotgun);
  weapons_.push_back(assaultRifle);
  weapons_.push_back(minigun);

  potatoGun.setOwned();
  curr_weapon_ = potatoGun;

  //This is the setup for the HUD bars
  hpTex.loadFromFile("images/hpbar/hp1.png");
  hpBar.setPosition(30, 700);
  f.loadFromFile("fonts/quest.ttf");
  hpVal.setFont(f);
  hpVal.setCharacterSize(20);
  hpVal.setColor(sf::Color::Black);
  hpVal.setString(std::to_string(health_.curr_value));
  hpVal.setPosition(65, 700);

  coinTex.loadFromFile("images/coinbar.png");
  coinBar.setPosition(30, 730);
  coinVal.setFont(f);
  coinVal.setColor(sf::Color::Black);
  coinVal.setCharacterSize(20);
  coinVal.setString(std::to_string(coins));
  coinVal.setPosition(150, 730);

  clipVal.setFont(f);
  clipVal.setCharacterSize(20);
  clipVal.setColor(sf::Color::Black);
  clipVal.setPosition(820, 705);
 
  maxclipVal.setFont(f);
  maxclipVal.setColor(sf::Color::Black);
  maxclipVal.setCharacterSize(20);
  maxclipVal.setPosition(840, 730);

  
  ammoBar.setPosition(800, 655);

  animation_handler_ = new AnimationHandler();
}

Player::~Player() {
  delete animation_handler_;
}

void Player::Update(float lag) {
  /* Commment out until there are some animations
  // Update animation time if moving or idling
  if (is_moving_ || animation_handler_->GetAnimationNumber() == 1)
    animation_handler_->Update(lag);
  
  // Change animation to walking if moving
  if (is_moving_)
    animation_handler_->ChangeAnimation(0);

  // Reset to idle animation?
  if (is_moving_ && velocity_x_ == 0) {
    animation_handler_->ChangeAnimation(1);
    is_moving_ = false;
  }
  */

  GetSprite().move(velocity_x_ * lag, velocity_y_ * lag);

  velocity_x_ = 0;
  velocity_y_ = 0;
}

void Player::Draw(float interp, sf::RenderWindow& window) {
  DrawHUD(window);

  //GetSprite().setTextureRect(animation_handler_->texture_bounds_);

  sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
  sf::Vector2f player_pos = GetSprite().getPosition();

  // Work out the angle to face towards mouse
  float angle = atan2(mouse_pos.y - player_pos.y, mouse_pos.x - player_pos.x);
  angle *= (180 / M_PI);

  GetSprite().setRotation(90 + angle);

  window.draw(GetSprite());
}

void Player::MoveUp() {
  velocity_y_ -= 0.3f;
  is_moving_ = true;
}

void Player::MoveDown() {
  velocity_y_ += 0.3f;
  is_moving_ = true;
}

void Player::MoveLeft() {
  velocity_x_ -= 0.3f;
  is_moving_ = true;
}

void Player::MoveRight() {
  velocity_x_ += 0.3f;
  is_moving_ = true;
}


void Player::Buy(std::string purchase) {
	std::list<Weapon>::iterator curr;
	
	for (curr = weapons_.begin(); curr != weapons_.end(); ++curr) {
		if (curr->getName().compare(purchase) == 0 && curr->getPrice() <= coins) {
			if (!(curr->Owned())){
				curr->setOwned();
				coins -= curr->getPrice();
				coinVal.setString(std::to_string(coins));
				break;
			}
		}	   	
	}
}

void Player::Upgrade(std::string upgradeable) {
  if (upgradeable == "health") {
    // Does the player have enough money to upgrade and not already max level?
    if (health_.cost <= coins && health_.curr_level < health_.max_level) {
      health_.max_value += health_.level_increase;
      // Set current health to new max
      health_.curr_level = health_.max_level;

      coins -= health_.cost;

      health_.cost += health_.cost_increase;

      health_.curr_level += 1;
    }
  } else if (upgradeable == "speed") {
    // Does the player have enough money to upgrade and not already max level?
    if (speed_.cost <= coins && speed_.curr_level < speed_.max_level) {
      speed_.max_level += speed_.level_increase;
      speed_.curr_level = speed_.max_level;

      coins -= speed_.cost;

      speed_.cost += speed_.cost_increase;

      speed_.curr_level += 1;
    }
  }

  coinVal.setString(std::to_string(coins));
}

void Player::DrawHUD(sf::RenderWindow &main_window_) {
	hpBar.setTexture(hpTex);
	coinBar.setTexture(coinTex);
	clipVal.setString(std::to_string(curr_weapon_.getClip()));
	maxclipVal.setString(std::to_string(curr_weapon_.getFullClip()));

	//Sets up the ammo bar
	std::stringstream stream;
	stream << "images/ammobar/" << curr_weapon_.getName() << "Bar.png";
	ammoTex.loadFromFile(stream.str());
	ammoBar.setTexture(ammoTex);

	main_window_.draw(hpBar);
	main_window_.draw(hpVal);
	main_window_.draw(coinBar);
	main_window_.draw(coinVal);
	main_window_.draw(ammoBar);

	//This is just due to the difference in the image for the potato gun HUD
	if (curr_weapon_.getName().compare("potatoGun") != 0) {
		main_window_.draw(clipVal);
		main_window_.draw(maxclipVal);
	}
}

void Player::Damage(int damage) {
  // Makes sure health never goes below 0
  health_.curr_level = (health_.curr_level - damage) > 0 ? health_.curr_level - damage : 0;

  // Load the new texture
  std::stringstream stream;
  stream << "images/hpbar/hp" << ((health_.max_value - health_.curr_value) / (health_.max_value / 25)) << ".png";
  hpTex.loadFromFile(stream.str());
  hpVal.setString(std::to_string(health_.curr_value));
}

void Player::Collect(int amount) {
	coins += amount;
	coinVal.setString(std::to_string(coins));
}

void Player::Switch(int dir) {
	std::list<Weapon>::iterator curr;

	for (curr = weapons_.begin(); curr != weapons_.end(); ++curr) {
		if (curr->getName().compare(curr_weapon_.getName()) == 0) {

			if (dir == 1) {
				curr++;
				for (curr; curr != weapons_.end(); ++curr) {
					if (curr->Owned()) {
						curr_weapon_ = *curr;
						break;
					}
				}	
			} else {
				for (curr; curr != weapons_.begin();) { 
					--curr;

					if (curr->Owned()) {
						curr_weapon_ = *curr;
						break;
					}
				}	
			}

			break;
		}
	}
}

void Player::Shoot() {
	curr_weapon_.fire();
}

int Player::getHealthLevel() {
  return health_.curr_level;
}

int Player::getSpeedLevel() {
  return speed_.curr_level;
}

float Player::GetVelocityX() {
  return 0.3;
}

float Player::GetVelocityY() {
  return 0.3;
}
