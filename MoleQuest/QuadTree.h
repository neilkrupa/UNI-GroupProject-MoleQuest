#ifndef QUAD_TREE_H_
#define QUAD_TREE_H_

#include "GameObject.h"

class QuadTreeNode {
 public:
  QuadTreeNode(int x, int y, int w, int h);
  ~QuadTreeNode();

  void Add(GameObject*);
  void Remove(GameObject*);
  void Clear();

  sf::IntRect GetBounds() const;

  QuadTreeNode* GetChild(int);
  bool HasChildren();

 private:
  std::vector<GameObject*> objects_;
  std::vector<QuadTreeNode*> children_;

  sf::IntRect bounds_;
};

class QuadTree {
 public:
  QuadTree(int max_depth, int max_objects, int w, int h);
  ~QuadTree();

  // Adds object to the quad tree and returns a pointer to the node it was inserted at
  QuadTreeNode* AddObject(GameObject*);

  // Removes object from the given quad tree
  void RemoveObject(QuadTreeNode*, GameObject*);

  // Clears all objects in the entire quad tree
  void Clear();

  // Returns all the objects in the give node
  std::vector<GameObject*> GetObjectsNear(QuadTreeNode*, GameObject*);

 private:
  int max_depth_;
  int max_objects_;
  int depth_;

  QuadTreeNode* root_;

  // Recursive insert for finding node object belongs to
  QuadTreeNode* Insert(QuadTreeNode*, GameObject*);
  
  // Returns true if object is contained within given node
  bool Contains(QuadTreeNode*, GameObject*);
};

#endif