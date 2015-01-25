#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

class GameObject {
 public:
  GameObject();
  virtual ~GameObject();

  virtual void Load(std::string filename);
  virtual void Draw(float interp, sf::RenderWindow &window);
  virtual void Update(float lag);

  sf::Vector2f GetPosition() const;
  
protected:
  sf::Sprite& GetSprite();

 private:
  sf::Sprite sprite_;
  sf::Texture texture_;
  std::string filename_;
  bool is_loaded_;
};

#endif