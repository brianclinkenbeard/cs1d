#include "graph.h"

void Graph::add_vertex(const std::string &name)
{
    vmap::iterator itr = work.find(name);
    if (itr == work.end()) {
        vertex *v;
        v = new vertex(name);
        work[name] = v;
        return;
    }
    std::cout << "\nVertex already exists!";
}

vertex* Graph::get_vertex(const std::string& name)
{
    vmap::iterator itr = work.find(name);
    // check if name exists
    if (itr != work.end()) {
        vertex *your_vertex = itr->second;
        return your_vertex;
    } else {
        std::cout << "Vertex does not exist." << std::endl;
        vertex *bad_vertex;
        *bad_vertex = vertex("INVALID");
        return bad_vertex;
    }
}

void Graph::add_edge(const std::string& end1, const std::string& end2, int cost)
{
    vertex *e1 = (work.find(end1)->second);
    vertex *e2 = (work.find(end2)->second);

    edge *my_edge = new edge;
    my_edge->end1 = e1;
    my_edge->end2 = e2;
    my_edge->distance = cost;
    my_edge->status = UNDISCOVERED;

    e1->adjacent.push_back(my_edge);
    sort_adjacent_edges(e1);
    e2->adjacent.push_back(my_edge);
    sort_adjacent_edges(e2);

    all_edges.push_back(my_edge);
}

void Graph::sort_adjacent_edges(vertex *in_vertex)
{
    std::sort(in_vertex->adjacent.begin(), in_vertex->adjacent.end(), [](edge *A, edge *B) { return B->distance > A->distance; });
}

vertex* Graph::opposite_vertex(vertex *in_vertex, edge *in_edge)
{
    if (in_vertex->name == in_edge->end1->name)
        return in_edge->end2;
    else
        return in_edge->end1;
}

int Graph::get_total_distance()
{
    return distance_traveled;
}

void Graph::print_edge_statuses()
{
    for (int i = 0; i < all_edges.size(); ++i) {
        if (all_edges.at(i)->status == UNDISCOVERED) {
            std::cout << all_edges.at(i)->end1->name << " and "
                      << all_edges.at(i)->end2->name << ": "
                      << "UNDISCOVERED." << std::endl;
        } else if (all_edges.at(i)->status == DISCOVERY) {
            std::cout << all_edges.at(i)->end1->name << " and "
                      << all_edges.at(i)->end2->name << ": "
                      << "DISCOVERY." << std::endl;
        } else if (all_edges.at(i)->status == BACK) {
            std::cout << all_edges.at(i)->end1->name << " and "
                      << all_edges.at(i)->end2->name << ": "
                      << "BACK." << std::endl;
        } else {
            std::cout << all_edges.at(i)->end1->name << " and "
                      << all_edges.at(i)->end2->name << ": "
                      << "CROSS." << std::endl;
        }
    }
}

// Resets all vertices to unvisited, all edges to undiscovered
void Graph::refresh_graph()
{
    for (vmap::iterator itr = work.begin(); itr != work.end(); ++itr)
        itr->second->visited = false;

    for (int i = 0; i < all_edges.size(); ++i)
        all_edges.at(i)->status = UNDISCOVERED;

    distance_traveled = 0;
}

void Graph::DFS(vertex *&start)
{
    start->visited = true;
    for (int i = 0; i < start->adjacent.size(); ++i) {
        if (start->adjacent.at(i)->status == UNDISCOVERED) {
            vertex *opposite = opposite_vertex(start, start->adjacent.at(i));
            if (!opposite->visited) {
                start->adjacent.at(i)->status = DISCOVERY;
                std::cout << start->name << " to " << opposite->name << std::endl;
                distance_traveled += start->adjacent.at(i)->distance;
                DFS(opposite);
            } else {
                start->adjacent.at(i)->status = BACK;
            }
        }
    }
}

void Graph::BFS(vertex *&start)
{
    start->visited = true;
    std::queue<vertex*> my_queue;
    my_queue.push(start);

    while (!my_queue.empty()) {
        start = my_queue.front();
        std::cout << start->name << std::endl;
        my_queue.pop();

        for (int i = 0; i < start->adjacent.size(); ++i) {
            if (start->adjacent.at(i)->status == UNDISCOVERED) {
                vertex *opposite = opposite_vertex(start, start->adjacent.at(i));
                if (!opposite->visited) {
                    start->adjacent.at(i)->status = DISCOVERY;
                    opposite->visited = true;
                    distance_traveled += start->adjacent.at(i)->distance;
                    my_queue.push(opposite);
                } else {
                    start->adjacent.at(i)->status = CROSS;
                }
            }
        }
    }
}
