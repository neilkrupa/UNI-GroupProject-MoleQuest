#include "stdafx.h"
#include "Player.h"

Player::Player() : velocity_x_(0), velocity_y_(0) {
  GetSprite().setPosition(1024 / 2, 600);
  Load("images/player.png");
  GetSprite().scale(0.5, 0.5);
  GetSprite().setOrigin(49, 173);
  
  coins = 0;
  
  Stat health;
  health.name = "health";
  health.level = 0;
  health.maxlevel = 4;
  
  health.value = 100;
  health.max = 100;
  health.amount = 100;
  
  health.cost = 150;
  health.increase = 75;

  Stat speed;
  speed.name = "speed";
  speed.level = 0;
  speed.maxlevel = 4;
  
  speed.value = 1;
  speed.amount = 1;
  
  speed.cost = 150;
  speed.increase = 75;

  stats_.push_back(speed);
  stats_.push_back(health);


  Weapon potatoGun("potatoGun",0,0.5,0,10,false); 
  Weapon duelPistols("duelPistols",650,2,12,15,false);
  Weapon pdw("pdw", 1500, 3, 25, 25, false);
  Weapon shotgun("shotgun", 2500, 0.5, 5, 50, true);
  Weapon smg("smg",4500,5,35,30,false);
  Weapon assaultRifle("assaultRifle",7000,4,30,45,false);
  Weapon minigun("minigun",10000,10,50,75,false);

  weapons_.push_back(potatoGun);
  weapons_.push_back(duelPistols);
  weapons_.push_back(pdw);
  weapons_.push_back(smg);
  weapons_.push_back(shotgun);
  weapons_.push_back(assaultRifle);
  weapons_.push_back(minigun);

  potatoGun.setOwned();
  currWep = potatoGun;


  //This is the setup for the HUD bars
  hpTex.loadFromFile("images/hpbar/hp1.png");
  hpBar.setPosition(30, 700);
  f.loadFromFile("fonts/quest.ttf");
  hpVal.setFont(f);
  hpVal.setCharacterSize(20);
  hpVal.setColor(sf::Color::Black);
  hpVal.setString(std::to_string(health.value));
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


void Player::Buy(std::string purchase){
	std::list<Weapon>::iterator curr;
	
	for (curr = weapons_.begin(); curr != weapons_.end(); ++curr){
		if (curr->getName().compare(purchase) == 0 && curr->getPrice() <= coins){
			if (!(curr->Owned())){
				curr->setOwned();
				coins -= curr->getPrice();
				coinVal.setString(std::to_string(coins));
				break;
			}
		  }	   	
	  }
}

void Player::Upgrade(std::string upgradable){
	std::list<Stat>::iterator curr;
	for (curr = stats_.begin(); curr != stats_.end(); ++curr){	
		if (curr->name.compare(upgradable) == 0 && curr->cost <= coins && curr->level <= curr->maxlevel){
			if (curr->level < curr->max){
				curr->value += curr->amount;
				curr->max += curr->amount;
				coins -= curr->cost;
				curr->cost += curr->increase;
				curr->level += 1;
				coinVal.setString(std::to_string(coins));
			}
			break;
		}
	}	
}

void Player::DrawHUD(sf::RenderWindow &main_window_){
	hpBar.setTexture(hpTex);
	coinBar.setTexture(coinTex);
	clipVal.setString(std::to_string(currWep.getClip()));
	maxclipVal.setString(std::to_string(currWep.getFullClip()));

	//Sets up the ammo bar
	std::stringstream stream;
	stream << "images/ammobar/" << currWep.getName() << "Bar.png";
	ammoTex.loadFromFile(stream.str());
	ammoBar.setTexture(ammoTex);

	main_window_.draw(hpBar);
	main_window_.draw(hpVal);
	main_window_.draw(coinBar);
	main_window_.draw(coinVal);
	main_window_.draw(ammoBar);

	//This is just due to the difference in the image for the potato gun HUD
	if (currWep.getName().compare("potatoGun") != 0){
		main_window_.draw(clipVal);
		main_window_.draw(maxclipVal);
	}
		
}

void Player::Damage(int damage){
	std::list<Stat>::iterator curr;
	std::stringstream stream;
	
	for (curr = stats_.begin(); curr != stats_.end(); ++curr){
		if (curr->name.compare("health") == 0 && curr->value - damage >= 0){
			curr->value -= damage;
			hpVal.setString(std::to_string(curr->value));

			if (curr->value <= (curr->max - (curr->max/25)*((curr->max - curr->value) / (curr->max/25)))){
				stream << "images/hpbar/hp" << ((curr->max - curr->value) / (curr->max / 25)) << ".png";
				hpTex.loadFromFile(stream.str());
				hpVal.setString(std::to_string(curr->value));
				break;
			}
		}
	}

	
}

void Player::Collect(int amount){
	coins += amount;
	coinVal.setString(std::to_string(coins));
}

void Player::Switch(int dir){
	std::list<Weapon>::iterator curr;

	for (curr = weapons_.begin(); curr != weapons_.end(); ++curr){
		if (curr->getName().compare(currWep.getName()) == 0){
			if (dir == 1){
				curr++;
				for (curr; curr != weapons_.end(); ++curr)
				{
					if (curr->Owned()){
						currWep = *curr;
						break;
					}
				}	
			}
			else{
				for (curr; curr != weapons_.begin();)
				{ 
					--curr;
					if (curr->Owned()){
						currWep = *curr;
						break;
					}
				}	
				
			}
			break;
		}
	}
}

void Player::Shoot(){
	currWep.fire();
}

int Player::getHealthLevel(){
	std::list<Stat>::iterator curr;
	for (curr = stats_.begin(); curr != stats_.end(); ++curr){
		if (curr->name.compare("health") == 0)
			return curr->level;
	}
	return 0;
}

int Player::getSpeedLevel(){
	std::list<Stat>::iterator curr;
	for (curr = stats_.begin(); curr != stats_.end(); ++curr){
		if (curr->name.compare("speed") == 0)
			return curr->level;
	}
	return 0;
}


float Player::GetVelocityX() {
  return 0.3;
}

float Player::GetVelocityY() {
  return 0.3;
}
