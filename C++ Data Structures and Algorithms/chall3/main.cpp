#include <iostream>
#include "BSTree.h"
using namespace std;

#include <iostream>
#include <limits>
#include "BSTree.h"

using namespace std;

void printOrders(BSTree *tree) {
  cout << "Preorder = ";
  tree->preOrder( );
  cout << endl;
  cout << "Inorder = ";
  tree->inOrder( );
  cout << endl;
  cout << "Postorder = ";
  tree->postOrder( );
  cout << endl;
}

int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: ";
  cout << endl;
  cout
    << "1. Insert" << endl
    << "2. Remove" << endl
    << "3. Print" << endl
    << "4. Search" << endl
    << "5. Smallest" << endl
    << "6. Largest" << endl
    << "7. Height" << endl
    << "8. Quit" << endl;
  cin >> choice;

  // fix buffer just in case non-numeric choice entered
  // also gets rid of newline character
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return choice;
}


void run_tests() {
        ///TESTING NODE STRUCT
//    string str = "asdf";
//    int val = 9;
//    Node nde(str, val);
//    Node nde1("aebg", 10);
//    nde.lftChld = &nde1;
//    cout << nde.lftChld->dupNum << endl;

        ///TESTING BSTree insert
//    BSTree tree;
//    tree.insert("asdf");
//    tree.insert("bbbbb");
//    tree.insert("ax");
//    tree.preOrder();
        ///TESTING BSTree search
//        BSTree tree;
//        tree.insert("asdf");
//        tree.insert("bbbbb");
//        cout << tree.search("bbbbb") << endl; // expecting 1

        ///TESTING remove
//        BSTree tree;
//        tree.insert("asdf");
//        tree.insert("bbbbb");
//        tree.remove("bbbbb");
//        tree.preOrder();

        ///TESTING height
//        BSTree tree;
//        tree.insert("a");
//        tree.insert("b");
//        tree.insert("c");
//        tree.insert("b");
//        cout << tree.height("c") << endl;
//        tree.preOrder();
}


int main( ) {
    // Pass all your tests before running the executable main
//    run_tests();  // TODO: Remove before submitting
//    return 0;

    BSTree tree;

    int choice = menu();

    string entry;

    while (choice != 8) {

        if (choice == 1) {
          cout << "Enter string to insert: " << endl;
          getline(cin, entry);
          tree.insert(entry);
        } else if (choice == 2) {
          cout << "Enter string to remove: " << endl;
          getline(cin, entry);
          tree.remove(entry);
        } else if (choice == 3) {
            printOrders(&tree);
        } else if (choice == 4) {
          cout << "Enter string to search for: " << endl;
          getline(cin, entry);
          if(tree.search(entry))
            cout << "Found" << endl;
          else
            cout << "Not Found" << endl;
        } else if (choice == 5) {
          cout << "Smallest: " << tree.smallest() << endl;
        } else if (choice == 6) {
          cout << "Largest: " << tree.largest() << endl;
        } else if (choice == 7) {
          cout << "Enter string: " << endl;
          getline(cin, entry);
          cout << "Height of subtree rooted at " << entry << ": " << tree.height(entry) << endl;
        }
        //fix buffer just in case non-numeric choice entered
        choice = menu();
    }
    return 0;
}
