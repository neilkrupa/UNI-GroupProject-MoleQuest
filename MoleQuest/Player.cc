#include "stdafx.h"
#include "Player.h"

Player::Player() : velocity_x_(0), velocity_y_(0) {
  GetSprite().setPosition(1024 / 2, 600);
  Load("images/player.png");

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

  //TODO(Mark): Player should always face the mouse

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

float Player::GetVelocityX() {
  return 0.3;
}

float Player::GetVelocityY() {
  return 0.3;
}