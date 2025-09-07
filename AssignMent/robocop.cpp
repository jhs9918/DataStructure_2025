#include <bits/stdc++.h>

using namespace std;

pair<int, int> v[51];
long long d[52];

int main() {
    int k;
    scanf("%d", &k);

    for (int i = 0; i < k; ++i) {
        scanf("%d %d", &v[i].first, &v[i].second);
    }

    d[0] = 0;
    for (int i = 0; i < k; ++i) {
        d[i + 1] = d[i] + abs(v[i].first - v[(i + 1) % k].first) + abs(v[i].second - v[(i + 1) % k].second);
    }

    for (int i = 0; i < 5; ++i) {
        long long t;
        scanf("%lld", &t);

        t %= d[k];

        int idx = upper_bound(d, d + k + 1, t) - d - 1;

        auto p = v[idx];
        auto np = v[(idx + 1) % k];

        t -= d[idx];

        if (p.first != np.first) {
            p.first += (np.first > p.first) ? t : -t;
        } else {
            p.second += (np.second > p.second) ? t : -t;
        }

        printf("%d %d\n", p.first, p.second);
    }

    return 0;
}