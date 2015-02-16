
#include "stdafx.h"
#include "Shop.h"
#include <Windows.h>


Shop::Shop() {
	texture_.loadFromFile("images/shop.png");
	sprite_.setTexture(texture_);

	ShopItem cont;
	cont.rect.top = 686;
	cont.rect.left = 732;
	cont.rect.width = 180;
	cont.rect.height = 70;
	cont.result = Result::kContinue;

	ShopItem duelPistols;
	duelPistols.name = "duelPistols";
	duelPistols.rect.top = 209;
	duelPistols.rect.left = 301;
	duelPistols.rect.height = 41;
	duelPistols.rect.width = 174;
	duelPistols.result = Result::kBuy;

	ShopItem pdw;
	pdw.name = "pdw";
	pdw.rect.top = 350;
	pdw.rect.left = 301;
	pdw.rect.height = 41;
	pdw.rect.width = 174;
	pdw.result = Result::kBuy;

	ShopItem shotgun;
	shotgun.name = "shotgun";
	shotgun.rect.top = 485;
	shotgun.rect.left = 340;
	shotgun.rect.height = 41;
	shotgun.rect.width = 134;
	shotgun.result = Result::kBuy;

	ShopItem smg;
	smg.name = "smg";
	smg.rect.top = 209;
	smg.rect.left = 726;
	smg.rect.height = 41;
	smg.rect.width = 174;
	smg.result = Result::kBuy;

	ShopItem assaultRifle;
	assaultRifle.name = "assaultRifle";
	assaultRifle.rect.top = 353;
	assaultRifle.rect.left = 726;
	assaultRifle.rect.height = 41;
	assaultRifle.rect.width = 174;
	assaultRifle.result = Result::kBuy;

	ShopItem minigun;
	minigun.name = "minigun";
	minigun.rect.top = 604;
	minigun.rect.left = 555;
	minigun.rect.height = 57;
	minigun.rect.width = 333;
	minigun.result = Result::kBuy;

	ShopItem health;
	health.name = "health";
	health.rect.top = 608;
	health.rect.left = 190;
	health.rect.height = 56;
	health.rect.width = 78;
	health.result = Result::kUpgrade;

	ShopItem speed;
	speed.name = "speed";
	speed.rect.top = 608;
	speed.rect.left = 388;
	speed.rect.height = 56;
	speed.rect.width = 78;
	speed.result = Result::kUpgrade;


	shop_items_.push_back(cont);
	shop_items_.push_back(duelPistols);
	shop_items_.push_back(pdw);
	shop_items_.push_back(smg);
	shop_items_.push_back(shotgun);
	shop_items_.push_back(assaultRifle);
	shop_items_.push_back(minigun);
	shop_items_.push_back(speed);
	shop_items_.push_back(health);
}

Shop::Result Shop::Show(sf::RenderWindow &window) {
	window.draw(sprite_);
	if (speed_sprite_.getTexture() != nullptr){

		window.draw(speed_sprite_);
	}
	if (health_sprite_.getTexture() != nullptr)
		window.draw(health_sprite_);
	
	window.display();

	// Now drop into an event loop waiting for the user to click
	// a button on the image that is now displayed
	return GetMenuResponse(window);
}

Shop::Result Shop::HandleClick(int x, int y) {
	for (const auto obj : shop_items_) {
		sf::Rect<int> shopItemRect = obj.rect;
		
		if (shopItemRect.contains(sf::Vector2<int>(x, y))){
			if (obj.result == Result::kBuy || obj.result == Result::kUpgrade)
				toBuy = obj.name;
			return obj.result;
		}
	}

	return Result::kNothing;
}

Shop::Result Shop::GetMenuResponse(sf::RenderWindow &window) {
	sf::Event event;

	// Continously poll for events waiting for the user to click on a
	// button or close the program
	while (true) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed) {
				Result result = HandleClick(event.mouseButton.x, event.mouseButton.y);

				if (result != Result::kNothing)
					return result;
			}

			if (event.type == sf::Event::Closed)
				return Result::kExit;
		}

		// Reduces cpu usage a lot during the main menu
		Sleep(1);
	}
}

void Shop::UpdateMenu(int hL, int sL){
	
	if (sL > 0){
		if (sL == 1)
			speed_tex_.loadFromFile("images/speed1.png");
		if (sL == 2)
			speed_tex_.loadFromFile("images/speed2.png");
		if (sL == 3)
			speed_tex_.loadFromFile("images/speed3.png");
		if (sL >= 4)
			speed_tex_.loadFromFile("images/speed4.png");

		speed_sprite_.setTexture(speed_tex_);
		speed_sprite_.setPosition(305, 553);
	}

	if (hL > 0){
		if(hL == 1)
			health_tex_.loadFromFile("images/health1.png");
		if(hL == 2)
			health_tex_.loadFromFile("images/health2.png");
		if(hL == 3)
			health_tex_.loadFromFile("images/health3.png");
		if(hL >= 4)
			health_tex_.loadFromFile("images/health4.png");
		
		health_sprite_.setTexture(health_tex_);
		health_sprite_.setPosition(110, 553);	
	}
}