/*
    Graph represented by Adjacency List.
    Elementary Graph Algorithms - BFS and DFS , implemented simply ( only exploring the graph )
    DFS is implemented both recursively and iteratively unlike BFS, which is, just iteratively.
    Topological sort is also implemented simply just using an additional stack.

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
#include <list>
using namespace std;

class Graph
{
    int V; // Number of vertices in the Graph
    vector<vector<int>> Adj; // Adjacency list ( Representation of the Graph );
    bool IsCyclicUtil(int V, bool Visited[], bool *RS);
    void PrintAllPathsUtil(int , int , bool [], int [], int &);

public:
    Graph(int V);
    void InsertEdge(int v, int u);
    void BFS(int StartVertex); // Explores the Graph in BFS Manner, starting from an arbitrary vertex

    void DFSIterative(int StartVertex); // Explores the Graph in DFS Manner, starting from an arbitrary vertex

    void DFSVisit(int Start, bool* Visited); // Procedure used in the Recursive implementation
    void DFSRecursive(int StartVertex);

    void TopologicalSortUtil(int V, bool Visited[], stack<int> &Stack); // Helper function for the Topological Sort
    void TopologicalSort();

    // If we want to construct the graph easily, just by entering edges number, and then add them one by one
    void ConstructGraph(int Edges);

    bool IsCyclic(); // Returns true if the Graph is cyclic , false otherwise

    void PrintAllPaths(int S, int D);
    void FindInDegreeOutDegree(); // Finds the in-degree and the out-degree of every vertex

};
Graph::Graph(int V) // Constructs a Graph with a specific number of vertices
{
    this->V = V;
    Adj.resize(V+1);
}

void Graph::InsertEdge(int v, int u) { // Connects a Vertex v with a Vertex u ( creates edge )
    Adj[v].push_back(u);
    //Adj[u].push_back(v); Uncomment this line if you want the Graph to be Undirected
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

void Graph::TopologicalSortUtil(int V, bool *Visited, stack<int> &Stack)
{
    // Mark the current node as visited.
    Visited[V] = true;

    // Recursively call this function for all the vertices adjacent to this vertex (that are not visited yet)
    vector<int>::iterator i;
    for (i = Adj[V].begin(); i != Adj[V].end(); ++i)
        if (!Visited[*i])
            TopologicalSortUtil(*i, Visited, Stack);

    // Push current vertex to the stack that stores the ordering
    Stack.push(V);
}

/*
   Can be thought of as the kind of sorting you can define without reference to comparison of numbers
   Topological sorting for DAG is a linear ordering of vertices such that for every directed edge uv,
   vertex u comes before v in the ordering. ( Not possible if the Graph is not a DAG )
*/
void Graph::TopologicalSort() // O(|V| + |E|) Since it is just modified DFS with an additional stack
{
    stack<int> Stack;

    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Recursively calling the helper function for all of the unvisited vertices in the graph
    for (int i = 0; i < V; i++)
        if (!visited[i])
            TopologicalSortUtil(i, visited, Stack);

    /*
       Print contents of stack
       Note: The first elements of the ordering should always be all the vertices with in-degree = 0 !
       In this algorithm, this is guaranteed due to the fact that we always call the function recursively
       for vertices ( and their adjacent vertices and so on and so on ... ) that have in-degree > 0 and push them
       in the stack only after when they are finished ( they don't have any adjacent vertices left )
       so on every iteration ( on every moment ) , the top of the stack cannot have a vertex with in-degree = 0,
       because we call the function only for those that have in-degree > 0, until the very last moment when there are
       only vertices with in-degree = 0 left unvisited , then they are pushed in the stack and since it is a stack,
       they come first in the ordering.
    */
    while (!Stack.empty())
    {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}
void Graph::ConstructGraph(int Edges)
{
    int u,v;
    for(int i=0; i<Edges; i++){
        cout<<"u,v : "<<endl;
        cin>>u>>v;
        InsertEdge(u,v);
    }
}
bool Graph::IsCyclicUtil(int V, bool Visited[], bool *RecStack)
{
    if(Visited[V] == false)
    {
        // Mark the current node as visited and part of recursion stack
        Visited[V] = true;
        RecStack[V] = true;

        // Recur for all the vertices adjacent to this vertex
        vector<int>::iterator It;
        for(It = Adj[V].begin(); It != Adj[V].end(); ++It)
        {
            if ( !Visited[*It] && IsCyclicUtil(*It, Visited, RecStack) )
                return true;
            else if (RecStack[*It])
                return true;
        }

    }
    RecStack[V] = false;  // remove the vertex from recursion stack
    return false;
}

bool Graph::IsCyclic()
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
    bool *Visited = new bool[V];
    bool *RecStack = new bool[V];
    for(int i = 0; i < V; i++)
    {
        Visited[i] = false;
        RecStack[i] = false;
    }

    // Call the recursive helper function to detect cycle in different
    // DFS trees
    for(int i = 0; i < V; i++)
        if (IsCyclicUtil(i, Visited, RecStack))
            return true;

    return false;
}
void Graph::PrintAllPaths(int S, int D)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];

    // Create an array to store paths
    int *path = new int[V];
    int path_index = 0; // Initialize path[] as empty

    // Initialize all vertices as not visited
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Call the recursive helper function to print all paths
    PrintAllPathsUtil(S, D, visited, path, path_index);
}

