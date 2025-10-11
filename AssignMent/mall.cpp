#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int main() {
    int N, k;
    cin >> N >> k;

    // k개의 계산대 큐 생성
    vector<queue<pair<int, int>>> cashiers(k);

    // 각 계산대의 현재 대기 시간 (물건 개수 합)
    vector<int> waitTime(k, 0);

    // 완료 이벤트 관리용 우선순위 큐
    // (완료시각, -계산대번호, 고객ID)
    // 음수를 사용해서 동시 완료 시 큰 계산대 번호가 먼저 나오도록
    priority_queue<tuple<int, int, int>, //자료형
                   vector<tuple<int, int, int>>,  //구현체
                   greater<tuple<int, int, int>>> pq;  //비교 연산자

    // N명의 고객 처리
    for (int i = 0; i < N; i++) {
        int id, items;
        cin >> id >> items;

        // 가장 대기 시간이 짧은 계산대 찾기
        int minWait = waitTime[0];
        int minIdx = 0;
        for (int j = 1; j < k; j++) {
            if (waitTime[j] < minWait) {
                minWait = waitTime[j];
                minIdx = j;
            }
        }

        // 해당 계산대에 고객 추가
        cashiers[minIdx].push({id, items});

        // 이 고객의 완료 시각 = 현재 대기 시간 + 물건 개수
        int finishTime = waitTime[minIdx] + items;

        // 대기 시간 업데이트
        waitTime[minIdx] = finishTime;

        // 완료 이벤트 추가 (-계산대번호로 큰 번호 우선)
        pq.push({finishTime, -minIdx, id});
    }

    // 완료 순서대로 출력
    while (!pq.empty()) {
        auto [time, negCashier, id] = pq.top();
        pq.pop();
        cout << id << "\n";
    }

    return 0;
}
