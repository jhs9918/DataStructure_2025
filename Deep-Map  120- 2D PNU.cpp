#include <bits/stdc++.h>
using namespace std;

int main() {

    map    < int, map< int, string >   > PNU_map ;

    // map < int, int, string > PNU_map ;


    PNU_map[35 ][ 5 ] = "÷�ܰ�" ;
    PNU_map[ 3][ 12 ] = "�İ���" ;
    PNU_map[ 5 ][ 12 ] = "�߾ӵ�����" ;
    PNU_map[34][ 67 ] = "����" ;
    PNU_map[ 2 ][ 1 ] = "����" ;
    PNU_map[ -23][ -29 ] = "�λ�뿪" ;

    int x, y ;
    x= 3 ; y = 12 ;

    cout << "x,y=" <<  PNU_map[ x][ y ] << "\n " ;
    x= -23 ; y = -29 ;

    cout << "x,y=" <<  PNU_map[ x][ y ] << "\n " ;


}