#ifndef DATABASE_H
#define DATABASE_H

#include "b-tree.h"
#include <unordered_set>

using namespace std;

template <typename K, typename D>
class IndexPair : public pair<K, D> {
public:
	IndexPair(const K& key = K(), const D& value = D())
		: pair<K,D>(key, value) {}

	K& key()   { return pair<K,D>::first; }
	D& data() { return pair<K,D>::second; }

	const K& key()   const { return pair<K,D>::first; }
	const D& data() const { return pair<K,D>::second; }

	bool operator==(const IndexPair& other_p) const {
		return key() == other_p.key();
	}

	bool operator!=(const IndexPair& other_p) const {
		return !(*this == other_p);
	}
};

template <typename K, typename D>
ostream& operator<<(ostream& os, const IndexPair<K, D>& p) {
	return os << p.data();
}

template <typename Row, typename Index>
class Database {
public:
  typedef typename Index::index_type index_type;
  typedef IndexPair<index_type, Row*> index_value;

  typedef BTree<index_value> tree_type;
  typedef typename tree_type::node_type node_type;

  Database() : index(4) {}

  ~Database() {
    //cout << "~~~~~~ \\/ DATABASE DELETE \\/ ~~~~~~\n";
    for(auto it = table.begin(); it != table.end(); ++it)
       delete *it;
    //cout << "~~~~~~ /\\ DATABASE DELETE /\\ ~~~~~~\n";
  }

  const Row* search(const index_type& query) const {
    index_value* result = index.search(query);
    if(result == NULL) return NULL;
    return result->data();
  }

  const Row* insert(const Row& row) {
    if(search(get_index(row)) != NULL)
      return NULL;

    Row* new_row = new Row(row);
    table.insert(new_row);

    index.insert(index_value(get_index(*new_row) , new_row));

    return new_row;
  }

  const Row* update(const Row& row) {
    index_value* old_index = index.search(get_index(row));
    if(old_index == NULL)
      return NULL;

    *old_index->data() = row;
    return old_index->data();
  }

  template <typename F>
  const Row* update(const index_type& query, F f) {
    index_value* old_index = index.search(query);
    if(old_index == NULL)
      return NULL;

    Row new_row = f(*old_index->data());

    if(get_index(new_row) != old_index->key())
      return NULL;

    *old_index->data() = new_row;
    return old_index->data();
  }

  void remove(const index_type& query) {
    index_value* index_to_remove = index.search(query);
    if(index_to_remove != NULL) {
      table.erase(index_to_remove->data());
      delete index_to_remove->data();
      index.remove(query);
    }
  }

  void dump(ostream& os) const {
  	index.print(os);
  }

private:
  unordered_set<Row*> table;
  tree_type index;
  Index get_index;
};


#endif
