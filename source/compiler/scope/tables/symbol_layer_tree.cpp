#include "symbol_layer_tree.hpp"
#include "scope/layers/class_scope_layer.hpp"

SymbolLayerTree::SymbolLayerTree(ScopeLayer* root) : root(root) {}

SymbolLayerTree::~SymbolLayerTree() {
  delete root;
}

void SymbolLayerTree::AddLayer(ScopeLayer* parent, const std::string& name) {
  parent->AddChild(new ScopeLayer(parent, name));
}

/*
void SymbolLayerTree::AddLayer(ScopeLayer* parent, ScopeLayer* class_layer) {
  //change to class layer;
  parent->AddChild(new ScopeLayer(parent, class_layer, "class"));
}
*/

void SymbolLayerTree::AddClassLayer(ScopeLayer* parent, SharedPtr<ClassType> type) {
  parent->AddChild(new ClassScopeLayer(parent, type));
}

SymbolLayerTree::Iterator SymbolLayerTree::begin() {
  return SymbolLayerTree::Iterator(root);
}

SymbolLayerTree::Iterator SymbolLayerTree::end() {
  return SymbolLayerTree::Iterator(root, root, root->GetChildNum());
}

SymbolLayerTree::Iterator::Iterator(ScopeLayer* root) : root(root), current_parent(root), curr_idx(0) {
}

SymbolLayerTree::Iterator::Iterator(ScopeLayer* root, ScopeLayer* parent, int idx) :
  root(root), current_parent(parent), curr_idx(idx) {}

SymbolLayerTree::Iterator::Iterator(ScopeLayer* root, ScopeLayer* parent) : root(root), current_parent(root), curr_idx(0) {}


ScopeLayer* SymbolLayerTree::Iterator::operator*() const {
  return current_parent->GetChild(curr_idx);
}

ScopeLayer* SymbolLayerTree::Iterator::operator->() const {
  return current_parent->GetChild(curr_idx);
}

void SymbolLayerTree::Iterator::GoDown() {
  current_parent = current_parent->GetChild(curr_idx);
  child_indexes.push(curr_idx);
  curr_idx = 0;
}

void SymbolLayerTree::Iterator::GoUp() {
  current_parent = current_parent->GetParent();
  curr_idx = child_indexes.top();
  child_indexes.pop();
}

SymbolLayerTree::Iterator& SymbolLayerTree::Iterator::operator++() {
  if (curr_idx == current_parent->GetChildNum()) {
    curr_idx = child_indexes.top();
    child_indexes.pop();
    current_parent = current_parent->GetParent();
  } else {
    curr_idx++;
  }

  return *this;
}