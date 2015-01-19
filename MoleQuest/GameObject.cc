#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject() : is_loaded_(false) {}

GameObject::~GameObject() {}

void GameObject::Load(std::string filename) {
  if (texture_.loadFromFile(filename)) {
    is_loaded_ = true;
    filename_ = filename;
    sprite_.setTexture(texture_);
    sprite_.scale(8, 8);
  } else {
    is_loaded_ = false;
    filename = "";
  }
}

void GameObject::Draw(float interp, sf::RenderWindow &renderWindow) {
  if (is_loaded_) 
    renderWindow.draw(sprite_);
}

void GameObject::SetPosition(float x, float y) {
  if (is_loaded_)
    sprite_.setPosition(x, y);
}

sf::Vector2f GameObject::GetPosition() const {
  if (is_loaded_)
    return sprite_.getPosition();

  return sf::Vector2f();
}

void GameObject::Update() {}