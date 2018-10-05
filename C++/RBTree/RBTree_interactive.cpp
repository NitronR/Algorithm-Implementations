#include <iostream>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

enum COLOR { RED, BLACK };

class Node {
public:
  int val;
  COLOR color;
  Node *left, *right, *parent;

  Node(int val) : val(val) {
    parent = left = right = NULL;
    color = RED;
  }

  Node *uncle() {
    if (parent == NULL or parent->parent == NULL)
      return NULL;

    if (parent->isOnLeft())
      return parent->parent->right;
    else
      return parent->parent->left;
  }

  bool isOnLeft() { return this == parent->left; }

  Node *sibling() {
    if (parent == NULL)
      return NULL;

    if (isOnLeft())
      return parent->right;

    return parent->left;
  }

  void moveDown(Node *nParent) {
    if (parent != NULL) {
      if (isOnLeft()) {
        parent->left = nParent;
      } else {
        parent->right = nParent;
      }
    }
    nParent->parent = parent;
    parent = nParent;
  }

  bool hasRedChild() {
    return (left != NULL and left->color == RED) or
           (right != NULL and right->color == RED);
  }
};

class RBTree {
  Node *root;

  void leftRotate(Node *x) {
    cout << "Left rotate:" << x->val << endl;

    Node *nParent = x->right;

    if (x == root)
      root = nParent;

    x->moveDown(nParent);

    x->right = nParent->left;
    if (nParent->left != NULL)
      nParent->left->parent = x;

    nParent->left = x;
  }

  void rightRotate(Node *x) {
    cout << "Right rotate:" << x->val << endl;

    Node *nParent = x->left;

    if (x == root)
      root = nParent;

    x->moveDown(nParent);

    x->left = nParent->right;
    if (nParent->right != NULL)
      nParent->right->parent = x;

    nParent->right = x;
  }

  void swapColors(Node *x1, Node *x2) {
    COLOR temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
  }

  void swapValues(Node *u, Node *v) {
    int temp;
    temp = u->val;
    u->val = v->val;
    v->val = temp;
  }

  void fixRedRed(Node *x) {
    cout << "Fixing Red Red at: " << x->val << endl;
    if (x == root) {
      cout << "It is root, coloring it black" << endl;
      x->color = BLACK;
      return;
    }

    Node *parent = x->parent, *grandparent = parent->parent,
         *uncle = x->uncle();

    if (parent->color != BLACK) {
      if (uncle != NULL && uncle->color == RED) {
        cout << "Uncle red, perform recoloring and recursing for grandparent"
             << endl;
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        fixRedRed(grandparent);
      } else {
        cout << "Uncle black" << endl;
        if (parent->isOnLeft()) {
          cout << "left ";
          if (x->isOnLeft()) {
            cout << "left" << endl;
            swapColors(parent, grandparent);
          } else {
            cout << "right" << endl;
            leftRotate(parent);
            swapColors(x, grandparent);
          }
          rightRotate(grandparent);
        } else {
          cout << "right ";
          if (x->isOnLeft()) {
            cout << "left" << endl;
            rightRotate(parent);
            swapColors(x, grandparent);
          } else {
            cout << "right" << endl;
            swapColors(parent, grandparent);
          }
          leftRotate(grandparent);
        }
      }
    } else {
      cout << "No voilation" << endl;
    }
  }

  Node *successor(Node *x) {
    Node *temp = x;

    while (temp->left != NULL)
      temp = temp->left;

    return temp;
  }

  Node *BSTreplace(Node *x) {
    if (x->left != NULL and x->right != NULL)
      return successor(x->right);

    if (x->left == NULL and x->right == NULL)
      return NULL;

    if (x->left != NULL)
      return x->left;
    else
      return x->right;
  }

  void deleteNode(Node *v) {
    Node *u = BSTreplace(v);

    // True when u and v are both black
    bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
    Node *parent = v->parent;

    if (u == NULL) {
      cout << "u is NULL therefore v is leaf" << endl;
      if (v == root) {
        cout << "v is root, making root null" << endl;
        root = NULL;
      } else {
        if (uvBlack) {
          cout << "u and v both black" << endl;
          cout << "v is leaf, fix double black at v" << endl;
          fixDoubleBlack(v);
        } else {
          cout << "u or v is red" << endl;
          if (v->sibling() != NULL) {
            cout << "sibling is not null, make it red" << endl;
            v->sibling()->color = RED;
          }
        }

        cout << "delete v from the tree" << endl;
        if (v->isOnLeft()) {
          parent->left = NULL;
        } else {
          parent->right = NULL;
        }
      }
      delete v;
      return;
    }

    if (v->left == NULL or v->right == NULL) {
      cout << "v has 1 child" << endl;
      if (v == root) {
        cout << "v is root, assign the value of u to v, and delete u" << endl;
        v->val = u->val;
        v->left = v->right = NULL;
        delete u;
      } else {
        cout << "Detach v from tree and move u up" << endl;
        if (v->isOnLeft()) {
          parent->left = u;
        } else {
          parent->right = u;
        }
        delete v;
        u->parent = parent;
        if (uvBlack) {
          cout << "u and v both black, fix double black at u" << endl;
          fixDoubleBlack(u);
        } else {
          cout << "u or v red, color u black" << endl;
          u->color = BLACK;
        }
      }
      return;
    }

    cout << "v has 2 children, swap values with successor and recurse" << endl;
    swapValues(u, v);
    deleteNode(u);
  }

