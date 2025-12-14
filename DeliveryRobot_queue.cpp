#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

// 전역 변수
int n, t;
int grid[25][25];
int dist[25][25][4];  // dist[y][x][dir] = 최소 시간

// 방향: 0=상, 1=우, 2=하, 3=좌
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

struct State {
    int x, y;
    int dir;      // 현재 방향
    int cost;     // 현재까지의 시간
};

int bfs() {
    // 일반 큐 사용! (당신이 평소에 쓰던 것)
    queue<State> q;

    // 시작점: (0, n-1) = 왼쪽 아래
    // 4방향으로 첫 이동 시도
    for (int d = 0; d < 4; d++) {
        int nx = 0 + dx[d];
        int ny = n - 1 + dy[d];

        // 첫 이동이 가능한 경우
        if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[ny][nx] == 0) {
            q.push({nx, ny, d, 1});
            dist[ny][nx][d] = 1;
        }
    }

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        // 이미 더 좋은 경로로 방문한 경우 스킵
        // (이 부분이 중요! 최소값만 처리)
        if (cur.cost > dist[cur.y][cur.x][cur.dir]) continue;

        // 4방향 모두 시도
        for (int newDir = 0; newDir < 4; newDir++) {
            int nx = cur.x + dx[newDir];
            int ny = cur.y + dy[newDir];

            // 범위 체크 및 장애물 체크
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (grid[ny][nx] == 1) continue;

            // 새로운 비용 계산
            // - 같은 방향이면: +1 (이동만)
            // - 다른 방향이면: +1+t (회전+이동)
            int newCost = cur.cost + 1;
            if (newDir != cur.dir) {
                newCost += t;  // 방향 전환 비용 추가
            }

            // 더 좋은 경로를 발견한 경우만 큐에 추가!
            if (newCost < dist[ny][nx][newDir]) {
                dist[ny][nx][newDir] = newCost;
                q.push({nx, ny, newDir, newCost});
            }
        }
    }

    // 목표점: (n-1, 0) = 오른쪽 위
    // 4방향 중 최소값 찾기
    int result = 1e9;
    for (int d = 0; d < 4; d++) {
        result = min(result, dist[0][n - 1][d]);
    }

    return result == 1e9 ? -1 : result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> t;

    // 그리드 입력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    // dist 배열 초기화
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int d = 0; d < 4; d++) {
                dist[i][j][d] = 1e9;
            }
        }
    }

    cout << bfs() << endl;

    return 0;
}