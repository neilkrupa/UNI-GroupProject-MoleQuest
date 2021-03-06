#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager() {
  // Reserve contiguous space for 100 objects. This will be more than enough for the entire game
  // Moles and bullets are removed when they are dead / not visible
  game_objects_.reserve(vector_size_);
  marked_for_deletion_.reserve(vector_size_);
}

GameObjectManager::~GameObjectManager() {
  // Delete all game objects - could also use std::unique_ptr instead to automatic deletion
  for (auto obj : game_objects_)
    delete obj;

  game_objects_.clear();
}

void GameObjectManager::Add(GameObject* game_object) {
  marked_for_insertion_.push_back(game_object);
}

void GameObjectManager::Insert() {
  /* If vector is nearly full, add vector_size_ more spaces */
  if (game_objects_.size() >= game_objects_.capacity() - 1)
    game_objects_.reserve(game_objects_.capacity() + vector_size_);

  for (auto obj : marked_for_insertion_) {
    obj->SetObjectManagerIndex(game_objects_.size());
    game_objects_.push_back(obj);
  }

  marked_for_insertion_.clear();
}

void GameObjectManager::Remove(int index) {
  marked_for_deletion_.push_back(index);
}

void GameObjectManager::RemoveDeleted() {
  for (int index : marked_for_deletion_) {
    // Check for a valid index (Objects initialise to -1 when made and haven't beed added to manager)
    if (index >= 0 && index < game_objects_.size()) {

      // If not last in vector then swap the object to be removed to the back of the vector
      if (index != game_objects_.size() - 1) {
        std::swap(game_objects_[index], game_objects_.back());
        game_objects_[index]->SetObjectManagerIndex(index);
      }

      delete game_objects_.back();
      game_objects_.pop_back();
    }
  }

  marked_for_deletion_.clear();
}

void GameObjectManager::DrawAll(int interp, sf::RenderWindow& window) {
  for (auto obj : game_objects_)
    obj->Draw(interp, window);
}

void GameObjectManager::UpdateAll(int lag) {
  RemoveDeleted();

  for (auto obj : game_objects_)
    obj->Update(lag);

  CollisionDetection();

  Insert();
}

void GameObjectManager::CollisionDetection() {
  // Brute force collision detection whilst quad trees are implemented
  for (auto obj : game_objects_) {
    for (auto obj2 : game_objects_) {
      // Dont check for collision against self
      if (obj == obj2)
        continue;

      // Check the bounds for intersection
      sf::FloatRect obj_bounds = obj->GetSprite().getGlobalBounds();
      sf::FloatRect obj2_bounds = obj2->GetSprite().getGlobalBounds();

      if (obj_bounds.intersects(obj2_bounds)) {
        obj->Collision(obj2);
        obj2->Collision(obj);
      }
    }
  }
}

std::vector<int> GameObjectManager::marked_for_deletion_;
std::vector<GameObject*> GameObjectManager::marked_for_insertion_;