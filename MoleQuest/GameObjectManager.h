#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include "GameObject.h"
#include "QuadTree.h"

class GameObjectManager {
 public:
  GameObjectManager();
  ~GameObjectManager();

  // Adds object to internal object vector
  static void Add(GameObject* game_object);

  // Adds index to internal marked_for_deletion vector to be deleted later in RemoveDeleted()
  static void Remove(int index);

  void DrawAll(int interp, sf::RenderWindow &window);
  void UpdateAll(int lag);

 private:
  int vector_size_ = 100;

  std::vector<GameObject*> game_objects_;

  static std::vector<int> marked_for_deletion_;
  static std::vector<GameObject*> marked_for_insertion_;

  void Insert();

  // Goes through marked_for_deletion vector deleting all the objects marked for deletion
  void RemoveDeleted();

  void CollisionDetection();

  //QuadTree quad_tree_ = QuadTree(5, 3, 1024, 768);
};

#endif 