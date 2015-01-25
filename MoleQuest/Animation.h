#ifndef ANIMATION_H_
#define ANIMATION_H_

class Animation {
 public:
  Animation(int start, int end, float duration);
   
  int start_frame_;
  int end_frame_;
  float duration_;

  inline int GetLength() { return end_frame_ - start_frame_ + 1; }
};

#endif