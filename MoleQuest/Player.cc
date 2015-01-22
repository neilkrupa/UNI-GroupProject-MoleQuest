#include "stdafx.h"
#include "Player.h"

Player::Player() {}

Player::~Player() {}

void Player::move(unsigned int w,unsigned int h){
	float y = GameObject::GetPosition().y;
	float x = GameObject::GetPosition().x;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		if (y - .5 >= 0)
			GameObject::SetPosition(x, y - .5);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		if (x - .5 >= 0)
			GameObject::SetPosition(x - .5, y);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		if (x + .5 < w)
			GameObject::SetPosition(x + .5, y);
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		if (y + .5 < h)
			GameObject::SetPosition(x, y + .5);

}