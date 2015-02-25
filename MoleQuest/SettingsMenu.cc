
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
  switch (keycode) {
    case sf::Key::Escape: return "Escape"; break;
    case sf::Key::LControl: return "LControl"; break;
    case sf::Key::LShift: return "LShift"; break;
    case sf::Key::LAlt: return "LAlt"; break;
    case sf::Key::LSystem: return "LSystem"; break;
    case sf::Key::RControl: return "RControl"; break;
    case sf::Key::RShift: return "RShift"; break;
    case sf::Key::RAlt: return "RAlt"; break;
    case sf::Key::RSystem: return "RSystem"; break;
    case sf::Key::Menu: return "Menu"; break;
    case sf::Key::LBracket: return "LBracket"; break;
    case sf::Key::RBracket: return "RBracket"; break;
    case sf::Key::SemiColon: return ";"; break;
    case sf::Key::Comma: return ","; break;
    case sf::Key::Period: return "."; break;
    case sf::Key::Quote: return "'"; break;
    case sf::Key::Slash: return  "/"; break;
    case sf::Key::BackSlash: return "\\"; break;
    case sf::Key::Tilde: return "~"; break;
    case sf::Key::Equal: return "="; break;
    case sf::Key::Dash: return "-"; break;
    case sf::Key::Space: return "Space"; break;
    case sf::Key::Return: return "Return"; break;
    case sf::Key::Back: return "Back"; break;
    case sf::Key::Tab: return "Tab"; break;
    case sf::Key::PageUp: return"Page Up"; break;
    case sf::Key::PageDown: return"Page Down"; break;
    case sf::Key::End: return"End"; break;
    case sf::Key::Home: return"Home"; break;
    case sf::Key::Insert: return"Insert"; break;
    case sf::Key::Delete: return"Delete"; break;
    case sf::Key::Add: return"+"; break;
    case sf::Key::Subtract: return"-"; break;
    case sf::Key::Multiply: return"*"; break;
    case sf::Key::Divide: return"/"; break;
    case sf::Key::Left: return"Left"; break;
    case sf::Key::Right: return"Right"; break;
    case sf::Key::Up: return"Up"; break;
    case sf::Key::Down: return"Down"; break;
    case sf::Key::Numpad0: return"NP 0"; break;
    case sf::Key::Numpad1: return"NP 1"; break;
    case sf::Key::Numpad2: return"NP 2"; break;
    case sf::Key::Numpad3: return"NP 3"; break;
    case sf::Key::Numpad4: return"NP 4"; break;
    case sf::Key::Numpad5: return"NP 5"; break;
    case sf::Key::Numpad6: return"NP 6"; break;
    case sf::Key::Numpad7: return"NP 7"; break;
    case sf::Key::Numpad8: return"NP 8"; break;
    case sf::Key::Numpad9: return"NP 9"; break;
    case sf::Key::F1: return"F1"; break;
    case sf::Key::F2: return"F2"; break;
    case sf::Key::F3: return"F3"; break;
    case sf::Key::F4: return"F4"; break;
    case sf::Key::F5: return"F5"; break;
    case sf::Key::F6: return"F6"; break;
    case sf::Key::F7: return"F7"; break;
    case sf::Key::F8: return"F8"; break;
    case sf::Key::F9: return"F9"; break;
    case sf::Key::F10: return"F10"; break;
    case sf::Key::F11: return"F11"; break;
    case sf::Key::F12: return"F12"; break;
    case sf::Key::F13: return"F13"; break;
    case sf::Key::F14: return"F14"; break;
    case sf::Key::F15: return"F15"; break;
    case sf::Key::Pause: return"Pause"; break;
	case sf::Key::A: return"A"; break;
	case sf::Key::B: return"B"; break;
	case sf::Key::C: return"C"; break;
	case sf::Key::D: return"D"; break;
	case sf::Key:E: return"E"; break;
	case sf::Key::F: return"F"; break;
	case sf::Key::G: return"G"; break;		
	case sf::Key::H: return"H"; break;
	case sf::Key::I: return"I"; break;
	case sf::Key::J: return"J"; break;
	case sf::Key::K: return"K"; break;
	case sf::Key::L: return"L"; break;
	case sf::Key::M: return"M"; break;
	case sf::Key::N: return"N"; break;
	case sf::Key::O: return"O"; break;
	case sf::Key::P: return"P"; break;
	case sf::Key::Q: return"Q"; break;
	case sf::Key::R: return"R"; break;
	case sf::Key::S: return"S"; break;
	case sf::Key::T: return"T"; break;
	case sf::Key::U: return"U"; break;
	case sf::Key::V: return"V"; break;
	case sf::Key::W: return"W"; break;
	case sf::Key::X: return"X"; break;
	case sf::Key::Y: return"Y"; break;
	case sf::Key::Z: return"Z"; break;
	case sf::Key::Num1: return"1"; break;
	case sf::Key::Num2: return"2"; break;
	case sf::Key::Num3: return"3"; break;
	case sf::Key::Num4: return"4"; break;
	case sf::Key::Num5: return"5"; break;
	case sf::Key::Num6: return"6"; break;
	case sf::Key::Num7: return"7"; break;
	case sf::Key::Num8: return"8"; break;
	case sf::Key::Num9: return"9"; break;
	case sf::Key::Num0: return"0"; break;
	}					
}