void Graph::PrintAllPathsUtil(int u, int d, bool visited[],
                              int path[], int &path_index)
{
    // Mark the current node and store it in path[]
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    // If current vertex is same as destination, then print
    // current path[]
    if (u == d)
    {
        for (int i = 0; i<path_index; i++)
            cout << path[i] << " ";
        cout <<"Path Length: "<<path_index<<endl;

    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        vector<int>::iterator It;
        for (It = Adj[u].begin(); It != Adj[u].end(); ++It)
            if (!visited[*It])
                PrintAllPathsUtil(*It, d, visited, path, path_index);
    }

    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[u] = false;
}
void Graph::FindInDegreeOutDegree()
{
    vector<int> In;
    vector<int> Out;
    In.resize(V);
    Out.resize(V);

    vector<vector<int>>::iterator It;
    int i = 0;
    for(It = Adj.begin();It != Adj.end();++It)
    {
        Out[i] = It->size();
        for (int j = 0; j < It->size(); j++)
        {
            // Every vertex that has an incoming
            // edge from i
            ++In[(*It)[j]];
        }
        ++i;
    }
    printf("Vertex\tIn\tOut");
    std::cout<<endl;
    for (int k = 0; k < V; k++) {
        std::cout<<k<<": "<<In[k]<<", "<<Out[k]<<endl;
        //Uncomment next lines if you want to know the number of isolated vertices in the graph
        //if(In[k] + Out[k] == 0)
            //num++;
    }
}

int main()
{
    Graph G(5); // Graph to run BFS and DFS on
    G.ConstructGraph(2); // Enter Edges (u,v) one by one
    G.FindInDegreeOutDegree();

    //G.PrintAllPaths(1, 2);


    //std::cout<<G.IsCyclic()<<endl;
//    G.InsertEdge(1, 4);
//    G.InsertEdge(1, 5);
//    G.InsertEdge(5, 6);
//    G.InsertEdge(5, 3);
//    G.InsertEdge(6, 2);
//    G.InsertEdge(6,7);
//    G.InsertEdge(6,9);
//    G.InsertEdge(7,8);
//    G.InsertEdge(3,8);
//    G.InsertEdge(9,3);
//    G.InsertEdge(5, 1);

//    cout<<"Running BFS: ";
//    G.BFS(1); // 1 4 5 6 3 2 7 9 8
//    cout<<endl;
//
//    cout<<"Running DFS: ";
//    G.DFSRecursive(1); // 1 4 5 6 2 7 8 9 3
//    cout<<endl;
//
//
//    Graph TopGraph(6); // A graph to run the Topological sort on
//    TopGraph.InsertEdge(5, 2);
//    TopGraph.InsertEdge(5, 0);
//    TopGraph.InsertEdge(4, 0);
//    TopGraph.InsertEdge(4, 1);
//    TopGraph.InsertEdge(2, 3);
//    TopGraph.InsertEdge(3, 1);
//
//    cout << "Following is a Topological Sort of the given Graph: \n";
//    TopGraph.TopologicalSort();

}

