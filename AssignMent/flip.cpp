#include <iostream>
#include <list>

using namespace std;

// mynode 구조체
struct mynode {
    long long start;  // 구간 시작 인덱스
    long long end;    // 구간 끝 인덱스
    int value;        // 값 (0 or 1)

    mynode(long long s, long long e, int v) : start(s), end(e), value(v) {}
};

// STL list 사용
list<mynode> FLIP;

// flip 연산 수행
void flip(long long i, long long j) {
    list<mynode> newList;

    for (auto it = FLIP.begin(); it != FLIP.end(); ++it) {
        long long s = it->start;
        long long e = it->end;
        int v = it->value;

        // 현재 segment가 flip 구간과 겹치지 않는 경우
        if (e < i || s > j) {
            newList.push_back(*it);
        } else {
            // 현재 segment가 flip 구간과 겹치는 경우

            // 1. flip 구간 앞부분 (변경되지 않음)
            if (s < i) {
                newList.push_back(mynode(s, i - 1, v));
            }

            // 2. flip 구간과 겹치는 부분 (값이 반전됨)
            long long overlapStart = max(s, i);
            long long overlapEnd = min(e, j);
            newList.push_back(mynode(overlapStart, overlapEnd, 1 - v));

            // 3. flip 구간 뒷부분 (변경되지 않음)
            if (e > j) {
                newList.push_back(mynode(j + 1, e, v));
            }
        }
    }

    // 인접한 같은 값을 가진 segment들을 병합
    FLIP.clear();
    for (auto& node : newList) {
        if (!FLIP.empty() &&
            FLIP.back().end + 1 == node.start &&
            FLIP.back().value == node.value) {
            // 병합: 이전 노드의 end를 확장
            FLIP.back().end = node.end;
        } else {
            FLIP.push_back(node);
        }
    }
}

int main() {
    long long n;
    int k;
    cin >> n >> k;

    // 초기 상태: 전체가 0인 하나의 segment
    FLIP.push_back(mynode(0, n - 1, 0));

    // k번의 flip 연산 수행
    for (int i = 0; i < k; i++) {
        long long start, end;
        cin >> start >> end;
        flip(start, end);
    }

    // 결과 계산: 1's run의 개수와 1의 총 개수
    int runCount = 0;
    long long oneCount = 0;

    for (auto& node : FLIP) {
        if (node.value == 1) {
            runCount++;
            oneCount += (node.end - node.start + 1);
        }
    }

    cout << runCount << " " << oneCount << endl;

    return 0;
}
