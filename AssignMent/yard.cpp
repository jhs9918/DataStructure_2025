#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;

    vector<vector<int>> yards(N);

    // 입력 처리
    for (int i = 0; i < N; i++) {
        int count;
        cin >> count;
        yards[i].resize(count);
        for (int j = 0; j < count; j++) {
            cin >> yards[i][j];
        }
    }

    // 재배치 작업
    while (true) {
        // 최고 높이와 최저 높이 찾기
        int maxHeight = 0, minHeight = 100000;
        for (int i = 0; i < N; i++) {
            int h = yards[i].size();
            maxHeight = max(maxHeight, h);
            minHeight = min(minHeight, h);
        }

        // 종료 조건: 높이 차이가 1 이하
        if (maxHeight - minHeight <= 1) break;

        // 가장 높은 위치의 컨테이너 찾기 (같은 높이면 더 무거운 것)
        int maxIdx = -1;
        int maxWeight = -1;
        for (int i = 0; i < N; i++) {
            if (yards[i].size() == maxHeight) {
                int weight = yards[i].back();
                if (weight > maxWeight) {
                    maxWeight = weight;
                    maxIdx = i;
                }
            }
        }

        // 가장 낮은 위치 찾기 (같은 높이면 앞쪽 우선)
        int minIdx = -1;
        for (int i = 0; i < N; i++) {
            if (yards[i].size() == minHeight) {
                minIdx = i;
                break;
            }
        }

        // 컨테이너 이동
        int container = yards[maxIdx].back();
        yards[maxIdx].pop_back();
        yards[minIdx].push_back(container);
    }

    // 출력
    for (int i = 0; i < N; i++) {
        if (i > 0) cout << "\r\n";
        if (yards[i].empty()) {
            cout << "0";
        } else {
            for (int j = 0; j < yards[i].size(); j++) {
                if (j > 0) cout << " ";
                cout << yards[i][j];
            }
            // 마지막 직전 줄이고 마지막이 0이면 공백 제외, 그 외에는 공백 추가
            if (i == N - 2 && yards[N - 1].empty()) {
                // 공백 제외
            } else {
                cout << " ";
            }
        }
    }
    // 마지막 줄이 비어있지 않으면 \r\n 추가
    if (!yards[N - 1].empty()) cout << "\r\n";

    return 0;
}