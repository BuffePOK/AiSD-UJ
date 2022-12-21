#include "RandomBinaryTree.h"
#include <iostream>
#include <ctime>

using namespace std;

int main(int argc, char const *argv[]) {
  RandomBinaryTree<int> tree;
  srand(time(NULL));
  int count = rand() % 20;

  for (int  i = 0; i < count; i++) {
    tree.insert(i);
  }

  tree.display();
  cout << '\n' << count << '\t' << tree.count_leafs() << '\t' << tree.count_leafs_iter() << '\n';

  return 0;
}
