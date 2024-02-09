//
// Created by Kevin Liam on 2023/11/10.
//
// 인접 행렬을 이용한 그래프의 깊이 우선 탐색 프로그램
#include <stdio.h>
#include <stdlib.h>
#define MAX_VTXS 256

void error(char str[]) {
    printf("%s\n", str);
    exit(1);
}

typedef char VtxData;
int adj[MAX_VTXS][MAX_VTXS];
int vsize;
VtxData vdata[MAX_VTXS];

int is_empty_graph() { return (vsize == 0); }
int is_full_graph() { return vsize >= MAX_VTXS; }
void init_graph()
{
    int i, j;
    vsize = 0;
    for (i = 0; i < MAX_VTXS; i++)
        for (j = 0; j < MAX_VTXS; j++)
            adj[i][j] = 0;
}
void insert_vertex(VtxData name)
{
    if (is_full_graph())
        error("Error: 그래프 정점의 개수 초과\n");
    else
        vdata[vsize++] = name;
}
void insert_edge(int u, int v, int val)
{
    adj[u][v] = val;
}
void insert_edge2(int u, int v, int val)
{
    adj[u][v] = adj[v][u] = val;
}
void load_graph(char * filename)
{
    int i, j, val, n;
    char str[80];
    FILE *fp = fopen(filename, "r");
    if (fp != NULL) {
        init_graph();
        fscanf(fp, "%d", &n);
        for (i = 0; i < n; i++) {
            fscanf(fp, "%s", str);
            insert_vertex(str[0]);
            for(j = 0; j < n; j++) {
                fscanf(fp, "%d", &val);
                if (val != 0)
                    insert_edge(i, j, val);
            }
        }
        fclose(fp);
    }
}

int visited[MAX_VTXS];  // 방문 여부를 기록하는 배열
void reset_visited()    // 방문 여부를 기록하는 배열을 초기화하는 함수
{
    int i;
    for(i = 0; i < vsize; i++)
        visited[i] = 0;
}
void DFS(int v) // 깊이 우선 탐색 함수
{
    int w;
    visited[v] = 1;
    printf("%c ", vdata[v]);
    for(w = 0; w < vsize; w++)
        if(adj[v][w] != 0 && visited[w] == 0)
            DFS(w);
}
int main()
{
    load_graph("graph.txt");
    reset_visited();
    printf("DFS ==> ");
    DFS(0);
    printf("\n");
}