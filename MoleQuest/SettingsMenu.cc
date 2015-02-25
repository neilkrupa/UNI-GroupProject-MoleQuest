
#include "stdafx.h"
#include "SettingsMenu.h"
#include <Windows.h>

SettingsMenu::SettingsMenu() {
	texture_.loadFromFile("images/settingsmenu.png");
	sprite_.setTexture(texture_);

	// Add clickable regions around the buttons
	SettingsItem shoot;
	shoot.rect.top = 280;
	shoot.rect.left = 155;
	shoot.rect.width = 678;
	shoot.rect.height = 44;
	shoot.result = Result::kMap;
	shoot.name = "shoot";
	shoot.key.setCharacterSize(20);
	shoot.key.setPosition( 475, 290);
	shoot.key.setString("Left Mouse");
	shoot.key.setColor(sf::Color::Black);

	SettingsItem foward;
	foward.rect.top = 326;
	foward.rect.left = 155;
	foward.rect.width = 678;
	foward.rect.height = 44;
	foward.result = Result::kMap;
	foward.name = "foward";
	foward.key.setCharacterSize(20);
	foward.key.setPosition(475, 336);
	foward.key.setString("W");
	foward.key.setColor(sf::Color::Black);

	SettingsItem backwards;
	backwards.rect.top = 372;
	backwards.rect.left = 155;
	backwards.rect.width = 678;
	backwards.rect.height = 44;
	backwards.result = Result::kMap;
	backwards.name = "backwards";
	backwards.key.setCharacterSize(20);
	backwards.key.setPosition(475, 381);
	backwards.key.setString("S");
	backwards.key.setColor(sf::Color::Black);

	SettingsItem left;
	left.rect.top = 415;
	left.rect.left = 155;
	left.rect.width = 678;
	left.rect.height = 44;
	left.result = Result::kMap;
	left.name = "left";
	left.key.setCharacterSize(20);
	left.key.setPosition(475, 425);
	left.key.setString("A");
	left.key.setColor(sf::Color::Black);

	SettingsItem right;
	right.rect.top = 461;
	right.rect.left = 155;
	right.rect.width = 678;
	right.rect.height = 44;
	right.result = Result::kMap;
	right.name = "right";
	right.key.setCharacterSize(20);
	right.key.setPosition(475, 469);
	right.key.setString("D");
	right.key.setColor(sf::Color::Black);

	SettingsItem cyclel;
	cyclel.rect.top = 504;	
	cyclel.rect.left = 155;
	cyclel.rect.width = 678;
	cyclel.rect.height = 44;
	cyclel.result = Result::kMap;
	cyclel.name = "cyclel";
	cyclel.key.setCharacterSize(20);
	cyclel.key.setPosition(475, 513);
	cyclel.key.setString("Q");
	cyclel.key.setColor(sf::Color::Black);

	SettingsItem cycler;
	cycler.rect.top = 552;	
	cycler.rect.left = 155;
	cycler.rect.width = 678;
	cycler.rect.height = 44;
	cycler.result = Result::kMap;
	cycler.name = "cycler";
	cycler.key.setCharacterSize(20);
	cycler.key.setPosition(475, 553);
	cycler.key.setString("E");
	cycler.key.setColor(sf::Color::Black);

	SettingsItem pause;
	pause.rect.top = 590;	
	pause.rect.left = 155;
	pause.rect.width = 678;
	pause.rect.height = 44;
	pause.result = Result::kMap;
	pause.name = "pause";
	pause.key.setCharacterSize(20);
	pause.key.setPosition(475, 603);
	pause.key.setString("Escape");
	pause.key.setColor(sf::Color::Black);


	SettingsItem back;
	back.rect.top = 674;
	back.rect.left = 401;
	back.rect.width = 179;
	back.rect.height = 54;
	back.result = Result::kBack;
	back.name = "back";

	// Add the items to the list
	settings_items_.push_back(shoot);
	settings_items_.push_back(foward);
	settings_items_.push_back(backwards);
	settings_items_.push_back(left);
	settings_items_.push_back(right);
	settings_items_.push_back(cyclel);
	settings_items_.push_back(cycler);
	settings_items_.push_back(pause);
	settings_items_.push_back(back);
}

