#include <iostream>
#include <string>
#include <vector>
using namespace std;

int k,sz,idx;
string qts;
vector<string> img;

void decode(int r,int c,int s){
    if(qts[idx]=='0'||qts[idx]=='1'){
        char ch=qts[idx++];
        for(int i=r;i<r+s;i++)
            for(int j=c;j<c+s;j++)
                img[i][j]=ch;
    }else{
        idx++;
        int h=s/2;
        decode(r,c+h,h);
        decode(r,c,h);
        decode(r+h,c,h);
        decode(r+h,c+h,h);
        idx++;
    }
}

string encode(int r,int c,int s){
    char f=img[r][c];
    bool same=true;
    for(int i=r;i<r+s&&same;i++)
        for(int j=c;j<c+s&&same;j++)
            if(img[i][j]!=f)same=false;
    if(same)return string(1,f);
    int h=s/2;
    return "("+encode(r,c+h,h)+encode(r,c,h)+encode(r+h,c,h)+encode(r+h,c+h,h)+")";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string type;
    cin>>k>>type;
    sz=1<<k;
    if(type=="QTS"){
        cin>>qts;
        idx=0;
        img.assign(sz,string(sz,'0'));
        decode(0,0,sz);
        for(auto&row:img)cout<<row<<'\n';
    }else{
        img.resize(sz);
        for(int i=0;i<sz;i++)cin>>img[i];
        cout<<encode(0,0,sz)<<'\n';
    }
    return 0;
}
