#include <stdio.h>
#include <stdlib.h>

// Node structure for adjacency list
struct node {
  int vertex;
  struct node* next;
};

// Function to create a new node
struct node* createNode(int v) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Graph structure
struct Graph {
  int numVertices;
  int* visited;
  struct node** adjLists;
};

// Function to create a graph with a given number of vertices
struct Graph* createGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  // Allocate memory for adjacency lists
  graph->adjLists = malloc(vertices * sizeof(struct node*));

  // Initialize visited array to track visited vertices during traversal
  graph->visited = malloc(vertices * sizeof(int));

  int i;
  for (i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL; // Initialize adjacency lists as empty
    graph->visited[i] = 0; // Initialize visited array as all vertices not visited
  }
  return graph;
}

// Function to add an edge between two vertices in an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
  // Create a new node for the destination vertex and add it to the adjacency list of the source vertex
  struct node* newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  // Since the graph is undirected, add an edge from dest to src as well
  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

// Function to perform Depth First Search (DFS) traversal recursively
void DFS(struct Graph* graph, int vertex) {
  // Mark the current vertex as visited
  graph->visited[vertex] = 1;
  printf("Visited %d \n", vertex);

  // Traverse all adjacent vertices of the current vertex recursively
  struct node* temp = graph->adjLists[vertex];
  while (temp != NULL) {
    int connectedVertex = temp->vertex;
    if (graph->visited[connectedVertex] == 0) {
      DFS(graph, connectedVertex);
    }
    temp = temp->next;
  }
}

// Function to print the adjacency list representation of the graph
void printGraph(struct Graph* graph) {
  int v;
  for (v = 0; v < graph->numVertices; v++) {
    struct node* temp = graph->adjLists[v];
    printf("\n Adjacency list of vertex %d\n ", v);
    while (temp) {
      printf("%d -> ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
  }
}

// Main function
int main() {
  // Create a graph with 4 vertices
  struct Graph* graph = createGraph(4);
  
  // Add edges between vertices
  addEdge(graph, 0, 1);
  addEdge(graph, 0, 2);
  addEdge(graph, 1, 2);
  addEdge(graph, 2, 3);

  // Print the adjacency list representation of the graph
  printGraph(graph);

  // Perform DFS traversal starting from vertex 2
  DFS(graph, 2);

  return 0;
}

Time Complexity Analysis:

- Creating the graph involves initializing the adjacency lists and the visited array, which takes O(V) time, where V is the number of vertices.

- Adding an edge between two vertices takes O(1) time since it involves adding a node to the adjacency list of both vertices.

- Depth First Search (DFS) traversal has a time complexity of O(V + E), where V is the number of vertices and E is the number of edges in the graph.

- Printing the adjacency list representation of the graph also takes O(V + E) time.

- Overall, the time complexity of the operations in this code mainly depends on the number of vertices and edges in the graph.