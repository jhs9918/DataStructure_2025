#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
using namespace std;

int main() {
    int N, k1, k2;
    cin >> N >> k1 >> k2;

    map<char, vector<string>> fn;
    for (int i = 0; i < N; i++) {
        char f;
        cin >> f;
        string t;
        while (cin >> t && t != "$") fn[f].push_back(t);
    }

    vector<string> ex;
    stack<pair<char, int>> stk;
    stk.push({'M', 0});

    while (!stk.empty()) {
        if (ex.size() >= 100000) {
            cout << "DEADLOCK\n";
            return 0;
        }

        auto& [f, p] = stk.top();

        if (p >= fn[f].size()) {
            stk.pop();
            continue;
        }

        string s = fn[f][p++];

        if (s.size() == 1 && s[0] >= 'A' && s[0] <= 'Z') {
            // 재귀 체크
            stack<pair<char, int>> tmp = stk;
            bool rec = false;
            while (!tmp.empty()) {
                if (tmp.top().first == s[0]) {
                    rec = true;
                    break;
                }
                tmp.pop();
            }
            if (rec) {
                cout << "DEADLOCK\n";
                return 0;
            }
            stk.push({s[0], 0});
        } else {
            ex.push_back(string(1, f) + "-" + s);
        }
    }

    auto print = [&](int k) {
        int n = ex.size();
        if (k > 0 && k <= n) cout << ex[k-1] << "\n";
        else if (k < 0 && -k <= n) cout << ex[n+k] << "\n";
        else cout << "NONE\n";
    };

    print(k1);
    print(k2);
    return 0;
}