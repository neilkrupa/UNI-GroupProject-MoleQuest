#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include "GameObject.h"

class GameObjectManager {
 public:
  GameObjectManager();
  ~GameObjectManager();

  // Adds object to internal object vector
  void Add(GameObject* game_object);

  // Removes object from the internal object vector using swap-and-pop
  static void Remove(int index);

  void DrawAll(int interp, sf::RenderWindow &window);
  void UpdateAll(int lag);

 private:
  int vector_size_ = 100;

  std::vector<GameObject*> game_objects_;
  static std::vector<int> marked_for_deletion_;

  void RemoveDeleted();
};

#endif 