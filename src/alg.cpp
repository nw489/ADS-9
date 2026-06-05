// Copyright 2022 NNTU-CS
#include <cstdint>
#include <vector>

#include "../include/tree.h"

void PMTree::buildTree(PMNode* node, std::vector<char>& remaining) {
  if (remaining.empty()) {
    return;
  }
  for (size_t i = 0; i < remaining.size(); ++i) {
    PMNode* child = new PMNode(remaining[i]);
    node->children.push_back(child);
    std::vector<char> nextRemaining;
    for (size_t j = 0; j < remaining.size(); ++j) {
      if (i != j) {
        nextRemaining.push_back(remaining[j]);
      }
    }
    buildTree(child, nextRemaining);
  }
}

PMTree::PMTree(std::vector<char> elements) {
  root = new PMNode('\0');
  buildTree(root, elements);
}

PMTree::~PMTree() {
  delete root;
}

void collectPerms(PMNode* node, std::vector<char>& current,
                  std::vector<std::vector<char>>& result) {
  if (node->children.empty() && node->value != '\0') {
    result.push_back(current);
    return;
  }
  for (auto child : node->children) {
    current.push_back(child->value);
    collectPerms(child, current, result);
    current.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> current;
  collectPerms(tree.getRoot(), current, result);
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  std::vector<std::vector<char>> allPerms = getAllPerms(tree);
  if (num < 1 || num > static_cast<int>(allPerms.size())) {
    return std::vector<char>();
  }
  return allPerms[num - 1];
}

static int64_t fact(int n) {
  if (n <= 1) return 1;
  int64_t result = 1;
  for (int i = 2; i <= n; ++i) {
    result *= i;
  }
  return result;
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<std::vector<char>> allPerms = getAllPerms(tree);
  if (num < 1 || num > static_cast<int>(allPerms.size())) {
    return std::vector<char>();
  }
  std::vector<char> result;
  PMNode* current = tree.getRoot();
  int remaining = num - 1;
  while (!current->children.empty()) {
    int childrenCount = static_cast<int>(current->children.size());
    int subtreeSize = fact(childrenCount - 1);
    int childIndex = remaining / subtreeSize;
    if (childIndex >= childrenCount) {
      return std::vector<char>();
    }
    current = current->children[childIndex];
    result.push_back(current->value);
    remaining = remaining % subtreeSize;
  }
  return result;
}
