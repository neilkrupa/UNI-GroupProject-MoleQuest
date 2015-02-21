#include "stdafx.h"
#include "Mole.h"

Mole::Mole(Player& player): velocity_x_(0), velocity_y_(0) {
	GetSprite().setPosition(1024 / 2, 600);
	Player player_ =player;
	Load("images/moles/normalMole.png");
	GetSprite().scale(0.5, 0.5);
	GetSprite().setOrigin(49, 173);
	animation_handler_ = new AnimationHandler();
}
Mole::~Mole() {
	delete animation_handler_;
}

void Mole::Update(float lag){
	GetSprite().move(velocity_x_ * lag, velocity_y_ * lag);
	float x = player->GetPosition().x;

//	printf("position y = %d/n", .GetPosition().y);
}
void Mole::Draw(float interp, sf::RenderWindow& window) {
	window.draw(GetSprite());
}