  void fixDoubleBlack(Node *x) {
    cout << "Fixing double black:" << x->val << endl;
    if (x == root) {
      cout << "Reached root" << endl;
      return;
    }

    Node *sibling = x->sibling(), *parent = x->parent;
    if (sibling == NULL) {
      cout << "No sibiling, double black pushed up" << endl;
      fixDoubleBlack(parent);
    } else {
      cout << "Sibling: " << sibling->val << endl;
      if (sibling->color == RED) {
        cout << "Sibling red" << endl;
        parent->color = RED;
        sibling->color = BLACK;
        if (sibling->isOnLeft()) {
          cout << "left case" << endl;
          rightRotate(parent);
        } else {
          cout << "right case" << endl;
          leftRotate(parent);
        }
        fixDoubleBlack(x);
      } else {
        cout << "Sibling black" << endl;
        if (sibling->hasRedChild()) {
          cout << "at least 1 red children" << endl;
          if (sibling->left != NULL and sibling->left->color == RED) {
            if (sibling->isOnLeft()) {
              cout << "left left" << endl;
              sibling->left->color = sibling->color;
              sibling->color = parent->color;
              rightRotate(parent);
            } else {
              cout << "right left" << endl;
              sibling->left->color = parent->color;
              rightRotate(sibling);
              leftRotate(parent);
            }
          } else {
            if (sibling->isOnLeft()) {
              cout << "left right" << endl;
              sibling->right->color = parent->color;
              leftRotate(sibling);
              rightRotate(parent);
            } else {
              cout << "right right" << endl;
              sibling->right->color = sibling->color;
              sibling->color = parent->color;
              leftRotate(parent);
            }
          }
          parent->color = BLACK;
        } else {
          cout << "2 black children" << endl;
          sibling->color = RED;
          if (parent->color == BLACK)
            fixDoubleBlack(parent);
          else
            parent->color = BLACK;
        }
      }
    }
  }

  void levelOrder(Node *x) {
    if (x == NULL)
      return;

    queue<Node *> q;
    Node *curr;

    q.push(x);

    while (!q.empty()) {
      curr = q.front();
      q.pop();

      cout << curr->val << "(" << ((curr->color == RED) ? 'R' : 'B') << ")"
           << " ";

      if (curr->left != NULL)
        q.push(curr->left);
      if (curr->right != NULL)
        q.push(curr->right);
    }
  }

  void inorder(Node *x) {
    if (x == NULL)
      return;
    inorder(x->left);
    cout << x->val;
    if (x->parent != NULL)
      cout << "(" << x->parent->val << ")";
    cout << " ";
    inorder(x->right);
  }

public:
  RBTree() { root = NULL; }

  Node *getRoot() { return root; }

  Node *search(int n) {
    Node *temp = root;
    while (temp != NULL) {
      if (n < temp->val) {
        if (temp->left == NULL)
          break;
        else
          temp = temp->left;
      } else if (n == temp->val) {
        break;
      } else {
        if (temp->right == NULL)
          break;
        else
          temp = temp->right;
      }
    }

    return temp;
  }

  void insert(int n) {
    cout << "Inserting: " << n << endl;
    Node *newNode = new Node(n);
    if (root == NULL) {
      newNode->color = BLACK;
      root = newNode;
      cout << "Inserted at root" << endl;
    } else {
      Node *temp = search(n);

      if (temp->val == n) {
        cout << "Already exists" << endl;
        return;
      }

      newNode->parent = temp;

      if (n < temp->val)
        temp->left = newNode;
      else
        temp->right = newNode;

      fixRedRed(newNode);
    }
  }

  void deleteByVal(int n) {
    if (root == NULL) {
      cout << "Tree is empty" << endl;
      return;
    }

    Node *v = search(n), *u;

    if (v->val != n) {
      cout << "No node found to delete with value:" << n << endl;
      return;
    }
    cout << "Deleting:" << n << endl;
    deleteNode(v);
  }

  void printInOrder() {
    cout << "Inorder: " << endl;
    if (root == NULL)
      cout << "Tree is empty" << endl;
    else
      inorder(root);
    cout << endl;
  }

