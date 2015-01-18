#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager() {}

GameObjectManager::~GameObjectManager() {
  std::for_each(game_objects_.begin(), game_objects_.end(), Deallocator());
}

void GameObjectManager::Add(std::string name, GameObject* game_object) {
  game_objects_.insert(std::pair<std::string, GameObject*>(name, game_object));
}

void GameObjectManager::Remove(std::string name) {
  std::map<std::string, GameObject*>::const_iterator it = game_objects_.find(name);

  if (it != game_objects_.end()) {
    // Delete the game object first
    delete it->second;
    game_objects_.erase(it);
  }
}

GameObject* GameObjectManager::Get(std::string name) const {
  std::map<std::string, GameObject*>::const_iterator it = game_objects_.find(name);

  if (it == game_objects_.end())
    return NULL;

  return it->second;
}

int GameObjectManager::GetObjectCount() const {
  return game_objects_.size();
}

void GameObjectManager::DrawAll(float interp, sf::RenderWindow &window) {
  std::map<std::string, GameObject*>::const_iterator it;

  for (it = game_objects_.begin(); it != game_objects_.end(); it++)
    it->second->Draw(interp, window);
}

void GameObjectManager::UpdateAll() {
  std::map<std::string, GameObject*>::const_iterator it;

  for (it = game_objects_.begin(); it != game_objects_.end(); it++)
    it->second->Update();
}