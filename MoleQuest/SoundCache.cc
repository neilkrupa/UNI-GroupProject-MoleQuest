#include "stdafx.h"
#include "SoundCache.h"

// Maybe refactor the Get methods as they're basically doing the same thing?

SoundCache::SoundCache() {}

SoundCache::~SoundCache() {
  std::for_each(sounds_.begin(), sounds_.end(), Deallocator<sf::SoundBuffer*>());
  std::for_each(music_.begin(), music_.end(), Deallocator<sf::Music*>());
}

sf::Sound SoundCache::GetSound(std::string name) {
  std::map<std::string, sf::SoundBuffer*>::const_iterator it = sounds_.find(name);

  /* Is the sound file already cached in the sound map? */
  if (it == sounds_.end()) {
    /* Not cached so load the file, cache it and return the sound*/
    sf::SoundBuffer* sound_buffer = new sf::SoundBuffer();

    if (!sound_buffer->loadFromFile("sounds/" + name)) {
      delete sound_buffer;
      throw new SoundNotFoundException("Error: " + name + " sound file was not \
                                        found");
    } else {
      sounds_.insert(std::pair<std::string, sf::SoundBuffer*>(name, sound_buffer));

      sf::Sound sound;
      sound.setBuffer(*sound_buffer);
      return sound;
    }

  } else {
    /* Sound was cached so just return that */
    sf::Sound sound;
    sound.setBuffer(*it->second);
    return sound;
  }
}

sf::Music* SoundCache::GetSong(std::string name) {
  std::map<std::string, sf::Music*>::const_iterator it = music_.find(name);

  if (it == music_.end()) {
    sf::Music* music = new sf::Music();

    if (!music->openFromFile("sounds/" + name)) {
      delete music;
      throw new SoundNotFoundException("Error: " + name + " sound file was not \
                                        found");
    } else {
      music_.insert(std::pair<std::string, sf::Music*>(name, music));
      return music;
    }

  } else {
    return it->second;
  }
}

