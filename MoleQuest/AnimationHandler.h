#ifndef ANIMATION_HANDLER_H_
#define ANIMATION_HANDLER_H_

#include "Animation.h"

class AnimationHandler {
 public:
  AnimationHandler();
  AnimationHandler(const sf::IntRect& frame_size);

  sf::IntRect texture_bounds_;
  sf::IntRect frame_size_;

  // Add a new animation to the vector 
  void AddAnimation(Animation& animation);

  // Update animation - checking if it needs to go to the next frame
  void Update(const int last_time);

  // Change the animation
  void ChangeAnimation(int num);

  inline int GetAnimationNumber() const { return current_animation_; } 

private:
  std::vector<Animation> animations_;
  float elapsed_time_;
  int current_animation_;
};

#endif