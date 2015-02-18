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

void GameObject::Draw(int interp, sf::RenderWindow &renderWindow) {
  if (is_loaded_) 
    renderWindow.draw(sprite_);
}

sf::Sprite& GameObject::GetSprite() {
  return sprite_;
}

void GameObject::Update(int lag) {}

sf::Vector2f GameObject::GetPosition() const {
  return sprite_.getPosition();
}
