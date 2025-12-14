#include <bits/stdc++.h>
using namespace std;

// 다중 map에서 key값을 찾아내기. 매우 중요한 작업. 기말고사에 유사한 문제 나옴,.

int main() {

    map <int, map<int,string>> w;
    w[ 1][ 5]= "Buchman" ;
    w[-1][ 9]= "Sosa" ;
    w[ 4][ 2]= "Pepe" ;
    w[ 9][-3]= "Delilar" ;
    w[ 0][ 7]= "Andro" ;
    w[-8][ 2]= "Bushmill" ;
    w[ 9][ 6]= "Dorian" ;
    w[-8][ 5]= "Arnnoc" ;
    w[ 9][ 6]= "Beronika" ;
    w[ 1][ 0]= "Amanda" ;
    w[ 9][-3]= "Quaga" ;

    for( auto p : w ) {
      map<int,string> & inner_map= p.second ; // p는 또 하나의 map입니다.
      for (auto it2: inner_map ) {
            cout << "\n w[ " <<  p.first << "," << it2.first << " ]= " << it2.second;
      }
    }

    return 0 ;
}

