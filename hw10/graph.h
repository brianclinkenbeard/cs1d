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

enum edge_status {UNDISCOVERED, DISCOVERY, BACK, CROSS};

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
private:
    vmap work;
    std::vector<edge*> all_edges;
    void sort_adjacent_edges(vertex *in_vertex);
    vertex* opposite_vertex(vertex *in_vertex, edge *in_edge);
    int distance_traveled = 0;
};

#endif // GRAPH_H
