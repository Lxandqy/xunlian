#include<iostream>
#include<vector>
using namespace std;
vector<int>v[500005];
int depth[500005],fa[500005][22],lg[500005];
int n,m,s;
void llgg(){
	for(int i = 1; i <= n; i++){
		lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
	}
}
void dfs(int now,int last){
	fa[now][0] = last,depth[now] = depth[last] + 1;
	for(int i = 1; i <= lg[depth[now]]; i++){
		fa[now][i] = fa[fa[now][i - 1]][i - 1];
	}
	for(int i = 0; i < v[now].size(); i++){
		if(v[now][i] != last) dfs(v[now][i],now);
	}
}
int lca(int x,int y){
	if(depth[x] < depth[y]) swap(x,y);
	while(depth[x] > depth[y]){
		x = fa[x][lg[depth[x] - depth[y]] - 1];
	}//de[x] = 9 ,de[y] = 1, xiangshang 2^2
	if(x == y) return x;
	for(int k = lg[depth[x]] - 1; k >= 0; --k){
		if(fa[x][k] != fa[y][k]){
			x = fa[x][k],y = fa[y][k];
		}
	} 
	return fa[x][0]; 
}
int main(){
	ios::sync_with_stdio(false);
    int x,y;
	cin >> n >> m >> s;
	for(int i = 1; i <= n - 1; i++){
		cin >> x >> y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	llgg();
	dfs(s,0);
	for(int i = 1; i <= m; i++){
		cin >> x >> y;
		cout << lca(x,y) << endl;
	} 
	return 0;
}
