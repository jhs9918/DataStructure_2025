#include<iostream>
#include<queue>
using namespace std;
int main(){
    int n,id,age;char sex;cin>>n;
    queue<int>om,of,c,af,am;
    for(int i=0;i<n;i++){
        cin>>id>>age>>sex;
        if(age>=61)sex=='M'?om.push(id):of.push(id);
        else if(age<=15)c.push(id);
        else sex=='F'?af.push(id):am.push(id);
        }
    while(!om.empty()) {
        cout<<om.front()<<'\n'; om.pop();
    }
    while(!of.empty()) {
        cout<<of.front()<<'\n'; of.pop();
    }
    while(!c.empty()) {
        cout<<c.front()<<'\n'; c.pop();
    }
    while(!af.empty()) {
        cout<<af.front()<<'\n'; af.pop();
    }
    while(!am.empty()) {
        cout<<am.front()<<'\n'; am.pop();
    }
}
