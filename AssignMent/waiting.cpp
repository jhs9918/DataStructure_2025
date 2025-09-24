#include <bits/stdc++.h>

using namespace std;

/*
    이 코드는 스킵 리스트(Skip List)와 유사한 데이터 구조를 사용.
    여러 줄로 정렬된 숫자들을 관리하고,
    한 줄이 너무 길어지면 반으로 나눠서 새로운 줄을 만둚.
    이렇게 하면 삽입/삭제 연산을 효율적으로 처리할 수 있음.
*/

vector<vector<int>> waitlistRows;
int N, k;

// 이진 탐색으로 숫자 a가 들어갈 줄(row)의 인덱스를 찾는 함수
int findRowBS(int a) {
    if (waitlistRows.empty()) return 0;

    // upper_bound를 사용해 a보다 큰 첫 요소를 가진 첫 번째 줄을 찾음
    // 람다 함수를 비교 연산자로 사용하여 int와 vector<int>를 비교
    auto it = upper_bound(waitlistRows.begin(), waitlistRows.end(), a,
        [](int val, const vector<int>& row) {
            // "값 < 요소"의 조건을 정의. 이 경우 "a < row의 첫 요소"
            return val < row.front();
        }
    );

    // 만약 a가 모든 줄의 첫 요소보다 작거나 같다면, 첫 번째 줄에 속함
    if (it == waitlistRows.begin()) {
        return 0;
    }

    // 그 외의 경우, 'it'이 가리키는 곳 바로 앞 줄이 정답
    return distance(waitlistRows.begin(), it) - 1;
}

// 숫자 a를 삽입하는 함수
void addNumber(int a) {
    if (waitlistRows.empty()) {
        waitlistRows.push_back({a});
        return;
    }

    int row_idx = findRowBS(a);

    // lower_bound로 삽입 위치를 찾음
    auto it = lower_bound(waitlistRows[row_idx].begin(), waitlistRows[row_idx].end(), a);
    waitlistRows[row_idx].insert(it, a);

    // 만약 한 줄이 너무 길어지면 반으로 나눠서 새 줄을 추가
    if (waitlistRows[row_idx].size() == 2 * k) {
        vector<int> new_row(waitlistRows[row_idx].begin() + k, waitlistRows[row_idx].end());
        waitlistRows[row_idx].resize(k);
        waitlistRows.insert(waitlistRows.begin() + row_idx + 1, move(new_row));
    }
}

// 숫자 a를 삭제하는 함수
void removeNumber(int a) {
    if (waitlistRows.empty()) return;

    int row_idx = findRowBS(a);

    // lower_bound로 삭제할 원소의 위치를 찾음
    auto it = lower_bound(waitlistRows[row_idx].begin(), waitlistRows[row_idx].end(), a);

    // 해당 위치의 값이 정말 a가 맞는지 확인 후 삭제
    if (it != waitlistRows[row_idx].end() && *it == a) {
        waitlistRows[row_idx].erase(it);
        // 만약 줄이 완전히 비면, 해당 줄 자체를 제거
        if (waitlistRows[row_idx].empty()) {
            waitlistRows.erase(waitlistRows.begin() + row_idx);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // 입력
    cin >> N >> k;

    // 연산 수행
    for (int i = 0; i < N; i++) {
        char op;
        int num;
        cin >> op >> num;
        if (op == '+') {
            addNumber(num);
        } else {
            removeNumber(num);
        }
    }

    // 결과 출력
    for (const auto& row : waitlistRows) {
        if (!row.empty()) {
            cout << row.front() << "\n";
        }
    }

    return 0;
}
