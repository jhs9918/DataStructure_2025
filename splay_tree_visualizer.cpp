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

    // 오른쪽 회전 (Zig)
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

    // 왼쪽 회전 (Zag)
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

    // Splay 연산: 노드를 루트로 이동
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

    // BST 삽입 (splay 없이)
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

    // 특정 key를 가진 노드 찾기
    Node* find(Node* node, int key) {
        if (!node) return nullptr;
        if (node->key == key) return node;
        if (key < node->key) return find(node->left, key);
        return find(node->right, key);
    }

    // 트리 시각화
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

    // 삽입 + Splay
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

    // 트리 출력
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

    // Inorder 순회 (정렬 확인용)
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
    cout << "\n데이터를 입력하면 각 삽입 단계별로" << endl;
    cout << "트리 구조를 시각화하여 보여줍니다.\n" << endl;

    cout << "입력 방법을 선택하세요:" << endl;
    cout << "  1. 한 줄에 여러 개 입력 (예: 10 5 15 3 7)" << endl;
    cout << "  2. 하나씩 입력 (0 입력 시 종료)" << endl;
    cout << "\n선택: ";

    int choice;
    cin >> choice;

    SplayTree tree;

    if (choice == 1) {
        cout << "\n숫자들을 공백으로 구분하여 입력: ";
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
        cout << "\n숫자를 하나씩 입력하세요 (0 입력 시 종료)" << endl;
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
    cout << "최종 트리 구조" << endl;
    cout << string(50, '=') << endl;
    tree.printTree();
    cout << endl;
    tree.printInorder();
    cout << endl;

    return 0;
}
