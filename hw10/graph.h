#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <iostream>
#include <stack>
#include <algorithm>
#include <queue>

enum edge_status { UNDISCOVERED, DISCOVERY, BACK, CROSS };

struct vertex;

struct edge {
    vertex *end1;
    vertex *end2;
    int distance;
    bool visited;
    edge_status status;
};

struct vertex {
    std::vector<edge*> adjacent; // cost of edge, destination vertex
    std::string name;
    bool visited = false;
    vertex(std::string s) : name(s) {}
    //vertex(vertex other_vertex) : adjacent(other_vertex.adjacent), name(other_vertex.name) {}
};

class Graph {
public:
    typedef std::map<std::string, vertex*> vmap;
    void add_vertex(const std::string&);
    void add_edge(const std::string& from, const std::string& to, int cost);
    vertex* get_vertex(const std::string&);
    int get_total_distance();
    void print_edge_statuses();
    void refresh_graph();
    void DFS(vertex*&);
    void BFS(vertex*&);
    void shortestPath(std::string);
private:
    vmap work;
    std::vector<edge*> all_edges;
    void sort_adjacent_edges(vertex *in_vertex);
    vertex* opposite_vertex(vertex *in_vertex, edge *in_edge);
    int distance_traveled = 0;
};

// Prints shortest paths from src to all other vertices
void Graph::shortestPath(std::string src)
{
    // Create a priority queue to store vertices that
    // are being preprocessed. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // http://geeksquiz.com/implement-min-heap-using-stl/
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

    // Create a vector for distances and initialize all
    // distances as infinite (INF)
    vector<int> dist(V, INF);

    // Insert source itself in priority queue and initialize
    // its distance as 0.
    pq.push(make_pair(0, src));
    dist[src] = 0;

    /* Looping till priority queue becomes empty (or all
      distances are not finalized) */
    while (!pq.empty())
    {
        // The first vertex in pair is the minimum distance
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted distance (distance must be first item
        // in pair)
        int u = pq.top().second;
        pq.pop();

        // 'i' is used to get all adjacent vertices of a vertex
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            // Get vertex label and weight of current adjacent
            // of u.
            int v = (*i).first;
            int weight = (*i).second;

            //  If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    // Print shortest distances stored in dist[]
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

#endif // GRAPH_H
