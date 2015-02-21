#include "stdafx.h"
#include "Mole.h"

Mole::Mole(Player* player): velocity_x_(0), velocity_y_(0) {
	Load("images/moles/normalMole.png");
	GetSprite().scale(0.5, 0.5);
  GetSprite().setPosition(1024 / 2, 100);

  // Store the player's memory address for use in AI logic
  player_ = player;

	animation_handler_ = new AnimationHandler();
}
Mole::~Mole() {
	delete animation_handler_;
}

void Mole::Update(float lag) {
	GetSprite().move(velocity_x_ * lag, velocity_y_ * lag);
	float x = player_->GetPosition().x;

//	printf("position y = %d/n", .GetPosition().y);
}
void Mole::Draw(float interp, sf::RenderWindow& window) {
	window.draw(GetSprite());
}