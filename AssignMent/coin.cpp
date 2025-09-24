#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

struct Node {
    double min_val, max_val;
};

Node merge(const Node& a, const Node& b) {
    return {min(a.min_val, b.min_val), max(a.max_val, b.max_val)};
}

vector<pair<int, double>> coin_data;
vector<Node> tree;

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = {coin_data[start].second, coin_data[start].second};
        return;
    }
    int mid = start + (end - start) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

Node query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return {1e9, -1e9};
    if (l <= start && end <= r) return tree[node];
    int mid = start + (end - start) / 2;
    Node left_query = query(2 * node, start, mid, l, r);
    Node right_query = query(2 * node + 1, mid + 1, end, l, r);
    return merge(left_query, right_query);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream data_file("Pitcoin.txt");
    int N;
    data_file >> N;
    coin_data.resize(N);

    for (int i = 0; i < N; i++) {
        data_file >> coin_data[i].first >> coin_data[i].second;
    }
    data_file.close();

    tree.resize(4 * N);
    build(1, 0, N - 1);

    int M;
    cin >> M;
    cout << fixed << setprecision(3);

    while (M--) {
        int t_b, t_e;
        cin >> t_b >> t_e;

        // t_b에 해당하는 시간 또는 그 이전 가장 최근 시간 찾기
        auto it_b = upper_bound(coin_data.begin(), coin_data.end(), make_pair(t_b, 1e9));
        if (it_b != coin_data.begin()) it_b--;

        // t_e에 해당하는 시간 또는 그 이전 가장 최근 시간 찾기
        auto it_e = upper_bound(coin_data.begin(), coin_data.end(), make_pair(t_e, 1e9));
        if (it_e != coin_data.begin()) it_e--;

        int actual_t_b = it_b->first;
        int actual_t_e = it_e->first;

        // 실제 구간 [actual_t_b, actual_t_e]에서 모든 시간 포인트 찾기
        int idx_b = lower_bound(coin_data.begin(), coin_data.end(), make_pair(actual_t_b, -1e9)) - coin_data.begin();
        int idx_e = upper_bound(coin_data.begin(), coin_data.end(), make_pair(actual_t_e, 1e9)) - coin_data.begin() - 1;

        // 유효한 범위 확인 및 보정
        if (idx_b >= N) idx_b = N - 1;
        if (idx_e < 0) idx_e = 0;
        if (idx_b > idx_e) {
            idx_b = idx_e;
        }

        Node result = query(1, 0, N - 1, idx_b, idx_e);

        cout << result.min_val << " " << result.max_val << "\n";
    }

    return 0;
}