#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

class GameObject {
 public:
  GameObject();
  virtual ~GameObject();

  virtual void Load(std::string filename);
  virtual void Draw(sf::RenderWindow &window);
  virtual void SetPosition(float x, float y);

 private:
  sf::Sprite sprite_;
  sf::Texture texture_;
  std::string filename_;
  bool is_loaded_;
};

#endif