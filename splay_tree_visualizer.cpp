#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node* parent;

    Node(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
};

class SplayTree {
private:
    Node* root;

    // Right rotation (Zig)
    Node* rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right) y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->right = x;
        x->parent = y;
        return y;
    }

    // Left rotation (Zag)
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
        return y;
    }

    // Splay operation: move node to root
    void splay(Node* x) {
        while (x->parent) {
            if (!x->parent->parent) {
                // Zig or Zag
                if (x == x->parent->left) rightRotate(x->parent);
                else leftRotate(x->parent);
            }
            else if (x == x->parent->left && x->parent == x->parent->parent->left) {
                // Zig-Zig
                rightRotate(x->parent->parent);
                rightRotate(x->parent);
            }
            else if (x == x->parent->right && x->parent == x->parent->parent->right) {
                // Zag-Zag
                leftRotate(x->parent->parent);
                leftRotate(x->parent);
            }
            else if (x == x->parent->right && x->parent == x->parent->parent->left) {
                // Zig-Zag
                leftRotate(x->parent);
                rightRotate(x->parent);
            }
            else {
                // Zag-Zig
                rightRotate(x->parent);
                leftRotate(x->parent);
            }
        }
    }

    // BST insertion (without splay)
    Node* insertBST(Node* node, int key) {
        if (!node) return new Node(key);

        if (key < node->key) {
            Node* lchild = insertBST(node->left, key);
            node->left = lchild;
            lchild->parent = node;
        }
        else if (key > node->key) {
            Node* rchild = insertBST(node->right, key);
            node->right = rchild;
            rchild->parent = node;
        }

        return node;
    }

    // Find node with specific key
    Node* find(Node* node, int key) {
        if (!node) return nullptr;
        if (node->key == key) return node;
        if (key < node->key) return find(node->left, key);
        return find(node->right, key);
    }

    // Tree visualization
    void printHelper(Node* node, string prefix, bool isLeft) {
        if (!node) return;

        cout << prefix;
        cout << (isLeft ? "├─L: " : "└─R: ");
        cout << node->key << endl;

        if (node->left || node->right) {
            string newPrefix = prefix + (isLeft ? "│    " : "     ");

            if (node->left) {
                printHelper(node->left, newPrefix, true);
            }

            if (node->right) {
                printHelper(node->right, newPrefix, false);
            }
        }
    }

public:
    SplayTree() : root(nullptr) {}

    // Insert + Splay
    void insert(int key) {
        if (!root) {
            root = new Node(key);
            return;
        }

        root = insertBST(root, key);
        Node* newNode = find(root, key);
        if (newNode) {
            splay(newNode);
        }
    }

    // Print tree
    void printTree() {
        if (!root) {
            cout << "(empty tree)" << endl;
            return;
        }

        cout << "Root: " << root->key << endl;

        if (root->left) {
            printHelper(root->left, "", true);
        }

        if (root->right) {
            printHelper(root->right, "", false);
        }
    }

    // Inorder traversal (for checking order)
    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

    void printInorder() {
        cout << "Inorder: ";
        inorder(root);
        cout << endl;
    }

    Node* getRoot() { return root; }
};

int main() {
    cout << "========================================" << endl;
    cout << "     Splay Tree Visualizer" << endl;
    cout << "========================================" << endl;
    cout << "\nEnter data and visualize the tree structure" << endl;
    cout << "at each insertion step.\n" << endl;

    cout << "Select input method:" << endl;
    cout << "  1. Multiple values in one line (e.g., 10 5 15 3 7)" << endl;
    cout << "  2. One by one (enter 0 to quit)" << endl;
    cout << "\nChoice: ";

    int choice;
    cin >> choice;

    SplayTree tree;

    if (choice == 1) {
        cout << "\nEnter numbers separated by spaces: ";
        cin.ignore();
        string line;
        getline(cin, line);
        stringstream ss(line);

        int num;
        int step = 1;
        while (ss >> num) {
            cout << "\n" << string(50, '=') << endl;
            cout << "Step " << step++ << ": Insert " << num << endl;
            cout << string(50, '=') << endl;
            tree.insert(num);
            tree.printTree();
            cout << endl;
            tree.printInorder();
        }
    }
    else {
        cout << "\nEnter numbers one by one (enter 0 to quit)" << endl;
        int num;
        int step = 1;

        while (true) {
            cout << "\n>> ";
            cin >> num;
            if (num == 0) break;

            cout << "\n" << string(50, '=') << endl;
            cout << "Step " << step++ << ": Insert " << num << endl;
            cout << string(50, '=') << endl;
            tree.insert(num);
            tree.printTree();
            cout << endl;
            tree.printInorder();
        }
    }

    cout << "\n" << string(50, '=') << endl;
    cout << "Final Tree Structure" << endl;
    cout << string(50, '=') << endl;
    tree.printTree();
    cout << endl;
    tree.printInorder();
    cout << endl;

    return 0;
}
