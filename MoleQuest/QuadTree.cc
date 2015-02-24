#include "stdafx.h"
#include "QuadTree.h"

// QuadTree definitions

QuadTree::QuadTree(int max_depth, int max_objects, int w, int h) {
  root_ = new QuadTreeNode(0, 0, w, h);
}

QuadTree::~QuadTree() {}

QuadTreeNode* QuadTree::AddObject(GameObject* object) {
  return Insert(root_, object);
}

QuadTreeNode* QuadTree::Insert(QuadTreeNode* node, GameObject* object) {
  // If node doesn't have children then insert at this level
  if (!node->HasChildren()) {
    node->Add(object);
    return node;
  }

  // Else find the child the object belongs to
  else {
    if (Contains(node->GetChild(0), object)) Insert(node->GetChild(0), object);
    else if (Contains(node->GetChild(1), object)) Insert(node->GetChild(1), object);
    else if (Contains(node->GetChild(2), object)) Insert(node->GetChild(2), object);
    else if (Contains(node->GetChild(3), object)) Insert(node->GetChild(3), object);
    else node->Add(object);
  }
}

bool QuadTree::Contains(QuadTreeNode* node, GameObject* object) {
  return false;
}

void QuadTree::RemoveObject(QuadTreeNode* node, GameObject* object) {
  node->Remove(object);
}

void QuadTree::Clear() {
  root_->Clear();
}



// QuadTreeNode definitions

QuadTreeNode::QuadTreeNode(int x, int y, int w, int h) {
  objects_.reserve(50);
  children_.reserve(4);

  bounds_.left = x;
  bounds_.top = y;
  bounds_.width = w;
  bounds_.height = h;
}

QuadTreeNode::~QuadTreeNode() {}

void QuadTreeNode::Add(GameObject* object) {
  objects_.push_back(object);
}

void QuadTreeNode::Remove(GameObject* object_to_remove) {
  // Go through all objects in this node to find the right object
  for (int i = 0; i < objects_.size(); i++) {
    
    if (objects_[i] == object_to_remove) {

      // If object isnt at the end then swap back and object
      if (i != objects_.size() - 1) 
        std::swap(objects_[i], objects_.back());

      delete objects_.back();
      objects_.pop_back();
    }
  }
}

void QuadTreeNode::Clear() {
  for (auto child : children_)
    child->Clear();

  for (auto obj : objects_)
    delete obj;

  children_.clear();
  objects_.clear();
}

bool QuadTreeNode::HasChildren() {
  return children_.size() > 0;
}

QuadTreeNode* QuadTreeNode::GetChild(int n) {
  return children_[n];
}