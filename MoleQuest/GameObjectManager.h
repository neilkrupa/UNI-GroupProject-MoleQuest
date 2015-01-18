#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include "GameObject.h"

class GameObjectManager {
 public:
  GameObjectManager();
  ~GameObjectManager();

  void Add(std::string name, GameObject* game_object);
  void Remove(std::string name);
  GameObject* Get(std::string name) const;

  int GetObjectCount() const;

  void DrawAll(float interp, sf::RenderWindow &window);
  void UpdateAll();

 private:
  std::map<std::string, GameObject*> game_objects_;

  struct Deallocator {
    void operator()(const std::pair<std::string, GameObject*> &p) const {
      delete p.second;
    }
  };
};

#endif 