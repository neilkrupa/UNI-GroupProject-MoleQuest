#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include "GameObject.h"

class GameObjectManager {
 public:
  GameObjectManager();
  ~GameObjectManager();

  void Add(GameObject game_object);
  void Remove(int index);

  void DrawAll(int interp, sf::RenderWindow &window);
  void UpdateAll(int lag);

 private:
  std::vector<GameObject> game_objects_;
};

#endif 