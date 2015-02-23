#ifndef ANIMATION_HANDLER_H_
#define ANIMATION_HANDLER_H_

#include "Animation.h"

class AnimationHandler {
 public:
  AnimationHandler(const std::vector<sf::IntRect>);

  sf::IntRect texture_bounds_;

  // Add a new animation to the vector 
  void AddAnimation(Animation& animation);

  // Update animation - checking if it needs to go to the next frame
  void Update(const int last_time);

  // Change the animation
  void ChangeAnimation(int num);

  inline int GetAnimationNumber() const { return current_animation_; } 

private:
  std::vector<sf::IntRect> texture_sizes_;
  std::vector<Animation> animations_;
  float elapsed_time_;
  int current_animation_;
};

#endif