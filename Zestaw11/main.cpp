#include "BST.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
  srand(1);

  BinarySearchTree<int> tree;

  for (size_t i = 0; i < 20; i++) {
    tree.insert(rand() % 100);
  }

  tree.display();
  std::cout << "\nMax value: " << *(tree.find_max()) << '\n';
  std::cout << "Min value: " << *(tree.find_min()) << '\n';

  return 0;
}
