#include "stdafx.h"
#include "QuadTree.h"

// QuadTree definitions

QuadTree::QuadTree(int max_depth, int max_objects, int w, int h) {
  root_ = new QuadTreeNode(max_objects, max_depth, 0, 0, 0, w, h);

  max_depth_ = max_depth;
  max_objects_ = max_objects;
  w_ = w;
  h_ = h;
}

QuadTree::~QuadTree() {
  root_->Clear();
}

void QuadTree::AddObject(GameObject* object) {
  root_->Add(object);
}

void QuadTree::RemoveObject(GameObject* object) {
  root_->Remove(object);
}

void QuadTree::Clear() {
  root_->Clear();
  root_ = new QuadTreeNode(max_objects_, max_depth_, 0, 0, 0, w_, h_);
}

void QuadTree::GetObjectsNear(GameObject* object, std::list<GameObject*>& object_list) {
  root_->GetItems(object, object_list);
}

// QuadTreeNode definitions

QuadTreeNode::QuadTreeNode(int max_objects, int max_depth, int depth, int x, int y, int w, int h) {
  objects_.reserve(max_objects + 1);
  children_.reserve(4);

  bounds_.left = x;
  bounds_.top = y;
  bounds_.width = w;
  bounds_.height = h;

  max_objects_ = max_objects;
  max_depth_ = max_depth;
}

QuadTreeNode::~QuadTreeNode() {}

void QuadTreeNode::GetItems(GameObject* object, std::list<GameObject*>& object_list) {
  // Does thide node contain the object
  if (Contains(this, object)) {
    for (auto obj : objects_)
      object_list.push_back(obj);

    // Check children if they exist
    if (this->HasChildren()) {
      for (auto child : children_)
        child->GetItems(object, object_list);
    }
  }
}

void QuadTreeNode::Add(GameObject* object) {
  // Attempt to insert node into children
  if (!InsertIntoChildren(object)) {
    objects_.push_back(object);

    // Does this node need splitting now?
    if (this->objects_.size() > max_objects_ && depth_ < max_depth_ && !this->HasChildren())
      SplitNode();
  }
}

void QuadTreeNode::Remove(GameObject* object) {

}

bool QuadTreeNode::InsertIntoChildren(GameObject* object) {
  for (auto child : children_) {
    if (Contains(child, object)) {
      child->Add(object);
      return true;
    }
  }

  return false;
}

bool QuadTreeNode::Contains(QuadTreeNode* node, GameObject* object) {
  // Just look at the center of the sprite to instead of fitting entire sprite 
  int x = object->GetSprite().getTextureRect().width / 2;
  int y = object->GetSprite().getTextureRect().height / 2;

  sf::IntRect bounds = node->GetBounds();

  if (x > bounds.left && x < bounds_.left + bounds_.width &&
      y > bounds.top && y < bounds.top + bounds.height)
    return true;

  return false;
}

void QuadTreeNode::SplitNode() {
  int x = bounds_.left;
  int y = bounds_.top;
  int w = bounds_.width / 2;
  int h = bounds_.height / 2;

  children_.push_back(new QuadTreeNode(max_objects_, max_depth_, depth_+1, x, y, w, h));
  children_.push_back(new QuadTreeNode(max_objects_, max_depth_, depth_ + 1, x + w, y, w, h));
  children_.push_back(new QuadTreeNode(max_objects_, max_depth_, depth_ + 1, x, y + h, w, h));
  children_.push_back(new QuadTreeNode(max_objects_, max_depth_, depth_ + 1, x + w, y + h, w, h));

  // Try to push objects in this node down to new children
  for (auto obj : objects_) {
    if (PushDown(obj)) break;
  }
}

bool QuadTreeNode::PushDown(GameObject* object) {
  std::vector<int> to_be_removed;

  for (int i = 0; i < objects_.size(); i++) {
    if (InsertIntoChildren(objects_[i])) {
      // If node was pushed down to child then remove from this node
      std::swap(objects_[i], objects_.back());
      objects_.pop_back();
      return true;
    }
  }

  return false;
}

void QuadTreeNode::Clear() {
  for (auto child : children_)
    child->Clear();

  children_.clear();
  objects_.clear();
}

bool QuadTreeNode::HasChildren() {
  return children_.size() > 0;
}

sf::IntRect QuadTreeNode::GetBounds() const {
  return bounds_;
}