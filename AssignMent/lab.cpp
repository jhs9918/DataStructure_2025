#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Student {
    string name;
    vector<int> metrics;

    Student(string n, vector<int> s) : name(n), metrics(5) {
        int sum = 0, minScore = 101, maxScore = 0, perfect = 0, attend = 0;

        for (int score : s) {
            if (score > 0) {
                attend++;
                sum += score;
                if (score < minScore) minScore = score;
                if (score == 100) perfect++;
            }
            maxScore = max(maxScore, score);
        }

        metrics[0] = attend;
        metrics[1] = sum;
        metrics[2] = (minScore == 101) ? 0 : minScore;
        metrics[3] = maxScore;
        metrics[4] = perfect;
    }
};

vector<int> priority;

bool compare(const Student& a, const Student& b) {
    for (int i = 0; i < 5; i++) {
        int idx = priority[i] - 1;
        if (a.metrics[idx] != b.metrics[idx])
            return a.metrics[idx] > b.metrics[idx];
    }
    return a.name < b.name;
}

int main() {
    int N, K;
    cin >> N >> K;

    priority.resize(5);
    for (int i = 0; i < 5; i++) cin >> priority[i];

    vector<Student> students;
    for (int i = 0; i < N; i++) {
        string name;
        cin >> name;
        vector<int> scores(K);
        for (int j = 0; j < K; j++) cin >> scores[j];
        students.push_back(Student(name, scores));
    }

    sort(students.begin(), students.end(), compare);

    for (const Student& s : students) cout << s.name << "\n";

    return 0;
}