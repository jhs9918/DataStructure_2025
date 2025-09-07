#define _USE_MATH_DEFINES
#define ld long double
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

struct Circle {
    ld x, y, r;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Circle c1, c2;

    cin >> c1.x >> c1.y >> c1.r;
    cin >> c2.x >> c2.y >> c2.r;

    if (c1.r < c2.r) {
        swap(c1, c2);
    }

    ld dx = c1.x - c2.x;
    ld dy = c1.y - c2.y;
    ld dr = c1.r - c2.r;

    ld d_sq = dx * dx + dy * dy; //중심 사이의 거리 제곱근
    ld l_sq = d_sq - dr * dr;  //외접선의 접점 사이의 거리 제곱근

    ld d = sqrt(d_sq);
    ld l = sqrt(l_sq);

    ld alpha = acos(dr / d);

    ld angle_large = M_PI - alpha;
    ld angle_small = alpha;

    ld perimeter = 2 * (l + c1.r * angle_large + c2.r * angle_small);  //둘레 구하기
    ld area = (c1.r + c2.r) * l + c1.r * c1.r * angle_large + c2.r * c2.r * angle_small;  //면적 구하기

    cout << static_cast<long long>(floor(area)) << " "
         << static_cast<long long>(floor(perimeter)) << '\n';

    return 0;
}





