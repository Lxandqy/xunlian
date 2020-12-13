#include<iostream>
#include<cstring>

using namespace std;

const int N = 4e4 + 10;
int n,m,root;

int head[N],to[N * 2],last[N * 2],cnt;
void add(int a,int b){
	to[++cnt] = b;
	last[cnt] = head[a];
	head[a] = cnt;
}

int fa[N][22],depth[N],q[N];
void bfs(int root){
	memset(depth,0x3f,sizeof depth);
	int tt = 0,hh = 0;
	depth[0] = 0;
	depth[root] = 1;
	q[0] = root;
	while(hh <= tt){
		int p = q[hh++];
		for(int i = head[p]; i != -1; i = last[i]){
			int j = to[i];
			if(depth[j] > depth[p] + 1){
				depth[j] = depth[p] + 1;
				q[++tt] = j;
				fa[j][0] = p;
				for(int k = 1; k <= 16; k++){
					fa[j][k] = fa[fa[j][k - 1]][k - 1];
				}
			} 
		}
	}
}

int lca(int x,int y){
	if(depth[x] < depth[y]) swap(x,y);
	for(int i = 16; i >= 0; i --){
		if(depth[fa[x][i]] >= depth[y]){
			x = fa[x][i];	
		}
	}
	
	if(x == y) return x;
	for(int k = 16; k >= 0; k--){
		if(fa[x][k] != fa[y][k]){
			x = fa[x][k],y = fa[y][k];
		}
	}
	
	return fa[x][0];
}

int main(){
	memset(head,-1,sizeof head);
	scanf("%d",&n);
	for(int i = 1,x,y;i <= n; i++){
		scanf("%d%d",&x,&y);
		if(y == -1) root = x;
		else{
			add(x,y);
			add(y,x);
		}
	}
	
	bfs(root);
	
	scanf("%d",&m);
	for(int i = 1; i <= m; i++){
		int x,y;
		scanf("%d%d",&x,&y);
		int s = lca(x,y);
		if(s == x){
			printf("%d\n",1);
		}else if(s == y){
			printf("%d\n",2);
		}else{
			printf("%d\n",0);
		}
	}
	
	
	
	
	return 0;
}
