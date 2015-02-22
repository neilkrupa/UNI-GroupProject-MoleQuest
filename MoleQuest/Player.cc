#include "stdafx.h"
#include "Player.h"

Player::Player() : velocity_x_(0), velocity_y_(0) {
  Load("images/spritesheet.png");

  GetSprite().setPosition(400, 700);
  GetSprite().scale(0.75, 0.75);
  GetSprite().setOrigin(91 / 2, 103 / 2);
  
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

  weapons_.push_back(Weapon("potatoGun", 0, 0.5, 0, 10, false));
  weapons_.push_back(Weapon("duelPistols", 650, 2, 12, 15, false));
  weapons_.push_back(Weapon("pdw", 1500, 3, 25, 25, false));
  weapons_.push_back(Weapon("shotgun", 2500, 0.5, 5, 50, true));
  weapons_.push_back(Weapon("smg", 4500, 5, 35, 30, false));
  weapons_.push_back(Weapon("assaultRifle", 7000, 4, 30, 45, false));
  weapons_.push_back(Weapon("minigun", 10000, 10, 50, 75, false));

  weapon_indexes_["potatoGun"] = 0;
  weapon_indexes_["duelPistols"] = 1;
  weapon_indexes_["pdw"] = 2;
  weapon_indexes_["shotgun"] = 3;
  weapon_indexes_["smg"] = 4;
  weapon_indexes_["assaultRifle"] = 5;
  weapon_indexes_["minigun"] = 6;

  // Set potato gun to default
  weapons_[0].setOwned();
  curr_weapon_ = weapons_[0];

  //This is the setup for the HUD bars
  hpTex.loadFromFile("images/hpbar/hp1.png");
  hpBar.setPosition(30, 700);
  f.loadFromFile("fonts/quest.ttf");
  hpVal.setFont(f);
  hpVal.setCharacterSize(20);
  hpVal.setColor(sf::Color::Black);
  hpVal.setString(std::to_string(health_.curr_value));
  hpVal.setPosition(65, 700);

  hpBar.setTexture(hpTex);

  coinTex.loadFromFile("images/coinbar.png");
  coinBar.setPosition(30, 730);
  coinVal.setFont(f);
  coinVal.setColor(sf::Color::Black);
  coinVal.setCharacterSize(20);
  coinVal.setString(std::to_string(coins));
  coinVal.setPosition(150, 730);

  coinBar.setTexture(coinTex);

  clipVal.setFont(f);
  clipVal.setCharacterSize(20);
  clipVal.setColor(sf::Color::Black);
  clipVal.setPosition(820, 705);
 
  maxclipVal.setFont(f);
  maxclipVal.setColor(sf::Color::Black);
  maxclipVal.setCharacterSize(20);
  maxclipVal.setPosition(840, 730);
  
  ammoBar.setPosition(800, 655);

  ammoTex.loadFromFile("images/ammobar/" + curr_weapon_.getName() + "Bar.png");
  ammoBar.setTexture(ammoTex);

  // Set up animations for every weapon

  sf::IntRect sub_rect;
  sub_rect.top = 0;
  sub_rect.height = 103;
  sub_rect.left = 0;
  sub_rect.width = 90;

  animation_handler_ = new AnimationHandler(sub_rect);
  
  // Add 7 animations representing the 7 guns
  for (int i = 0; i < 7; i++)
    animation_handler_->AddAnimation(Animation(0, 2, 150));

  animation_handler_->ChangeAnimation(0);
}

Player::~Player() {
  delete animation_handler_;
}

void Player::Update(int lag) {
  if (velocity_x_ == 0 && velocity_y_ == 0 && is_moving_)
    is_moving_ = false;

  if (is_moving_)
    animation_handler_->Update(lag);

  GetSprite().move(velocity_x_ * lag, velocity_y_ * lag);

  velocity_x_ = 0;
  velocity_y_ = 0;
}

void Player::Draw(int interp, sf::RenderWindow& window) {
  DrawHUD(window);

  GetSprite().setTextureRect(animation_handler_->texture_bounds_);

  sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
  sf::Vector2f player_pos = GetSprite().getPosition();

  // Work out the angle to face towards mouse
  float angle = atan2(mouse_pos.y - player_pos.y, mouse_pos.x - player_pos.x);
  angle *= (float) (180 / M_PI);

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
  Weapon* weapon = &weapons_[weapon_indexes_[purchase]];
  weapon->setOwned();
  coins -= weapon->getPrice();
  coinVal.setString(std::to_string(coins));
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
  int health_file = ((health_.max_value - health_.curr_value) / (health_.max_value / 25));
  hpTex.loadFromFile("images/hpbar/hp" + std::to_string(health_file) + ".png");
  hpVal.setString(std::to_string(health_.curr_value));
}

void Player::Collect(int amount) {
	coins += amount;
	coinVal.setString(std::to_string(coins));
}

void Player::Switch(int dir) {
  int curr_weapon_index = weapon_indexes_[curr_weapon_.getName()];

  // Using modulo 7 to wrap weapons around so if on weapon 6, and go right, you get weapon 0
  // Looks quite complicated beacuse of dumb as fuck implementation of % which is actually
  // just a division and not mathemtical modulus
  int new_index = ((curr_weapon_index + dir) % 7 + 7) % 7;

  curr_weapon_ = weapons_[new_index];

  animation_handler_->ChangeAnimation(new_index);

  // Set new max clip text 
  clipVal.setString(std::to_string(curr_weapon_.getClip()));
  maxclipVal.setString(std::to_string(curr_weapon_.getFullClip()));

  // Load ammobar texture for new weapon
  ammoTex.loadFromFile("images/ammobar/" + curr_weapon_.getName() + "Bar.png");
  ammoBar.setTexture(ammoTex);
}

void Player::Shoot() {
	curr_weapon_.fire();
  clipVal.setString(std::to_string(curr_weapon_.getClip()));
}

int Player::getHealthLevel() {
  return health_.curr_level;
}

int Player::getSpeedLevel() {
  return speed_.curr_level;
}

float Player::GetVelocityX() {
  return 0.3f;
}

float Player::GetVelocityY() {
  return 0.3f;
}
