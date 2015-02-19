#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager() {
  // Reserve contiguous space for 1000 objects. This will be more than enough for the entire game
  game_objects_.reserve(1000);
}

GameObjectManager::~GameObjectManager() {
  game_objects_.clear();
}

void GameObjectManager::Add(GameObject game_object) {
  game_objects_.push_back(game_object);
}

void GameObjectManager::Remove(int index) {
  // Put end object in place of the object we are removing, then remove end object
  // This keeps all the objects together in the vector with no spaces
  std::swap(game_objects_[index], game_objects_.back());
  game_objects_.pop_back();
}

void GameObjectManager::DrawAll(int interp, sf::RenderWindow& window) {
  for (auto obj : game_objects_)
    obj.Draw(interp, window);
}

void GameObjectManager::UpdateAll(int lag) {
  for (auto obj : game_objects_)
    obj.Update(lag);
}