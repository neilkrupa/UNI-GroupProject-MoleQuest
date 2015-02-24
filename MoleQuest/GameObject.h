#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

class GameObject {
 public:
  GameObject();
  virtual ~GameObject();

  virtual void Load(std::string filename);
  virtual void Draw(int interp, sf::RenderWindow &window);
  virtual void Update(int lag);
  virtual void Collision(GameObject*);

  enum ObjectType { kPlayer, kMole, kProjectile };

  ObjectType GetObjectType();
  void SetObjectType(ObjectType type);

  // When object is added to game object manager, the index it was inserted as
  // is returned. To remove this object from the manager later, store the index
  // using this function
  void SetObjectManagerIndex(int n);

  // Get the index this object is stored in the object manager to remove it
  int GetObjectManagerIndex() const;

  sf::Vector2f GetPosition() const;

  sf::Sprite& GetSprite();

  

 private:
  int object_manager_index_;

  sf::Sprite sprite_;
  sf::Texture texture_;
  std::string filename_;
  bool is_loaded_;

  ObjectType type_;
};

#endif