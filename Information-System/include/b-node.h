#ifndef B_NODE_H
#define B_NODE_H

#include <iostream>
#include <utility>
#include <functional>
using namespace std;

template <typename Key>
class BTree;

template <typename Key>
class BNode {
public:
  typedef Key key_type;
  typedef BNode<Key> self_type;

private:
  int degree;
  // The array of values.
  key_type* values;
  // The count of the number of values in the node.
  int count;
  // The array of child pointers
  BNode** children;
  // A boolean indicating whether the node is a leaf or not.
  bool _leaf;

public:
  BNode(int _degree, bool _leaf) : degree(_degree), _leaf(_leaf) {
    values = new key_type [2 * degree - 1];
    children = new self_type* [2 * degree];

    for(int i = 0; i < 2 * degree - 1 ; ++i)
      children[i] = NULL;

    count = 0;
  }

  ~BNode() {
    delete [] values;
    for(int i = 0; i < 2 * degree - 1 ; ++i)
      delete children[i];
    delete [] children;
  }

  key_type* get_values() const { return values; }
  self_type** get_childern() const { return children; }
  int size() const { return count; }

  // is this node full
  bool full() const {
    return count == 2 * degree - 1;
  }

  bool leaf() const {
    return _leaf;
  }

  key_type* search(const key_type& k) {
    // find first key greater than or equal to key
    int i = find_key_index(k);

    // if key is found return this node
    if (values[i] == k)
      return &values[i];

    // if this node is leaf return NULL
    if (leaf())
      return NULL;

    // search deeper
    return children[i]->search(k);
  }

  void traverse(ostream& os) const
  {
    int i;
    for (i = 0; i < count; i++) {
      // If this is not leaf, then before printing key[i],
      // traverse the subtree rooted with child C[i].
      if (leaf() == false)
        children[i]->traverse(os);

      os << values[i] << endl;
    }

    // Print the subtree rooted with last child
    if (leaf() == false)
      children[i]->traverse(os);
  }

  void print(ostream& os)
  {
    for (int i = 0; i < count; i++)
      os << " " << values[i];
  }

  void non_full_insert(const key_type& k) {
    int last_key = count - 1; // int index = last_key();

    if (leaf()) {
      while (last_key >= 0 && values[last_key] > k) {
        values[last_key + 1] = values[last_key];
        --last_key;
      }

      values[last_key + 1] = k;
      ++count;
      return;
    }

    while (last_key >= 0 && values[last_key] > k)
      --last_key;

    if (children[last_key + 1]->full()) {
      split_child(last_key + 1);

      if (values[last_key + 1] < k)
        ++last_key;
    }

    children[last_key + 1]->non_full_insert(k);
  }

  // Method assumes that current node is a nonfull internal node
  // and takes an index such that children[child_index] is a full child.
  void split_child(int child_index) {
    self_type* y = children[child_index]; // node to be split
    self_type* z = new self_type(y->degree, y->leaf());

    z->count = degree - 1; // numbers of keys in z

    // copy last half of keys from y
    for (int j = 0; j < z->count; ++j)
      z->values[j] = y->values[j + degree];

    // if y is a leaf, copy half of it's nodes
    if (y->leaf() == false)
      for (int j = 0; j < degree; ++j)
        z->children[j] = y->children[j + degree];

    // cut last keys
    y->count = degree - 1;

    // shift all nodes to the right
    for (int j = count; j >= child_index + 1; --j)
      children[j + 1] = children[j];

    children[child_index + 1] = z;

    // shift right
    for (int j = count - 1; j >= child_index; --j)
      values[j+1] = values[j];

    // Copy the middle key of y to this node
    values[child_index] = y->values[degree - 1];

    ++count;
  }

  int find_key_index(const key_type& k) const {
    int i = 0;
    while (i < count && values[i] < k)
      ++i;

    return i;
  }

  key_type max() const {
    const self_type* current = this;
    while (!current->leaf())
      current = current->children[current->count];
      // current = current->get_last_node();

    return current->values[current->count - 1];
    // return current->get_last_key();
  }

