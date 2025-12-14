#include <iostream>
#include <string>
#include <set>
using namespace std;

struct N {
    string k;
    N *l,*r;
    N(string s):k(s),l(0),r(0){}
};

N* root=0;

N* ins(N* n,string s){
    if(!n)return new N(s);
    if(s<n->k)n->l=ins(n->l,s);
    else if(s>n->k)n->r=ins(n->r,s);
    return n;
}

string getMax(N* n){
    while(n->r)n=n->r;
    return n->k;
}

string getMin(N* n){
    while(n->l)n=n->l;
    return n->k;
}

N* del(N* n,string s){
    if(!n)return 0;
    if(s<n->k){
        n->l=del(n->l,s);
        return n;
    }
    if(s>n->k){
        n->r=del(n->r,s);
        return n;
    }
    if(!n->l&&!n->r){
        delete n;
        return 0;
    }
    if(n->l){
        n->k=getMax(n->l);
        n->l=del(n->l,n->k);
    }else{
        n->k=getMin(n->r);
        n->r=del(n->r,n->k);
    }
    return n;
}

void getDep(N* n,int d,int t,set<string>& s){
    if(!n)return;
    if(d==t)s.insert(n->k);
    getDep(n->l,d+1,t,s);
    getDep(n->r,d+1,t,s);
}

void getLeaf(N* n,set<string>& s){
    if(!n)return;
    if(!n->l&&!n->r)s.insert(n->k);
    getLeaf(n->l,s);
    getLeaf(n->r,s);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string cmd,s;
    int d;
    while(cin>>cmd){
        if(cmd=="quit")break;
        if(cmd=="+"){
            cin>>s;
            root=ins(root,s);
        }else if(cmd=="-"){
            cin>>s;
            root=del(root,s);
        }else if(cmd=="depth"){
            cin>>d;
            set<string> res;
            getDep(root,1,d,res);
            if(res.empty())cout<<"NO\n";
            else{
                for(auto& x:res)cout<<x<<" ";
                cout<<"\n";
            }
        }else if(cmd=="leaf"){
            set<string> res;
            getLeaf(root,res);
            for(auto& x:res)cout<<x<<" ";
            cout<<"\n";
        }
    }
}
