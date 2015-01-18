#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

class GameObject {
 public:
  GameObject();
  virtual ~GameObject();

  virtual void Load(std::string filename);
  virtual void Draw(sf::RenderWindow &window);
  virtual void Update(float elapsed_time);

  virtual void SetPosition(float x, float y);
  virtual sf::Vector2f GetPosition() const;

  inline virtual bool IsLoaded() const { return is_loaded_; }

 private:
  sf::Sprite sprite_;
  sf::Texture texture_;
  std::string filename_;
  bool is_loaded_;
};

#endif