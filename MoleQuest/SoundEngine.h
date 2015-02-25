#ifndef SOUND_ENGINE_
#define SOUND_ENGINE_

#include "SoundCache.h"

class SoundEngine {
 public:
  SoundEngine();

  void PlaySound(std::string filename);
  void PlaySong(std::string filename, bool loop);
  
  void StopAllSounds();
  void StopSong();

  bool IsSoundPlaying();
  bool IsSongPlaying();

 private:
  SoundCache sound_cache_;

  static const int kMaxSoundChannels = 2;
  std::string current_song_name_;
  sf::Sound current_sounds_[kMaxSoundChannels];
};

#endif