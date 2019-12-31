/*
    Graph represented by Adjacency List.
    Elementary Graph Algorithms - BFS and DFS , implemented simply ( only exploring the graph )
    DFS is implemented both recursively and iteratively unlike BFS, which is, just iteratively.

    In different cpp files there will be added a more complex implementations of both , where :
    BFS can tell us the distance between a vertex and another vertex ( shortest path ) and also
    which is the parent of a particular node.
    DFS would be able to timestamp nodes ( showing when a node was explored and when it was finished exploring )
    and also a parent of a particular node.

 */

#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

class Graph
{
    int V; // Number of vertices in the Graph
    vector<vector<int>> Adj; // Adjacency list ( Representation of the Graph );

public:
    Graph(int V);
    void InsertEdge(int v, int u);
    void BFS(int StartVertex); // Explores the Graph in BFS Manner, starting from an arbitrary vertex
    void DFSIterative(int StartVertex); // Explores the Graph in DFS Manner, starting from an arbitrary vertex

    void DFSVisit(int Start, bool* Visited); // Procedure used in the Recursive implementation
    void DFSRecursive(int StartVertex);
};
Graph::Graph(int V) // Constructs a Graph with a specific number of vertices
{
    this->V = V;
    for (int i = 0; i < V; ++i) {
        vector<int> Vertex;
        Adj.push_back(Vertex);
    }
}

void Graph::InsertEdge(int v, int u) { // Connects a Vertex v with a Vertex u ( creates edge )
    Adj[v].push_back(u);
}

// O(V+E) ( Linear in the size of the adjacency-list representation )
// If we modify BFS, so that the Graph is matrix-represented , time becomes O(V^2) , which is far more inefficient
void Graph::BFS(int StartVertex)
{
    bool* Visited = new bool[V];
    for(int i = 0;i < V;i++)
        Visited[i] = false;

    queue<int> Q;
    Q.push(StartVertex);
    Visited[StartVertex] = true;

    while(!Q.empty())
    {
        int CurrentVertex = Q.front();
        Q.pop();
        cout<<CurrentVertex<<" ";
        for(int i = 0; i < Adj[CurrentVertex].size() ; ++i) {
            int Neighbour = Adj[CurrentVertex][i];
            if(Visited[Neighbour])
                continue;
            Visited[Neighbour] = true;
            Q.push(Neighbour);
            /*
                Lemma: During execution, if Q contains V1...Vr vertices,
                then the following inequalities hold:
                Vr.distance <= V1.distance + 1 and
                Vi.distance <= Vi+1.distance for i = 1..r-1 ( Source : CLR )
                */
             }
    }
    delete[] Visited;
    /*
        This algorithm is so named because it discovers all vertices at distance k from s
        before discovering any vertices at distance k + 1. ( Breadth )
     */
}
void Graph::DFSIterative(int StartVertex)
{
    bool* Visited = new bool[V];
    for(int i = 0;i < V;i++)
        Visited[i] = false;

    stack<int> S;
    S.push(StartVertex);

    while(!S.empty())
    {
        int CurrentVertex = S.top();
        S.pop();
        if(Visited[CurrentVertex])
            continue;
        Visited[CurrentVertex] = true;
        cout<<CurrentVertex<<" ";

        for(int i = 0; i < Adj[CurrentVertex].size() ; ++i)
        {
            int Neighbour = Adj[CurrentVertex][i];
            S.push(Neighbour);
        }
    }
    delete[] Visited;
}

void Graph::DFSVisit(int Start,bool* Visited) // Procedure used in the Recursive implementation
{
    Visited[Start]=true;
    cout<<Start<<" ";
    for(int i = 0; i < Adj[Start].size();i++)
    {
        int neighbor = Adj[Start][i];
        if(!Visited[neighbor])
            DFSVisit(neighbor,Visited);
    }
}
void Graph::DFSRecursive(int StartVertex)
{
    bool* Visited = new bool[V];
    for(int i = 0;i<V;i++)
        Visited[i]=false;

    DFSVisit(StartVertex,Visited);

    delete[] Visited;
}

int main()
{
    Graph G(9);

    G.InsertEdge(1, 4);
    G.InsertEdge(1, 5);
    G.InsertEdge(5, 6);
    G.InsertEdge(5, 3);
    G.InsertEdge(6, 2);
    G.InsertEdge(6,7);
    G.InsertEdge(6,9);
    G.InsertEdge(7,8);
    G.InsertEdge(3,8);

    cout<<"Running BFS: ";
    G.BFS(1); // 1 4 5 6 3 2 7 9 8
    cout<<endl;

    cout<<"Running DFS: ";
    G.DFSIterative(1); // 1 4 5 6 2 7 8 9 3
    cout<<endl;

}
