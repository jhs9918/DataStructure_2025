#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

#define HM 100000000
unsigned long PNUhash(unsigned long long x, int salt) {
    x = x + salt;
    x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
    x = x ^ (x >> 31);
    return x % HM;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, salt;
    cin >> N >> salt;

    int valid = 0, invalid = 0, used = 0;
    unordered_set<unsigned long long> usedCodes;

    for (int i = 0; i < N; i++) {
        string code;
        cin >> code;

        // d1~d12 추출 (0-indexed 위치: 2,3,4,5,8,9,10,11,14,15,16,17)
        unsigned long long K = 0;
        K = K * 10 + (code[2] - '0');   // d1
        K = K * 10 + (code[3] - '0');   // d2
        K = K * 10 + (code[4] - '0');   // d3
        K = K * 10 + (code[5] - '0');   // d4
        K = K * 10 + (code[8] - '0');   // d5
        K = K * 10 + (code[9] - '0');   // d6
        K = K * 10 + (code[10] - '0');  // d7
        K = K * 10 + (code[11] - '0');  // d8
        K = K * 10 + (code[14] - '0');  // d9
        K = K * 10 + (code[15] - '0');  // d10
        K = K * 10 + (code[16] - '0');  // d11
        K = K * 10 + (code[17] - '0');  // d12

        // PNUhash 계산
        unsigned long hash = PNUhash(K, salt);

        // 8자리 문자열로 변환 (leading zero 포함)
        string hashStr = to_string(hash);
        while (hashStr.length() < 8) {
            hashStr = "0" + hashStr;
        }

        // H1~H8 검증 (0-indexed 위치: 0,1,6,7,12,13,18,19)
        bool isValid =
            code[0] == hashStr[0] &&   // H1
            code[1] == hashStr[1] &&   // H2
            code[6] == hashStr[2] &&   // H3
            code[7] == hashStr[3] &&   // H4
            code[12] == hashStr[4] &&  // H5
            code[13] == hashStr[5] &&  // H6
            code[18] == hashStr[6] &&  // H7
            code[19] == hashStr[7];    // H8

        if (!isValid) {
            invalid++;
        } else {
            if (usedCodes.count(K)) {
                used++;
            } else {
                valid++;
                usedCodes.insert(K);
            }
        }
    }

    cout << valid << "\n" << invalid << "\n" << used << "\n";

    return 0;
}