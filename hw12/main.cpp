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

    // to store parent array of MST
    std::map<std::string, std::string> parent;
    //std::map<std::string, std::vector<std::string>> parent;
    for (auto it = adj.begin(); it != adj.end(); it++) {
        parent[it->first] = "UNITIALIZED";
    }

    // keep track of vertices within MST
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
                parent[v] = u;
            }
        }
    }

    // print MST
    std::cout << "Finding MST using Prim's algorithm..." << std::endl;

    int mst_total = 0;
    for (auto i = std::next(parent.begin()); i != parent.end(); i++) {
        // find edge
        int edge = -1;
        for (auto j = adj[i->first].begin(); j != adj[i->first].end(); ++j) {
            if (j->second == i->second) {
                edge = j->first;
            }
        }

        std::cout << i->first << " <-> " << i->second << " (" << edge << ")" << std::endl;

        mst_total += edge;
    }

    std::cout << "Total cost: " << mst_total << std::endl;
}

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
