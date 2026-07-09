#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct {
    int arr[MAX_NODES];
    int top;
} Stack;
 
typedef struct {
    int n;
    int **adjLists;
} Graph;

void push(Stack *s, int n) {
    s->arr[(s->top)++] = n;
}

void insertEnd(int *list, int n) {
    int i = 0;
    while (list[i] != -1)
        i++;
    list[i] = n;
    list[i + 1] = -1;
}

Graph createDAG(int n) {
    Graph g;
    g.n = n;
    int i, x, j;
    g.adjLists = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        g.adjLists[i] = (int *)malloc(n * sizeof(int));
        g.adjLists[i][0] = -1;
    }

    int edges[6][2] = {{2, 3}, {3, 1}, {4, 0}, {4, 1}, {5, 0}, {5, 2}};
    for (i = 0; i < 6; i++) {
        insertEnd(g.adjLists[edges[i][0]], edges[i][1]);
    }
    return g;
}

void topoDFS(Graph *g, int *visited, Stack *s, int ind) {
    visited[ind] = 1;
    int *list = g->adjLists[ind];
    int i = 0;
    while (list[i] != -1) {
        if (visited[list[i]] == 0)
            topoDFS(g, visited, s, list[i]);
        i++;
    }
    push(s, ind);
}

void topoSourceRem(Graph *g) {
    int i, j, *list;
    int removed[MAX_NODES];
    int degree[MAX_NODES] = {0};
    for (i = 0; i < g->n; i++) {
        list = g->adjLists[i];
        j = 0;
        while (list[j] != -1) {
            degree[list[j]]++;
            j++;
        }
    }
    int ind = 0;
    printf("Topological sort using source removal: ");
    for (i = 0; i < g->n; i++) {
        for (j = 0; j < g->n; j++) {
            if (degree[j] == 0) {
                removed[ind++] = j;
                printf("%d ", j);
                degree[j] = -1;
                list = g->adjLists[j];
                int k = 0;
                while (list[k] != -1) {
                    degree[list[k]]--;
                    k++;
                }
                break;
            }
        }
    }
    printf("\n");
}

int main() {
    int i, n = 6;
    Graph g = createDAG(n);

    int visited[MAX_NODES] = {0};
    Stack s;
    s.top = 0;

    printf("Topological sort using DFS: ");
    for (i = 0; i < n; i++)
        if (visited[i] == 0)
            topoDFS(&g, visited, &s, i);
    while (s.top != 0)
        printf("%d ", s.arr[--(s.top)]);
    printf("\n");

    topoSourceRem(&g);

    return 0;
}