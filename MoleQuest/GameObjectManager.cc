#include "stdafx.h"
#include "GameObjectManager.h"

// TODO(Mark): It would be better to use a vector instead of a map to store the game objects
//             because of the huge increase in performance from contiguous memory.
//             Store the actual objects themselves in the vector as well, not pointers
// http://gamedev.stackexchange.com/questions/33888/what-is-the-most-efficient-container-to-store-dynamic-game-objects-in

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
    return nullptr;

  return it->second;
}

int GameObjectManager::GetObjectCount() const {
  return (int) game_objects_.size();
}

void GameObjectManager::DrawAll(int interp, sf::RenderWindow &window) {
  for (const auto obj : game_objects_)
    obj.second->Draw(interp, window);
}

void GameObjectManager::UpdateAll(int lag) {
  for (const auto obj : game_objects_)
    obj.second->Update(lag);
}