#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct App { string g; int id, c; };
struct Grad {
    vector<App> apps;
    int total = 0;
    void add(App a) {
        apps.push_back(a);
        total += a.c;
        sort(apps.begin(), apps.end(), [](auto& x, auto& y) { return x.c > y.c || (x.c == y.c && x.id > y.id); });
    }
    void rem(int id) {
        for (auto it = apps.begin(); it != apps.end(); ++it) {
            if (it->id == id) { total -= it->c; apps.erase(it); break; }
        }
    }
};

int main() {
    int N, k; cin >> N >> k;
    map<string, Grad> m;
    map<string, int> order;
    string s;
    while (cin >> s && s != "END") {
        if (s == "POP") {
            int p, q; cin >> p >> q;

            // 현재 시점에서 k명 이상인 대학만 선별
            vector<string> v;
            for (auto& [g, d] : m) if (d.apps.size() >= k) v.push_back(g);

            // 대학 정렬 (지원자 수 내림차순 → COTE 점수 합 내림차순 → 알파벳 순)
            sort(v.begin(), v.end(), [&](auto& a, auto& b) {
                if (m[a].apps.size() != m[b].apps.size()) return m[a].apps.size() > m[b].apps.size();
                if (m[a].total != m[b].total) return m[a].total > m[b].total;
                return a < b;
            });

            // 라운드 로빈으로 전체 순위 생성 (매 라운드마다 k 조건 재확인)
            vector<int> ranking;
            if (!v.empty()) {
                int mx = 0;
                for (auto& g : v) mx = max(mx, (int)m[g].apps.size());
                for (int rank = 0; rank < mx; rank++) {
                    // 매 라운드마다 k 조건을 만족하는 대학만 선별
                    vector<string> current_valid;
                    for (auto& g : v) {
                        if (m[g].apps.size() >= k && rank < m[g].apps.size()) {
                            current_valid.push_back(g);
                        }
                    }
                    // 유효한 대학들에서 해당 순위 지원자 추가
                    for (auto& g : current_valid) {
                        ranking.push_back(m[g].apps[rank].id);
                    }
                }
            }

            // p등부터 q등까지 선발
            vector<int> selected;
            for (int i = p-1; i < q && i < ranking.size(); i++) {
                selected.push_back(ranking[i]);
            }

            // 선발된 지원자 출력
            if (!selected.empty()) {
                for (int i = 0; i < selected.size(); i++) {
                    if (i > 0) cout << " ";
                    cout << selected[i];
                }
                cout << "\n";
            }

            // 선발된 지원자 제거
            for (int id : selected) {
                for (auto& [g, d] : m) d.rem(id);
            }
        } else {
            int id, c; cin >> id >> c;
            if (order.find(s) == order.end()) order[s] = order.size();
            m[s].add({s, id, c});
        }
    }
}