#ifndef SOUND_CACHE_
#define SOUND_CACHE_

class SoundCache {
 public:
  SoundCache();
  ~SoundCache();

  sf::Sound GetSound(std::string name);
  sf::Music* GetSong(std::string name);

 private:
  std::map<std::string, sf::SoundBuffer*> sounds_;
  std::map<std::string, sf::Music*> music_;

  template <typename T>
  struct Deallocator {
    void operator()(const std::pair<std::string, T> &p) {
      delete p.second;
    }
  };
};

class SoundNotFoundException : public std::runtime_error {
public:
  SoundNotFoundException(std::string const& msg) : std::runtime_error(msg) {}
};

#endif