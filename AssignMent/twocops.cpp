#include <bits/stdc++.h>

using namespace std;

/*
    로봇 두 개가 부딪혀서 방향이 바뀌는 건,
    사실 로봇들이 똑같이 생겨서 구별이 안 되니까
    서로를 그냥 '통과'해서 각자 갈 길 가는 거랑 결과가 똑같다.

    따라서 복잡하게 충돌 감지하고 방향 바꿀 필요 없이,
    '통과' 모델로 각자 위치를 계산한 뒤,
    실제 충돌 횟수가 홀수인지 짝수인지 마지막에 한 번만 확인해서
    결과를 뒤집을지 말지 결정하면 된다.
*/

// 특정 거리(effective_dist)에 해당하는 최종 (x, y) 좌표를 찾는 함수
pair<int, int> findPosition(long long effective_dist, int k,
                            const vector<pair<int, int>>& v,
                            const vector<long long>& d) {
    // 이진 탐색으로 현재 로봇이 있는 선분의 시작점 인덱스를 찾음
    int idx = upper_bound(d.begin(), d.end(), effective_dist) - d.begin() - 1;

    // 해당 선분 위에서 얼마나 더 이동했는지 계산
    long long move = effective_dist - d[idx];

    // 시작점 좌표를 기준으로 이동 방향에 맞춰 최종 좌표 계산
    pair<int, int> pos = v[idx];
    pair<int, int> next_pos = v[(idx + 1) % k];

    if (pos.first != next_pos.first) { // 수평 이동
        pos.first += (next_pos.first > pos.first) ? move : -move;
    } else { // 수직 이동
        pos.second += (next_pos.second > pos.second) ? move : -move;
    }
    return pos;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;

    vector<pair<int, int>> v(k);
    for (auto& p : v) cin >> p.first >> p.second;

    // 시계 방향 기준 누적 거리 및 전체 둘레 계산
    vector<long long> d(k + 1, 0);
    for (int i = 0; i < k; ++i) {
        d[i + 1] = d[i] + abs(v[i].first - v[(i + 1) % k].first) + abs(v[i].second - v[(i + 1) % k].second);
    }
    long long perimeter = d[k];

    long long t;
    cin >> t;

    // '통과' 모델로 각 로봇의 최종 위치 후보 계산
    pair<int, int> pos_A = findPosition(t % perimeter, k, v, d);
    long long c2_start_dist = d[k / 2 - 1];
    pair<int, int> pos_B = findPosition((c2_start_dist - (t % perimeter) + perimeter) % perimeter, k, v, d);

    // 충돌 횟수 계산으로 스왑 여부 최종 결정
    long long collision_count = 0;
    if (perimeter > 0) {
        long double final_time = t;
        long double p_d = perimeter;
        long double d_start_d = c2_start_dist;

        long double first_meet_dist = min(d_start_d, p_d - d_start_d);
        long double first_meet_time = first_meet_dist / 2.0;

        if (final_time >= first_meet_time) {
            long double time_period = p_d / 2.0;
            collision_count = floor((final_time - first_meet_time) / time_period) + 1;
        }
    }

    // 충돌 횟수가 홀수이면, c1과 c2의 최종 위치가 뒤바뀜
    if (collision_count % 2 != 0) {
        swap(pos_A, pos_B);
    }

    // 결과 출력
    cout << pos_A.first << " " << pos_A.second << '\n';
    cout << pos_B.first << " " << pos_B.second << '\n';

    return 0;
}