#ifndef QUAD_TREE_H_
#define QUAD_TREE_H_

#include "GameObject.h"

class QuadTreeNode {
 public:
  QuadTreeNode(int max_objects, int max_depth, int depth, int x, int y, int w, int h);
  ~QuadTreeNode();

  void Add(GameObject*);
  void Clear();

  sf::IntRect GetBounds() const;

  void GetItems(GameObject*, std::list<GameObject*>&);

  bool HasChildren();

 private:
  std::vector<GameObject*> objects_;
  std::vector<QuadTreeNode*> children_;

  sf::IntRect bounds_;

  int max_objects_;
  int max_depth_;
  int depth_;

  // Attempts to insert GameObject* into the children nodes
  // Returns true is an insert was successful
  bool InsertIntoChildren(GameObject*);

  // Returns true if object fits within the bounds of quad node
  bool Contains(QuadTreeNode*, GameObject*);

  // Splits the node - Generates 4 children and attempts to PushDown() objects
  void SplitNode();

  // Attempts to move objects in this node to its children
  void PushDown(GameObject*);
};

class QuadTree {
 public:
  QuadTree(int max_depth, int max_objects, int w, int h);
  ~QuadTree();

  // Adds object to the quad tree
  void AddObject(GameObject*);

  // Clears all objects in the entire quad tree
  void Clear();

  // Adds objects near given object to the list passed in by reference
  void GetObjectsNear(GameObject*, std::list<GameObject*>& object_list);

 private:
  int max_depth_;
  int max_objects_;
  int depth_;

  QuadTreeNode* root_;
};

#endif