  key_type min() const {
    const self_type* current = this;

    while (!current->leaf())
      current = current->children[0];

    return current->values[0];
  }

  void remove(const key_type& k) {
    int key_index = find_key_index(k);

    // If the key k is in the node
    if (key_index < count && values[key_index] == k) {
      if (leaf()) // and this node is a leaf, delete the key from it.
        remove_from_leaf(key_index);
      else
        remove_from_internal(key_index);

      return;
    }

    if (leaf())
      return;

    bool is_in_last_node = (key_index == count)? true : false;

    if (children[key_index]->count < degree) {
      extend(key_index);
    }

    if (is_in_last_node && key_index > count)
      children[key_index - 1]->remove(k);
    else
      children[key_index]->remove(k);
  }

protected:
  key_type get_predecessor(const int& key_index) {
    return children[key_index]->max();
  }

  key_type get_successor(const int& key_index) {
    return children[key_index + 1]->min();
  }

  // removes key with given index from leaf node
  void remove_from_leaf(const int& key_index) {
    for (int i = key_index + 1; i < count; ++i)
      values[i - 1] = values[i];

    --count;
  }

  void remove_from_internal(const int& key_index) {
    key_type value = values[key_index];

    if (children[key_index]->count >= degree) {
      key_type predecessor = get_predecessor(key_index);
      values[key_index] = predecessor;

      children[key_index]->remove(predecessor);
    } else if (children[key_index + 1]->count >= degree) {
      key_type successor = get_successor(key_index);
      values[key_index] = successor;

      children[key_index + 1]->remove(successor);
    } else {
      merge(key_index);
      children[key_index]->remove(value);
    }
  }

  void merge(int node_index) {
    // merge last node with previous one
    if (node_index == count && node_index > 0) --node_index;

    self_type* child = children[node_index];
    self_type* sibling = children[node_index + 1];

    child->values[degree - 1] = values[node_index];

    for (int i = 0; i < sibling->count; ++i)
      child->values[i + degree] = sibling->values[i];

    if (!child->leaf()) {
        for (int i = 0; i <= sibling->count; ++i)
          child->children[i + degree] = sibling->children[i];
    }

    for (int i = node_index + 1; i < count; ++i)
      values[i - 1] = values[i];

    for (int i = node_index + 2; i <= count; ++i)
      children[i-1] = children[i];

    child->count += sibling->count + 1;
    --count;

    delete sibling;
  }

  void extend(const int& node_index)
  {
    if (node_index != 0 && children[node_index - 1]->count >= degree)
      get_from_previous(node_index);
    else if (node_index != count && children[node_index + 1]->count >= degree)
      get_from_next(node_index);
    else
      merge(node_index);
  }

  void get_from_previous(const int& node_index) {
    self_type* child = children[node_index];
    self_type* prev_sibling = children[node_index - 1];

    for (int i = child->count - 1; i >= 0; --i)
      child->values[i + 1] = child->values[i];

    if (!child->leaf())
      for(int i = child->count; i >= 0; --i)
        child->children[i + 1] = child->children[i];

    child->values[0] = values[node_index - 1];

    if (!child->leaf())
      child->children[0] = prev_sibling->children[prev_sibling->count];

    values[node_index - 1] = prev_sibling->values[prev_sibling->count - 1];

    ++child->count;
    --prev_sibling->count;
  }

  void get_from_next(const int& node_index) {
    self_type* child = children[node_index];
    self_type* next_sibling = children[node_index + 1];

    child->values[child->count] = values[node_index];

    if (!child->leaf())
      child->children[child->count + 1] = next_sibling->children[0];

    values[node_index] = next_sibling->values[0];

    for (int i = 1; i < next_sibling->count; ++i)
      next_sibling->values[i - 1] = next_sibling->values[i];

    if (!next_sibling->leaf())
      for(int i = 1; i <= next_sibling->count; ++i)
        next_sibling->children[i - 1] = next_sibling->children[i];

    ++child->count;
    --next_sibling->count;
  }

  friend class BTree<Key>;
};

#endif
