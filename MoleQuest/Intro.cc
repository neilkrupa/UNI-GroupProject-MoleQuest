//  Intro.cc
//  This file is part of MoleQuest
//
//  For purpose, see Intro.h
#include "stdafx.h"
#include "Intro.h"
#include <Windows.h>

Intro::Intro() {
  // Load the introduction animation
  texture_B_.loadFromFile("images/introAn/B1.png");
  sprite_B_.setTexture(texture_B_);

  texture_M_.loadFromFile("images/introAn/M.png");
  sprite_M_.setTexture(texture_M_);

  texture_F_.loadFromFile("images/introAn/F1.png");
  sprite_F_.setTexture(texture_F_);
  sprite_F_.setPosition(600, 500);
  sprite_F_.scale(0.40, 0.40);
}

Intro::Result Intro::Show(sf::RenderWindow &window) {
  //Animate first scene.
  float yAxis = 300;
  float xAxis = 600;
  for (int a = 0; a < 400; a++){
    window.draw(sprite_B_);
    window.draw(sprite_F_);
    window.display();
    yAxis = yAxis + 0.2;
    xAxis = xAxis - 1;
    sprite_F_.setPosition(xAxis, yAxis);
    Sleep(10);
  }

  //Load in second scene.
  texture_B_.loadFromFile("images/introAn/B2.png");
  sprite_B_.setTexture(texture_B_);

  texture_F2_.loadFromFile("images/introAn/F2.png");
  sprite_F2_.setTexture(texture_F2_);

  //Animate second scene.
  yAxis = 0;
  xAxis = 0;
  for (int a = 0; a < 400; a++){
    window.draw(sprite_B_);
    window.draw(sprite_M_);
    window.draw(sprite_F2_);
    window.display();
    xAxis = xAxis + 0.2;
    yAxis = yAxis - 0.5;
    sprite_M_.setPosition(xAxis, yAxis);
    Sleep(10);
  }

  //Load in third scene.
  texture_B_.loadFromFile("images/introAn/B3.png");
  sprite_B_.setTexture(texture_B_);

  texture_F2_.loadFromFile("images/introAn/F3.png");
  sprite_F2_.setTexture(texture_F2_);
  sprite_F2_.setPosition(-100, 100);

  //Animate third scene.
  yAxis = 1;
  xAxis = 1;
  for (int a = 0; a < 40; a++){
    window.draw(sprite_B_);
    window.draw(sprite_F2_);
    window.display();
    xAxis = xAxis - 0.0002;
    yAxis = yAxis - 0.0002;
    sprite_F2_.scale(xAxis, yAxis);
    Sleep(100);
  }
  return Result::kNothing;
}