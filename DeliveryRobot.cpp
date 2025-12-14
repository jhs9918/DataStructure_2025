#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct State{
    int c,x,y,d;
    bool operator>(const State& o)const{return c>o.c;}
};

int main(){
    int n,t,i,j,d,x,y,nx,ny,nc,ans=1e9;
    cin>>n>>t;
    vector<vector<int>> g(n,vector<int>(n));
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            cin>>g[i][j];
    priority_queue<State,vector<State>,greater<State>> pq;
    vector<vector<vector<int>>> dist(n,vector<vector<int>>(n,vector<int>(4,1e9)));
    int dx[]={0,1,0,-1},dy[]={-1,0,1,0};
    for(d=0;d<4;d++){
        nx=dx[d],ny=n-1+dy[d];
        if(nx>=0&&nx<n&&ny>=0&&ny<n&&!g[ny][nx])
            pq.push({1,nx,ny,d}),dist[ny][nx][d]=1;
    }
    while(!pq.empty()){
        State s=pq.top();
        pq.pop();
        if(s.c>dist[s.y][s.x][s.d])continue;
        for(int k=0;k<4;k++){
            nx=s.x+dx[k],ny=s.y+dy[k];
            if(nx<0||nx>=n||ny<0||ny>=n||g[ny][nx])continue;
            nc=s.c+1+(k!=s.d?t:0);
            if(nc<dist[ny][nx][k])
                dist[ny][nx][k]=nc,pq.push({nc,nx,ny,k});
        }
    }
    for(d=0;d<4;d++)
        ans=min(ans,dist[0][n-1][d]);
    cout<<(ans==1e9?-1:ans);
}
