#include <vector>
#include <queue>
#include <list>
#include <string>
#include <map>
#include <iostream>

#define INF 0x3f3f3f3f

typedef std::pair<std::string, std::string> sPair;
typedef std::pair<int, std::string> isPair;

class Graph {
    // store vertex and weight pair for every edge
    std::map<std::string, std::list<isPair>> adj;
public:
    // function to add an edge to graph
    void add_edge(std::string u, std::string v, int w);

    // prints shortest path from s
    void shortest_path(std::string s);

    // prints MST from s
    void mst(std::string s);
};

void Graph::add_edge(std::string u, std::string v, int w)
{
    adj[u].push_back(std::make_pair(w, v));
    adj[v].push_back(std::make_pair(w, u));
}

// prints shortest paths from src to all other vertices
void Graph::shortest_path(std::string src)
{
    // create a priority queue to store vertices
    std::priority_queue<isPair, std::vector<isPair>, std::greater<isPair>> pq;

    // create a vector for distances and initialize all distances as infinite
    std::map<std::string, int> dist;
    for (auto it = adj.begin(); it != adj.end(); it++) {
        dist[it->first] = INF;
    }

    // insert source in priority queue with distance 0
    pq.push(std::make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
        // extract first vertex in queue
        std::string u = pq.top().second;
        pq.pop();

        // get all adjacent vertices of u
        for (auto i = adj[u].begin(); i != adj[u].end(); ++i) {
            // get vertex label and weight of current adjacent
            std::string v = i->second;
            int weight = i->first;

            // if there is shorter path to v through u, update distance of v
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    // print shortest distances
    std::cout << "Finding shortest distances from " << src << " using Dijkstra's algorithm..." << std::endl;
    for (auto i = dist.begin(); i != dist.end(); ++i) {
        std::cout << "Vertex: " << i->first << std::endl;
        std::cout << "Distance from Source: " << i->second << std::endl;
    }
}

// prints shortest paths from src to all other vertices
void Graph::mst(std::string src)
{
    // create a priority queue to store vertices
    std::priority_queue<isPair, std::vector<isPair>, std::greater<isPair>> pq;

    // create a vector for keys and initialize all distances as infinite
    std::map<std::string, int> key;
    for (auto it = adj.begin(); it != adj.end(); it++) {
        key[it->first] = INF;
    }

    // To store parent array which in turn store MST
    //std::map<std::string, std::string> parent;
    std::map<std::string, std::vector<std::string>> parent;
    for (auto it = adj.begin(); it != adj.end(); it++) {
        //parent[it->first] = "unitialized";
        parent[it->first].push_back("unitialized");
    }

    // To keep track of vertices included in MST
    std::map<std::string, bool> inMST;
    for (auto it = adj.begin(); it != adj.end(); it++) {
        inMST[it->first] = false;
    }

    // insert source in priority queue with distance 0
    pq.push(std::make_pair(0, src));
    key[src] = 0;

    while (!pq.empty()) {
        // extract first vertex in queue
        std::string u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        // get all adjacent vertices of u
        for (auto i = adj[u].begin(); i != adj[u].end(); ++i) {
            // get vertex label and weight of current adjacent
            std::string v = i->second;
            int weight = i->first;

            // if there is shorter path to v through u, update distance of v
            if (inMST[v] == false && key[v] > weight) {
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                //parent[v] = u;
                parent[v].push_back(u);
            }
        }
    }

    // print MST
    std::cout << "Finding MST using Prim's algorithm..." << std::endl;
    /*
    for (auto i = parent.begin(); i != parent.end(); ++i) {
        std::cout << "Key: " << i->first << std::endl;
        std::cout << "Parent: " << i->second << std::endl;
    }
    */
    auto end = parent.end();
    end--;
    for (unsigned int i = 0; i < end->second.size(); ++i) {
        std::cout << end->second.at(i) << std::endl;
    }
}

/*
// Prints shortest paths from src to all other vertices
void Graph::primMST()
{
    // Create a priority queue to store vertices that
    // are being preinMST. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // http://geeksquiz.com/implement-min-heap-using-stl/
    std::priority_queue<isPair, std::vector<isPair>, std::greater<isPair>> pq;

    int src = 0; // Taking vertex 0 as source

    // Create a vector for keys and initialize all
    // keys as infinite (INF)
    vector<int> key(V, INF);

    // To store parent array which in turn store MST
    vector<int> parent(V, -1);

    // To keep track of vertices included in MST
    vector<bool> inMST(V, false);

    // Insert source itself in priority queue and initialize
    // its key as 0.
    pq.push(make_pair(0, src));
    key[src] = 0;

    // Looping till priority queue becomes empty
    while (!pq.empty())
    {
        // The first vertex in pair is the minimum key
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted key (key must be first item
        // in pair)
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;  // Include vertex in MST

        // 'i' is used to get all adjacent vertices of a vertex
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            // Get vertex label and weight of current adjacent
            // of u.
            int v = (*i).first;
            int weight = (*i).second;

            //  If v is not in MST and weight of (u,v) is smaller
            // than current key of v
            if (inMST[v] == false && key[v] > weight)
            {
                // Updating key of v
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    // Print edges of MST using parent array
    for (int i = 1; i < V; ++i)
        printf("%d - %d\n", parent[i], i);
}
*/

int main()
{
    Graph my_graph;

    // from San Francisco
    my_graph.add_edge("San Francisco", "Los Angeles", 381);
    my_graph.add_edge("San Francisco", "Seattle", 807);
    my_graph.add_edge("San Francisco", "Denver", 1267);

    // from Seattle
    my_graph.add_edge("Seattle", "Denver", 1331);
    my_graph.add_edge("Seattle", "Chicago", 2097);

    // from Los Angeles
    my_graph.add_edge("Los Angeles", "Denver", 1015);
    my_graph.add_edge("Los Angeles", "Dallas", 1435);
    my_graph.add_edge("Los Angeles", "Kansas City", 1663);

    // from Denver
    my_graph.add_edge("Denver", "Kansas City", 599);
    my_graph.add_edge("Denver", "Chicago", 1003);

    // from Kansas City
    my_graph.add_edge("Kansas City", "Chicago", 533);
    my_graph.add_edge("Kansas City", "New York", 1260);
    my_graph.add_edge("Kansas City", "Atlanta", 864);
    my_graph.add_edge("Kansas City", "Dallas", 496);

    // from Dallas
    my_graph.add_edge("Dallas", "Atlanta", 781);
    my_graph.add_edge("Dallas", "Houston", 239);

    // from Chicago
    my_graph.add_edge("Chicago", "Boston", 983);
    my_graph.add_edge("Chicago", "New York", 787);

    // from Houston
    my_graph.add_edge("Houston", "Atlanta", 810);
    my_graph.add_edge("Houston", "Miami", 1187);

    // from Atlanta
    my_graph.add_edge("Atlanta", "Miami", 661);
    my_graph.add_edge("Atlanta", "New York", 888);

    // from New York
    my_graph.add_edge("New York", "Boston", 214);

    // from Miami
    // none

    my_graph.shortest_path("Atlanta");
    my_graph.mst("Atlanta");

    return 0;
}
