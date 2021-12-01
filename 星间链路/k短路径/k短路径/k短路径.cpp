// k短路径.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int M = 7e5 + 1, N = 1e3 + 10;
const int inf = 0x7fffffff;
int n, m;

struct ss {
	int to, last, len;
	ss() {}
	ss(int a, int b, int c) :to(a), last(b), len(c) {}
};

struct Graphy {
	ss g[M];
	int head[M], cnt;
	void add(int a, int b, int c) {
		g[++cnt] = ss(b, head[a], c); head[a] = cnt;
	}
}G, GI;

struct node {
	int val, v;
	node() {}
	node(int a, int b) :val(a), v(b) {}
	bool operator <(const node &a)const { return val > a.val; }
}pp, qq;
priority_queue <node> Q;

struct Left_Tree {
	int h[M], v[M], w[M], son[2][M], tot, root[M];
	void clear() { tot = 0; }
#define l(o) son[0][o]
#define r(o) son[1][o]
	int newnode(int vv, int idd, int hh) {
		++tot;
		w[tot] = vv; v[tot] = idd; h[tot] = hh;
		l(tot) = r(tot) = 0;
		return tot;
	}
	int merge(int a, int b) {
		if (!a || !b) return a | b;
		if (w[a] > w[b])swap(a, b);
		int newp = newnode(w[a], v[a], h[a]);
		l(newp) = l(a); r(newp) = r(a);
		r(newp) = merge(r(newp), b);
		if (h[l(newp)] < h[r(newp)])swap(l(newp), r(newp));
		h[newp] = h[r(newp)] + 1;
		return newp;
	}
	void insert(int &o, int vv, int idd) {
		int p = newnode(vv, idd, 0);
		o = merge(p, o);
	}
}LT;

int que[M], p, q; bool in[M];
void spfa(int st, int en, int *dis, Graphy &G) {
	int *head = G.head, v; ss *g = G.g;
	for (int i = 1; i <= n; i++)dis[i] = inf;
	que[p = q = 0] = en; in[en] = 1; dis[en] = 0;
	for (; p <= q; p++) {
		int a = que[p%M];
		for (int i = head[a]; i; i = g[i].last) {
			v = g[i].to;
			if (dis[v] > dis[a] + g[i].len) {
				dis[v] = dis[a] + g[i].len;
				if (!in[v]) {
					in[v] = 1;
					que[++q%M] = v;
					if (dis[que[(p + 1) % M]] > dis[que[q%M]]) {
						swap(que[(p + 1) % M], que[q%M]);
					}
				}
			}
		}
		in[a] = 0;
	}
}
int fd[M], stk[M], dis[M], top, fs[M];
void dfs(int a) {
	in[a] = 1; stk[++top] = a; int v, w;
	for (int i = GI.head[a]; i; i = GI.g[i].last) {
		v = GI.g[i].to; w = GI.g[i].len;
		if (!in[v] && dis[v] == dis[a] + w) {
			fd[v] = a; fs[i] = 1;
			dfs(v);
		}
	}
}
void Rebuild() {
	int a, v;
	for (int w = 1; w <= top; w++) {
		a = stk[w];
		LT.root[a] = LT.root[fd[a]];
		for (int i = G.head[a]; i; i = G.g[i].last) {
			v = G.g[i].to;
			if (!fs[i] && dis[v] != inf) {
				LT.insert(LT.root[a], dis[v] - dis[a] + G.g[i].len, v);
			}
		}
	}
}
int Solve_K(int st, int en, int kth) {
	if (!LT.root[st]) return -1;
	if (kth == 1) return dis[st];
	pp.val = dis[st] + LT.w[LT.root[st]];
	pp.v = LT.root[st];
	Q.push(pp);
	while (!Q.empty()) {
		--kth;
		qq = Q.top(); Q.pop();
		if (kth == 1) return qq.val;
		int ls = LT.l(qq.v), rs = LT.r(qq.v), o = LT.v[qq.v];
		int nowv = qq.val;
		if (LT.root[o]) Q.push(node(nowv + LT.w[LT.root[o]], LT.root[o]));
		if (ls) Q.push(node(nowv + LT.w[ls] - LT.w[qq.v], ls));
		if (rs) Q.push(node(nowv + LT.w[rs] - LT.w[qq.v], rs));
	}
	return -1;
}

void add_side(int a, int b, int c) {
	G.add(a, b, c); GI.add(b, a, c);
}

void calc_K(int ss, int tt, int kk) {
	if (ss == tt)++kk;
	spfa(ss, tt, dis, GI);
	if (dis[ss] == inf) { puts("-1"); return; }
	dfs(tt);
	Rebuild();
	int ans = Solve_K(ss, tt, kk);
	printf("%d\n", ans);
}
int s, t, k;
void work() {
	int a, b, c;
	scanf_s("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf_s("%d%d%d", &a, &b, &c);
		add_side(a, b, c);
	}
	scanf_s("%d%d%d", &s, &t, &k);
	calc_K(s, t, k);
}
int main() 
{ 
	work();
	return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