  void printLevelOrder() {
    cout << "Level order: " << endl;
    if (root == NULL)
      cout << "Tree is empty" << endl;
    else
      levelOrder(root);
    cout << endl;
  }
};

// returns true if red-red voilaton
bool RedRed(Node *x) {
  if (x == NULL) {
    return false;
  }

  queue<Node *> q;
  Node *curr;

  q.push(x);

  while (!q.empty()) {
    curr = q.front();
    q.pop();
    if (curr->left != NULL) {
      q.push(curr->left);
      if (x->color == RED and x->left->color == RED)
        return true;
    }
    if (curr->right != NULL) {
      q.push(curr->right);
      if (x->color == RED and x->right->color == RED)
        return true;
    }
  }
  return false;
}

// calculates black height of given node
int bHeight(Node *x) {
  int h = 0;
  while (x != NULL) {
    if (x->color == BLACK) {
      h++;
    }
    x = x->parent;
  }

  return h;
}

// returns true if black height is
// not same for all paths from root
// to leaves
bool diffBlack(Node *x) {
  if (x == NULL) {
    return false;
  }

  queue<Node *> q;
  Node *curr;

  q.push(x);

  int blackHeight = -1;
  while (!q.empty()) {
    curr = q.front();
    q.pop();
    if (curr->left != NULL) {
      q.push(curr->left);
    }
    if (curr->right != NULL) {
      q.push(curr->right);
    }

    if (curr->left == NULL and curr->right == NULL) {
      if (blackHeight != -1 and bHeight(curr) != blackHeight) {
        return true;
      } else
        blackHeight = bHeight(curr);
    }
  }

  return false;
}

bool treeValid(Node *root) {
  bool rr, bl;
  cout << "=====Checking for Red Red and Black height voilation=====" << endl;
  if (rr = RedRed(root))
    cout << "!!!!!!!!! Has Red Red !!!!!!!!!" << endl;
  else
    cout << "No Red Red voilaton" << endl;
  if (bl = diffBlack(root))
    cout << "!!!!!!!!! Different black height detected !!!!!!!!!" << endl;
  else
    cout << "Correct Black Height" << endl;
  cout << "=====End Check=====" << endl;
  return !(rr or bl);
}

int getRandom(int min, int max) { return (rand() % max + min); }

void insertRandom(RBTree &tree) {
  int n, max, min;
  cout << "Enter number of values:" << endl;
  cin >> n;
  cout << "Enter maximum:" << endl;
  cin >> max;
  cout << "Enter minimum:" << endl;
  cin >> min;

  for (int i = 0; i < n; i++) {
    cout << endl;
    tree.insert(getRandom(min, max));
    if (!treeValid(tree.getRoot()))
      break;
    cout << endl;
  }
}

void deleteRandom(RBTree &tree) {
  if (tree.getRoot() == NULL) {
    cout << "Tree is empty" << endl;
    return;
  }
  int n, random;
  vector<int> vals;
  queue<Node *> q;
  Node *curr;
  cout << "Enter number of values:" << endl;
  cin >> n;

  q.push(tree.getRoot());
  while (!q.empty()) {
    curr = q.front();
    q.pop();

    vals.push_back(curr->val);

    if (curr->left != NULL)
      q.push(curr->left);
    if (curr->right != NULL)
      q.push(curr->right);
  }

  if (n > vals.size())
    n = vals.size();

  for (int i = 0; i < n; i++) {
    cout << endl;
    random = (vals.size() == 1) ? 0 : getRandom(0, vals.size() - 1);
    tree.deleteByVal(vals[random]);
    vals.erase(vals.begin() + random);
    if (!treeValid(tree.getRoot()))
      break;
    cout << endl;
  }
}

void printOptions() {
  cout << endl << endl;
  cout << "Options:" << endl;
  cout << "1: Insert value" << endl;
  cout << "2: Delete value" << endl;
  cout << "3: Inorder" << endl;
  cout << "4: Level order" << endl;
  cout << "5: Insert random values" << endl;
  cout << "6: Delete random values" << endl;
  cout << "0: Exit" << endl;
  cout << "Enter option:" << endl;
}

int main() {
  RBTree tree;
  int command = 1, value;

  srand(time(NULL));
  while (command != 0) {
    printOptions();
    cin >> command;

    switch (command) {
    case 1:
      cout << "Enter value to insert:";
      cin >> value;
      tree.insert(value);
      break;
    case 2:
      cout << "Enter value to delete:";
      cin >> value;
      tree.deleteByVal(value);
      break;
    case 3:
      tree.printInOrder();
      break;
    case 4:
      tree.printLevelOrder();
      break;
    case 5:
      insertRandom(tree);
      break;
    case 6:
      deleteRandom(tree);
      break;
    case 0:
      break;
    default:
      cout << "Invalid option" << endl;
    }
  }
  cout << "Exit" << endl;
  return 0;
}