SettingsMenu::Result SettingsMenu::Show(sf::RenderWindow &window) {
	window.draw(sprite_);
	sf::Font f; 
	f.loadFromFile("fonts/quest.ttf");
	for ( auto obj : settings_items_) {
			obj.key.setFont(f);
			window.draw(obj.key);
	}
	window.display();

	// Now drop into an event loop waiting for the user to click
	// a button on the image that is now displayed
	return GetMenuResponse(window);
}

SettingsMenu::Result SettingsMenu::HandleClick(int x, int y) {
	for (const auto obj : settings_items_) {
		sf::Rect<int> settingsItemRect = obj.rect;

		if (settingsItemRect.contains(sf::Vector2<int>(x, y))){
			if (obj.result == Result::kMap)
				tomap = obj.name;
			return obj.result;
		}
	}

	return Result::kNothing;
}

SettingsMenu::Result SettingsMenu::GetMenuResponse(sf::RenderWindow &window) {
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

void SettingsMenu::UpdateMenu(std::map<std::string, Game::Input> key_map_){
	std::map<std::string, Game::Input>::iterator mapCurr;
	std::list<SettingsItem>::iterator curr;

	for (mapCurr = key_map_.begin(); mapCurr != key_map_.end(); ++mapCurr){
		for (curr = settings_items_.begin(); curr != settings_items_.end(); ++curr){
			if (curr->name.compare(mapCurr->first) == 0){
				if (mapCurr->second.type == Game::InputType::kKey)
					curr->key.setString(GetKey(mapCurr->second.KeyCode));
				else
					curr->key.setString(std::to_string(mapCurr->second.MouseButton));
				break;
			}
		}
	}
}

std::string SettingsMenu::GetKey(sf::Keyboard::Key key){
  switch (key) {
    case sf::Keyboard::Key::Escape: return "Escape"; 
    case sf::Keyboard::Key::LControl: return "LControl"; 
    case sf::Keyboard::Key::LShift: return "LShift"; 
    case sf::Keyboard::Key::LAlt: return "LAlt"; 
    case sf::Keyboard::Key::LSystem: return "LSystem"; 
    case sf::Keyboard::Key::RControl: return "RControl"; 
    case sf::Keyboard::Key::RShift: return "RShift"; 
    case sf::Keyboard::Key::RAlt: return "RAlt"; 
    case sf::Keyboard::Key::RSystem: return "RSystem"; 
    case sf::Keyboard::Key::Menu: return "Menu"; 
    case sf::Keyboard::Key::LBracket: return "LBracket"; 
    case sf::Keyboard::Key::RBracket: return "RBracket"; 
    case sf::Keyboard::Key::SemiColon: return ";"; 
    case sf::Keyboard::Key::Comma: return ","; 
    case sf::Keyboard::Key::Period: return "."; 
    case sf::Keyboard::Key::Quote: return "'"; 
    case sf::Keyboard::Key::Slash: return  "/"; 
    case sf::Keyboard::Key::BackSlash: return "\\"; 
    case sf::Keyboard::Key::Tilde: return "~"; 
    case sf::Keyboard::Key::Equal: return "="; 
    case sf::Keyboard::Key::Dash: return "-"; 
    case sf::Keyboard::Key::Space: return "Space"; 
    case sf::Keyboard::Key::Return: return "Return"; 
    case sf::Keyboard::Key::BackSpace: return "Back"; 
    case sf::Keyboard::Key::Tab: return "Tab"; 
    case sf::Keyboard::Key::PageUp: return"Page Up"; 
    case sf::Keyboard::Key::PageDown: return"Page Down"; 
    case sf::Keyboard::Key::End: return"End"; 
    case sf::Keyboard::Key::Home: return"Home"; 
    case sf::Keyboard::Key::Insert: return"Insert"; 
    case sf::Keyboard::Key::Delete: return"Delete"; 
    case sf::Keyboard::Key::Add: return"+"; 
    case sf::Keyboard::Key::Subtract: return"-"; 
    case sf::Keyboard::Key::Multiply: return"*"; 
    case sf::Keyboard::Key::Divide: return"/"; 
    case sf::Keyboard::Key::Left: return"Left"; 
    case sf::Keyboard::Key::Right: return"Right"; 
    case sf::Keyboard::Key::Up: return"Up"; 
    case sf::Keyboard::Key::Down: return"Down"; 
    case sf::Keyboard::Key::Numpad0: return"NP 0"; 
    case sf::Keyboard::Key::Numpad1: return"NP 1"; 
    case sf::Keyboard::Key::Numpad2: return"NP 2"; 
    case sf::Keyboard::Key::Numpad3: return"NP 3"; 
    case sf::Keyboard::Key::Numpad4: return"NP 4"; 
    case sf::Keyboard::Key::Numpad5: return"NP 5"; 
    case sf::Keyboard::Key::Numpad6: return"NP 6"; 
    case sf::Keyboard::Key::Numpad7: return"NP 7"; 
    case sf::Keyboard::Key::Numpad8: return"NP 8"; 
    case sf::Keyboard::Key::Numpad9: return"NP 9"; 
    case sf::Keyboard::Key::F1: return"F1"; 
    case sf::Keyboard::Key::F2: return"F2"; 
    case sf::Keyboard::Key::F3: return"F3"; 
    case sf::Keyboard::Key::F4: return"F4"; 
    case sf::Keyboard::Key::F5: return"F5"; 
    case sf::Keyboard::Key::F6: return"F6"; 
    case sf::Keyboard::Key::F7: return"F7"; 
    case sf::Keyboard::Key::F8: return"F8"; 
    case sf::Keyboard::Key::F9: return"F9"; 
    case sf::Keyboard::Key::F10: return"F10"; 
    case sf::Keyboard::Key::F11: return"F11"; 
    case sf::Keyboard::Key::F12: return"F12"; 
    case sf::Keyboard::Key::F13: return"F13"; 
    case sf::Keyboard::Key::F14: return"F14"; 
    case sf::Keyboard::Key::F15: return"F15"; 
    case sf::Keyboard::Key::Pause: return"Pause"; 
	  case sf::Keyboard::Key::A: return"A"; 
	  case sf::Keyboard::Key::B: return"B"; 
	  case sf::Keyboard::Key::C: return"C"; 
	  case sf::Keyboard::Key::D: return"D"; 
    case sf::Keyboard::Key::E: return"E"; 
	  case sf::Keyboard::Key::F: return"F"; 
	  case sf::Keyboard::Key::G: return"G"; 		
	  case sf::Keyboard::Key::H: return"H"; 
	  case sf::Keyboard::Key::I: return"I"; 
	  case sf::Keyboard::Key::J: return"J"; 
	  case sf::Keyboard::Key::K: return"K"; 
	  case sf::Keyboard::Key::L: return"L"; 
	  case sf::Keyboard::Key::M: return"M"; 
	  case sf::Keyboard::Key::N: return"N"; 
	  case sf::Keyboard::Key::O: return"O"; 
	  case sf::Keyboard::Key::P: return"P"; 
	  case sf::Keyboard::Key::Q: return"Q"; 
	  case sf::Keyboard::Key::R: return"R"; 
	  case sf::Keyboard::Key::S: return"S"; 
	  case sf::Keyboard::Key::T: return"T"; 
	  case sf::Keyboard::Key::U: return"U"; 
	  case sf::Keyboard::Key::V: return"V"; 
	  case sf::Keyboard::Key::W: return"W"; 
	  case sf::Keyboard::Key::X: return"X"; 
	  case sf::Keyboard::Key::Y: return"Y"; 
	  case sf::Keyboard::Key::Z: return"Z"; 
	  case sf::Keyboard::Key::Num1: return"1"; 
	  case sf::Keyboard::Key::Num2: return"2"; 
	  case sf::Keyboard::Key::Num3: return"3"; 
	  case sf::Keyboard::Key::Num4: return"4"; 
	  case sf::Keyboard::Key::Num5: return"5"; 
	  case sf::Keyboard::Key::Num6: return"6"; 
	  case sf::Keyboard::Key::Num7: return"7"; 
	  case sf::Keyboard::Key::Num8: return"8"; 
	  case sf::Keyboard::Key::Num9: return"9"; 
	  case sf::Keyboard::Key::Num0: return"0"; 
    default: return "n/a"; 
	}					
}





