/*
    An example implementation of Dijkstra's algorithm using STL Priority Queue
    which is modified a little bit to be a min heap ( because it is max by default ).
    Definitely not the best implementation but good enough to get the idea of how the algorithm works.
*/

#include <iostream>
#include <queue>
#include <utility> // for the pair structure
#include <list>

using namespace std;

typedef pair<int, int> IntPair; // Just to make it easier to define some things below.
# define INF 0x3f3f3f3f // Has a crazy large value, so in fact is infinity.


class Graph
{
    int V; // Number of Vertices
    list<pair<int,int>> *Adj; // Vertex and Weight pair for every edge

    public:
        Graph(int V);
        void AddEdge(int u, int v, int Weight);

        void DijkstraSP(int Source); // Runs Dijkstra's shortest path algorithm on the graph

};
Graph::Graph(int V)
{
    this->V = V;
    Adj = new list<IntPair>[V]; // Notice number of elements in the list is v
}
void Graph::AddEdge(int u, int v, int Weight)
{
    Adj[u].push_back(make_pair(v,Weight));
    //Adj[v].push_back(make_pair(u,Weight)); Graph is directed so we don't want this line
}
void Graph::DijkstraSP(int Source)
{
    priority_queue<IntPair, vector<IntPair>, greater <IntPair>> PQ;

    /*
       This syntax is crazy and a little bit complicated but in order to understand how
       Dijkstra's Shortest Path Algorithm works, we don't need to know how this priority queue
       works.
       Only consider the fact that every element of the Prior.Queue is a pair defined as (weight, vertex)
       ( Weight is the 1st element because pairs are compared by 1st element by default ).
       Which tells us 'the hardness level' (weight) to get to the respect vertex from the Single Source.
    */

    vector<int> Dist(V, INF); // Create a vector to track the distances and initialize every dist as Inf

    PQ.push(make_pair(0, Source)); // The cost to get to the Source vertex from the Source vertex is 0
    Dist[Source] = 0; // Shortest path from SSource to SSource is 0

    while(!PQ.empty())
    {
        int u = PQ.top().second;
        /*
            The next vertex which is the easiest to get to ( has the lowest weight in the queue)
            is the second element in the pair, so we take it
        */
        PQ.pop();
        //Later think about whether popping a pair guarentees us that it is visited will never be visited again ?

        // Iter is used to get all adjacent vertices of a particular vertex
        list< pair<int,int> >::iterator Iter;
        for (Iter = Adj[u].begin(); Iter != Adj[u].end(); ++Iter)
        {
            int v = (*Iter).first;
            int Weight = (*Iter).second;

            //  If there is an easier path to v through u.
            if (Dist[v] > Dist[u] + Weight)
            {
                Dist[v] = Dist[u] + Weight; // Update distance of v
                PQ.push(make_pair(Dist[v], v));
                /*
                    This priority queue is defined as a min heap and every time we push
                    a pair of the form (weight, vertex), the weight param with the lowest value
                    has the highest priority which guarantees us that the next pair removed from
                    the queue is the vertex that is the easiest to get to.
                    ( because its weight is the smallest)
                */
            }
        }
    }
    // Print shortest distances stored in dist[]
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, Dist[i]);
}
int main()
{
    // This example is from the CLR's Dijkstra chapter

    int V = 5;
    Graph g(V);

    g.AddEdge(0, 1, 10);
    g.AddEdge(0, 2, 5);
    g.AddEdge(1, 2, 2);
    g.AddEdge(2, 1, 3);
    g.AddEdge(1, 3, 1);
    g.AddEdge(2, 3, 9);
    g.AddEdge(2, 4, 2);
    g.AddEdge(4, 0, 7);
    g.AddEdge(3, 4, 4);
    g.AddEdge(4, 3, 6);

    g.DijkstraSP(0); // Start the Algorithm from vertex 0
}