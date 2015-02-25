//  Intro.h
//  This file is part of MoleQuest
//
//  This class handles the displaying of the introduction animation after the 
//  play button has been pressed on the main menu.
#ifndef INTRO_H_
#define INTRO_H_

class Intro {
  public:
    Intro();

    enum class Result {kNothing};
    
   void Show(sf::RenderWindow &window);

	//For the loading of Background, Midground and Foreground layers.
    sf::Texture texture_B_;
    sf::Sprite sprite_B_;

    sf::Texture texture_M_;
    sf::Sprite sprite_M_;
    
    sf::Texture texture_F_;
    sf::Sprite sprite_F_;
    sf::Texture texture_F2_;
    sf::Sprite sprite_F2_;
};

#endif