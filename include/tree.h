// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <cstdint>

struct PMNode {
  char value;
  std::vector<PMNode*> children;

  explicit PMNode(char v) : value(v) {}

  ~PMNode() {
    for (auto child : children) {
      delete child;
    }
  }
};

class PMTree {
 private:
  PMNode* root;

  void buildTree(PMNode* node, std::vector<char>& remaining);

 public:
  explicit PMTree(std::vector<char> elements);
  ~PMTree();

  PMNode* getRoot() const { return root; }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);

std::vector<char> getPerm1(PMTree& tree, int num);

std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
