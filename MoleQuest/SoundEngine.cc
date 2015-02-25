#include "stdafx.h"
#include "SoundEngine.h"
#include "SoundCache.h"

SoundEngine::SoundEngine() : current_song_name_("") {}

void SoundEngine::PlaySound(std::string filename) {
  int channel = -1;

  // Find an available channel to play sound on
  for (int i = 0; i < kMaxSoundChannels; i++) {
    if (current_sounds_[i].getStatus() != sf::Sound::Playing) {
      channel = i;
      break;
    }
  }

  if (channel != -1) {
    current_sounds_[channel] = sound_cache_.GetSound(filename);
    current_sounds_[channel].play();
  }
}

void SoundEngine::PlaySong(std::string filename, bool loop) {
  sf::Music* current_song;

  current_song = sound_cache_.GetSong(filename);

  /* Stop any song that is currently playing */
  if (current_song_name_ != "") {
    sf::Music* prior_song = sound_cache_.GetSong(current_song_name_);
      
    if (prior_song->getStatus() != sf::Sound::Stopped)
      prior_song->stop();
  }

  current_song_name_ = filename;
  current_song->setLoop(loop);
  current_song->play();
}

void SoundEngine::StopAllSounds() {
  for (int i = 0; i < kMaxSoundChannels; i++)
    current_sounds_[i].stop();

  if (current_song_name_ != "") {
    sf::Music* current_song = sound_cache_.GetSong(current_song_name_);

    if (current_song->getStatus() != sf::Sound::Playing)
      current_song->stop();
  }
}

void SoundEngine::StopSong() {
  sound_cache_.GetSong(current_song_name_)->stop();
}

bool SoundEngine::IsSoundPlaying() {
  for (int i = 0; i < kMaxSoundChannels; i++)
    if (current_sounds_[i].getStatus() == sf::Sound::Playing)
      return true;
  
  return false;
}

bool SoundEngine::IsSongPlaying() {
  if (current_song_name_ != "")
    return sound_cache_.GetSong(current_song_name_)->getStatus() == sf::Sound::Playing;

  return false;
}


