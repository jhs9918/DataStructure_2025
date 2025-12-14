#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 트리 노드 구조체
struct TreeNode {
    vector<TreeNode*> children;  // 자식 노드들

    TreeNode() {}

    ~TreeNode() {
        for (TreeNode* child : children) {
            delete child;
        }
    }
};

// BLOCK 문자열에서 '{', '}' 추출
string extractBlocks(istream& input) {
    string blocks = "";
    char c;
    while (input.get(c)) {
        if (c == '{' || c == '}') {
            blocks += c;
        }
    }
    return blocks;
}

// BLOCK 문자열로부터 트리 구축
TreeNode* buildTree(const string& blocks, int& pos) {
    TreeNode* node = new TreeNode();

    while (pos < blocks.length()) {
        if (blocks[pos] == '{') {
            pos++;  // '{' 건너뛰기
            TreeNode* child = buildTree(blocks, pos);
            node->children.push_back(child);
        } else if (blocks[pos] == '}') {
            pos++;  // '}' 건너뛰기
            return node;
        }
    }

    return node;
}

// 트리 순회하며 모든 노드의 depth 합 계산
int calculateComplexity(TreeNode* node, int depth) {
    if (!node) return 0;

    int sum = depth;  // 현재 노드의 depth

    // 모든 자식 노드에 대해 재귀적으로 계산
    for (TreeNode* child : node->children) {
        sum += calculateComplexity(child, depth + 1);
    }

    return sum;
}

int main() {
    // 1. stdin에서 BLOCK 문자열 추출
    string blocks = extractBlocks(cin);

    // 2. 트리 구축
    int pos = 0;
    TreeNode* root = buildTree(blocks, pos);

    // 3. 복잡도 계산 (root의 depth는 0)
    int complexity = calculateComplexity(root, 0);

    cout << complexity;

    // 5. 메모리 해제
    delete root;

    return 0;
}
