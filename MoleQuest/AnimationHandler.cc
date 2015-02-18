#include "stdafx.h"
#include "AnimationHandler.h"

AnimationHandler::AnimationHandler() : elapsed_time_(0), current_animation_(-1) {}

AnimationHandler::AnimationHandler(const sf::IntRect& frame_size) 
  : elapsed_time_(0), current_animation_(-1) {
  frame_size_ = frame_size;
}

void AnimationHandler::AddAnimation(Animation& animation) {
  animations_.push_back(animation);
}

void AnimationHandler::Update(const float last_time) {
  // Check for a valid animation
  if (current_animation_ == -1)
    return;

  float duration = animations_[current_animation_].duration_;

  // Has enough time passed to move on to the next frame?
  if ((elapsed_time_ + last_time) / duration > (elapsed_time_ / duration)) {
    // Calculate current frame number
    int frame = (int) ((elapsed_time_ + last_time) / duration);

    // Frames should wrap from last frame to first frame
    frame %= animations_[current_animation_].GetLength();

    // Set the new sprite for this frame
    // This is subject to change based on how the textures are laid out in the
    // spritesheets
    sf::IntRect rect = frame_size_;
    rect.left = (rect.width * frame);

    rect.top = rect.height * current_animation_;
    texture_bounds_ = rect;
  }

  // Increment time
  elapsed_time_ += last_time;

  if (elapsed_time_ > duration * animations_[current_animation_].GetLength())
    elapsed_time_ = 0;
}

void AnimationHandler::ChangeAnimation(int num) {
  // Check if animation changing to is already running and valid animation num
  if (current_animation_ == num || num > animations_.size() || num < 0)
    return;

  current_animation_ = num;

  // This is subject to change based on how the textures are laid out in the
  // spritesheets
  sf::IntRect rect = frame_size_;
  rect.top = rect.height * num;
  texture_bounds_ = rect;
  elapsed_time_ = 0;
}
