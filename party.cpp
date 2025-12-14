#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <climits>
using namespace std;

// BFS로 특정 시작점에서 모든 정점까지의 최단 시간 계산
// 시작점: -2 (트릭: -2 + 3 = 1분)
// Edge: 1분, Vertex 통과: 2분 → 합쳐서 +3분
map<char, int> bfs(char start, map<char, vector<char>>& graph) {
    map<char, int> dist;
    queue<char> q;

    q.push(start);
    dist[start] = -2;  // 시작점은 -2로 초기화

    while (!q.empty()) {
        char u = q.front();
        q.pop();

        if (graph.find(u) == graph.end()) continue;

        for (char v : graph[u]) {
            if (dist.find(v) == dist.end()) {
                // u 통과(2분) + edge(1분) = 3분
                // 단, u가 시작점이면 -2 + 3 = 1분 (edge만)
                dist[v] = dist[u] + 3;
                q.push(v);
            }
        }
    }

    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    char f1, f2, f3;
    cin >> f1 >> f2 >> f3;

    map<char, vector<char>> graph;
    set<char> all_vertices;

    // 그래프 입력
    for (int i = 0; i < n; i++) {
        char vertex;
        cin >> vertex;
        all_vertices.insert(vertex);

        char adj;
        while (cin >> adj && adj != '$') {
            graph[vertex].push_back(adj);
            all_vertices.insert(adj);
        }
    }

    // 3명 각각의 시작점에서 BFS
    map<char, int> dist1 = bfs(f1, graph);
    map<char, int> dist2 = bfs(f2, graph);
    map<char, int> dist3 = bfs(f3, graph);

    // 3명 모두 도달 가능한 정점 찾기
    char best_vertex = '@';
    int min_max_time = INT_MAX;

    // 모든 정점 확인
    for (char v : all_vertices) {
        // 3명 모두 도달 가능한지 확인
        if (dist1.find(v) != dist1.end() &&
            dist2.find(v) != dist2.end() &&
            dist3.find(v) != dist3.end()) {

            // 3명 중 가장 늦게 도착하는 시간
            // -2는 시작점이므로 max에서 자동으로 무시됨
            int max_time = max({dist1[v], dist2[v], dist3[v]});

            // 최소값 갱신 (시간이 같으면 알파벳 순)
            if (max_time < min_max_time ||
                (max_time == min_max_time && v < best_vertex)) {
                min_max_time = max_time;
                best_vertex = v;
            }
        }
    }

    // 출력
    if (best_vertex == '@') {
        cout << "@\n-1\n";
    } else {
        cout << best_vertex << "\n" << min_max_time << "\n";
    }

    return 0;
}
