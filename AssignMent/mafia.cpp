#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int n,root;
vector<string> names;
vector<vector<int>> children;
vector<int> subordinates,depth;
vector<bool> hasParent;

int calcSub(int node){
    int count=0;
    for(int child:children[node])
        count+=1+calcSub(child);
    return subordinates[node]=count;
}

void calcDepth(int node,int d){
    depth[node]=d;
    for(int child:children[node])
        calcDepth(child,d+1);
}

bool cmp(int a,int b){
    if(subordinates[a]!=subordinates[b])return subordinates[a]>subordinates[b];
    if(depth[a]!=depth[b])return depth[a]<depth[b];
    return names[a]<names[b];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;

    unordered_map<string,int> nameIdx;
    names.reserve(n);
    children.resize(n);
    subordinates.resize(n);
    depth.resize(n);
    hasParent.resize(n,false);

    for(int i=0;i<n-1;i++){
        string person,boss;
        cin>>person>>boss;

        if(!nameIdx.count(person)){
            nameIdx[person]=names.size();
            names.push_back(person);
        }
        if(!nameIdx.count(boss)){
            nameIdx[boss]=names.size();
            names.push_back(boss);
        }

        int pIdx=nameIdx[person],bIdx=nameIdx[boss];
        children[bIdx].push_back(pIdx);
        hasParent[pIdx]=true;
    }

    for(int i=0;i<n;i++)
        if(!hasParent[i]){
            root=i;
            break;
        }

    calcSub(root);
    calcDepth(root,0);

    vector<int> indices(n);
    for(int i=0;i<n;i++)indices[i]=i;

    sort(indices.begin(),indices.end(),cmp);

    for(int idx:indices)
        cout<<names[idx]<<'\n';
}
