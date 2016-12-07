#ifndef B_TREE_H
#define B_TREE_H

#include "b-node.h"
#include <utility>
#include <functional>
using namespace std;

template <typename Key>
class BTree {
public:
  typedef BNode<Key> node_type;
  typedef typename node_type::key_type key_type;

private:
  int degree;
  node_type* root;

public:
  BTree (int _degree) : degree(_degree), root(NULL) {}

  ~BTree () {
    delete root;
  }

  bool empty() const { return root == NULL; }

  const node_type* get_root() const { return root; }

  void print(ostream& os) const
  {  if (root != NULL) root->traverse(os); }

  key_type* search(const key_type& key) const {
    return empty() ? NULL : root->search(key);
  }

  void insert(const key_type& key) {
    if (empty())
    {
      root = new node_type(degree, true);
      root->values[0] = key;
      ++root->count;
      return;
    }

    if (root->full())
    {
      node_type* new_root = new node_type (degree, false);
      new_root->children[0] = root;

      new_root->split_child(0);
      new_root->non_full_insert(key);
      root = new_root;
    }
    else
      root->non_full_insert(key);
  }

  void remove(const key_type& key) {
    if (empty())
      return;

    root->remove(key);

    if (root->count == 0) {
      node_type* old_root = root;

      if (root->leaf())
        root = NULL;
      else
        root = root->children[0];

      delete old_root;
    }
  }
};

#endif
