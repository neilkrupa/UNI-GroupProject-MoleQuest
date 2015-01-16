#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject() : is_loaded_(false) {}

GameObject::~GameObject() {}

void GameObject::Load(std::string filename) {
  if (texture_.loadFromFile(filename)) {
    is_loaded_ = true;
    filename_ = filename;
    sprite_.setTexture(texture_);
  } else {
    is_loaded_ = false;
    filename = "";
  }
}

void GameObject::Draw(sf::RenderWindow &renderWindow) {
  if (is_loaded_)
    renderWindow.draw(sprite_);
}

void GameObject::SetPosition(float x, float y) {
  if (is_loaded_)
    sprite_.setPosition(x, y);
}
