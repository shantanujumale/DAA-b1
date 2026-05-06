#include <stdio.h>

#define MAX 100

// Structure to represent an edge
struct Edge {
    int u, v, weight;
};

// Function to find the parent of a vertex in the union-find structure
int findParent(int parent[], int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

// Function to perform union of two subsets
void unionSets(int parent[], int rank[], int x, int y) {
    int rootX = findParent(parent, x);
    int rootY = findParent(parent, y);

    if (rank[rootX] < rank[rootY])
        parent[rootX] = rootY;
    else if (rank[rootX] > rank[rootY])
        parent[rootY] = rootX;
    else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

// Function to implement Kruskal's algorithm
void kruskalMST(int graph[MAX][MAX], int n) {
    struct Edge edges[MAX * MAX];
    int edgeCount = 0;

    // Convert adjacency matrix to edge list
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) { // upper triangle only
            if (graph[i][j] != 0) {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].weight = graph[i][j];
                edgeCount++;
            }
        }
    }

    // Sort edges by weight (simple bubble sort for clarity)
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                struct Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    int parent[MAX], rank[MAX];
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    printf("\nEdges in the Minimum Cost Spanning Tree:\n");
    int totalCost = 0;
    int edgesUsed = 0;

    for (int i = 0; i < edgeCount && edgesUsed < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        int setU = findParent(parent, u);
        int setV = findParent(parent, v);

        // If including this edge doesn't cause a cycle
        if (setU != setV) {
            printf("%d - %d  (Cost: %d)\n", u, v, edges[i].weight);
            totalCost += edges[i].weight;
            unionSets(parent, rank, setU, setV);
            edgesUsed++;
        }
    }

    printf("Total Minimum Cost of Travel: %d\n", totalCost);
}

int main() {
    int n;
    int graph[MAX][MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (0 for no edge):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    kruskalMST(graph, n);

    return 0;
}
