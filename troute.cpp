//cloude 와 미리 트리 구조를 입력받고, inoder_list를 구현하는 코드를 만들어놨습니다.


#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

unordered_map<char, pair<char, char>> children;
unordered_map<char, char> parents;
unordered_map<char, int> depth;
vector<char> inorder_list;

void calcDepth(char node, int d) {
    depth[node] = d;
    if (children.count(node)) {
        char l = children[node].first, r = children[node].second;
        if (l != '-') calcDepth(l, d + 1);
        if (r != '-') calcDepth(r, d + 1);
    }
}

void inorder(char node) {
    if (node == '-') return;
    if (children.count(node)) inorder(children[node].first);
    inorder_list.push_back(node);
    if (children.count(node)) inorder(children[node].second);
}

char findLCA(char u, char v) {
    while (depth[u] > depth[v]) u = parents[u];
    while (depth[v] > depth[u]) v = parents[v];
    while (u != v) u = parents[u], v = parents[v];
    return u;
}

int main() {
    int n;
    cin >> n;
    set<char> all_nodes;
    for (int i = 0; i < n; i++) {
        char p, l, r;
        cin >> p >> l >> r;
        children[p] = {l, r};
        all_nodes.insert(p);
        if (l != '-') parents[l] = p, all_nodes.insert(l);
        if (r != '-') parents[r] = p, all_nodes.insert(r);
    }

    char root;
    for (char node : all_nodes)
        if (!parents.count(node)) {
            root = node;
            break;
        }

    calcDepth(root, 0);
    inorder(root);

    char x, y;
    cin >> x >> y;

    int pos_x = 0, pos_y = 0;
    for (int i = 0; i < inorder_list.size(); i++)
        if (inorder_list[i] == x) pos_x = i;
        else if (inorder_list[i] == y) pos_y = i;

    char start = pos_x < pos_y ? x : y;
    char target = pos_x < pos_y ? y : x;
    char lca = findLCA(start, target);

    cout << depth[start] - depth[lca] << " " << depth[target] - depth[lca] << "\n";
}