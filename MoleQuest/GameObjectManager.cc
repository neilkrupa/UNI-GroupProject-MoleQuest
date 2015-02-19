#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager() {
  // Reserve contiguous space for 100 objects. This will be more than enough for the entire game
  // Moles and bullets are removed when they are dead / not visible
  game_objects_.reserve(100);
}

GameObjectManager::~GameObjectManager() {
  game_objects_.clear();
}

void GameObjectManager::Add(GameObject game_object) {
  game_object.SetObjectManagerIndex(game_objects_.size());
  game_objects_.push_back(game_object);
}

void GameObjectManager::Remove(int index) {
  // Check for a valid index (game objects initialise to index -1)
  if (index > 0 && index < game_objects_.size()) {
    // Put end object in place of the object we are removing, then remove end object
    // This keeps all the objects together in the vector with no spaces
    std::swap(game_objects_[index], game_objects_.back());
    game_objects_.pop_back();

    // Set the new index for the object that was moved
    game_objects_[index].SetObjectManagerIndex(index);
  }
}

void GameObjectManager::DrawAll(int interp, sf::RenderWindow& window) {
  for (auto obj : game_objects_)
    obj.Draw(interp, window);
}

void GameObjectManager::UpdateAll(int lag) {
  for (auto obj : game_objects_)
    obj.Update(lag);
}