//  Pause.h
//  This file is part of MoleQuest
//
//  This class loads and displays the pause menu on key press
//	The buttons here will return to the game, open the st
//  speed, and damage. 
//  The input is managed in a simliar manner to the other menus

#ifndef PAUSE_H_
#define PAUSE_H_

class Pause {
public:
	Pause();

	enum class Result { kPlay, kSettings, kExit, kNothing, kMenu };

	Result Show(sf::RenderWindow &window);

private:
	// A struct to hold data about the buttons on the main menu
	struct PauseItem {
	public:

		sf::Rect<int> rect;

		Result result;
	};

	Result GetMenuResponse(sf::RenderWindow &window);

	Result HandleClick(int x, int y);

	std::list<PauseItem> pause_items_;

	
	sf::Texture texture_;
	sf::Sprite sprite_;
};

#endif